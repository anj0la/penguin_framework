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

# NOTE: The main library is built as a SHARED library instead of a STATIC library.

# In future updates, a static library may be provided, but as the API is currently unstable, a dynamic build
# would make the development process easier.

set(PF_BUILD_SHARED ON) 
set(BUILD_SHARED_LIBS ${PF_BUILD_SHARED})

option(PF_BUILD_TESTS "Build Penguin Framework tests" OFF) # TODO: Update tests CMakeLists.txt file
option(PF_BUILD_EXAMPLES "Build Penguin Framework examples" OFF) # NOTE: No examples currently
option(PF_BUILD_DOCS "Build Penguin Framework documentation" OFF) # NOTE: No documentation currently
option(PF_INSTALL "Generate target for installing Penguin Framework" ${IS_TOP_LEVEL})

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

set(SDL3_BUILD_SHARED ON CACHE BOOL "Build SDL as Shared Library")
set(SDL3_BUILD_STATIC OFF CACHE BOOL "Don't build SDL as Static Library" FORCE)
set(SDL_TESTS OFF CACHE BOOL "Disable SDL Tests" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "Disable SDL Examples" FORCE)
set(SDL_INSTALL ON CACHE BOOL "Enable SDL Install Targets" FORCE)

FetchContent_Declare(
    sdl3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git 
    GIT_TAG        release-3.2.10
    CMAKE_ARGS
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

#----------------------------------------------------------------------------------------------------------------------
# Library Definition
#----------------------------------------------------------------------------------------------------------------------

message(STATUS "Adding penguin_framework library...")

add_library(penguin_framework
            ${CMAKE_CURRENT_SOURCE_DIR}/src/core/math/vector2.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/core/math/vector2i.cpp       
            #${CMAKE_CURRENT_SOURCE_DIR}/src/core/events/event.cpp -> these classes need to be updated
            #${CMAKE_CURRENT_SOURCE_DIR}/src/core/events/windowevent.cpp
            #${CMAKE_CURRENT_SOURCE_DIR}/src/core/input/input.cpp
            #${CMAKE_CURRENT_SOURCE_DIR}/src/core/input/keyboard/keyboard.cpp
            "src/core/window/penguin_window.cpp"
            ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/string.cpp
)
add_library(penguin::penguin ALIAS penguin_framework)

message(STATUS "Added penguin_framework library.")

#----------------------------------------------------------------------------------------------------------------------
# Exports
#----------------------------------------------------------------------------------------------------------------------

generate_export_header(penguin_framework
      BASE_NAME PENGUIN
      EXPORT_MACRO_NAME PENGUIN_API
      NO_EXPORT_MACRO_NAME PENGUIN_HIDDEN
      EXPORT_FILE_NAME include/penguin_framework/penguin_api.hpp
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

if(NOT TARGET SDL3::SDL3)
    message(FATAL_ERROR "Target SDL3::SDL3 not found. SDL3 FetchContent might have failed or SDL_INSTALL was OFF.")
endif()
target_link_libraries(penguin_framework
     PRIVATE
         SDL3::SDL3
)

target_compile_features(penguin_framework PUBLIC cxx_std_20)

set_target_properties(penguin_framework PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib 
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin 

    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}

    POSITION_INDEPENDENT_CODE ON 
)

message(STATUS "Finished linking penguin_framework.")

#----------------------------------------------------------------------------------------------------------------------
# Post-Build
#----------------------------------------------------------------------------------------------------------------------

if(PF_BUILD_SHARED)
    message(STATUS "penguin_framework is SHARED, adding post-build copy command...")

    if(WIN32)
        set(SDL3_COPY_DEST_DIR "${CMAKE_BINARY_DIR}/bin")
    else()
        set(SDL3_COPY_DEST_DIR "${CMAKE_BINARY_DIR}/lib")
    endif()
    message(STATUS "SDL3 copy destination directory: ${SDL3_COPY_DEST_DIR}")


    add_custom_command(
        TARGET penguin_framework POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3>
            ${SDL3_COPY_DEST_DIR}

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE_DIR:SDL3::SDL3>/$<TARGET_FILE_BASE_NAME:SDL3::SDL3>.pdb"
            ${SDL3_COPY_DEST_DIR}

        COMMENT "Copying SDL3 runtime artifacts to ${SDL3_COPY_DEST_DIR}..."
        VERBATIM
    )
endif()

#----------------------------------------------------------------------------------------------------------------------
# Installation
#----------------------------------------------------------------------------------------------------------------------

if(PF_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    message(STATUS "Configuring installation for penguin_framework...")

    install(DIRECTORY include/penguin_framework/
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/penguin_framework
            COMPONENT Development
            FILES_MATCHING PATTERN "*.hpp"
    )

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/penguin_framework/penguin_api.hpp
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/penguin_framework
            COMPONENT Development
    )

    install(TARGETS penguin_framework
            EXPORT penguin_framework_export 
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime # Installs penguin_framework.dll/so to bin/
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Runtime # Installs import lib/.so link to lib/
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    set(targets_export_file "penguin_framework-targets.cmake")

    install(EXPORT penguin_framework_export 
            FILE ${targets_export_file}
            NAMESPACE penguin:: 
            DESTINATION ${PF_INSTALL_CMAKEDIR}
            COMPONENT Development
    )

    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/penguin_framework-config-version.cmake"
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY SameMajorVersion
    )

    configure_package_config_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/cmake/penguin_framework-config.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/penguin_framework-config.cmake"
            INSTALL_DESTINATION "${PF_INSTALL_CMAKEDIR}"
    )

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/penguin_framework-config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/penguin_framework-config-version.cmake"
            DESTINATION "${PF_INSTALL_CMAKEDIR}"
            COMPONENT Development
    )

    install(FILES $<TARGET_FILE:SDL3::SDL3>
            DESTINATION ${CMAKE_INSTALL_BINDIR} # Install SDL3.dll/.so to bin/
            COMPONENT Runtime
            )

    if(MSVC)
        message(STATUS "Configuring PDB installation for MSVC...")

        set(PF_PDB_FILE "")
        set(PF_PDB_DESTINATION "")
        set(PF_PDB_COMPONENT Development)

        if(PF_BUILD_SHARED)
            set(PF_PDB_FILE "$<TARGET_PDB_FILE:penguin_framework>")
            set(PF_PDB_DESTINATION "${CMAKE_INSTALL_BINDIR}") # PDB goes with DLL
        endif()
       
        if(NOT PF_PDB_FILE STREQUAL "")
            install(FILES ${PF_PDB_FILE}
                    COMPONENT ${PF_PDB_COMPONENT}
                    CONFIGURATIONS Debug RelWithDebInfo 
                    DESTINATION ${PF_PDB_DESTINATION}
                    OPTIONAL # Don't fail if PDB doesn't exist
            )

            message(STATUS "    Installed PDB rule for penguin_framework.")
        else()
            message(WARNING "    Could not determine PDB path for penguin_framework.")
        endif()


        string(REPLACE ".dll" ".pdb" SDL3_PDB_FILE "$<TARGET_FILE:SDL3::SDL3>")
        install(FILES "${SDL3_PDB_FILE}"
              COMPONENT ${PF_PDB_COMPONENT}
              CONFIGURATIONS Debug RelWithDebInfo 
              DESTINATION ${CMAKE_INSTALL_BINDIR}
              OPTIONAL # Don't fail if PDB doesn't exist
             )

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