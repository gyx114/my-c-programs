#include <stdio.h>
#include <string.h>

#define MAX_NODE 100001

int run_father[MAX_NODE];
int mix_father[MAX_NODE];

int find(char *mode, int x)
{

    if (strcmp(mode, "run") == 0)
    {

        if (run_father[x] != x)
        {
            run_father[x] = find("run", run_father[x]);
        }
        return run_father[x];
    }

    if (strcmp(mode, "mix") == 0)
    {

        if (mix_father[x] != x)
        {
            mix_father[x] = find("mix", mix_father[x]);
        }
        return mix_father[x];
    }
}

void connect(char *mode, int u, int v)
{
    if (strcmp(mode, "run") == 0)
    {
        int u_root = find("run", u);
        int v_root = find("run", v);
        if (u_root != v_root)
        {
            run_father[u_root] = v_root;
        }
    }

    if (strcmp(mode, "mix") == 0)
    {
        int u_root = find("mix", u);
        int v_root = find("mix", v);
        if (u_root != v_root)
        {
            mix_father[u_root] = v_root;
        }
    }
}

int examine(int u, int v)
{
    if (find("run", u) == find("run", v))
    {
        return 1;
    }

    else if (find("mix", u) == find("mix", v))
    {
        return 2;
    }

    else
    {
        return -1;
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        run_father[i] = i;
        mix_father[i] = i;
    }

    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        connect("mix", u, v);
    }

    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        int op, u, v;
        scanf("%d %d %d", &op, &u, &v);
        ;
        if (op == 1)
        {
            connect("run", u, v);
            connect("mix", u, v);
        }
        else if (op == 3)
        {
            connect("mix", u, v);
        }
        else
        {
            printf("%d\n", examine(u, v));
        }
    }

    return 0;
}
