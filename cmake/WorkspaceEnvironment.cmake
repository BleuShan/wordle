# Global environment setup
include(CMakeDependentOption)
include(WorkspaceHelpers)

# Globals
set(WORKSPACE_PACKAGE_NAME Wordle)
string(TOLOWER ${WORKSPACE_PACKAGE_NAME}_workspace WORKSPACE_NAME)
set(WORKSPACE_PACKAGE_VERSION "0.1.0" CACHE STRING "Current project version")
