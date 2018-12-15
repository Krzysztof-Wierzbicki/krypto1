#include <ctime>
#include <cstdlib>

/*
    Calculates a^b mod m
*/
int moduloPow(int a, int b, int m)
{
    int result = 1;

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
bool isPrime(long long n, int k = 128)
{
    if (n == 2 || n == 3)
        return true;

    if (n <= 1 || n % 2 == 0)
        return false;

    int s = 0;
    int r = n - 1;

    while (r % 2 == 0)
    {
        s++;
        r /= 2;
    }

    srand (time(NULL));

    for(int i = 0; i < k; i++)
    {
        long long a = (rand() % n - 3) + 2;
        int x = moduloPow(a, r, n);

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

/*
    Generate an odd integer randomly

    Args:
        length: int - the length of the number to generate, in bits

    return an integer
*/
long long generatePrimeCandidate(int length)
{

}

long long generatePrime(int length = 1024)
{
    long long prime = 1;

    while(!isPrime(prime))
        prime = generatePrimeCandidate(length);

    return prime;
}

long long generateParameters()
{

}


