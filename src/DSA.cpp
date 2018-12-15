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
bool isPrime(int n, int k = 128)
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

    for 
    {

    }
}




    # find r and s
    s = 0
    r = n - 1
    while r & 1 == 0:
        s += 1
        r //= 2
    # do k tests
    for _ in range(k):
        a = random.randrange(2, n - 1)
        x = pow(a, r, n)
        if x != 1 and x != n - 1:
            j = 1
            while j < s and x != n - 1:
                x = pow(x, 2, n)
                if x == 1:
                    return False
                j += 1
            if x != n - 1:
                return False
 
    return True