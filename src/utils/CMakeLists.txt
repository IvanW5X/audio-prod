# Add the utilities library

list(APPEND UTILS_SOURCE_FILES
    common.h
    commands.h
    syncedQueue.h
)

add_library(utils STATIC
    ${UTILS_SOURCE_FILES}
)

target_include_directories(utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
