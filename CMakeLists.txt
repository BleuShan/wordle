cmake_minimum_required(VERSION 3.22)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include(Workspace)

project(${WORKSPACE_NAME})

if(BUILD_TESTING)
  enable_testing()
  include(Dart)
  include(GoogleTest)
endif()

find_installed_vcpkg_packages()

include(GNUInstallDirs)

add_subdirectory(wordle)
