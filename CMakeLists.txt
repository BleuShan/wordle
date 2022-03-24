cmake_minimum_required(VERSION 3.22)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include(Workspace)

project(${WORKSPACE_NAME})

if(BUILD_TESTING)
  declare_vpckg_packages(gtest)
  enable_testing()
  include(Dart)
  include(GoogleTest)
endif()

declare_vpckg_packages(
  simdjson
  folly
)


install_declared_vpckg_packages()

include(GNUInstallDirs)

add_subdirectory(wordle)
