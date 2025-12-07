include(FetchContent)

FetchContent_Declare(
    googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(tests test_stack.cpp)

target_link_libraries(tests DataStructures GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)