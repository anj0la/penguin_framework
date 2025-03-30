# Backwards comptability for CMake 3.15 to 3.31 (doesn't support CMake 4.0 or higher).
cmake_minimum_required(VERSION 3.15...3.31)

###### TESTING SETUP ######

add_executable(
  run_math_tests
  test_colour.cpp
  test_vector2.cpp
  test_vector2i.cpp
  ${CMAKE_SOURCE_DIR}/src/math/vector2.cpp
  ${CMAKE_SOURCE_DIR}/src/math/vector2i.cpp
 "test_rect2.cpp" "test_rect2i.cpp" "test_circle2.cpp")
target_link_libraries(
  run_math_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_math_tests)