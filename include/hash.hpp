#ifndef HASH_H_
#define HASH_H_

#include <string>
#include <stdexcept>

#include <openssl/evp.h>

#include "convert.hpp"


class HashTools {
public:
    static std::string md5(const std::string &src);
};

#endif