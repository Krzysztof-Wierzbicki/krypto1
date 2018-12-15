#ifndef KRYPTO_CIPHER_INTERFACE_H
#define KRYPTO_CIPHER_INTERFACE_H

#include <cstdint>
#include <vector>
#include <memory>
#include "KeyInterface.h"

enum class CipherType{
    DES,
    Stream,
    DSA,
};

class CipherInterface {
public:
    template<CipherType> std::vector<uint8_t> encrypt(const std::vector<uint8_t>& input);
    template<CipherType> std::vector<uint8_t> decrypt(const std::vector<uint8_t>& input);
    void setKey(std::unique_ptr<KeyInterface> key){ m_key = std::move(key); }
private:
    std::unique_ptr<KeyInterface> m_key;
};

#endif //KRYPTO_CIPHER_INTERFACE_H
