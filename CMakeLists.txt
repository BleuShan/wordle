cmake_minimum_required(VERSION 3.22)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include(WorkspaceEnvironment)

project(${WORKSPACE_NAME})

if(BUILD_TESTS)
  enable_testing()
endif()

include(GNUInstallDirs)

add_subdirectory(wordle)
