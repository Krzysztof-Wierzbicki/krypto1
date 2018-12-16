#include "DSAGenerator.h"
#include <ctime>
#include <cstdlib>

DSAGenerator::DSAGenerator(BigInteger p, BigInteger q)
: p(p), q(q)
{
    generateParameters();
}

BigInteger DSAGenerator::biRand(BigInteger a)
{
    return a / 2147483646;
}

/*
    Calculates a^b mod m
*/
BigInteger DSAGenerator::moduloPow(BigInteger a, BigInteger b, BigInteger m)
{
    BigInteger result = 1;

    while (b > 0)
    {
        if (b % 2 == 1)
            result = (result * a) % m; 

        b /= 2;
        a = a*a %m;
    }

    return result % m;
}

/*
    Run Miller-Rabin test to check if a number is prime
 
    Args:
        n: int - the number to test
        k: int - the number of tests to do
 
    return True if n is prime
*/
bool DSAGenerator::isPrime(BigInteger n, int k = 128)
{
    if (n == 2 || n == 3)
        return true;

    if (n <= 1 || n % 2 == 0)
        return false;

    int s = 0;
    BigInteger r = n - 1;

    while (r % 2 == 0)
    {
        s++;
        r /= 2;
    }

    srand (time(NULL));

    for(int i = 0; i < k; i++)
    {
        BigInteger a = rand() + 2;
        BigInteger x = moduloPow(a, r, n);

        if (x != 1 && x != n-1)
        {
            int j = 1;

            while (j < s && x != n-1)
            {
                x = moduloPow(x, 2, n);

                if (x==1)
                    return false;

                j++;    
            }

            if (x != n -1)
                return false;
        }
    }

    return true;
}

void DSAGenerator::generateParameters()
{
    BigInteger h = biRand(p-1);

    g = moduloPow(h, ((p-1)/q), p);

    privateKey = biRand(q);
    publicKey = moduloPow(g, privateKey, p);
}

BigInteger DSAGenerator::getG()
{
    return g;
}

BigInteger DSAGenerator::getPrivateKey()
{
    return privateKey;
}

BigInteger DSAGenerator::getPublicKey()
{
    return publicKey;
}