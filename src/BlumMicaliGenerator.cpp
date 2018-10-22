#include "BlumMicaliGenerator.h"

int BlumMicaliGenerator::getNextBit(){
    int newNumber = 1;
    while(m_currentNumber--){
        newNumber = (newNumber*m_root) % m_prime;
    }
    m_currentNumber = newNumber;
    int resultBit = m_currentNumber <= (m_prime-1)/2 ? 1 : 0;

    return resultBit;
}