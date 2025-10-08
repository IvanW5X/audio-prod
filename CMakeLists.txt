# Standard CMake Setup
cmake_minimum_required(VERSION 3.25)

project(AudioProd VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-O3" CACHE STRING "Compiler flags")

set(CMAKE_AUTORCC ON CACHE BOOL "")
set(CMAKE_AUTOMOC ON CACHE BOOL "")

message(STATUS "Loading project: ${CMAKE_PROJECT_NAME} for C++20")

if (DEFINED ENV{CMAKE_TAGLIB_PATH})
    list(APPEND CMAKE_PREFIX_PATH
        "$ENV{CMAKE_TAGLIB_PATH}"
    )
    message(STATUS "TagLib library path found at $ENV{CMAKE_TAGLIB_PATH}")
else ()
    message(STATUS "TagLib library path not found, set the env variable (CMAKE_TAGLIB_PATH)")
endif ()

if (DEFINED ENV{CMAKE_LIBSNDFILE_PATH})
    list(APPEND CMAKE_PREFIX_PATH
        "$ENV{CMAKE_LIBSNDFILE_PATH}"
    )
    message(STATUS "libsndfile library path found at $ENV{CMAKE_LIBSNDFILE_PATH}")
else ()
    message(STATUS "libsndfile library path not found, set the env variable (CMAKE_LIBSNDFILE_PATH)")
endif ()

find_package(TagLib 2.1.1 REQUIRED)
find_package(SndFile 1.2.2 REQUIRED)
find_package(Qt6 6.8 REQUIRED COMPONENTS 
    Core
    Gui
    Quick
)

qt_standard_project_setup(REQUIRES 6.8)

add_subdirectory(src)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE FALSE
)