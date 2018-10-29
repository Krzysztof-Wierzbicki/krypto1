#ifndef DES_H
#define DES_H

#include <cstdint>

using namespace std;

class DES
{
public:
    DES() = default;
    DES(uint64_t key);

    void countSubKeys(uint64_t key);
    uint64_t encrypt(uint64_t block);
    uint64_t decrypt(uint64_t block);

private:
    void permutedChoice1(uint64_t &key);
    void shiftKey(uint64_t &key, uint8_t bits);
    uint64_t permutedChoice2(uint64_t key);

    uint64_t initialPermutation(uint64_t block);
    uint64_t expansionFunction(uint32_t block);
    void pBlocksPermutation(uint32_t &block);
    void finalPermutation(uint64_t &block);
    void feistelFunction(uint64_t &key, uint32_t &blockL, uint32_t &blockR);
    uint64_t algorithm(uint64_t block, bool mode);

private:
    uint64_t subKey[16];
};

#endif