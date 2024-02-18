cmake_minimum_required(VERSION 3.10)

project(SHA256)

add_executable(SHA256
    src/main.cpp
    src/sha256.cpp
)

project(SHA256-Test)

add_executable(SHA256-Test
    src/test.cpp
    src/sha256.cpp
)