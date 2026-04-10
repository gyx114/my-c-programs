#include <stdio.h>
#include <math.h>
double f(int x)
{

    double up = 3 * pow(x, 2) + 4 * x + 5;
    double down = 7 * x + 13;
    printf("%.5lf ", up / down);
}
int main()
{

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        f(i);
    }
}