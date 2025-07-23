#----------------------------------------------------------------------------------------------------------------------
# Testing Setup
#----------------------------------------------------------------------------------------------------------------------

include(TestHelpers)

add_executable(run_math_tests
	  "test_colour.cpp" "test_vector2.cpp"
	  "test_vector2i.cpp" "test_rect2.cpp" 
	  "test_rect2i.cpp" "test_circle2.cpp"
)

target_link_libraries(run_math_tests
	PRIVATE
		penguin::penguin
		GTest::gtest_main
)

gtest_discover_tests(run_math_tests
    WORKING_DIRECTORY ${TEST_BINARY_DIR}
)

add_dependencies(run_math_tests copy_penguin_dll)
