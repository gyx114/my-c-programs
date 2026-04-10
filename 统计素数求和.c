// 求m和n区间内的素数个数并求和
#include <stdio.h>
int main()
{

    int m, n;
    int q = 0;
    int sum = 0;
    int count = 0;
    printf("输入范围，中间带一个空格");
    scanf("%d %d", &m, &n);

    for (int i = m; i <= n; i++)
    {
        q = 0;
        for (int x = 2; x < i; x++)
        {
            if (i % x == 0)
            {
                q = 1;
                break;
            }
        }
        if (q == 0 && i != 1)
        {
            printf("%d\n", i);
            count += 1;
            sum += i;
        }
    }

    printf("共有%d个素数，和为%d\n", count, sum);

    return 0;
}