
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

FetchContent_Declare(
  vcpkg
  GIT_REPOSITORY git@github.com:microsoft/vcpkg.git
)
