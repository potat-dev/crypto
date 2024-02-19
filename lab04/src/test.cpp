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
    std::vector<uint8_t> hash_bits{8, 10, 12, 14, 16 /**/};

    for (uint8_t bits : hash_bits) {
        std::cout << "Testing collisions for first " << (unsigned int)bits << " bits" << std::endl;

        for (std::string pass : passwords) {
            std::cout << "Testing for password: '" << pass << "'" << std::endl;
            hash_t pass_hash = SHA256(pass).head(bits);

            std::vector<uint64_t> arrN(ITERS);
            std::vector<uint64_t> arrS(ITERS);

            for (int iter = 0; iter < ITERS; iter++) {
                std::vector<hash_t> hashes;  // "y1..yN" array

                while (true) {
                    std::string rand_pass = get_rand_pass();
                    hash_t rand_hash = SHA256(rand_pass).head(bits);

                    hashes.push_back(rand_hash);
                    if (rand_hash == pass_hash) {
                        arrN[iter] = hashes.size();
                        break;
                    }
                }

                for (int i = 0; i < hashes.size(); i++) {
                    bool found = false;

                    for (int j = i + 1; j < hashes.size(); j++) {
                        if (hashes[i] == hashes[j]) {
                            arrS[iter] = (2 * (hashes.size() - 1) - i) * i / 2 + (j - i);  // instead of count...
                            found = true;
                            break;
                        }
                    }

                    if (found) break;
                }
            }

            auto avgN = std::reduce(arrN.begin(), arrN.end()) / ITERS;
            auto avgS = std::reduce(arrS.begin(), arrS.end()) / ITERS;
            std::cout << "Average N: " << avgN << ", Average S: " << avgS << std::endl;
        }

        std::cout << std::endl;
    }
}
