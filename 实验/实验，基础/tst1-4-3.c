#include <stdio.h>
#include <math.h>

int main()
{

    const double pai = 3.1415926;

    double ans1 = sqrt((1 - cos(pai / 3)) / 2.0);
    double ans2 = pow(sin(pai / 4), 2) + (sin(pai / 4)) * (cos(pai / 4)) - pow(cos(pai / 4), 2);

    printf("%lf\n%lf", ans1, ans2);
}