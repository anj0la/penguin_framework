###### PROJECT SETUP ######

# Backwards comptability for CMake 3.15 to 3.31 (doesn't support CMake 4.0 or higher).
cmake_minimum_required(VERSION 3.15...3.31)

# Define the project, version and languages support.
project(PenguinFramework VERSION 0.1.0 LANGUAGES CXX)

# Requires C++ 20.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the output directory for built objects (dynamic library automatically goes into the build directory).
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Assumed the SDL source is available in external/SDL.
add_subdirectory(external/SDL EXCLUDE_FROM_ALL)

###### TESTING SETUP ######

# Ensure FetchContent is included.
include(FetchContent)

# Fetch GoogleTest.
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.16.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add test subdirectory to enable testing.
# add_subdirectory(tests)
