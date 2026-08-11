cmake_minimum_required(VERSION 3.14)
project(oven_system_tests CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests
    test_filter.cpp
    test_hysteresis.cpp
    test_frameparser.cpp
    test_oven_system.cpp
)
target_link_libraries(tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
