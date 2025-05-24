#----------------------------------------------------------------------------------------------------------------------
# Testing Setup
#----------------------------------------------------------------------------------------------------------------------

include(TestHelpers)

add_executable(run_penguin_primitives_tests
		"test_penguin_texture.cpp"
		"test_penguin_sprite.cpp")

target_link_libraries(
	  run_penguin_primitives_tests
	  penguin::penguin
	  SDL3::SDL3
	  GTest::gtest_main
)

copy_dll_files(run_penguin_primitives_tests)
add_macro(run_penguin_primitives_tests TEST_ASSETS_DIR "${CMAKE_SOURCE_DIR}/tests/assets")
gtest_discover_tests(run_penguin_primitives_tests)