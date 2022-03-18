library_project(
  wordle
)

target_link_libraries(${PROJECT_TARGET}
  simdjson::simdjson
)

add_sources(
  SUBDIRECTORY include/wordle
  PUBLIC
  prelude.h
  foundation.h
  wordle.h
  dictionary.h
)

add_sources(
  SUBDIRECTORY include/wordle/prelude
  PUBLIC
  compile_features.h
  exports_symbols.h
)

add_sources(
  SUBDIRECTORY include/wordle/foundation
  PUBLIC
  ShareableObject.h
  string.h
)

add_sources(
  SUBDIRECTORY src
  PRIVATE
  dictionary.cc
)

add_test_suite(dictionary)
