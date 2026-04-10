
// 功能：输出指定数量的素数

#include <stdio.h>
int isprime(int x, int known_primes[], int sum_of_known_primes);

int main()
{
    int n;
    printf("输入你要几个素数");
    scanf("%d", &n);
    printf("2\n");
    int primes[n];
    primes[0] = 2;
    int count = 1;
    for (int j = 3; count < n; j++)
    {
        if (isprime(j, primes, count))
        {
            primes[count] = j; // 可以合并为 primes[count++]=j;
            count++;
            printf("%d\n", j);
        }
    }

    return 0;
}

// 这是一个判断函数，通过已知的素数表known_primes[]来判断x是否为素数
// 是素数则返回0，不是则返回1

int isprime(int x, int known_primes[], int sum_of_known_primes)
{

    for (int i = 0; i < sum_of_known_primes; i++)
    {
        if (x % (known_primes[i]) == 0)
        {
            return 0;
        }
    }

    return 1;
}