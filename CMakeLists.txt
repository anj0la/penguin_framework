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

# NOTE: The main library is currently built as a SHARED library instead of a STATIC library.

set(PF_BUILD_SHARED ON) 
set(BUILD_SHARED_LIBS ${PF_BUILD_SHARED})

option(PF_BUILD_TESTS "Build Penguin Framework tests" ON) # TODO: Update tests CMakeLists.txt file
option(PF_BUILD_EXAMPLES "Build Penguin Framework examples" OFF) # NOTE: No examples currently
option(PF_BUILD_DOCS "Build Penguin Framework documentation" OFF) # NOTE: No documentation currently
option(PF_INSTALL "Generate target for installing Penguin Framework" ${IS_TOP_LEVEL})

set(PF_BUILD_TESTS ON) # JUST FOR TESTING PURPOSES

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

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

#----------------------------------------------------------------------------------------------------------------------
# Dependencies
#----------------------------------------------------------------------------------------------------------------------

message(STATUS "Installing dependencies for penguin_framework...")

FetchContent_Declare(
    sdl3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git 
    GIT_TAG        release-3.2.10
    CMAKE_ARGS
        -DSDL_SHARED=ON 
        -DSDL_STATIC=OFF # Disable static build for now
        -DSDL_TESTS=OFF 
        -DSDL_EXAMPLES=OFF 
        -DSDL_INSTALL=ON
    SYSTEM
)

FetchContent_Declare(
    sdl3_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG        release-3.2.2
    CMAKE_ARGS
        -DSDLTTF_SHARED=ON
        -DSDLTTF_STATIC=OFF # Disable static build for now
        -DSDLTTF_VENDORED=ON
        -DSDLTTF_SAMPLES=OFF
        -DSDLTTF_INSTALL=ON
    SYSTEM
)

FetchContent_Declare(
    sdl3_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG        release-3.2.4
    CMAKE_ARGS
        -DSDLIMAGE_SHARED=ON
        -DSDLIMAGE_STATIC=OFF
        -DSDLIMAGE_TESTS=OFF 
        -DSDLIMAGE_VENDORED=OFF
        -DSDLIMAGE_INSTALL=ON

        # Disabled formats
        -DSDLIMAGE_AVIF=OFF
        -DSDLIMAGE_JXL=OFF
        -DSDLIMAGE_TIF=OFF
        -DSDLIMAGE_WEBP=OFF
        -DSDLIMAGE_LBM=OFF
        -DSDLIMAGE_PCX=OFF
        -DSDLIMAGE_PNM=OFF
        -DSDLIMAGE_QOI=OFF
        -DSDLIMAGE_TGA=OFF
        -DSDLIMAGE_XCF=OFF
        -DSDLIMAGE_XPM=OFF
        -DSDLIMAGE_XV=OFF
        
        # Enabled formats
        -DSDLIMAGE_JPG=ON
        -DSDLIMAGE_PNG=ON
        -DSDLIMAGE_GIF=ON
        -DSDLIMAGE_BMP=ON 
        -DSDLIMAGE_SVG=ON
)

message(STATUS "Populating dependencies...")

FetchContent_MakeAvailable(sdl3)
FetchContent_MakeAvailable(sdl3_ttf)
FetchContent_MakeAvailable(sdl3_image)

message(STATUS "SDL3, SDL3_ttf and SDL_image are available.")
message(STATUS "Finished installing dependencies for penguin_framework.")

#----------------------------------------------------------------------------------------------------------------------
# Library Definition
#----------------------------------------------------------------------------------------------------------------------

message(STATUS "Adding penguin_framework library...")

add_library(penguin_framework
        "src/math/vector2.cpp"
        "src/math/vector2i.cpp"
        "src/math/circle2.cpp" 
        "src/math/rect2.cpp" 
        "src/math/rect2i.cpp" 
        "src/math/colour.cpp"
        "src/window/window.cpp"
        "src/rendering/renderer.cpp"
        "src/rendering/primitives/texture.cpp" 
        "src/rendering/primitives/sprite.cpp" 
        "src/rendering/systems/texture_loader.cpp" 
        "src/rendering/systems/asset_manager.cpp"
        "src/window/internal/window_impl.cpp" 
        "src/logger/internal/logger_impl.cpp" 
        "src/logger/logger.cpp" 
        "src/rendering/primitives/internal/texture_impl.cpp" 
        "src/rendering/primitives/internal/sprite_impl.cpp" 
        "src/rendering/systems/internal/texture_loader_impl.cpp" 
        "src/rendering/systems/internal/asset_manager_impl.cpp" 
        "src/rendering/internal/renderer_impl.cpp" "src/rendering/primitives/internal/font_impl.cpp" "src/rendering/primitives/font.cpp" "src/rendering/drawables/internal/text_impl.cpp" "src/rendering/drawables/text.cpp" "src/rendering/systems/internal/text_context_impl.cpp" "src/rendering/systems/text_context.cpp" "src/rendering/systems/internal/font_loader_impl.cpp" "src/rendering/systems/font_loader.cpp")

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
    message(FATAL_ERROR "Target SDL3::SDL3 not found. Check FetchContent.")
endif()
if(NOT TARGET SDL3_ttf::SDL3_ttf)
    message(FATAL_ERROR "Target SDL3_ttf::SDL3_ttf not found. Check FetchContent.")
endif()
if(NOT TARGET SDL3_image::SDL3_image)
    message(FATAL_ERROR "Target SDL3_image::SDL3_image not found. Check FetchContent.")
endif()

target_link_libraries(penguin_framework
     PRIVATE
         SDL3::SDL3
         SDL3_ttf::SDL3_ttf
         SDL3_image::SDL3_image
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
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL3::SDL3> $<TARGET_FILE_DIR:penguin_framework>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL3_ttf::SDL3_ttf> $<TARGET_FILE_DIR:penguin_framework>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL3_image::SDL3_image> $<TARGET_FILE_DIR:penguin_framework>

        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        "$<TARGET_FILE_DIR:SDL3::SDL3>/$<TARGET_FILE_BASE_NAME:SDL3::SDL3>.pdb" $<TARGET_FILE_DIR:penguin_framework>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        "$<TARGET_FILE_DIR:SDL3_ttf::SDL3_ttf>/$<TARGET_FILE_BASE_NAME:SDL3_ttf::SDL3_ttf>.pdb" $<TARGET_FILE_DIR:penguin_framework>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        "$<TARGET_FILE_DIR:SDL3_image::SDL3_image>/$<TARGET_FILE_BASE_NAME:SDL3_image::SDL3_image>.pdb" $<TARGET_FILE_DIR:penguin_framework>
        COMMENT "Copying SDL runtime artifacts for local build..."
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

    install(FILES
            $<TARGET_FILE:SDL3::SDL3>
            $<TARGET_FILE:SDL3_ttf::SDL3_ttf>
            $<TARGET_FILE:SDL3_image::SDL3_image>
            DESTINATION ${CMAKE_INSTALL_BINDIR} # Install DLLs to bin/
            COMPONENT Runtime
    )

    if(MSVC)
        message(STATUS "Configuring PDB installation for MSVC...")
        
        install(FILES
            "$<TARGET_FILE_DIR:SDL3::SDL3>/$<TARGET_FILE_BASE_NAME:SDL3::SDL3>.pdb"
            "$<TARGET_FILE_DIR:SDL3_ttf::SDL3_ttf>/$<TARGET_FILE_BASE_NAME:SDL3_ttf::SDL3_ttf>.pdb"
            "$<TARGET_FILE_DIR:SDL3_image::SDL3_image>/$<TARGET_FILE_BASE_NAME:SDL3_image::SDL3_image>.pdb"
            DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT Development
            CONFIGURATIONS Debug RelWithDebInfo
            OPTIONAL
        )
    endif()

    include(CPack)

    message(STATUS "Finished installing penguin_framework.")

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