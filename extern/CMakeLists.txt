add_subdirectory(simdjson)
workspace_helpers_set_target_properties(simdjson)

if(BUILD_TESTING)
  add_subdirectory(googletest)
endif()
