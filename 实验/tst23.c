#include <stdio.h>
int main()
{

    int x;
    int y;
    int z;

    int money;
    scanf("%d", &money);
    int min = money * 3;
    int cnt = 0;

    for (int i = 1; i <= money / 5; i++)
    {
        for (int j = 1; j <= money / 3; j++)
        {
            for (int k = 1; k <= money; k++)
            {
                if (i * 5 + j * 3 + k == money)
                {
                    cnt++;
                    if (i + j + 3 * k < min)
                    {
                        min = i + j + 3 * k;
                        x = i;
                        y = j;
                        z = k * 3;
                    }
                }
            }
        }
    }

    printf("%d\n%d %d %d %d", cnt, x + y + z, x, y, z);

    return 0;
}