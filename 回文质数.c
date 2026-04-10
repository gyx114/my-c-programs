#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int huiwen[1000000];

int is_prime(int x)
{
    if (x == 1)
        return 0;
    if (x == 2)
        return 1;
    if (x == 3)
        return 1;
    for (int i = 2; i <= sqrt(x); i++)
    {
        if (x % i == 0)
            return 0;
    }
    return 1;
}

int main()
{

    huiwen[0] = 2;
    huiwen[1] = 3;
    huiwen[2] = 5;
    huiwen[3] = 7;
    int sum = 4;
    for (int i = 1; i <= 9; i += 2)
    {
        huiwen[sum++] = 10 * i + i;
    }
    for (int i = 1; i <= 9; i += 2)
    {
        for (int j = 0; j <= 9; j++)
        {
            huiwen[sum++] = i * 100 + j * 10 + i;
        }
    }
    for (int i = 1; i <= 9; i += 2)
    {
        for (int j = 0; j <= 9; j++)
        {
            huiwen[sum++] = i * 1000 + j * 100 + j * 10 + i;
        }
    }
    for (int i = 1; i <= 9; i += 2)
    {
        for (int j = 0; j <= 9; j++)
        {
            for (int k = 0; k <= 9; k++)
            {
                huiwen[sum++] = i * 10000 + j * 1000 + k * 100 + j * 10 + i;
            }
        }
    }
    for (int i = 1; i <= 9; i += 2)
    {
        for (int j = 0; j <= 9; j++)
        {
            for (int k = 0; k <= 9; k++)
            {
                huiwen[sum++] = i * 100000 + j * 10000 + k * 1000 + k * 100 + j * 10 + i;
            }
        }
    }
    for (int i = 1; i <= 9; i += 2)
    {
        for (int j = 0; j <= 9; j++)
        {
            for (int k = 0; k <= 9; k++)
            {
                for (int l = 0; l <= 9; l++)
                {
                    huiwen[sum++] = i * 1000000 + j * 100000 + k * 10000 + l * 1000 + k * 100 + j * 10 + i;
                }
            }
        }
    }
    for (int i = 1; i <= 9; i += 2)
    {
        for (int j = 0; j <= 9; j++)
        {
            for (int k = 0; k <= 9; k++)
            {
                for (int l = 0; l <= 9; l++)
                {
                    huiwen[sum++] = i * 10000000 + j * 1000000 + k * 100000 + l * 10000 + l * 1000 + k * 100 + j * 10 + i;
                }
            }
        }
    }

    int a, b;
    scanf("%d %d", &a, &b);
    int i = 0;
    while (huiwen[i] < a)
    {
        i++;
    }
    while (i < sum && huiwen[i] <= b)
    {
        if (is_prime(huiwen[i]))
        {
            printf("%d\n", huiwen[i]);
        }
        i++;
    }

    return 0;
}
