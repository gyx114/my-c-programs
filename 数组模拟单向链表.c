#include <stdio.h>
int next[(int)1e6];

void insert(int x, int y)
{
    int tmp = next[x];
    next[x] = y;
    next[y] = tmp;
}

void inquire(int x)
{
    printf("%d\n", next[x]);
}

void del(int x)
{
    int tmp = next[x];
    next[x] = next[tmp];
}

void op()
{
    int w, x, y;
    scanf("%d", &w);
    if (w == 1)
    {
        scanf("%d %d", &x, &y);
        insert(x, y);
    }
    else if (w == 2)
    {
        scanf("%d", &x);
        inquire(x);
    }
    else
    {
        scanf("%d", &x);
        del(x);
    }
}

int main()
{

    next[1] = 0;
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        op();
    }

    return 0;
}
