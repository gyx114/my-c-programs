#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    int num = 0;

    int count = 0;
    int t = 0;
    int divi = 1;
    printf("输入一个正整数\n");
    scanf("%d", &num);
    int a = num;
    while (a != 0)
    {
        count += 1;
        a /= 10;
    }

    for (int i = count; i > 0; i--)
    {
        for (int s = 1; s < i; s++)
        {

            divi *= 10;
        }

        printf("%d\n", num / (divi)-10 * t);
        t = num / (divi);
        divi = 1;
    }

    return 0;
}