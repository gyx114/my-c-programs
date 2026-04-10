#include <stdio.h>
int isprime(int x);
int main()
{

    int n;
    scanf("%d", &n);
    int num[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", num + i);
    }
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (isprime(num[i]))
            sum += num[i];
    }

    printf("%d", sum);

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
        {
            return 0;
        }
    }

    return 1;
}