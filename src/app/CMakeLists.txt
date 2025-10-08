# TODO: add header

list(APPEND THIRD_PARTY
    "TagLib::TagLib"
    # "SndFile::sndFile"
)

list(APPEND RESOURCE_SOURCES
    # Empty for now
)

qt_add_executable(AudioProd
    main.cpp
)

qt_add_qml_module(AudioProd
    URI AudioProd.Main
    VERSION 1.0
    QML_FILES
        Main.qml
    RESOURCES
        ${RESOURCE_SOURCES}
)

target_link_libraries(AudioProd PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    ${THIRD_PARTY}
)
