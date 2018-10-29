#include "TrippleDes.h"

TrippleDES::TrippleDES(uint64_t key1, uint64_t key2, uint64_t key3)
{
    des1.countSubKeys(key1);
    des2.countSubKeys(key2);
    des3.countSubKeys(key3);
}

uint64_t TrippleDES::encrypt(uint64_t block)
{
    block = des1.encrypt(block);
    block = des2.decrypt(block);
    block = des3.encrypt(block);

    return block;
}

uint64_t TrippleDES::decrypt(uint64_t block)
{
    block = des1.decrypt(block);
    block = des2.encrypt(block);
    block = des3.decrypt(block);

    return block;
}