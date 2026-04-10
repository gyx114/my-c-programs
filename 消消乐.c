#include <stdio.h>

void check(int *plate, int len);

int main()
{
    int m, n;
    scanf("%d %d", &n, &m);
    int plate[n][m];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &plate[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        check(plate[i], m);
    }

    for (int i = 0; i < m; i++)
    {
        int tmp[n];
        for (int j = 0; j < n; j++)
        {
            tmp[j] = plate[j][i];
        }

        check(tmp, n);

        for (int x = 0; x < n; x++)
        {
            plate[x][i] = tmp[x];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (plate[i][j] > 100)
                plate[i][j] = 0;
            printf("%d ", plate[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void check(int *plate, int len)
{
    int cnt = 1;
    for (int i = 0; i < len - 1; i++)
    {
        // if (plate[i+1]%100 == plate[i]%100)
        if (plate[i + 1] == plate[i] || plate[i + 1] == plate[i] + 100 || plate[i + 1] + 100 == plate[i])
        {
            cnt++;
        }
        else
        {
            if (cnt >= 3)
            {
                for (int k = i; k > i - cnt; k--)
                {
                    if (plate[k] < 100)
                        plate[k] += 100;
                }
            }

            cnt = 1;
        }
    }
    if (cnt >= 3)
    {
        for (int k = len - 1; k > len - cnt - 1; k--)
        {
            if (plate[k] < 100)
                plate[k] += 100;
        }
    }
}