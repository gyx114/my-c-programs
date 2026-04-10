#include <stdio.h>
#include <math.h>
int main()
{

    int n;
    scanf("%d", &n);

    double pai = 0;
    double a_k;
    int k = 1;
    while (1)
    {

        a_k = 4.0 / (2 * k - 1);
        if (a_k <= 4 * pow(10, -n))
        {
            printf("%lf", pai);
            break;
        }
        else
        {
            if (k % 2 == 0)
            {
                pai -= a_k;
            }
            else
            {
                pai += a_k;
            }
        }
        k++;
    }

    return 0;
}