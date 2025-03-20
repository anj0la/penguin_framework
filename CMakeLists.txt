# Backwards comptability for CMake 3.15 to 3.31 (doesn't support CMake 4.0 or higher)
cmake_minimum_required(VERSION 3.15...3.31)

# Define the project, version and languages support
project(PenguinFramework VERSION 0.1.0 LANGUAGES CXX)

# Requires C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include external sub-directories used for Penguin Framework
# add_subdirectory(external/SDL3)
