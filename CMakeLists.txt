cmake_minimum_required(VERSION 3.5)
project(lesson_individual)

add_executable(canapp canapp.cpp)
target_include_directories(
    canapp PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    #"${CMAKE_CURRENT_SOURCE_DIR}/canopenmaster/include"
)

set_target_properties(canapp PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

#add_subdirectory(${CMAKE_SOURCE_DIR}/canopenmaster)
#target_include_directories(	ccanopenmaster PRIVATE ${CMAKE_SOURCE_DIR}/canopenmaster/include)
##set(ccanopenmaster "${CMAKE_CURRENT_SOURCE_DIR}/libccanopenmaster.so")
#add_library(ccanopenmaster SHARED)
add_library(ccanopenmaster SHARED IMPORTED)
set_target_properties(ccanopenmaster PROPERTIES
  IMPORTED_IMPLIB "libccanopenmaster.so"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/canopenmaster/include")
#target_include_directories(	ccanopenmaster PRIVATE ${CMAKE_SOURCE_DIR}/canopenmaster/include)
#target_link_libraries(	canapp PUBLIC ccanopenmaster)
###target_link_libraries(	canapp PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libccanopenmaster.so")
#set(CMAKE_INSTALL_RPATH ".")
#SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
SET(CMAKE_EXE_LINKER_FLAGS 
          "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,.")

target_link_libraries(	canapp PUBLIC ccanopenmaster)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

target_compile_options(
    canapp PRIVATE
    -Wall -Wextra -pedantic -Werror
)