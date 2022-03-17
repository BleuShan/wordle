library_project(
  wordle
  LINK_LIBRARIES
  simdjson::simdjson
)

add_sources(
  SUBDIRECTORY src
  PRIVATE
  dictionary.cc
)

add_test_suite(dictionary)
