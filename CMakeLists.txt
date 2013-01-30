cmake_minimum_required(VERSION 2.6)

project(zombieland)
set (CMAKE_CXX_FLAGS "-Wall --std=c++11")

# Extend the CMake module path to find the FindSFML.cmake file in {project root}/cmake/Modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

add_custom_target(clean-cmake-files
   COMMAND ${CMAKE_COMMAND} -P clean-all.cmake
)

add_custom_target(clean-all
   COMMAND ${CMAKE_BUILD_TOOL} clean
   COMMAND ${CMAKE_COMMAND} -P clean-all.cmake
)

set(BASEPATH "${CMAKE_SOURCE_DIR}")
include_directories("${BASEPATH}")

add_subdirectory(zombieland)
add_subdirectory(zombieland-sfml)