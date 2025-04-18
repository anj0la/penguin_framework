#----------------------------------------------------------------------------------------------------------------------
# Project Settings
#----------------------------------------------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.15...3.31)
project(penguin_framework VERSION 0.1.0 LANGUAGES CXX)

#----------------------------------------------------------------------------------------------------------------------
# General Settings
#----------------------------------------------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
include(FetchContent)
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" IS_TOP_LEVEL)

#----------------------------------------------------------------------------------------------------------------------
# Build Options
#----------------------------------------------------------------------------------------------------------------------

# Allow users to choose between static and shared library builds
option(PF_BUILD_SHARED "Build shared libraries" ON) # Builds shared library by default
# Propagate the option to the standard CMake variable
set(BUILD_SHARED_LIBS ${PF_BUILD_SHARED})

message(STATUS "PF_BUILD_SHARED: ${PF_BUILD_SHARED} and BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")

option(PF_BUILD_TESTS "Build Penguin Framework tests" OFF) # Testing off by default
option(PF_BUILD_EXAMPLES "Build Penguin Framework examples" OFF) # NOTE: No examples currently
option(PF_BUILD_DOCS "Build Penguin Framework documentation" OFF) # NOTE: No documentation currently
# Determine if installation rules should be generated
option(PF_INSTALL "Generate target for installing Penguin Framework" ${IS_TOP_LEVEL})
#set(PF_INSTALL OFF)

#----------------------------------------------------------------------------------------------------------------------
# Build Settings
#----------------------------------------------------------------------------------------------------------------------

if(NOT DEFINED PF_INSTALL_CMAKEDIR)
    set(PF_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/penguin_framework" CACHE PATH
        "Install path for Penguin Framework package-related CMake files")
endif()
if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Add -fvisibility=hidden to command line arguments of GCC and clang
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

#----------------------------------------------------------------------------------------------------------------------
# Dependencies
#----------------------------------------------------------------------------------------------------------------------

# Set SDL3 build options BEFORE FetchContent_MakeAvailable

# Match SDL3's build type (shared/static) to the framework's build type
if(PF_BUILD_SHARED)
    set(SDL3_BUILD_SHARED ON)
    set(SDL3_BUILD_STATIC OFF)
    message(STATUS "penguin_framework is SHARED, building SDL3 as SHARED.")
else()
    set(SDL3_BUILD_SHARED OFF)
    set(SDL3_BUILD_STATIC ON)
    message(STATUS "penguin_framework is STATIC, building SDL3 as STATIC.")
endif()

set(SDL_TESTS OFF CACHE BOOL "Disable SDL Tests" FORCE) # Prevent SDL3 from building tests
set(SDL_EXAMPLES OFF CACHE BOOL "Disable SDL Examples" FORCE) # Prevent SDL3 from building examples
set(SDL_INSTALL ON CACHE BOOL "Enable SDL Install Targets" FORCE)

FetchContent_Declare(
    sdl3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git 
    GIT_TAG        release-3.2.10
    CMAKE_ARGS # Pass options to SDL's CMake configure step
        -DSDL_SHARED=${SDL3_BUILD_SHARED}
        -DSDL_STATIC=${SDL3_BUILD_STATIC}
        -DSDL_TESTS=${SDL_TESTS}
        -DSDL_EXAMPLES=${SDL_EXAMPLES}
        -DSDL_INSTALL=${SDL_INSTALL}
    SYSTEM # Suppress warnings during build
)

message(STATUS "Fetching and configuring SDL3...")
FetchContent_MakeAvailable(sdl3)
message(STATUS "SDL3 available. Linking against target: SDL3::SLD3")

# find_package(SDL3)

#----------------------------------------------------------------------------------------------------------------------
# Library Definition
#----------------------------------------------------------------------------------------------------------------------

message(STATUS "Adding penguin_framework library...")

add_library(penguin_framework
            ${CMAKE_CURRENT_SOURCE_DIR}/src/core/math/vector2.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/core/math/vector2i.cpp       
            #${CMAKE_CURRENT_SOURCE_DIR}/src/core/events/event.cpp
            #${CMAKE_CURRENT_SOURCE_DIR}/src/core/events/windowevent.cpp
            #${CMAKE_CURRENT_SOURCE_DIR}/src/core/input/input.cpp
            #${CMAKE_CURRENT_SOURCE_DIR}/src/core/input/keyboard/keyboard.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/window.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/string.cpp
)
add_library(penguin::penguin ALIAS penguin_framework)

message(STATUS "Added penguin_framework library.")

#----------------------------------------------------------------------------------------------------------------------
# Exports
#----------------------------------------------------------------------------------------------------------------------

generate_export_header(penguin_framework
  EXPORT_MACRO_NAME PENGUIN_API
  NO_EXPORT_MACRO_NAME PENGUIN_NO_EXPORT
  EXPORT_FILE_NAME include/penguin_framework/core/penguin_api.hpp
  BASE_NAME PENGUIN
)

#----------------------------------------------------------------------------------------------------------------------
# Target Properties & Linking
#----------------------------------------------------------------------------------------------------------------------

message(STATUS "Linking penguin_framework...")

target_include_directories(penguin_framework
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(penguin_framework
     PRIVATE
         SDL3::SDL3
)

target_compile_features(penguin_framework PUBLIC cxx_std_20)

set_target_properties(penguin_framework PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin # DLLs go here on Windows

    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}

    POSITION_INDEPENDENT_CODE ON # Required for shared libs but good to keep for static libs linking to shared
)

message(STATUS "Finished linking penguin_framework.")

#----------------------------------------------------------------------------------------------------------------------
# Installation (the issue)
#----------------------------------------------------------------------------------------------------------------------

if(PF_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    message(STATUS "Configuring installation for penguin_framework...")

    install(DIRECTORY include/penguin_framework/
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/penguin_framework
            COMPONENT Development
            FILES_MATCHING PATTERN "*.hpp"
    )

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/penguin_framework/core/penguin_api.hpp
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/penguin_framework/core
            COMPONENT Development
    )

    install(TARGETS penguin_framework
            EXPORT penguin_framework_export 
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime # DLLs, EXEs
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Runtime # Shared Libs (.so, .dylib)
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development # Static Libs (.a, .lib), Import Libs (.lib)
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # Headers associated with the target interface
    )

    set(targets_export_file "penguin_framework-targets.cmake")

    # Important: This export needs the dependency info handled correctly.
    # If framework is static and links static SDL3 -> OK
    # If framework is shared and links shared SDL3 -> OK (SDL3 runtime installed above)
    # If framework is shared and links static SDL3 -> OK (SDL3 code baked into framework DLL)
    # If framework is static and links shared SDL3 -> Requires consumer to find SDL3 DLL. This is generally avoided.
    # The matching build types logic prevents the last case.
    install(EXPORT penguin_framework_export 
            FILE "${targets_export_file}"
            NAMESPACE penguin:: 
            DESTINATION "${PF_INSTALL_CMAKEDIR}"
            COMPONENT Development
    )

    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/penguin_framework-config-version.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    configure_package_config_file(
    # --- INPUT ---
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/penguin_framework-config.cmake.in"
    # --- OUTPUT ---
    "${CMAKE_CURRENT_BINARY_DIR}/penguin_framework-config.cmake"
    # --- Options ---
    INSTALL_DESTINATION "${PF_INSTALL_CMAKEDIR}"
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_BINDIR # Keep these if needed by your .in file, though this template doesn't use them directly
    )

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/penguin_framework-config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/penguin_framework-config-version.cmake"
        DESTINATION "${PF_INSTALL_CMAKEDIR}"
        COMPONENT Development
    )

    if(MSVC)
        message(STATUS "Configuring PDB installation for MSVC...")

        # PDB for penguin_framework 
        set(PF_PDB_FILE "")
        set(PF_PDB_DESTINATION "")
        set(PF_PDB_COMPONENT Development)

        if(PF_BUILD_SHARED)
            # Shared library PDB using standard generator expression
            set(PF_PDB_FILE "$<TARGET_PDB_FILE:penguin_framework>")
            set(PF_PDB_DESTINATION "${CMAKE_INSTALL_BINDIR}") # PDB goes with DLL
            message(STATUS "  - Framework is SHARED. PDB path: ${PF_PDB_FILE} -> ${PF_PDB_DESTINATION}")
        else()
            # Static library PDB - manual path construction
            set(PF_PDB_FILE "$<TARGET_FILE_DIR:penguin_framework>/$<TARGET_FILE_BASE_NAME:penguin_framework>.pdb")
            set(PF_PDB_DESTINATION "${CMAKE_INSTALL_LIBDIR}") # PDB goes with static LIB
            message(STATUS "  - Framework is STATIC. PDB path: ${PF_PDB_FILE} -> ${PF_PDB_DESTINATION}")
        endif()

        if(NOT PF_PDB_FILE STREQUAL "")
            install(FILES "${PF_PDB_FILE}"
                    COMPONENT ${PF_PDB_COMPONENT}
                    CONFIGURATIONS Debug RelWithDebInfo # Only install for configs likely to have PDBs
                    DESTINATION "${PF_PDB_DESTINATION}"
                    OPTIONAL # Don't fail if PDB doesn't exist for some reason
            )
            message(STATUS "    Installed PDB rule for penguin_framework.")
        else()
            message(WARNING "    Could not determine PDB path for penguin_framework.")
        endif()

    endif()

    include(CPack)

    message(STATUS "Finished installation for penguin_framework.")

endif() 

#----------------------------------------------------------------------------------------------------------------------
# Other Targets
#----------------------------------------------------------------------------------------------------------------------

if(PF_BUILD_TESTS)
    message(STATUS "Building penguin_framework tests...")
    enable_testing()
    add_subdirectory(tests) # Assumes tests/CMakeLists.txt links penguin::penguin
endif()

if(PF_BUILD_EXAMPLES)
    message(STATUS "Building penguin_framework examples...")
    add_subdirectory(examples) # Assumes examples/CMakeLists.txt links penguin::penguin
endif()

if(PF_BUILD_DOCS)
    message(STATUS "Configuring penguin_framework documentation build...")
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        # TODO: Add Doxygen target generation here
    else()
        message(WARNING "Doxygen not found, documentation target cannot be generated.")
    endif()
endif()