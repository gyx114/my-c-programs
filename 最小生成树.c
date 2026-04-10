#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int u;
    int v;
    int len;
} uvline;

int compare(const void *a, const void *b)
{
    return (((uvline *)a)->len - ((uvline *)b)->len);
}

int find(int *father, int x)
{
    if (father[x - 1] != x)
    {
        father[x - 1] = find(father, father[x - 1]);
    }
    return father[x - 1];
}

void combine(int *father, int u, int v)
{
    int u_dad = find(father, u);
    int v_dad = find(father, v);
    if (u_dad != v_dad)
    {
        father[u_dad - 1] = v_dad;
    }
}

int check(int *father, int u, int v)
{
    int u_dad = find(father, u);
    int v_dad = find(father, v);
    return (u_dad == v_dad);
}

int main()
{

    int n, m;
    scanf("%d %d", &n, &m);
    int father[n];
    for (int i = 0; i < n; i++)
    {
        father[i] = i + 1;
    }

    uvline lines[m];
    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        lines[i].len = z;
        lines[i].u = x;
        lines[i].v = y;
    }

    if (m < n - 1)
    {
        printf("orz");
        return 0;
    }

    else
    {
        // 将边按长度从小到大排序
        qsort(lines, m, sizeof(uvline), compare);
        int total_len = 0;
        int cnt = 0;
        int is_ok = 0;
        for (int i = 0; i < m; i++)
        {
            if (!check(father, lines[i].u, lines[i].v))
            {
                total_len += lines[i].len;
                cnt++;
                combine(father, lines[i].u, lines[i].v);
            }

            if (cnt == n - 1)
            {

                is_ok = 1;
                break;
            }
        }

        if (is_ok)
        {
            printf("%d", total_len);
        }
        else
        {
            printf("orz");
        }
    }

    return 0;
}