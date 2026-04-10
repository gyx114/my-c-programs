#include <stdio.h>
long long f(int x);
int main()
{

    int n;
    scanf("%d", &n);

    printf("%lld", f(n));

    return 0;
}

long long f(int x)
{

    long long f_x[40];
    f_x[1] = 1;
    f_x[2] = 2;
    f_x[3] = 4;
    for (int i = 4; i <= x; i++)
    {
        f_x[i] = f_x[i - 1] + f_x[i - 2] + f_x[i - 3];
    }
    return f_x[x];
}