#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "sha256.hpp"

#define ITERS 1000

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
    std::srand(42);

    std::vector<std::string> passwords{"hello", "world", "\x00"};
    std::vector<uint8_t> hash_bits{8, 10, /*12, 14, 16*/};

    for (uint8_t bits : hash_bits) {
        std::cout << "Testing collisions for first " << (unsigned int)bits << " bits" << std::endl;

        for (std::string pass : passwords) {
            std::cout << "Testing for password: '" << pass << "'" << std::endl;
            hash_t pass_hash = SHA256(pass).head(bits);

            std::vector<uint64_t> arrN(ITERS);

            for (int i = 0; i < ITERS; i++) {
                std::vector<hash_t> hashes;  // "y1..yN" array

                while (true) {
                    std::string rand_pass = get_rand_pass();
                    hash_t rand_hash = SHA256(rand_pass).head(bits);

                    hashes.push_back(rand_hash);
                    if (rand_hash == pass_hash) {
                        // std::cout << "Found collision: '" << rand_pass << "'" << std::endl;
                        // std::cout << "Hashes: " << hashes.size() << std::endl;
                        arrN[i] = hashes.size();
                        break;
                    }
                }
            }

            auto avg = std::reduce(arrN.begin(), arrN.end()) / arrN.size();
            std::cout << "Average collision in: " << avg << " hashes" << std::endl;

            // std::cout << "Hash: " << sha.hexdigest() << std::endl;
            // std::cout << "Hash: " << sha.digest() << std::endl;
            // std::cout << "Head: " << sha.head(bits) << std::endl;
        }
    }
}
