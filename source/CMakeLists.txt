add_subdirectory(python)
add_subdirectory(tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


# include(FetchContent)


find_package(nanobind CONFIG REQUIRED)

# set(BOOST_COMPONENTS program_options) #date_time chrono filesystem iostreams program_options regex system thread unit_test_framework)

# find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})

add_subdirectory(cpp)