#----------------------------------------------------------------------------------------------------------------------
# Testing Setup
#----------------------------------------------------------------------------------------------------------------------

include(TestHelpers)

add_executable(run_penguin_rendering_system_tests
				"test_penguin_texture_loader.cpp" "test_penguin_asset_manager.cpp")

target_link_libraries(
	  run_penguin_rendering_system_tests
	  penguin::penguin
	  SDL3::SDL3
	  GTest::gtest_main
)

target_include_directories(run_penguin_rendering_system_tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/tests
)

copy_dll_files(run_penguin_rendering_system_tests)
add_macro(run_penguin_rendering_system_tests TEST_ASSETS_DIR "${CMAKE_SOURCE_DIR}/tests/assets")
gtest_discover_tests(run_penguin_rendering_system_tests)