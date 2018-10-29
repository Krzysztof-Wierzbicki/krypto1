#ifndef TRIPPLE_DES_H
#define TRIPPLE_DES_H

#include "Des.h"
#include <cstdint>
#include <vector>

class TrippleDES
{
public:
    TrippleDES(uint64_t key1, uint64_t key2, uint64_t key3);

    std::vector<uint8_t> encrypt(std::vector<uint8_t> dataBlock);
    std::vector<uint8_t> decrypt(std::vector<uint8_t> dataBlock);

private:
    std::vector<uint8_t> algorithm(std::vector<uint8_t> dataBlock, bool mode);

private:
    DES des1;
    DES des2;
    DES des3;
};

#endif