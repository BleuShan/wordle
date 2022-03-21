library_project(
  wordle
)

target_link_libraries(${PROJECT_TARGET}
  simdjson::simdjson
)

add_subdirectory(include)
add_subdirectory(src)
