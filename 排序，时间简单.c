#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return (*(int *)a) - (*(int *)b);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int x[m];
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &x[i]);
    }
    qsort(x, m, sizeof(int), cmp);
    for (int i = 0; i < m; i++)
    {
        printf("%d", x[i]);
        if (i != m - 1)
            printf(" ");
    }
    return 0;
}