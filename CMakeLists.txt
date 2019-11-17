project(R-Type)
cmake_minimum_required(VERSION 3.12)
add_definitions("-fPIC")

set (CMAKE_CXX_STANDARD 17)

set (CLIENT_EXEC "r-type_client")
set (SERVER_EXEC "r-type_server")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
include_directories(${CMAKE_INCLUDE_PATH} include)

function(get_include LISTNAME)
	foreach(dir ${ARGN})
		list(APPEND ${LISTNAME} dir/include)
	endforeach(dir)
endfunction(get_include)

function(get_src LISTNAME)
	foreach(dir ${ARGN})
		list(APPEND ${LISTNAME} "dir/src/*.cpp")
	endforeach(dir)
endfunction(get_src)

function(make_rengine_package package_name package_dir)
	get_include(${package_name}_INCLUDE package_dir)
	get_src(${package_name}_SOURCE package_dir)
	include_directories(${${package_name}_INCLUDE})
	add_library(${package_name} SHARED ${${package_name}_SOURCE})
endfunction(make_rengine_package)

# R-Engine

set(RENGINE_DIR ECS instance)
get_include(RENGINE_INCLUDE ${RENGINE_DIR})
get_src(RENGINE_SOURCE ${RENGINE_DIR})
include_directories(${RENGINE_INCLUDE})
add_library(r_engine STATIC ${RENGINE_SOURCE})

# Client

file(GLOB CLIENT_SOURCE "client/src/*.cpp")#tmp
include_directories(client/include)
add_executable(${CLIENT_EXEC} ${CLIENT_SOURCE})
target_link_libraries(${CLIENT_EXEC} ${CONAN_LIBS} r_engine)# adding sfml + r_engine

# Server

file(GLOB SERVER_SOURCE "client/src/*.cpp")#tmp
include_directories(server/include)
add_executable(${SERVER_EXEC} ${SERVER_SOURCE})
target_link_libraries(${SERVER_EXEC} ${CONAN_LIBS} r_engine)# adding r_engine
