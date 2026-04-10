#include <stdio.h>

#define N_M_MAX 500005
int lowbit_i[N_M_MAX];
int range_sum_of_diff[N_M_MAX] = {0};

int lowbit(int x)
{
    return (x & (-x));
}

void x_add(int x, int k, int n)
{
    // 第x位的差分+k
    int cur = x;
    while (cur <= n)
    {
        range_sum_of_diff[cur] += k;
        cur = cur + lowbit_i[cur];
    }
}

void x_to_y_all_add(int x, int y, int k, int n)
{

    // 区间[x,y]都加k，则[x+1,y]的差分都不变化,x的差分增加k，y+1的差分减少k
    x_add(x, k, n);
    x_add(y + 1, -k, n);
}

int get_x_val(int x)
{

    // 返回1到x的差分和(即为第x位的值)
    int cur = x;
    int sum = 0;
    while (cur >= 1)
    {
        sum += range_sum_of_diff[cur];
        cur = cur - lowbit_i[cur];
    }
    return sum;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
    {
        lowbit_i[i] = lowbit(i);
    }

    int val[n + 1];
    val[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &val[i]);
        int diff_i = val[i] - val[i - 1];
        x_add(i, diff_i, n);
    }

    for (int i = 0; i < m; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            int x, y, k;
            scanf("%d %d %d", &x, &y, &k);
            x_to_y_all_add(x, y, k, n);
        }
        else
        {
            int x;
            scanf("%d", &x);
            printf("%d\n", get_x_val(x));
        }
    }
}