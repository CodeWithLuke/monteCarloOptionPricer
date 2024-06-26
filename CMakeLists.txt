cmake_minimum_required(VERSION 3.18)
project(monte_carlo_option_pricer)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("-pthread")
add_compile_options("-F/Library/Frameworks -framework Python")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_Declare(
  pybind11
  URL https://github.com/pybind/pybind11/archive/refs/tags/v2.12.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_Declare(
  date
  URL https://github.com/HowardHinnant/date/archive/refs/tags/v3.0.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(pybind11)
FetchContent_MakeAvailable(date)

find_package(pybind11 REQUIRED)

add_library(
  gaussian_rng
  src/gaussian_rng.cc
)

add_library(
  asset_random_walk SHARED src/asset_random_walk.cc
)

target_include_directories(asset_random_walk PRIVATE ${CMAKE_BINARY_DIR}/_deps/date-src/include)

target_link_libraries(asset_random_walk gaussian_rng)

pybind11_add_module(monte_carlo_option_pricer src/main.cpp)

target_link_libraries(monte_carlo_option_pricer PRIVATE asset_random_walk)
set_target_properties(monte_carlo_option_pricer PROPERTIES PREFIX "")

target_include_directories(monte_carlo_option_pricer PRIVATE ${CMAKE_BINARY_DIR}/_deps/date-src/include)

# if(APPLE)
#   set_target_properties(${MODULE} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
# endif(APPLE)

enable_testing()

add_executable(
  unit_test
  src/unit_test.cc
)

target_link_libraries(
  unit_test GTest::gtest_main gaussian_rng date asset_random_walk
)

include(GoogleTest)
gtest_discover_tests(unit_test)