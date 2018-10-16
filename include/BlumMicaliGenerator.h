#ifndef KRYPTO_BLUM_MICALI_GENERATOR_H
#define KRYPTO_BLUM_MICALI_GENERATOR_H

#include <cstdint>

class BlumMicaliGenerator{
public:
    BlumMicaliGenerator(int root, int prime, int seed)
        : m_root(root)
        , m_prime(prime)
        , m_currentNumber(seed) {}
    template<typename Integral> Integral getNextBits(){
        Integral ret=0;
        int i = sizeof(Integral)*8;
        while(i--){
            int newNumber = 1;
            while(m_currentNumber--){
                newNumber = (newNumber*m_root) % m_prime;
            }
            m_currentNumber = newNumber;
            uint8_t resultBit = m_currentNumber <= (m_prime-1)/2 ? 0x1 : 0x0;
            ret |= resultBit<<i;
        }
        return ret;
    }
private:
    int m_root;
    int m_prime;
    int m_currentNumber;
};

#endif //KRYPTO_BLUM_MICALI_GENERATOR_H
