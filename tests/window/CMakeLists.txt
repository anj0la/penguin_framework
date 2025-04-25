#----------------------------------------------------------------------------------------------------------------------
# Testing Setup
#----------------------------------------------------------------------------------------------------------------------

add_executable(run_window_tests
	  "test_penguin_window.cpp"
	  "test_penguin_windowflags.cpp"
)

target_link_libraries(
	  run_window_tests
	  penguin::penguin
	  SDL3::SDL3
	  GTest::gtest_main
)

if(WIN32 AND PF_BUILD_SHARED) 
    set(PF_DLL_PATH "$<TARGET_FILE:penguin::penguin>")
    set(SDL3_DLL_PATH "$<TARGET_FILE:SDL3::SDL3>")
    set(GTEST_DLL_PATH "$<TARGET_FILE:GTest::gtest>")
    set(GTEST_MAIN_DLL_PATH "$<TARGET_FILE:GTest::gtest_main>")
    set(TEST_EXE_DIR "$<TARGET_FILE_DIR:run_window_tests>")

    # Add steps to copy specific dlls
    add_custom_command(TARGET run_window_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PF_DLL_PATH}"
            "${TEST_EXE_DIR}"
        COMMENT "Copying penguin_framework.dll for ${run_window_tests}"
        VERBATIM)

    add_custom_command(TARGET run_window_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_DLL_PATH}"
            "${TEST_EXE_DIR}"
        COMMENT "Copying SDL3.dll for ${run_window_tests}"
        VERBATIM)

    add_custom_command(TARGET run_window_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GTEST_DLL_PATH}"
            "${TEST_EXE_DIR}"
        COMMENT "Copying gtest.dll for ${run_window_tests}"
        VERBATIM)

    add_custom_command(TARGET run_window_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GTEST_MAIN_DLL_PATH}"
            "${TEST_EXE_DIR}"
        COMMENT "Copying gtest_main.dll for ${run_window_tests}"
        VERBATIM)

endif()

gtest_discover_tests(run_window_tests)
