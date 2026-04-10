#include <stdio.h>
int main()
{

    printf("输入两个数，中间隔一个空格");
    int a, b, t;
    scanf("%d %d", &a, &b);
    do
    {
        t = a % b;
        a = b;
        b = t;
    } while (b != 0);

    printf("最大公约数是%d", a);

    return 0;
}