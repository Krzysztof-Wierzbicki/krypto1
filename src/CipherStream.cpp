#include "CipherInterface.h"

template<>
std::vector<uint8_t> CipherInterface::encrypt(const std::vector<uint8_t>& input, StreamTag type){}

template<>
std::vector<uint8_t> CipherInterface::decrypt(const std::vector<uint8_t>& input, StreamTag type){}