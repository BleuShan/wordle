cmake_minimum_required(VERSION 3.22)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
include(globals)
include(CXXStandard)

project(wordle
        VERSION 0.1.0
        LANGUAGES CXX C)

add_subdirectory(extern)
add_subdirectory(${PROJECT_NAME})
add_subdirectory(${PROJECT_NAME}_solver)
