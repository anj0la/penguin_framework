#----------------------------------------------------------------------------------------------------------------------
# Testing Setup
#----------------------------------------------------------------------------------------------------------------------

include(TestHelpers)

add_executable(run_renderer_system_tests
				"test_texture_loader.cpp" 
				"test_asset_manager.cpp" 
				"test_font_loader.cpp")

target_link_libraries(
	  run_renderer_system_tests
	  penguin::penguin
	  SDL3::SDL3
	  GTest::gtest_main
)

target_include_directories(run_renderer_system_tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/tests
)

add_macro(run_renderer_system_tests TEST_ASSETS_DIR "${CMAKE_SOURCE_DIR}/tests/assets")

gtest_discover_tests(run_renderer_system_tests
    WORKING_DIRECTORY ${TEST_BINARY_DIR}
)

add_dependencies(run_renderer_system_tests copy_penguin_dll)
