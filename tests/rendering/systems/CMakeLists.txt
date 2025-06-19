#----------------------------------------------------------------------------------------------------------------------
# Testing Setup
#----------------------------------------------------------------------------------------------------------------------

include(TestHelpers)

add_executable(run_renderer_system_tests
				"test_texture_loader.cpp" "test_asset_manager.cpp")

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

copy_dll_files(run_renderer_system_tests)
add_macro(run_renderer_system_tests TEST_ASSETS_DIR "${CMAKE_SOURCE_DIR}/tests/assets")
gtest_discover_tests(run_renderer_system_tests)