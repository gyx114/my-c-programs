#include <stdio.h>

long long fast_pow_and_mod(int a, int n, int p)
{
    // 计算(a^n) mod p
    // 用long long,要不一乘就溢出了
    long long ans = 1;
    long long base = a % p;
    int tmp = n;
    while (tmp != 0)
    {
        if (1 & tmp)
        {
            ans = (ans * base) % p;
                }
        tmp = tmp >> 1;
        base = (base * base) % p;
    }

    return ans;
}

int main()
{
    int a, b, p;
    scanf("%d %d %d", &a, &b, &p);
    printf("%d^%d mod %d=%lld", a, b, p, fast_pow_and_mod(a, b, p));
    return 0;
}