set(SOURCES
  calc_model.py
  csv_export.py
  factors.py
  group.py
  __init__.py
  profiles.py
  spatial_context.py
  weekly_exposure.py
  ws_base.py
  ws_od_matrix.py
)

set(ACTIVITY_SOURCES
  schedules/act.py
  schedules/config.py
  schedules/__init__.py
  schedules/schedules.py
  schedules/timer.py
)

add_custom_target(init_python_sources ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/__init__.py
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/schedules/__init__.py
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/__init__.py
  DEPENDS ${SOURCES}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "Copying Python sources..."
  COMMAND ${CMAKE_COMMAND} -E make_directory  ${CMAKE_BINARY_DIR}/bin/abem/
  COMMAND ${CMAKE_COMMAND} -E copy ${SOURCES} ${CMAKE_BINARY_DIR}/bin/abem/
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/schedules/__init__.py
  DEPENDS ${FIELD_SOURCES}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "Copying Python sources schedules..."
  COMMAND ${CMAKE_COMMAND} -E copy_directory schedules ${CMAKE_BINARY_DIR}/bin/abem/schedules #${CMAKE_CURRENT_BINARY_DIR}/schedules
)

install(
  FILES
    ${SOURCES}
  DESTINATION
    ${ABEM_INSTALL_DIR}/
)

install(
  FILES
    ${ACTIVITY_SOURCES}
  DESTINATION
    ${ABEM_INSTALL_DIR}/schedules
)
