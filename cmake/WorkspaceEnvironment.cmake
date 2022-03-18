
include_guard()

# Global environment setup
include(CMakeDependentOption)
include(FetchContent)

# Globals
set(WORKSPACE_PACKAGE_NAME Wordle)
string(TOLOWER ${WORKSPACE_PACKAGE_NAME}_workspace WORKSPACE_NAME)
set(WORKSPACE_PACKAGE_VERSION "0.1.0" CACHE STRING "Current project version")
set(WORKSPACE_TEST_SUFFIX_REGEX "([-_]t|T)ests?$")

set(VCPKG_ROOT
  ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg
  CACHE STRING "Vcpkg root directory")

set(CMAKE_TOOLCHAIN_FILE
  ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")


set(VCPKG_EXECUTABLE
  ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg
  CACHE STRING "Vcpkg executable")


mark_as_advanced(FORCE CMAKE_TOOLCHAIN_FILE VCPKG_EXECUTABLE)

if(VCPKG_ROOT STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
  if(NOT EXISTS ${CMAKE_TOOLCHAIN_FILE})
    execute_process(
      COMMAND git
      submodule
      update
      "--init"
      "--recursive"
    )
  endif()
  if(NOT EXISTS ${VCPKG_EXECUTABLE})
    if(WIN32)
      execute_process(
        COMMAND ${VCPKG_ROOT}/bootstrap-vcpkg.bat
      )
    else()
      execute_process(
        COMMAND ${VCPKG_ROOT}/bootstrap-vcpkg.sh
      )
    endif()
  endif()
endif()
