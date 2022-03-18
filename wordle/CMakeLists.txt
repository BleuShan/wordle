library_project(
  wordle
)
target_link_libraries(${PROJECT_TARGET} simdjson)

add_sources(
  SUBDIRECTORY src
  PRIVATE
  dictionary.cc
)

add_test_suite(dictionary)
