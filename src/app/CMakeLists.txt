# Defines the application and links submodules and libraries to it

list(APPEND THIRD_PARTY
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
)

list(APPEND QML_MODULE_FILES
    ui/Main.qml
)

list(APPEND RESOURCE_MODULE_SOURCES
    #empty for now
)

qt_add_executable(audioprod
    main.cpp
)

qt_add_qml_module(audioprod
    URI AudioProd.Main
    VERSION 1.0
    QML_FILES
        ${QML_MODULE_FILES}
    RESOURCES
        ${RESOURCE_MODULE_SOURCES}
)

target_link_libraries(audioprod PUBLIC
    ${THIRD_PARTY}
)
