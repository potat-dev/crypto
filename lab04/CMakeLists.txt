cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

# packet manager

file(DOWNLOAD
     https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.7/CPM.cmake
     ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

# test

project(sha256_test)

add_executable(sha256_test src/test.cpp src/sha256.cpp)

# lab

project(sha256)

add_executable(sha256 src/lab.cpp src/sha256.cpp)

cpmaddpackage(NAME json GITHUB_REPOSITORY nlohmann/json VERSION 3.11.3)

target_link_libraries(sha256_test nlohmann_json::nlohmann_json)
