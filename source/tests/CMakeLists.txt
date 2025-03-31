set(SOURCES
  unit_tests.py
  test_activities.py
)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/config.py "inmem_schedules = True")

add_custom_target(init_test_sources ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/unit_tests.py
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/unit_tests.py
  DEPENDS ${SOURCES}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "Copying test sources..."
  COMMAND ${CMAKE_COMMAND} -E copy ${SOURCES} ${CMAKE_CURRENT_BINARY_DIR}
)

add_test(
  NAME
    unit_tests
  COMMAND
    ${Python_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/unit_tests.py
)

set_tests_properties(unit_tests PROPERTIES
  DEPENDS
    init_test_sources
  DEPENDS
    init_python_sources
)

# add path of project's unit test related files to PYTHONPATH
# required to execute this unit test via ctest properly
if(WIN32)
  message(FATAL_ERROR)
else()
  set(ENV_PATH $ENV{PYTHONPATH})
  set_tests_properties(unit_tests PROPERTIES
    ENVIRONMENT "PYTHONPATH=${CMAKE_BINARY_DIR}/source:$ENV{PYTHONPATH}"
  )
endif()