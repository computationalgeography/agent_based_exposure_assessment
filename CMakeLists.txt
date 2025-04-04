cmake_minimum_required(VERSION 3.26)

project(agent_based_exposure_assessment
  VERSION 0.0.1
  DESCRIPTION "Agent-based exposure assessment"
  HOMEPAGE_URL "https://www.computationalgeography.org/"
)

set(DEV_CURRENT_YEAR "2025")

set(${PROJECT_NAME}_ORGANISATION_NAME "Computational Geography group, Dept. of Physical Geography, Utrecht University")
set(${PROJECT_NAME}_COPYRIGHT
     "2024, ${DEV_CURRENT_YEAR}, ${${PROJECT_NAME}_ORGANISATION_NAME}")

find_package(Python 3.8
  REQUIRED COMPONENTS Interpreter Development.Module
)

set(CMAKE_MODULE_PATH
  $ENV{CMAKE_MODULE_PATH}
  ${CMAKE_SOURCE_DIR}/environment/cmake
)

include(CPM)

CPMAddPackage(
  GITHUB_REPOSITORY Project-OSRM/osrm-backend
  GIT_TAG 646384a9480323344bc5984f236879d2db3da87e
  OPTIONS "BUILD_SHARED_LIBS ON" "CMAKE_BUILD_TYPE Release"
)

enable_testing()

add_subdirectory(source)
add_subdirectory(documentation)

message(STATUS "-------------------------------------------------")
message(STATUS "Configuration summary:")
message(STATUS "  Version:                " ${${PROJECT_NAME}_VERSION})
message(STATUS "  Build configuration:")
message(STATUS "    Python interpreter:   " ${Python_EXECUTABLE})
message(STATUS "    Python version:       " ${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}.${Python_VERSION_PATCH})
message(STATUS "    Site-packages:        " ${Python_SITELIB})
message(STATUS "-------------------------------------------------")
