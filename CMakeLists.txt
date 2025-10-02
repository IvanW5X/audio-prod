# Standard CMake Setup
cmake_minimum_required(VERSION 3.25)

project(AudioProd VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)

# Standard Qt Setup
find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Widgets
    Multimedia
)

qt_standard_project_setup()
set(CMAKE_AUTORCC ON CACHE BOOL "")
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/uiFiles CACHE FILEPATH "UI files directory")
set(CMAKE_CXX_FLAGS "-O3" CACHE STRING "Compiler flags")

# TagLib options
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(TAGLIB_BUILD_TESTS OFF CACHE BOOL "")
set(TAGLIB_BUILD_EXAMPLES OFF CACHE BOOL "")

add_subdirectory(third-party/taglib)

qt_add_executable(AudioProd
    # Resource file
    resources/resources.qrc

    # Utilities
    utils/commonDefines.h
    utils/utils.h
    utils/utils.cpp

    # Headers
    headers/syncedAudioQueue.h
    headers/audioEngine.h
    headers/mainWindow.h
    headers/audioControllerWidget.h
    headers/audioController.h
    headers/audioDataWidget.h
    headers/audioPlayerWidget.h
    headers/waveFormWidget.h

    # UI files
    uiFiles/mainWindow.ui
    uiFiles/audioControllerWidget.ui
    uiFiles/audioDataWidget.ui
    uiFiles/audioPlayerWidget.ui
    uiFiles/waveFormWidget.ui
    
    # Sources
    sources/syncedAudioQueue.cpp
    sources/audioEngine.cpp
    sources/mainWindow.cpp
    sources/audioControllerWidget.cpp
    sources/audioController.cpp
    sources/audioDataWidget.cpp
    sources/audioPlayerWidget.cpp
    sources/waveFormWidget.cpp
    main.cpp
)

# Linking externals
target_link_libraries(AudioProd PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Multimedia
    "${CMAKE_SOURCE_DIR}/build/third-party/taglib/taglib/libtag.a"
)

target_include_directories(AudioProd PRIVATE
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_SOURCE_DIR}/third-party/taglib/taglib
)

# Prevent the creation of a console window on Windows.
# Create an application bundle on macOS.
set_target_properties(AudioProd PROPERTIES
    # TODO: set back to ON when done debugging messages through console
    WIN32_EXECUTABLE OFF
    MACOSX_BUNDLE ON
)
