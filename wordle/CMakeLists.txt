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
  SUBDIRECTORY src
  PRIVATE
  dictionary.cc
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
  filesystem.h
  json.h
  mixins.h
  string.h
)

add_sources(
  SUBDIRECTORY include/wordle/foundation/filesystem
  PUBLIC
  FileManager.h
)

add_sources(
  SUBDIRECTORY src/foundation/filesystem
  PRIVATE
  FileManager.cc
)

add_sources(
  SUBDIRECTORY include/wordle/foundation/json
  PUBLIC
  JsonSerializer.h
)

add_sources(
  SUBDIRECTORY src/foundation/json
  PRIVATE
  JsonSerializer.cc
)

add_sources(
  SUBDIRECTORY include/wordle/foundation/mixins
  PUBLIC
  Shareable.h
  Singleton.h
  concepts.h
)


add_test_suite(dictionary)
