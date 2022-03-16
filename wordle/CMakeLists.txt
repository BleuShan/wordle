library_project(
  wordle
  LINK_LIBRARIES
  simdjson
)


add_subdirectory(src)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
