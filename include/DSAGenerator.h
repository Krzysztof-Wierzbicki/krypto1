#ifndef KRYPTO_DSA_GENERATOR_H
#define KRYPTO_DSA_GENERATOR_H

#include "BigInteger.h"

class DSAGenerator
{
private:
    BigInteger biRand(BigInteger a); 
    BigInteger moduloPow(BigInteger a, BigInteger b, BigInteger m);
    bool isPrime(BigInteger n, int k);
    BigInteger generatePrimeCandidate(int length);
    BigInteger generatePrime(int length);
    void generateParameters();

public:
    DSAGenerator(BigInteger p, BigInteger q);
    BigInteger getG();
    BigInteger getPrivateKey();
    BigInteger getPublicKey();

private:
    BigInteger p;
    BigInteger g;
    BigInteger q;
    BigInteger privateKey;
    BigInteger publicKey;
};

#endif //KRYPTO_DSA_GENERATOR_H