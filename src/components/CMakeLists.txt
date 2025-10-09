# Library for custom components, Could be used for more in future

list(APPEND QML_MODULE_FILES

)

list(APPEND RESOURCE_MODULE_FILES

)

qt_add_qml_module(AudioProdComponents
    URI AudioProd.Components
    VERSION 1.0
    QML_FILES
        ${QML_MODULE_FILES}
    RESOURCES
        ${RESOURCE_MODULE_FILES}
)