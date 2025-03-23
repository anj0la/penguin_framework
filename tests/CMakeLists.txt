# Backwards comptability for CMake 3.15 to 3.31 (doesn't support CMake 4.0 or higher).
cmake_minimum_required(VERSION 3.15...3.31)

###### TESTING SETUP ######

# Add subdirectories for modular tests.
add_subdirectory(math)