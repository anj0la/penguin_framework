#----------------------------------------------------------------------------------------------------------------------
# Testing Setup
#----------------------------------------------------------------------------------------------------------------------

include(TestHelpers)

add_executable(run_penguin_renderer_tests
		"test_penguin_renderer.cpp"
)

target_link_libraries(
	  run_penguin_renderer_tests
	  penguin::penguin
	  SDL3::SDL3
	  GTest::gtest_main
)

copy_dll_files(run_penguin_renderer_tests)
gtest_discover_tests(run_penguin_renderer_tests)
