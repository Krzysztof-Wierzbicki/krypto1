#ifndef KRYPTO_CIPHER_INTERFACE_H
#define KRYPTO_CIPHER_INTERFACE_H

#include <cstdint>
#include <vector>

enum class CipherType{
    DES,
    Stream,
    DSA,
};

struct CipherTag {};
struct DESTag : CipherTag {};
struct StreamTag : CipherTag{};
struct DSATag : CipherTag{};

class CipherInterface {
public:
    template<class Tag> std::vector<uint8_t> encrypt(const std::vector<uint8_t>& input, Tag type){}
    template<class Tag> std::vector<uint8_t> decrypt(const std::vector<uint8_t>& input, Tag type){}
};

#endif //KRYPTO_CIPHER_INTERFACE_H
