#ifndef TRIPPLE_DES_H
#define TRIPPLE_DES_H

#include "Des.h"
#include <cstdint>

using namespace std;

class TrippleDES
{
public:
    TrippleDES(uint64_t key1, uint64_t key2, uint64_t key3);

    uint64_t encrypt(uint64_t block);
    uint64_t decrypt(uint64_t block);

private:
    DES des1;
    DES des2;
    DES des3;
};

#endif