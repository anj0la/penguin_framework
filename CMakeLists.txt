# Backwards comptability for CMake 3.15 to 3.31 (doesn't support CMake 4.0 or higher)
cmake_minimum_required(VERSION 3.15...3.31)

project(PenguinFramework VERSION 0.1.0 LANGUAGES CXX)

# C++ 20 is the standard version, but can defer to earlier versions if C++ 20 isn't available
set(CMAKE_CXX_STANDARD 20)


