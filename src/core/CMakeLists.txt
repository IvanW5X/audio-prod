# Defines the core application library for processing logic
# Links all necessary submodules into an interface for the main application

add_subdirectory(audio)

add_library(core INTERFACE)

target_link_libraries(core INTERFACE
    audio
)
