# Standard CMake Setup
cmake_minimum_required(VERSION 3.25)

project(AudioProd VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Standard Qt Setup
find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Widgets
    # QuickWidgets
)

qt_standard_project_setup()
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/UIFiles)

qt_add_executable(AudioProd
    # Headers for classes
    headers/mainWindow.h

    # Resource file
    resources/resources.qrc

    # UI files
    UIFiles/mainWindow.ui
    
    # Sources for classes
    sources/mainWindow.cpp
    main.cpp
)

# Linking externals
target_link_libraries(AudioProd PRIVATE
    Qt6::Core
    Qt6::Widgets
    # Qt6::QuickWidgets
)

target_include_directories(AudioProd PRIVATE
    ${CMAKE_SOURCE_DIR}/headers
)

# Prevent the creation of a console window on Windows.
# Create an application bundle on macOS.
set_target_properties(AudioProd PROPERTIES
    # TODO: set back to ON when done debugging messages through console
    WIN32_EXECUTABLE OFF
    MACOSX_BUNDLE ON
)
