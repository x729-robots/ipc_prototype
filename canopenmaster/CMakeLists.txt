cmake_minimum_required(VERSION 3.5)
project(ccanopenmaster)

add_library(ccanopenmaster SHARED ccanopenmaster.cpp)
target_include_directories(
    ccanopenmaster PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

#TODO made version processing
set_target_properties(ccanopenmaster PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(ccanopenmaster PROPERTIES PUBLIC_HEADER include/ccanopenmaster.h)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#target_compile_options(
#    canapp PRIVATE
#    -Wall -Wextra -pedantic -Werror
#)