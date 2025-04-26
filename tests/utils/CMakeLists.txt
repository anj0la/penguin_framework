#----------------------------------------------------------------------------------------------------------------------
# Testing Setup
#----------------------------------------------------------------------------------------------------------------------

include(TestHelpers)

add_executable(run_util_tests
	  "test_string.cpp"
)

target_link_libraries(
	  run_util_tests
	  penguin::penguin
	  GTest::gtest_main
)

copy_dll_files(run_util_tests)
gtest_discover_tests(run_util_tests)
