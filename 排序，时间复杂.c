#include <stdio.h>
int main()
{
    // m个数，每个数不大于n
    int n, m;
    scanf("%d %d", &n, &m);
    int x[m];
    int y[m];
    for (int i = 0; i < m; i++)
    {
        scanf("%d", x + i);
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (x[j] == i)
            {
                y[cnt] = i;
                cnt++;
            }
        }
    }

    for (int i = 0; i < m - 1; i++)
    {
        printf("%d ", y[i]);
    }
    printf("%d", y[m - 1]);

    return 0;
}