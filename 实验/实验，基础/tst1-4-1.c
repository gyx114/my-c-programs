#include <stdio.h>
int main()
{

    double tmp = 5.0;
    for (int i = 0; i < 3; i++)
    {
        tmp = 1 + 1 / tmp;
    }
    printf("%lf", tmp);

    return 0;
}