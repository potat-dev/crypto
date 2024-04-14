cmake_minimum_required(VERSION 3.10)

project(rsa)

add_executable(rsa
    src/main.cpp
)

find_package(OpenSSL)

target_link_libraries(rsa PUBLIC OpenSSL::SSL OpenSSL::Crypto)
