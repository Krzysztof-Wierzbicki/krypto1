#include "CipherInterface.h"

template<>
std::vector<uint8_t> CipherInterface::encrypt<CipherType::DES>(const std::vector<uint8_t>& input){
    std::vector<uint64_t> blocks;
    blocks.reserve(input.size()/8+1);
    uint64_t tmp=0;
    for(size_t i=0; i<input.size(); i++){
        tmp|=input[i]<<(8*(7-(i%8)));
        if(i%8==7){
            blocks.push_back(tmp);
            tmp=0;
        }
    }
    blocks.push_back(tmp);

    //wygląda głupio, ale działa
}

template<>
std::vector<uint8_t> CipherInterface::decrypt<CipherType::DES>(const std::vector<uint8_t>& input){}