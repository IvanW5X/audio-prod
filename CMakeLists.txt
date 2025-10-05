# Standard CMake Setup
cmake_minimum_required(VERSION 3.25)

project(AudioProd VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-O3" CACHE STRING "Compiler flags")

set(CMAKE_AUTORCC ON CACHE BOOL "")
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/uiFiles CACHE FILEPATH "UI files directory")

if(DEFINED ENV{CMAKE_TAGLIB_PATH})
    set(CMAKE_PREFIX_PATH "$ENV{CMAKE_TAGLIB_PATH}")
    message(STATUS "TagLib library path found at $ENV{CMAKE_TAGLIB_PATH}")
else()
    message(STATUS "TagLib library not found, set the environment variable (CMAKE_TAGLIB_PATH)")
endif()

# Qt Setup
find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Widgets
    Multimedia
)

find_package(TagLib 2.1.1 REQUIRED)

qt_standard_project_setup()

set(AUDIOPROD_HEADERS
    utils/utils.h
    utils/commands.h
    utils/errorHandler.h
    utils/syncedQueue.h
    headers/audioEngine.h
    headers/mainWindow.h
    headers/audioController.h
    headers/audioPlayerWidget.h
)

set(AUDIOPROD_SOURCES
    sources/utils.cpp
    sources/errorHandler.cpp
    sources/audioEngine.cpp
    sources/mainWindow.cpp
    sources/audioController.cpp
    sources/audioPlayerWidget.cpp
    sources/main.cpp
)

set(AUDIOPROD_UI_FILES
    uiFiles/mainWindow.ui
    uiFiles/audioPlayerWidget.ui
)

set(AUDIOPROD_RESOURCES
    resources/resources.qrc
)

qt_add_executable(AudioProd
    ${AUDIOPROD_HEADERS}
    ${AUDIOPROD_SOURCES}
    ${AUDIOPROD_UI_FILES}
    ${AUDIOPROD_RESOURCES}    
)

target_link_libraries(AudioProd PUBLIC
    Qt6::Core
    Qt6::Widgets
    Qt6::Multimedia
    TagLib::TagLib
)

target_include_directories(AudioProd PRIVATE
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/headers
)

set_target_properties(AudioProd PROPERTIES
    # TODO: set back to ON when done debugging messages through console
    WIN32_EXECUTABLE OFF
    MACOSX_BUNDLE ON
)
