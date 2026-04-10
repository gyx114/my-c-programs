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

int main()
{

    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);

    node nodes[n + 1];
    line_set *lines[n + 1];

    for (int i = 1; i <= n; i++)
    {
        nodes[i].distance = INF;
        nodes[i].is_visited = 0;
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

    for (int i = 1; i <= n; i++)
    {
        printf("%d ", nodes[i].distance);
    }

    return 0;
}
