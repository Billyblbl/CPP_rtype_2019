project(Babel)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC")

set (CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${CMAKE_INCLUDE_PATH} ECS/include include)

#set source files
file(GLOB SOURCES "src/*.cpp" "ECS/src/*.cpp")

add_executable(rtype ${SOURCES})
target_link_libraries(rtype ${CONAN_LIBS})
