
// n个人获奖s个
// 总分高靠前，总分一样比高数，高数一样学号小的靠前
// 最后按学号递增输出

// 练习冒泡排序

#include <stdio.h>
int main()
{

    int n, s;
    scanf("%d %d", &n, &s);

    int sample[n][4];
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &sample[i][0], &sample[i][1], &sample[i][2]);
        sample[i][3] = sample[i][1] + sample[i][2];
    }
    for (int i = 0; i < n - 1; i++)
    {
        int swapped = 0;

        for (int j = 0; j < n - 1 - i; j++)
        {
            int x = (sample[j][3] < sample[j + 1][3]);
            int y = (sample[j][3] == sample[j + 1][3] && sample[j][1] < sample[j + 1][1]);
            int z = (sample[j][3] == sample[j + 1][3] && sample[j][1] == sample[j + 1][1] && sample[j][0] > sample[j + 1][0]);
            if (x || y || z)
            {

                int tmp[4];

                for (int t = 0; t < 4; t++)
                {
                    tmp[t] = sample[j][t];
                    sample[j][t] = sample[j + 1][t];
                    sample[j + 1][t] = tmp[t];
                }

                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }

    int winner[s];
    for (int i = 0; i < s; i++)
    {
        winner[i] = sample[i][0];
    }

    for (int i = 0; i < s - 1; i++)
    {
        int swapped = 0;
        for (int j = 0; j < s - 1 - i; j++)
        {
            if (winner[j] > winner[j + 1])
            {
                int tmp = winner[j];
                winner[j] = winner[j + 1];
                winner[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }

    for (int i = 0; i < s; i++)
    {
        printf("%d\n", winner[i]);
    }

    return 0;
}