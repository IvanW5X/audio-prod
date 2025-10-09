list(APPEND AUDIOPROD_ENGINE_SOURCE_FILES
    audioEngine.h
    audioEngine.cpp
    audioController.h
    audioController.cpp
)

add_library(engine STATIC
    ${AUDIOPROD_ENGINE_SOURCE_FILES}
)

target_link_libraries(engine PRIVATE
    utils
)
