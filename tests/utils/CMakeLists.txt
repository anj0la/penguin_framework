# Backwards comptability for CMake 3.15 to 3.31 (doesn't support CMake 4.0 or higher).
cmake_minimum_required(VERSION 3.15...3.31)

###### TESTING SETUP ######

add_executable(
  run_util_tests
  "${CMAKE_SOURCE_DIR}/src/utils/string.cpp"
  test_string.cpp
  )
target_link_libraries(
  run_util_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_util_tests)