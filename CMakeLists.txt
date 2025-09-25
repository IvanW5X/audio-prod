# Standard CMake Setup
cmake_minimum_required(VERSION 3.25)

project(AudioProd VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Standard Qt Setup
find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Widgets
    Multimedia
)

qt_standard_project_setup()
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/uiFiles)

qt_add_executable(AudioProd
    # Resource file
    resources/resources.qrc

    # Headers for classes
    headers/mainWindow.h
    headers/audioPlayer.h
    headers/audioController.h
    headers/waveForm.h

    # UI files
    uiFiles/mainWindow.ui
    uiFiles/audioPlayer.ui
    uiFiles/audioController.ui
    uiFiles/waveForm.ui
    
    # Sources for classes
    sources/mainWindow.cpp
    sources/audioPlayer.cpp
    sources/audioController.cpp
    sources/waveForm.cpp
    main.cpp
)

# Linking externals
target_link_libraries(AudioProd PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Multimedia
)

target_include_directories(AudioProd PRIVATE
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_SOURCE_DIR}/utils
)

# Prevent the creation of a console window on Windows.
# Create an application bundle on macOS.
set_target_properties(AudioProd PROPERTIES
    # TODO: set back to ON when done debugging messages through console
    WIN32_EXECUTABLE OFF
    MACOSX_BUNDLE ON
)
