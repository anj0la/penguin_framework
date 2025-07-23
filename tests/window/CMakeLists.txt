#----------------------------------------------------------------------------------------------------------------------
# Testing Setup
#----------------------------------------------------------------------------------------------------------------------

add_executable(run_window_tests
	  "test_window.cpp"
	  "test_windowflags.cpp"
)

target_link_libraries(run_window_tests
	PRIVATE
		penguin::penguin
		GTest::gtest_main
)

gtest_discover_tests(run_window_tests
    WORKING_DIRECTORY ${TEST_BINARY_DIR}
)

add_dependencies(run_window_tests copy_penguin_dll)
