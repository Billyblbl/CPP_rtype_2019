project(R-Type)
cmake_minimum_required(VERSION 3.12)
add_definitions("-fPIC")

set (CMAKE_CXX_STANDARD 17)

set (ENGINE_LIB "r-engine")
set (CLIENT_EXEC "r-type_client")
set (SERVER_EXEC "r-type_server")

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

function(make_rengine_package package_name package_dir)
	get_include(${package_name}_INCLUDE ${package_dir})
	get_src(${package_name}_SOURCE ${package_dir})
	include_directories(${${package_name}_INCLUDE})
	add_library(${package_name} SHARED ${${package_name}_SOURCE})
endfunction(make_rengine_package)

# R-Engine

message(STATUS "Configuring R-Engine Build")
set(RENGINE_DIR "ECS" "instance")
get_include(RENGINE_INCLUDE ${RENGINE_DIR})
get_src(RENGINE_SOURCE ${RENGINE_DIR})
include_directories(${RENGINE_INCLUDE})
add_library(${ENGINE_LIB} SHARED ${RENGINE_SOURCE})

# Client

message(STATUS "Configuring R-Type Client Build")
file(GLOB CLIENT_SOURCE "client/src/*.cpp")#tmp
include_directories(client/include)
add_executable(${CLIENT_EXEC} ${CLIENT_SOURCE})
target_link_libraries(${CLIENT_EXEC} ${CONAN_LIBS} ${ENGINE_LIB})# adding sfml + r_engine

# Server

message(STATUS "Configuring R-Type Server Build")
file(GLOB SERVER_SOURCE "client/src/*.cpp")#tmp
include_directories(server/include)
add_executable(${SERVER_EXEC} ${SERVER_SOURCE})
target_link_libraries(${SERVER_EXEC} ${CONAN_LIBS} ${ENGINE_LIB})# adding r_engine
