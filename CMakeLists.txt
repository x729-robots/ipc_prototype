cmake_minimum_required(VERSION 3.5)
project(lesson_individual)

add_executable(canapp canapp.cpp)
target_include_directories(
    canapp PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

set_target_properties(canapp PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#target_compile_options(
#    canapp PRIVATE
#    -Wall -Wextra -pedantic -Werror
#)