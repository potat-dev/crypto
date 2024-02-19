#include <chrono>
#include <ctime>
#include <iostream>

#include "sha256.hpp"

int main(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        std::string hash = SHA256(argv[i]).hexdigest();
        std::cout << hash << " - " << argv[i] << std::endl;
    }

    return EXIT_SUCCESS;
}
