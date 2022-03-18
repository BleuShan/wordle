cmake_minimum_required(VERSION 3.22)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include(WorkspaceHelpers)

project(${WORKSPACE_NAME})

include(WorkspaceOptions)

if(BUILD_TESTING)
  add_packages(gtest)
  enable_testing()
  include(Dart)
  include(GoogleTest)
endif()

add_packages(simdjson)

include(GNUInstallDirs)

add_subdirectory(wordle)
