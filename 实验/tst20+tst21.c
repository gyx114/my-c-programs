#include <stdio.h>
#include <math.h>

double f(int x);
int main()
{

    int n;
    scanf("%d", &n);
    int x[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", x + i);
    }
    double ans;
    for (int i = 0; i < n; i++)
    {
        ans = f(x[i]);
        if (fabs(ans - (int)ans) < 1e-10)
            printf("%d ", (int)ans);
        else
        {
            printf("%.5lf ", ans);
        }
    }

    return 0;
}

double f(int x)
{

    if (x < -2000)
        return (2 * x - 1);
    else if (x >= 2000)
        return (sqrt(x));
    else
        return x * x;
}