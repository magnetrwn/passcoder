#include "hash.hpp"

std::string HashTools::md5(const std::string &src) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int mdLen;

    OpenSSL_add_all_digests();
    md = EVP_get_digestbyname("md5");

    if (!md)
        throw std::runtime_error("Unable to initialize HashTools::md5 digest.");

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, src.c_str(), src.size());
    EVP_DigestFinal_ex(mdctx, digest, &mdLen);
    EVP_MD_CTX_free(mdctx);

    std::string output;
    output.reserve(mdLen);
    for (unsigned char c : digest)
        output.push_back(c);

    return StringUtils::toHex(output);
}