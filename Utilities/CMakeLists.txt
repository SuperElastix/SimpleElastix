configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/pypi.sh.in
  ${CMAKE_CURRENT_BINARY_DIR}/pypi.sh
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/valgrind.sh.in
  ${CMAKE_CURRENT_BINARY_DIR}/valgrind.sh
)
