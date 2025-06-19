#----------------------------------------------------------------------------------------------------------------------
# Testing Setup
#----------------------------------------------------------------------------------------------------------------------

include(TestHelpers)

add_executable(run_renderer_primitives_tests
		"test_texture.cpp"
		"test_sprite.cpp")

target_link_libraries(
	  run_renderer_primitives_tests
	  penguin::penguin
	  SDL3::SDL3
	  GTest::gtest_main
)

target_include_directories(run_renderer_primitives_tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/tests
)

copy_dll_files(run_renderer_primitives_tests)
add_macro(run_renderer_primitives_tests TEST_ASSETS_DIR "${CMAKE_SOURCE_DIR}/tests/assets")
gtest_discover_tests(run_renderer_primitives_tests)