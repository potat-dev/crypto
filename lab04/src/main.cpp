#include <chrono>
#include <ctime>
#include <iostream>

#include "sha256.hpp"

int main(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        SHA256 sha;
        sha.update(argv[i]);
        std::cout << sha.hexdigest() << " - " << argv[i] << std::endl;
    }

    return EXIT_SUCCESS;
}
