#include <stdio.h>

typedef struct
{
    int x;
    int y;
} point;

typedef struct
{
    point zuoxia;
    int len_x;
    int len_y;
} carpet;

int is_covered(point a, carpet carpet_i)
{
    int x = a.x - carpet_i.zuoxia.x;
    int y = a.y - carpet_i.zuoxia.y;
    if (x >= 0 && x <= carpet_i.len_x && y >= 0 && y <= carpet_i.len_y)
    {
        return 1;
    }
    return 0;
}

int main()
{

    int n;
    int which_one = -1;
    scanf("%d", &n);
    carpet carpets[n + 1];
    for (int i = 1; i <= n; i++)
    {
        int a, b, x, y;
        scanf("%d %d %d %d", &a, &b, &x, &y);
        point zuoxia;
        zuoxia.x = a;
        zuoxia.y = b;
        carpet carpet_i;
        carpet_i.zuoxia = zuoxia;
        carpet_i.len_x = x;
        carpet_i.len_y = y;
        carpets[i] = carpet_i;
    }
    point a;
    scanf("%d %d", &(a.x), &(a.y));
    for (int i = n; i >= 1; i--)
    {
        if (is_covered(a, carpets[i]))
        {
            printf("%d", i);
            return 0;
        }
    }
    printf("-1");
    return 0;
}
