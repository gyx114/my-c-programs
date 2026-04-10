#include <stdio.h>

int main()
{

    int n, seed, a, b, m;
    scanf("%d %d %d %d %d", &n, &seed, &a, &b, &m);

    long long arr[n + 1];
    arr[0] = seed;
    for (int i = 1; i <= n; i++)
    {
        arr[i] = (a * arr[i - 1] + b) % m;
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%lld ", arr[i]);
    }

    return 0;
}
