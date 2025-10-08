# Defines the application and links submodules and libraries to it

list(APPEND THIRD_PARTY
    TagLib::TagLib
    SndFile::sndfile
)

list(APPEND RESOURCE_SOURCES
    # Empty for now
)

qt_add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
)

qt_add_qml_module(${CMAKE_PROJECT_NAME}
    URI AudioProd.Main
    VERSION 1.0
    QML_FILES
        Main.qml
    RESOURCES
        ${RESOURCE_SOURCES}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    ${THIRD_PARTY}
)
