library_project(
  wordle
  LINK_LIBRARIES
  PUBLIC
  simdjson::simdjson
  Folly::folly 
  Folly::folly_deps
)

add_subdirectory(include)
add_subdirectory(src)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()