#ifndef KRYPTO_DSA_H
#define KRYPTO_DSA_H

#include <string>

class DSA
{
private:
    int moduloPow(int a, int b, int m);
    bool isPrime(long long n, int k);
    long long generatePrimeCandidate(int length);
    long long generatePrime(int length);
    void generateParameters(int N, int L);
    void generateUserKreys();
    void sign(std::string message);
    bool verify();

public:
    DSA();

private:
    long long p;
    long long g;
    long long q;

    long long publicKey;
    long long privateKey;
};

#endif //KRYPTO_DSA_H