#----------------------------------------------------------------------------------------------------------------------
# General Settings
#----------------------------------------------------------------------------------------------------------------------

include_guard(GLOBAL)
message(STATUS "Loading TestHelpers module...") 

#----------------------------------------------------------------------------------------------------------------------
# Functions
#----------------------------------------------------------------------------------------------------------------------

function(copy_dll_files target_name)
    message(STATUS "Running copy_dll_files function for ${target_name}...")

    if(WIN32 AND PF_BUILD_SHARED)
        set(TEST_EXE_DIR "$<TARGET_FILE_DIR:${target_name}>")
        set(DLL_TARGETS "penguin::penguin;SDL3::SDL3;GTest::gtest;GTest::gtest_main") 
        foreach(DLL_TARGET ${DLL_TARGETS})
            if(TARGET ${DLL_TARGET})
                add_custom_command(TARGET ${target_name} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        $<TARGET_FILE:${DLL_TARGET}>
                        ${TEST_EXE_DIR}
                    COMMENT "Copying $<TARGET_FILE_NAME:${DLL_TARGET}> for ${target_name}"
                    VERBATIM
                )
            endif()
        endforeach()
    endif() 

endfunction()