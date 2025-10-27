list(APPEND THIRD_PARTY
    TagLib::TagLib
    SndFile::sndfile
    RtAudio::rtaudio
)

list(APPEND AUDIOPROD_HEADERS
    include/audioEngine.h
    include/audioController.h
)

list(APPEND AUDIOPROD_SOURCES
    src/audioEngine.cpp
    src/audioController.cpp
)

add_library(engine STATIC
    ${AUDIOPROD_HEADERS}
    ${AUDIOPROD_SOURCES}
)

target_include_directories(engine PUBLIC
    ${PROJECT_SOURCE_DIR}/src/core/engine/include
    ${PROJECT_SOURCE_DIR}/src/utils/include
)

target_link_libraries(engine PUBLIC
    ${THIRD_PARTY}
)
