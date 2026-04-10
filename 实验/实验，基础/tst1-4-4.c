#include <stdio.h>
#include <math.h>

int main()
{

    const double pai = 3.1415926;

    double ans1 = (2 * sqrt(5) * (sqrt(6) + sqrt(3))) / (6.0 + 3.0);
    double ans2 = (log(5 * log(3)) - log(2)) / (sin(pai / 3));
    double ans3 = exp(3.0) + (log(105)) / (log(10));

    printf("%lf\n%lf\n%lf", ans1, ans2, ans3);
}