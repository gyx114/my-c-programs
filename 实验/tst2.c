#include <stdio.h>
int isprime(int x);
int main()
{

    int a;
    scanf("%d", &a);

    for (int i = 2; i <= a / 2; i++)
    {
        if (isprime(i) && isprime(a - i))
        {
            printf("%d %d", i, a - i);
            break;
        }
    }

    return 0;
}

int isprime(int x)
{

    if (x == 1)
        return 0;
    if (x == 2)
        return 1;

    for (int i = 2; i < x; i++)
    {
        if (x % i == 0)
            return 0;
    }
    return 1;
}