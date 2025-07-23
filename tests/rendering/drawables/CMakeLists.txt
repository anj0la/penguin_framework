#----------------------------------------------------------------------------------------------------------------------
# Testing Setup
#----------------------------------------------------------------------------------------------------------------------

include(TestHelpers)

add_executable(run_renderer_drawables_tests
		"test_text.cpp"
		"test_sprite.cpp")

target_link_libraries(run_renderer_drawables_tests
	PRIVATE
		penguin::penguin
		GTest::gtest_main
)

target_include_directories(run_renderer_drawables_tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/tests
)

add_macro(run_renderer_drawables_tests TEST_ASSETS_DIR "${CMAKE_SOURCE_DIR}/tests/assets")

gtest_discover_tests(run_renderer_drawables_tests
    WORKING_DIRECTORY ${TEST_BINARY_DIR}
)

add_dependencies(run_renderer_drawables_tests copy_penguin_dll)
