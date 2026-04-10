#include <stdio.h>
#define N_M_MAX 500005

int range_sum[N_M_MAX];
int lowbit_i[N_M_MAX] = {0};

int lowbit(int x)
{
    return x & (-x);
}

void add(int x, int k, int n)
{
    int cur_i = x;
    while (cur_i <= n)
    {
        range_sum[cur_i] += k;
        cur_i = cur_i + lowbit_i[cur_i];
    }
}

int get_sum_1_to_x(int x)
{
    int cur_i = x;
    int sum = 0;
    while (cur_i >= 1)
    {
        sum += range_sum[cur_i];
        cur_i = cur_i - lowbit_i[cur_i];
    }
    return sum;
}

int get_sum_x_to_y(int x, int y)
{
    return get_sum_1_to_x(y) - get_sum_1_to_x(x - 1); // 注意是x-1,因为(a,b)=(1,b)-(1,a-1)
}

int main()
{

    int n, m;
    scanf("%d %d", &n, &m);

    // 预计算lowbit(i),防止重复计算
    for (int i = 1; i <= n; i++)
    {
        lowbit_i[i] = lowbit(i);
    }

    for (int i = 1; i <= n; i++)
    {

        int val;
        scanf("%d", &val);
        // 读取第i个等价于做一次add计算
        // 边读取边add比全读取完再求和节省大量时间
        add(i, val, n);
    }

    for (int i = 0; i < m; i++)
    {
        int op, x, y;
        scanf("%d %d %d", &op, &x, &y);
        if (op == 1)
        {
            add(x, y, n);
        }
        else
        {
            printf("%d\n", get_sum_x_to_y(x, y));
        }
    }

    return 0;
}
