include_guard()

include(WorkspaceEnvironment)

if(${${WORKSPACE_NAME}_IS_TOP_LEVEL})
  option(BUILD_TESTING "Build the testing tree." ON)
  option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)" ON)

  workspace_normalize_vcpkg_target_triplet()
endif()
