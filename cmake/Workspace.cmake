include_guard()

# Global environment setup
include(CMakeDependentOption)
include(WorkspaceUtilities)
include(VcpkgHelpers)
include(WorkspaceHelpers)

# Globals
set(WORKSPACE_PACKAGE_NAME Wordle)
string(TOLOWER ${WORKSPACE_PACKAGE_NAME}_workspace WORKSPACE_NAME)
set(WORKSPACE_PACKAGE_VERSION "0.1.0" CACHE STRING "Current project version")
set(WORKSPACE_TEST_SUFFIX_REGEX "([-_]t|T)ests?$")

setup_vcpkg()

if(${${WORKSPACE_NAME}_IS_TOP_LEVEL})
  option(BUILD_TESTING "Build the testing tree." ON)
  option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)" ON)
endif()
