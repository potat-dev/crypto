#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "sha256.hpp"

std::string get_rand_pass() {
    int length = std::rand() % 32 + 1;  // random length between 1 and 32
    std::string password;
    password.reserve(length);  // reserve memory in advance

    for (int i = 0; i < length; i++) {
        char randomChar = '!' + (std::rand() % (126 - '!' + 1));  // generate a random printable ASCII character
        password += randomChar;
    }

    return password;
}

int main(int argc, char** argv) {
    // std::srand(std::time(0));
    std::srand(42);

    std::vector<std::string> passwords{"hello", "world", "\x00\x00\x00"};
    std::vector<uint8_t> hash_bits{8, /*10, 12, 14,*/ 16};

    for (uint8_t bits : hash_bits) {
        std::cout << "Testing collisions for first " << (unsigned int)bits << " bits" << std::endl;

        for (std::string pass : passwords) {
            std::cout << "Testing for password: '" << pass << "'" << std::endl;

            SHA256 sha;
            sha.update(pass);
            hash16_t pass_hash = sha.head(bits);

            std::vector<hash16_t> hashes;  // "y1..yN" array

            while (true) {
                std::string rand_pass = get_rand_pass();

                SHA256 sha;
                sha.update(rand_pass);
                hash16_t rand_hash = sha.head(bits);

                hashes.push_back(rand_hash);
                if (rand_hash == pass_hash) {
                    std::cout << "Found collision: '" << rand_pass << "'" << std::endl;
                    std::cout << "Hashes: " << hashes.size() << std::endl;
                    break;
                }
            }

            std::cout << "Hash: " << sha.hexdigest() << std::endl;
            std::cout << "Hash: " << sha.digest() << std::endl;
            std::cout << "Head: " << sha.head(bits) << std::endl;
        }
    }
}
