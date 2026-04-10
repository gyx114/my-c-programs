#include <stdio.h>
int main()
{

    float ans1 = 3.0 / 4 + 103 % 3;
    int ans2 = (int)3.8;
    int ans3 = (int)(-3.8) - 1;
    int ans4 = (int)3.2 + 1;
    int ans5 = (int)(-3.2);

    printf("%lf\n%lf\n%lf\n%lf\n%lf", ans1, (double)ans2, (double)ans3, (double)ans4, (double)ans5);

    return 0;
}