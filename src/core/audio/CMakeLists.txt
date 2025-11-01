list(APPEND THIRD_PARTY
    TagLib::TagLib
    SndFile::sndfile
    RtAudio::rtaudio
)

list(APPEND AUDIOPROD_HEADERS
    include/audioEngine.h
    include/audioController.h
    include/abstractAudioSource.h
    include/audioFileSource.h
    include/toneGenerator.h
)

list(APPEND AUDIOPROD_SOURCES
    src/audioEngine.cpp
    src/audioController.cpp
    src/audioFileSource.cpp
    src/toneGenerator.cpp
)

add_library(audio STATIC
    ${AUDIOPROD_HEADERS}
    ${AUDIOPROD_SOURCES}
)

target_include_directories(audio PUBLIC
    ${PROJECT_SOURCE_DIR}/src/core/audio/include
    ${PROJECT_SOURCE_DIR}/src/utils/include
)

target_link_libraries(audio PUBLIC
    ${THIRD_PARTY}
)
