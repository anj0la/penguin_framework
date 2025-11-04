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

set(PF_BUILD_SHARED ON) # For testing purposes
set(PF_BUILD_TESTS ON) # For testing purposes

option(PF_BUILD_SHARED "Build Penguin Framework as a shared library" ON) 

option(PF_BUILD_TESTS "Build Penguin Framework tests" ON)
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

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

#----------------------------------------------------------------------------------------------------------------------
# Dependencies
#----------------------------------------------------------------------------------------------------------------------

message(STATUS "Installing dependencies for penguin_framework...")
set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(
    sdl3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git 
    GIT_TAG        release-3.2.18
    CMAKE_ARGS
        -DSDL_SHARED=OFF 
        -DSDL_STATIC=ON
        -DSDL_TESTS=OFF 
        -DSDL_EXAMPLES=OFF 
        -DSDL_INSTALL=OFF
    SYSTEM
)

FetchContent_Declare(
    sdl3_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG        release-3.2.2
    CMAKE_ARGS
        -DSDLTTF_SHARED=OFF
        -DSDLTTF_STATIC=ON
        -DSDLTTF_VENDORED=ON
        -DSDLTTF_SAMPLES=OFF
        -DSDLTTF_INSTALL=OFF
    SYSTEM
)

FetchContent_Declare(
    sdl3_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG        release-3.2.4
    CMAKE_ARGS
        -DSDLIMAGE_SHARED=OFF
        -DSDLIMAGE_STATIC=ON
        -DSDLIMAGE_TESTS=OFF 
        -DSDLIMAGE_VENDORED=OFF
        -DSDLIMAGE_INSTALL=OFF

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

#----------------------------------------------------------------------------------------------------------------------
# Library Definition
#----------------------------------------------------------------------------------------------------------------------

message(STATUS "Adding penguin_framework library...")

add_library(penguin_main STATIC "src/penguin_main.cpp")

set(PF_SOURCES 
        "src/math/vector2.cpp"
        "src/math/vector2i.cpp"
        "src/math/circle2.cpp" 
        "src/math/rect2.cpp" 
        "src/math/rect2i.cpp" 
        "src/math/colour.cpp"
        "src/window/window.cpp"
        "src/rendering/renderer.cpp"
        "src/rendering/primitives/texture.cpp" 
        "src/rendering/drawables/sprite.cpp" 
        "src/rendering/systems/texture_loader.cpp" 
        "src/rendering/systems/asset_manager.cpp"
        "src/window/internal/window_impl.cpp" 
        "src/logger/internal/logger_impl.cpp" 
        "src/logger/logger.cpp" 
        "src/rendering/primitives/internal/texture_impl.cpp" 
        "src/rendering/drawables/internal/sprite_impl.cpp" 
        "src/rendering/systems/internal/texture_loader_impl.cpp" 
        "src/rendering/systems/internal/asset_manager_impl.cpp" 
        "src/rendering/internal/renderer_impl.cpp" 
        "src/rendering/primitives/internal/font_impl.cpp" 
        "src/rendering/primitives/font.cpp" 
        "src/rendering/drawables/internal/text_impl.cpp" 
        "src/rendering/drawables/text.cpp" 
        "src/rendering/systems/internal/text_context_impl.cpp" 
        "src/rendering/systems/text_context.cpp" 
        "src/rendering/systems/internal/font_loader_impl.cpp" 
        "src/rendering/systems/font_loader.cpp"
        "src/internal/penguin_init.cpp"
        "src/events/internal/input_event_impl.cpp"
        "src/events/input_event.cpp"
)

set(BUILD_SHARED_LIBS ${PF_BUILD_SHARED}) # Set after SDL dependencies

if(PF_BUILD_SHARED)
    message(STATUS "Building penguin_framework as a SHARED library.")
    add_library(penguin_framework SHARED ${PF_SOURCES})
else()
    message(STATUS "Building penguin_framework as a STATIC library.")
    add_library(penguin_framework STATIC ${PF_SOURCES})
    target_compile_definitions(penguin_framework
        INTERFACE PENGUIN_STATIC_DEFINE
)

endif()

add_library(penguin::penguin ALIAS penguin_framework)

message(STATUS "Added penguin_framework library.")

#----------------------------------------------------------------------------------------------------------------------
# Exports
#----------------------------------------------------------------------------------------------------------------------

generate_export_header(penguin_framework
      BASE_NAME PENGUIN
      EXPORT_MACRO_NAME PENGUIN_API
      NO_EXPORT_MACRO_NAME PENGUIN_HIDDEN
      STATIC_DEFINE PENGUIN_STATIC_DEFINE
      EXPORT_FILE_NAME penguin_api.hpp
)

#----------------------------------------------------------------------------------------------------------------------
# Target Properties & Linking
#----------------------------------------------------------------------------------------------------------------------

message(STATUS "Linking penguin_framework...")

target_include_directories(penguin_main
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_include_directories(penguin_framework
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(penguin_main 
    PRIVATE 
        penguin_framework
        SDL3::SDL3-static
)

target_link_libraries(penguin_framework
     PRIVATE
        SDL3::SDL3-static
        SDL3_ttf::SDL3_ttf-static
        SDL3_image::SDL3_image-static
)

target_compile_features(penguin_framework PUBLIC cxx_std_20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set_target_properties(penguin_framework PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}

    POSITION_INDEPENDENT_CODE ON 
)

message(STATUS "Finished linking penguin_framework.")

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
                    SDL3_Headers           
                    SDL3-static
                    SDL3_ttf-static
                    SDL3_image-static
            EXPORT penguin_framework_export 
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Runtime
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