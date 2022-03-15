cmake_path(GET CMAKE_CURRENT_LIST_DIR STEM SOLVER_EXECUTABLE_NAME)

add_executable(${SOLVER_EXECUTABLE_NAME})

target_sources(
  ${SOLVER_EXECUTABLE_NAME}
  PRIVATE
  main.cc
)

target_link_libraries(
  ${SOLVER_EXECUTABLE_NAME}
  ${PROJECT_NAME}
)
