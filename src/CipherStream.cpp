#include <BlumMicaliGenerator.h>
#include "CipherInterface.h"

template<>
std::vector<uint8_t> CipherInterface::encrypt<CipherType::Stream>(const std::vector<uint8_t>& input){
    auto generator = dynamic_cast<BlumMicaliGenerator*>(m_key.get());
    std::vector<uint8_t> output;
    output.reserve(input.size());
    for(uint8_t in : input){
        output.push_back(generator->getNextBits<uint8_t >() ^ in);
    }
    return std::move(output);
}

template<>
std::vector<uint8_t> CipherInterface::decrypt<CipherType::Stream>(const std::vector<uint8_t>& input){}