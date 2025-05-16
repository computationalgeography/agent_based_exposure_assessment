nanobind_add_module(routing
  LTO
  routing.cc
  extension.cc
)

target_include_directories(routing
  PRIVATE
    ${CMAKE_BINARY_DIR}/_deps/osrm-backend-src/include/
    ${CMAKE_BINARY_DIR}/_deps/osrm-backend-src/third_party/flatbuffers/include/
)

install(
  TARGETS routing
  DESTINATION ${ABEM_INSTALL_DIR}/
)


# Dummy target to attach post-build commands.
add_custom_target(routing_dummy ALL)

add_dependencies(routing_dummy routing)

add_custom_command(
  TARGET
    routing_dummy
  POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/abem
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:routing> ${CMAKE_BINARY_DIR}/bin/abem/
)
