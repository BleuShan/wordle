add_subdirectory(simdjson)
workspace_helpers_set_target_output_directory_properties(simdjson)

if(BUILD_TESTING)
  add_subdirectory(googletest)
endif()
