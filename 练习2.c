#include <stdio.h>
#include <stdlib.h>
int main()
{

    printf("输入a和n，中间空格隔开");
    int a, n;
    scanf("%d %d", &a, &n);
    int x = a;
    int sum = 0;
    for (int i = n; i >= 1; i--)
    {
        for (int cnt = 1; cnt <= n - i; cnt++)
        {
            x *= 10;
        }

        sum += i * x;
        x = a;
    }
    printf("%d", sum);

    return 0;
}