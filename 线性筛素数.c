#include <stdio.h>
#include <stdlib.h>

#define MAX_RANGE 100000000
#define MAX_PRIME 6000000

char is_prime[MAX_RANGE + 1];
int primes[MAX_PRIME];

void generate_primes_table(int range);
int main()
{

    // 查询范围为1至range，查询n次

    int range, n;
    scanf("%d %d", &range, &n);
    generate_primes_table(range);
    for (int i = 0; i < n; i++)
    {
        int k;
        scanf("%d", &k);
        // 输出第k个素数
        printf("%d\n", primes[k - 1]);
    }

    return 0;
}

void generate_primes_table(int range)
{

    for (int i = 0; i <= range; i++)
    {
        is_prime[i] = 1;
    }
    is_prime[0] = 0;
    is_prime[1] = 0;
    int cnt = 0;

    for (int i = 2; i <= range; i++)
    {

        if (is_prime[i])
        {
            primes[cnt++] = i;
        }

        for (int j = 0; j < cnt; j++)
        {
            long long tmp = (long long)i * (long long)primes[j];
            if (tmp > range)
                break;
            is_prime[tmp] = 0;
            if (i % primes[j] == 0)
                break;
        }
    }
}