project(R-Type)
cmake_minimum_required(VERSION 3.12)
add_definitions("-fPIC")

set (CMAKE_CXX_STANDARD 17)

set (ENGINE_LIB "r-engine")
set (CLIENT_EXEC "r-type_client")
set (SERVER_EXEC "r-type_server")

if (UNIX)
	set(PLUGINLOADLIB dl)
elseif(WIN32)
	set(PLUGINLOADLIB "")
endif(UNIX)

# find_library()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
include_directories(${CMAKE_INCLUDE_PATH} include)

function(get_include LISTNAME)
	set(LOCALDIR ${LISTNAME}_get_src_dir_local)
	set("${LOCALDIR}" "")
	foreach(dir ${ARGN})
		list(APPEND "${LOCALDIR}" ${dir}/include)
	endforeach(dir)
	set(${LISTNAME} "${${LOCALDIR}}" PARENT_SCOPE)
endfunction(get_include)

function(get_src LISTNAME)
	# build list of globbing expression
	set(LOCALDIR ${LISTNAME}_get_src_dir_local)
	set("${LOCALDIR}" "")
	foreach(dir ${ARGN})
		list(APPEND "${LOCALDIR}" "./${dir}/src/*.cpp")
	endforeach(dir)

	# build list of source files
	set(LOCALSRCGL ${LISTNAME}_get_src_globbed_local)
	set("${LOCALSRCGL}" "")
	set(LOCALSRC ${LISTNAME}_get_src_local)
	set("${LOCALSRC}" "")
	foreach(src ${${LOCALDIR}})
		# get list of source for a globbing expression
		file(GLOB "${LOCALSRCGL}" "${src}")
		# add the globbed source files to the list
		list(APPEND ${LOCALSRC} "${${LOCALSRCGL}}")
	endforeach(src)
	# return the completed list of source files in ${LISTNAME}
	set(${LISTNAME} "${${LOCALSRC}}" PARENT_SCOPE)
endfunction(get_src)

function(make_rengine_plugin package_name package_dir)
	get_include(${package_name}_INCLUDE ${package_dir})
	get_src(${package_name}_SOURCE ${package_dir})
	include_directories(${${package_name}_INCLUDE})
	add_library(${package_name} SHARED ${${package_name}_SOURCE})
endfunction(make_rengine_plugin)

# check if Doxygen is installed
find_package(Doxygen)

# indicate the documentation build as an option
option(BUILD_DOC "Build documentation" ${DOXYGEN_FOUND})

if (${BUILD_DOC} AND ${DOXYGEN_FOUND})
	# set input and output files
	set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
	set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

	# request to configure the file
	configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
	message(STATUS "Doxygen build started")

	add_custom_target(docs
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen"
		VERBATIM
	)
	message(STATUS "Doxygen build complete")
elseif(${BUILD_DOC})
	message("Doxygen need to be installed to generate the doxygen documentation")
endif (${BUILD_DOC} AND ${DOXYGEN_FOUND})

# R-Engine

message(STATUS "Configuring R-Engine Build")
set(RENGINE_DIR "ECS" "instance" "JSON" "loader" "AssetCache")
get_include(RENGINE_INCLUDE ${RENGINE_DIR})
get_src(RENGINE_SOURCE ${RENGINE_DIR})
include_directories(${RENGINE_INCLUDE})
add_library(${ENGINE_LIB} SHARED ${RENGINE_SOURCE})
target_link_libraries(${ENGINE_LIB} ${PLUGINLOADLIB})# adding sfml + r_engine

# Client

message(STATUS "Configuring R-Type Client Build")
file(GLOB CLIENT_SOURCE "client/src/*.cpp")#tmp
include_directories(client/include)
add_executable(${CLIENT_EXEC} ${CLIENT_SOURCE})
target_link_libraries(${CLIENT_EXEC} ${CONAN_LIBS} ${ENGINE_LIB})# adding sfml + r_engine

# Server

message(STATUS "Configuring R-Type Server Build")
file(GLOB SERVER_SOURCE "server/src/*.cpp")#tmp
include_directories(server/include)
add_executable(${SERVER_EXEC} ${SERVER_SOURCE})
target_link_libraries(${SERVER_EXEC} ${CONAN_LIBS} ${ENGINE_LIB})# adding r_engine
