#include "CipherInterface.h"

template<>
std::vector<uint8_t> CipherInterface::encrypt<CipherType::DSA>(const std::vector<uint8_t>& input){}

template<>
std::vector<uint8_t> CipherInterface::decrypt<CipherType::DSA>(const std::vector<uint8_t>& input){}