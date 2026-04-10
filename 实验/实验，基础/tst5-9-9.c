#include <stdio.h>
#include <stdlib.h>
int main()
{

    int seed, n;
    scanf("%d %d", &seed, &n);
    srand(seed);
    int cnt = 0;
    double x, y;
    for (int i = 0; i < n; i++)
    {
        x = 1 + rand() / (double)RAND_MAX;
        y = rand() / (double)RAND_MAX;

        if (y <= 1.0 / x)
            cnt++;
    }

    printf("%lf", (double)cnt / n);

    return 0;
}