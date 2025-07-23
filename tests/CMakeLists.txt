#----------------------------------------------------------------------------------------------------------------------
# General Settings
#----------------------------------------------------------------------------------------------------------------------

# Add the tests/cmake directory to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake") 

set(TEST_BINARY_DIR ${CMAKE_BINARY_DIR}/tests/bin)
file(MAKE_DIRECTORY ${TEST_BINARY_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TEST_BINARY_DIR})

set(PF_OLD_BUILD_SHARED ${BUILD_SHARED_LIBS})
set(BUILD_SHARED_LIBS OFF) # Turn it off to built Gtest statically

#----------------------------------------------------------------------------------------------------------------------
# Testing Framework
#----------------------------------------------------------------------------------------------------------------------

include(FetchContent)

FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG        v1.16.0
)

# set(gtest_build_shared_libs OFF CACHE BOOL "")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)
include(GoogleTest) 

set(BUILD_SHARED_LIBS ${PF_OLD_BUILD_SHARED}) # Safe to store original value


if(TARGET GTest::gtest)
    get_target_property(GTEST_INCLUDES GTest::gtest INTERFACE_INCLUDE_DIRECTORIES)
    message(STATUS "GTest::gtest INTERFACE_INCLUDE_DIRECTORIES reported: ${GTEST_INCLUDES}")
else()
    message(WARNING "GTest::gtest target was NOT found after FetchContent_MakeAvailable!")
endif()

#----------------------------------------------------------------------------------------------------------------------
# Testing Dependencies
#----------------------------------------------------------------------------------------------------------------------

if(PF_BUILD_SHARED)

    add_custom_target(copy_penguin_dll ALL
        COMMENT "Copying runtime DLLs for test executables..."
    )

    add_custom_command(
        TARGET copy_penguin_dll
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:penguin::penguin>
            ${TEST_BINARY_DIR}
        COMMENT "Copying penguin_framework.dll to test directory..."
    )

    add_dependencies(copy_penguin_dll penguin::penguin)

endif()

#----------------------------------------------------------------------------------------------------------------------
# Testing Subdirectories
#----------------------------------------------------------------------------------------------------------------------

add_subdirectory(math) 
add_subdirectory(window)
add_subdirectory(rendering)
