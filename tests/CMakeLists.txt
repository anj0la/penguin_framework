#----------------------------------------------------------------------------------------------------------------------
# Testing Framework
#----------------------------------------------------------------------------------------------------------------------

include(FetchContent)

FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG        v1.16.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)

include(GoogleTest) # provides the gtest_discover_tests() function 

#----------------------------------------------------------------------------------------------------------------------
# Dependencies
#----------------------------------------------------------------------------------------------------------------------

#find_package(penguin_framework 0.1.0 QUIET)
#if(NOT penguin_framework_FOUND)
 #   message(STATUS "find_package(penguin_framework) was NOT found, using as a subproject...")
    # test if the targets are usable if used as subproject
 #   add_subdirectory(.. penguin_framework EXCLUDE_FROM_ALL)
#endif()

#----------------------------------------------------------------------------------------------------------------------
# Testing Subdirectories
#----------------------------------------------------------------------------------------------------------------------

#add_subdirectory(math) 
#add_subdirectory(utils)