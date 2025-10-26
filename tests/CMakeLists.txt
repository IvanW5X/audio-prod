# CMake file for testing

list(APPEND THIRD_PARTY
    GTest::gtest_main
)

list(APPEND AUDIOPROD_LIBS
    engine
)

if (DEFINED ENV{CMAKE_GOOGLETEST_PATH})
    list(APPEND CMAKE_PREFIX_PATH
        $ENV{CMAKE_GOOGLETEST_PATH}
    )
    message(STATUS "GoogleTest library path found at $ENV{CMAKE_GOOGLETEST_PATH}")
else()
    message(STATUS "GoogleTest library not found, set the env variable (CMAKE_GOOGLETEST_PATH)")
endif()

find_package(GTest REQUIRED)

# Unit tests
add_executable(unitTests
    unit/initEngineTests.cpp
)

target_link_libraries(unitTests PRIVATE
    ${AUDIOPROD_LIBS}
    ${THIRD_PARTY}
)

include(GoogleTest)
gtest_discover_tests(unitTests)
