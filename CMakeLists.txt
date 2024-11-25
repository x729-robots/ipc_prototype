cmake_minimum_required(VERSION 3.5)
project(lesson_individual)

add_executable(canapp canapp.cpp)
target_include_directories(
    canapp PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

set_target_properties(canapp PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/canopenmaster")
add_library(ccanopenmaster SHARED "${CMAKE_CURRENT_SOURCE_DIR}/canopenmaster")
set_target_properties(ccanopenmaster PROPERTIES LINKER_LANGUAGE CXX)
#include("${CMAKE_CURRENT_SOURCE_DIR}/canopenmaster/CMakeLists.txt")
#target_link_libraries(canapp PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/build/canopenmaster/libccanopenmaster.so")
target_link_libraries(canapp PUBLIC ccanopenmaster)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#target_compile_options(
#    canapp PRIVATE
#    -Wall -Wextra -pedantic -Werror
#)