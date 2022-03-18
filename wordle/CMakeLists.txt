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
  wordle.h
  dictionary.h
)

add_sources(
  SUBDIRECTORY include/wordle/prelude
  PUBLIC
  exports_symbols.h
  memory.h
  string.h
)

add_sources(
  SUBDIRECTORY include/wordle/prelude/memory
  PUBLIC
  ShareableObject.h
)

add_sources(
  SUBDIRECTORY src
  PRIVATE
  dictionary.cc
)

add_test_suite(dictionary)
