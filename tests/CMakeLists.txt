#----------------------------------------------------------------------------------------------------------------------
# General Settings
#----------------------------------------------------------------------------------------------------------------------

# Add the tests/cmake directory to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake") 

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

if(TARGET GTest::gtest)
    get_target_property(GTEST_INCLUDES GTest::gtest INTERFACE_INCLUDE_DIRECTORIES)
    message(STATUS "GTest::gtest INTERFACE_INCLUDE_DIRECTORIES reported: ${GTEST_INCLUDES}")
else()
    message(WARNING "GTest::gtest target was NOT found after FetchContent_MakeAvailable!")
endif()

#----------------------------------------------------------------------------------------------------------------------
# Testing Subdirectories
#----------------------------------------------------------------------------------------------------------------------

add_subdirectory(math) 
add_subdirectory(window)
add_subdirectory(rendering/primitives)
add_subdirectory(rendering/systems)
add_subdirectory(rendering)
