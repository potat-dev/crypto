cmake_minimum_required(VERSION 3.10)

file(
    DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.7/CPM.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
)

include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

project(sha256)

add_executable(sha256
    src/main.cpp
    src/sha256.cpp
)

project(sha256-Test)

add_executable(sha256_test
    src/test.cpp
    src/sha256.cpp
)

CPMAddPackage(
    NAME matplotplusplus
    GITHUB_REPOSITORY alandefreitas/matplotplusplus
    GIT_TAG v1.2.0
)

target_link_libraries(sha256_test PUBLIC matplot)
