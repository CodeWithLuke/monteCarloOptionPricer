cmake_minimum_required(VERSION 3.18)
project(monte_carlo_option_pricer)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

add_subdirectory(build/_deps/pybind11-src)

add_library(
  gaussian_rng
  gaussian_rng.cc
)

pybind11_add_module(monte_carlo_option_pricer main.cpp)
target_include_directories(monte_carlo_option_pricer PRIVATE build/_deps/date-src/include)

enable_testing()

add_executable(
  unit_test
  unit_test.cc
)

target_link_libraries(
  unit_test
  date
)

target_link_libraries(
  unit_test
  gaussian_rng
)

target_link_libraries(
  unit_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_test)