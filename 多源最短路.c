

// 本程序由单元最短路升级而来
// 具体体现在封装成了函数，并且把单向边转换成了双向
// 注意的是，由于要多次执行单元最短路函数
// 用于显示节点状态的数组需要每次都更新（因为每次调用函数时起始点都不同）
// 因此节点数组在函数内定义，每次调用时都会重新定义
// 但是表示边的链表数组不会变化，因而在main函数中定义即可

#include <stdio.h>
#include <stdlib.h>

#define INF 2147483647

typedef struct
{
    int u;
    int v;
    int len;
} line;

typedef struct
{
    int distance;
    int is_visited;
} node;

typedef struct a
{
    line a_line;
    struct a *next;
} line_set;

int *get_min_distance(int n, int m, int s, line_set **lines)
{
    node nodes[n + 1];
    for (int i = 1; i <= n; i++)
    {
        nodes[i].distance = INF;
        nodes[i].is_visited = 0;
    }

    nodes[s].distance = 0;
    int now = s;

    for (int j = 0; j < n; j++)
    {
        nodes[now].is_visited = 1;
        line_set *tmp = lines[now];
        while (tmp)
        {
            int current_distance = tmp->a_line.len + nodes[now].distance;
            if (current_distance < nodes[tmp->a_line.v].distance)
            {
                nodes[tmp->a_line.v].distance = current_distance;
            }
            tmp = tmp->next;
        }

        int min_diatance = INF;
        now = -1;
        for (int i = 1; i <= n; i++)
        {
            if (!nodes[i].is_visited && nodes[i].distance < min_diatance)
            {
                min_diatance = nodes[i].distance;
                now = i;
            }
        }
        if (now == -1)
            break;
    }
    int *ans = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++)
    {
        ans[i] = nodes[i].distance;
    }
    return ans;
}

int main()
{

    int n, m;
    scanf("%d %d", &n, &m);

    line_set *lines[n + 1];

    for (int i = 1; i <= n; i++)
    {

        lines[i] = NULL;
    }
    for (int i = 0; i < m; i++)
    {
        int u, v, len;
        scanf("%d %d %d", &u, &v, &len);

        line_set *now = (line_set *)malloc(sizeof(line_set));
        now->a_line.u = u;
        now->a_line.v = v;
        now->a_line.len = len;
        now->next = NULL;
        if (lines[u])
        {
            now->next = lines[u];
            lines[u] = now;
        }
        else
        {
            lines[u] = now;
        }
        now = (line_set *)malloc(sizeof(line_set));
        now->a_line.u = v;
        now->a_line.v = u;
        now->a_line.len = len;
        now->next = NULL;
        if (lines[v])
        {
            now->next = lines[v];
            lines[v] = now;
        }
        else
        {
            lines[v] = now;
        }
    }
    int arr[n + 1][n + 1];
    for (int i = 1; i <= n; i++)
    {
        int *ans_i = get_min_distance(n, m, i, lines);
        for (int j = 1; j <= i; j++)
        {
            int x = ans_i[j];
            if (x == INF)
                x = -1;
            arr[i][j] = arr[j][i] = x;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}
