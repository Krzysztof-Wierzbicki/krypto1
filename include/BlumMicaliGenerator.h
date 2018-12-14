#ifndef KRYPTO_BLUM_MICALI_GENERATOR_H
#define KRYPTO_BLUM_MICALI_GENERATOR_H

#include <cstdint>
#include "KeyInterface.h"

// a^b mod m
static long fast_pow(long a, long b, long m){
    long r = 1;
    while(b){
        if(b%2){
            r = r*a % m;
        }
        b /= 2;
        a = a*a % m;
    }
    return r%m;
}

class BlumMicaliGenerator : public KeyInterface{
public:
    BlumMicaliGenerator(long root, long prime, long seed)
        : m_root(root)
        , m_prime(prime)
        , m_currentNumber(seed) {}
    template<typename Integral> Integral getNextBits(){
        Integral ret=0;
        int i = sizeof(Integral)*8;
        while(i--){
            m_currentNumber = fast_pow(m_root, m_currentNumber, m_prime);
            uint8_t resultBit = m_currentNumber <= (m_prime-1)/2 ? 0x1 : 0x0;
            ret |= resultBit<<i;
        }
        return ret;
    }
    int getNextBit();
private:
    long m_root;
    long m_prime;
    long m_currentNumber;
};

#endif //KRYPTO_BLUM_MICALI_GENERATOR_H
