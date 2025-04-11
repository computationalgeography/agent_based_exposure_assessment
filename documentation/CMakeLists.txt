configure_file(conf.py.in
  conf.py
)

set(SOURCES
  index.rst
  concepts.md
  reference.rst
)

add_custom_target(init_doc_sources ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/index.rst
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/index.rst
  DEPENDS
    ${SOURCES}
    ${CMAKE_CURRENT_BINARY_DIR}/conf.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy_directory _static ${CMAKE_CURRENT_BINARY_DIR}/_static
  COMMAND ${CMAKE_COMMAND} -E copy_directory _templates ${CMAKE_CURRENT_BINARY_DIR}/_templates
  COMMAND ${CMAKE_COMMAND} -E copy ${SOURCES} ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(documentation
  DEPENDS init_python_sources
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/_build/html/index.html
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/_build/html/index.html
  DEPENDS init_doc_sources
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  VERBATIM
  COMMAND ${CMAKE_COMMAND} -E remove_directory _build
  COMMAND ${CMAKE_COMMAND} -E make_directory _build
  COMMAND sphinx-build -q -W -b html ${CMAKE_CURRENT_BINARY_DIR} _build
)
