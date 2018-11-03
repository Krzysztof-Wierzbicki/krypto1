#include "TrippleDes.h"
#include <deque>

TrippleDES::TrippleDES(uint64_t key1, uint64_t key2, uint64_t key3)
{
    des1.countSubKeys(key1);
    des2.countSubKeys(key2);
    des3.countSubKeys(key3);
}

std::vector<uint8_t> TrippleDES::encrypt(std::vector<uint8_t> dataBlock)
{
    return algorithm(dataBlock, true);
}

std::vector<uint8_t> TrippleDES::decrypt(std::vector<uint8_t> dataBlock)
{
    return algorithm(dataBlock, false);
}

std::vector<uint8_t> TrippleDES::algorithm(std::vector<uint8_t> dataBlock, bool mode)
{
    std::vector<uint8_t> result;

    for(uint32_t i = 0; i < dataBlock.size(); i = i + 8)
    {
        uint64_t block = 0;  
        
        for (uint32_t j = i; j < i + 8; j++)
        {
            block <<= 8;
            if (j < dataBlock.size())
            {
                block |= dataBlock[j];
            }
        }
        
        mode ? block = des1.encrypt(block) : block = des3.decrypt(block); 
        mode ? block = des2.decrypt(block) : block = des2.encrypt(block);
        mode ? block = des3.encrypt(block) : block = des1.decrypt(block);

        std::deque<uint8_t> tmpResult;
        for (uint32_t j = i + 8; j > i; j--)
        {
            uint8_t tmpChar = block & 0x00000000000000FF;
            if (j < dataBlock.size() + 1)
            {
                tmpResult.push_front(tmpChar);
            }
            block >>= 8;
        }
        result.insert(result.end(), tmpResult.begin(), tmpResult.end());
    }

    return result;
}
