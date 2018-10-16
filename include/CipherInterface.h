#ifndef KRYPTO_CIPHER_INTERFACE_H
#define KRYPTO_CIPHER_INTERFACE_H

#include <cstdint>
#include <vector>

enum class CipherType{
    DES,
    Stream,
    DSA,
};

class CipherInterface {
public:
    template<CipherType> std::vector<uint8_t> encrypt(const std::vector<uint8_t>& input);
    template<CipherType> std::vector<uint8_t> decrypt(const std::vector<uint8_t>& input);
};

#endif //KRYPTO_CIPHER_INTERFACE_H
