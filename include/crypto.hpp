#ifndef CRYPTO_H_
#define CRYPTO_H_

#include <iostream>
#include <string>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <stdexcept>

class AESTools {
public:
    enum bitNumber
    { AES128, AES256 };
    static std::string encCTR(const std::string &key, const std::string &iv, const std::string &plaintext,
                              const bitNumber bits = AES256);
    static std::string decCTR(const std::string &key, const std::string &iv, const std::string &ciphertext,
                              const bitNumber bits = AES256);
};

#endif