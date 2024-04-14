#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>

#include <iostream>
#include <string>

// Генерация ключей RSA
RSA* generate_RSA_keys(int keylength) {
    RSA* rsa = RSA_new();
    BIGNUM* e = BN_new();

    BN_set_word(e, RSA_F4);
    RSA_generate_key_ex(rsa, keylength, e, NULL);

    BN_free(e);
    return rsa;
}

// Шифрование
std::string RSA_encrypt(RSA* rsa, const std::string& message) {
    std::string ciphertext(RSA_size(rsa), 0);
    int ciphertext_len = RSA_public_encrypt(message.size(), (unsigned char*)message.data(),
                                            (unsigned char*)ciphertext.data(), rsa, RSA_PKCS1_OAEP_PADDING);
    return ciphertext.substr(0, ciphertext_len);
}

// Дешифрование
std::string RSA_decrypt(RSA* rsa, const std::string& ciphertext) {
    std::string plaintext(RSA_size(rsa), 0);
    int plaintext_len = RSA_private_decrypt(ciphertext.size(), (unsigned char*)ciphertext.data(),
                                            (unsigned char*)plaintext.data(), rsa, RSA_PKCS1_OAEP_PADDING);
    return plaintext.substr(0, plaintext_len);
}

// Создание подписи
std::string create_signature(RSA* rsa, const std::string& message) {
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    EVP_PKEY* pkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pkey, rsa);

    EVP_DigestSignInit(mdctx, NULL, EVP_sha256(), NULL, pkey);
    EVP_DigestSignUpdate(mdctx, message.data(), message.size());

    size_t siglen;
    EVP_DigestSignFinal(mdctx, NULL, &siglen);

    std::string signature(siglen, 0);
    EVP_DigestSignFinal(mdctx, (unsigned char*)signature.data(), &siglen);

    EVP_MD_CTX_free(mdctx);
    return signature;
}

// Проверка подписи
bool verify_signature(RSA* rsa, const std::string& message, const std::string& signature) {
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    EVP_PKEY* pkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pkey, rsa);

    EVP_DigestVerifyInit(mdctx, NULL, EVP_sha256(), NULL, pkey);
    EVP_DigestVerifyUpdate(mdctx, message.data(), message.size());

    int result = EVP_DigestVerifyFinal(mdctx, (unsigned char*)signature.data(), signature.size());

    EVP_MD_CTX_free(mdctx);
    return result == 1;
}

int main() {
    RSA* rsa = generate_RSA_keys(2048);

    std::string message = "Hello, world!";
    std::string ciphertext = RSA_encrypt(rsa, message);
    std::string decrypted_message = RSA_decrypt(rsa, ciphertext);

    std::cout << "Original message: " << message << std::endl;
    // std::cout << "Ciphertext: " << ciphertext << std::endl;
    std::cout << "Decrypted message: " << decrypted_message << std::endl;

    std::string signature = create_signature(rsa, message);
    bool is_valid = verify_signature(rsa, message, signature);

    std::cout << "Signature is " << (is_valid ? "valid" : "invalid") << std::endl;

    RSA_free(rsa);
    return 0;
}
