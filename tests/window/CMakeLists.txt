#----------------------------------------------------------------------------------------------------------------------
# Testing Setup
#----------------------------------------------------------------------------------------------------------------------

include(TestHelpers)

add_executable(run_window_tests
	  "test_window.cpp"
	  "test_windowflags.cpp"
)

target_link_libraries(
	  run_window_tests
	  penguin::penguin
	  SDL3::SDL3
	  GTest::gtest_main
)

copy_dll_files(run_window_tests)
gtest_discover_tests(run_window_tests)
