
include_guard()

# Global environment setup
include(CMakeDependentOption)
include(FetchContent)
include(WorkspaceHelpers)

# Globals
set(WORKSPACE_PACKAGE_NAME Wordle)
string(TOLOWER ${WORKSPACE_PACKAGE_NAME}_workspace WORKSPACE_NAME)
set(WORKSPACE_PACKAGE_VERSION "0.1.0" CACHE STRING "Current project version")
set(WORKSPACE_TEST_SUFFIX_REGEX "([-_]t|T)ests?$")


if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED VCPKG_ROOT)
  set(VCPKG_ROOT
    $ENV{VCPKG_ROOT}
    CACHE STRING "Vcpkg root directory")
elseif(NOT DEFINED VCPKG_ROOT)
  set(VCPKG_ROOT
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg
    CACHE STRING "Vcpkg root directory")
endif()

if(VCPKG_ROOT STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
  set(LOCAL_VCPKG_ROOT ON)
endif()


set(VCPKG_EXECUTABLE
  ${VCPKG_ROOT}/vcpkg
  CACHE STRING "Vcpkg executable")

set(VCPKG_BOOTSTRAP_SCRIPT
  ${VCPKG_ROOT}/bootstrap-vcpkg.sh
  CACHE STRING "Vcpkg bootstrap script"
)

if(CMAKE_HOST_WIN32)
  set(VCPKG_EXECUTABLE
    ${VCPKG_EXECUTABLE}.exe
    CACHE STRING "Vcpkg executable")

  set(VCPKG_BOOTSTRAP_SCRIPT
    ${VCPKG_ROOT}/bootstrap-vcpkg.bat
    CACHE STRING "Vcpkg bootstrap script"
  )
endif()

if(DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET)
  set(VCPKG_TARGET_TRIPLET $ENV{VCPKG_DEFAULT_TRIPLET} CACHE STRING "")
endif()

set(CMAKE_TOOLCHAIN_FILE
  ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

workspace_normalize_vcpkg_target_triplet()

set(VCPKG_COMMAND_ARGS 
    "--x-json;--triplet=${VCPKG_TARGET_TRIPLET}"
    CACHE
    STRING
    "Common vcpkg command arguments"
    FORCE
)

mark_as_advanced(FORCE
  CMAKE_TOOLCHAIN_FILE
  VCPKG_EXECUTABLE
  VCPKG_BOOTSTRAP_SCRIPT
  VCPKG_COMMAND_ARGS
)

if(LOCAL_VCPKG_ROOT)
   execute_process(
        COMMAND git
        submodule
        update
        "--init"
        "--recursive"
      )
endif()

if(NOT EXISTS ${VCPKG_EXECUTABLE})
  execute_process(COMMAND ${VCPKG_BOOTSTRAP_SCRIPT})
endif()
