#include "crypto.hpp"

std::string
AESTools::encCTR(const std::string &key, const std::string &iv, const std::string &plaintext, const bitNumber bits) {
    std::string ciphertext;
    const unsigned char *keyBytes = reinterpret_cast<const unsigned char *>(key.c_str());
    const unsigned char *ivBytes = reinterpret_cast<const unsigned char *>(iv.c_str());
    const unsigned char *ciphertextBytes = reinterpret_cast<const unsigned char *>(plaintext.c_str());
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();

    ciphertext.resize(plaintext.size() + EVP_MAX_BLOCK_LENGTH);
    if (bits == AESTools::bitNumber::AES128)
        EVP_EncryptInit_ex(ctx, EVP_aes_128_ctr(), nullptr, keyBytes, ivBytes);
    else if (bits == AESTools::bitNumber::AES256)
        EVP_EncryptInit_ex(ctx, EVP_aes_256_ctr(), nullptr, keyBytes, ivBytes);
    else
        throw std::runtime_error("Invalid bits number requested for AESTools::encCTR().");

    int len;
    unsigned char *ciphertextStart = reinterpret_cast<unsigned char *>(&ciphertext[0]);
    EVP_EncryptUpdate(ctx, ciphertextStart, &len, ciphertextBytes, plaintext.size());

    int final_len = len;
    unsigned char *ciphertextFinal = reinterpret_cast<unsigned char *>(&ciphertext[len]);
    EVP_EncryptFinal_ex(ctx, ciphertextFinal, &len);
    final_len += len;

    EVP_CIPHER_CTX_free(ctx);
    ciphertext.resize(final_len);
    return ciphertext;
}

// Passthrough
std::string
AESTools::decCTR(const std::string &key, const std::string &iv, const std::string &ciphertext,
                 const bitNumber bits) {
    return encCTR(key, iv, ciphertext, bits);
}