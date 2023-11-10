#ifndef AES_H_
#define AES_H_

#include <iostream>
#include <string>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <stdexcept>

#include "convert.hpp"


class AESTools {
public:
    enum BitNumber { AES128, AES256 };

    static std::string encCTR(const std::string &key, const std::string &iv, const std::string &plaintext,
                              const BitNumber bits = AES256);
    static std::string decCTR(const std::string &key, const std::string &iv, const std::string &ciphertext,
                              const BitNumber bits = AES256);
};

#endif