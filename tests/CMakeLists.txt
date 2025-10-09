# TODO: add header for tests

if (NOT DEFINED ENV{CMAKE_GOOGLETEST_PATH})
    list(APPEND CMAKE_PREFIX_PATH
        "C:/libs/googletest"
    )
    message(STATUS "GoogleTest library path found at $ENV{CMAKE_GOOGLETEST_PATH}")
else()
    message(STATUS "GoogleTest library not found, set the env variable (CMAKE_GOOGLETEST_PATH)")
endif()

find_package(GTest REQUIRED)

add_executable(FirstTest
    firstTest.cpp
)

add_test(NAME example COMMAND FirstTest)

target_link_libraries(FirstTest PRIVATE
    GTest::GTest
)