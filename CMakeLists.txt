cmake_minimum_required(VERSION 3.14)
project(MatchingEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(DataStructures INTERFACE)

target_include_directories(DataStructures INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(CTest)
enable_testing()

add_subdirectory(test)