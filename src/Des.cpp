#include "Des.h"
#include "DesTables.h"

DES::DES(uint64_t key)
{
    countSubKeys(key);
}

void DES::countSubKeys(uint64_t key)
{
    permutedChoice1(key);
    for (uint8_t i = 0; i < 16; i++)
    {
        shiftKey(key, SHIFT[i]);
        subKey[i] = permutedChoice2(key);
    }
}

uint64_t DES::encrypt(uint64_t block)
{
    return algorithm(block, true);
}

uint64_t DES::decrypt(uint64_t block)
{
    return algorithm(block, false);
}

void DES::permutedChoice1(uint64_t &key)
{
    uint64_t result = 0;
    for (uint8_t i = 0; i < 56; i++)
    {
        result <<= 1;
        result |= (key >> (64-PC1[i])) & MASK_64;
    }
    key = result;
}

void DES::shiftKey(uint64_t &key, uint8_t bits)
{
    uint32_t keyL = (uint32_t) ((key >> 28) & BI_MASK);
    uint32_t keyR = (uint32_t)  (key & BI_MASK);
    for (uint8_t i = 0; i < bits; i++)
    {
        keyL = (0x0fffffff & (keyL << 1)) | (0x00000001 & (keyL >> 27));
        keyR = (0x0fffffff & (keyR << 1)) | (0x00000001 & (keyR >> 27));
    }
    key = (((uint64_t) keyL) << 28) | (uint64_t) keyR;
}

uint64_t DES::permutedChoice2(uint64_t key)
{
    uint64_t result = 0;
    for (uint8_t i = 0; i < 48; i++)
    {
        result <<= 1;
        result |= (key >> (56-PC2[i])) & MASK_64;
    }
    return result;
}

uint64_t DES::initialPermutation(uint64_t block)
{
    uint64_t result = 0;
    for (uint8_t i = 0; i < 64; i++)
    {
        result <<= 1;
        result |= (block >> (64-IP[i])) & MASK_64;
    }
    return result;
}

uint64_t DES::expansionFunction(uint32_t block)
{
    uint64_t result = 0;
    for (uint8_t i = 0; i < 48; i++)
    {
        result <<= 1;
        result |= (uint64_t) (block >> (32-E[i])) & MASK_32;
    }
    return result;
}

void DES::pBlocksPermutation(uint32_t &block)
{
    uint32_t result = 0;
    for (uint8_t i = 0; i < 32; i++)
    {
        result <<= 1;
        result |= (block >> (32-PB[i])) & MASK_32;
    }
    block = result;
}

void DES::finalPermutation(uint64_t &block)
{
    uint64_t result = 0;
    for (uint8_t i = 0; i < 64; i++)
    {
        result <<= 1;
        result |= (block >> (64-FP[i])) & MASK_64;
    }
    block = result;
}

void DES::feistelFunction(uint64_t &key, uint32_t &blockL, uint32_t &blockR)
{
    uint64_t blockE = expansionFunction(blockR);

    // xor block with key
    blockE ^= key;

    uint32_t blockF = 0;
    for (uint8_t j = 0; j < 8; j++)
    {
        blockF <<= 4;
        
        // Outer bits
        char row = (char) ((blockE & (0x0000840000000000 >> 6*j)) >> (42-6*j));
        row = (row >> 4) | (row & 0x01);

        // Middle 4 bits of input
        char column = (char) ((blockE & (0x0000780000000000 >> 6*j)) >> (43-6*j));

        blockF |= (uint32_t) (SBOX[j][16*row + column] & 0x0F);
    }
    
    pBlocksPermutation(blockF);
    
    blockF = blockL ^ blockF;
    blockL = blockR;
    blockR = blockF;
}

uint64_t DES::algorithm(uint64_t block, bool mode)
{
    uint64_t blockIP = initialPermutation(block);
    uint32_t blockL = (uint32_t) (blockIP >> 32) & BI_MASK;
    uint32_t blockR = (uint32_t) (blockIP & BI_MASK);

    for (uint8_t i = 0; i < 16; i++)
        mode ? feistelFunction(subKey[i], blockL, blockR): feistelFunction(subKey[15-i], blockL, blockR);

    block = (((uint64_t) blockR) << 32) | (uint64_t) blockL;

    finalPermutation(block);

    return block;
}