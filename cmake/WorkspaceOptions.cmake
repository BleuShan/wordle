if(CMAKE_PROJECT_NAME STREQUAL ${WORKSPACE_NAME})
  option(BUILD_TESTING "Build the testing tree." ON)
  option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)" ON)
endif()
