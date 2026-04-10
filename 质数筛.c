#include <stdio.h>
int isprime(int x);
int main()
{
    int n;
    scanf("%d", &n);
    int num[n];
    int prime[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", num + i);
    }
    int a = 0;
    for (int i = 0; i < n; i++)
    {
        if (isprime(num[i]))
        {

            prime[a] = num[i];
            a++;
        }
    }

    for (int i = 0; i < a - 1; i++)
    {
        printf("%d ", prime[i]);
    }
    printf("%d", prime[a - 1]);

    return 0;
}

int isprime(int x)
{
    if (x == 2)
        return 1;
    for (int i = 2; i < x; i++)
    {
        if (x % i == 0)
        {
            return 0;
        }
    }

    return 1;
}