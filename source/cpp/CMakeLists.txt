cmake_minimum_required(VERSION 3.20)

project(routing CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH  OFF)
set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)
set(CMAKE_INSTALL_RPATH "$ORIGIN")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(LibOSRM REQUIRED)

find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()


execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE NB_DIR)
list(APPEND CMAKE_PREFIX_PATH "${NB_DIR}")
find_package(nanobind CONFIG REQUIRED)


nanobind_add_module(routing
  LTO
  routing.cc
  extension.cc
)

set(BOOST_COMPONENTS date_time chrono filesystem iostreams program_options regex system thread unit_test_framework)

find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})

target_include_directories(nanrouting PUBLIC ${LibOSRM_INCLUDE_DIR} ${LibOSRM_INCLUDE_DIR}/osrm ${LibOSRM_INCLUDE_DIR}/../../osrm-backend-5.27.0/include)

target_link_libraries(nanrouting PRIVATE ${LibOSRM_LIBRARIES} ${LibOSRM_DEPENDENT_LIBRARIES} Boost::filesystem)


install(
  TARGETS routing
  DESTINATION python/mobiair/
)
