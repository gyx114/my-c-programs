#include <stdio.h>
int main()
{

    float a;
    double b;
    scanf("%f %lf", &a, &b);
    printf("%f %e\n%lf %e", a, a, b, b);

    return 0;
}