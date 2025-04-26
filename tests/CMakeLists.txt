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
# Functions
#----------------------------------------------------------------------------------------------------------------------

# TODO: Add function to add test executable. Needs to copy DLL files to avoid violating DRY (Don't Repeat Yourself)
function(add_test_executable target_name)
endfunction()

#----------------------------------------------------------------------------------------------------------------------
# Testing Subdirectories
#----------------------------------------------------------------------------------------------------------------------

add_subdirectory(math) 
add_subdirectory(utils)
add_subdirectory(window) # -> Tests don't build currently due to unresolved externals, need to go back to implementation of Window
#add_subdirectory(system)
