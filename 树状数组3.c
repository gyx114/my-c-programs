#include <stdio.h>

#define N_M_MAX 500005
typedef long long ll;
ll lowbit_i[N_M_MAX];
ll range_sum_of_diff[N_M_MAX] = {0};
ll range_sum_of_plussed_diff[N_M_MAX] = {0};

ll lowbit(ll x)
{
    return (x & (-x));
}

void x_add(ll x, ll k, ll n)
{
    // 第x位的差分+k,(差分*x)应该增加 k*x
    ll cur = x;
    while (cur <= n)
    {
        ll tmp = k * x;
        range_sum_of_diff[cur] += k;
        range_sum_of_plussed_diff[cur] += tmp;
        cur = cur + lowbit_i[cur];
    }
}

void x_to_y_all_add(ll x, ll y, ll k, ll n)
{

    // 区间[x,y]都加k，则[x+1,y]的差分都不变化,x的差分增加k，y+1的差分减少k
    // （差分*x）做相应改变
    x_add(x, k, n);
    x_add(y + 1, -k, n);
}

ll get_one_to_n_val_sum(ll n)
{

    // 返回1到n位的值之和
    ll cur = n;
    ll val_n = 0;
    ll total_sum_of_plussed_diff = 0;

    while (cur >= 1)
    {
        val_n += range_sum_of_diff[cur];
        total_sum_of_plussed_diff += range_sum_of_plussed_diff[cur];
        cur = cur - lowbit_i[cur];
    }
    ll ans = (n + 1) * val_n - total_sum_of_plussed_diff;
    return ans;
}

ll get_x_to_y_val_sum(ll x, ll y)
{
    return get_one_to_n_val_sum(y) - get_one_to_n_val_sum(x - 1);
}

int main()
{
    ll n, m;
    scanf("%lld %lld", &n, &m);

    for (ll i = 1; i <= n; i++)
    {
        lowbit_i[i] = lowbit(i);
    }

    ll val[n + 1];
    val[0] = 0;
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &val[i]);
        ll diff_i = val[i] - val[i - 1];
        x_add(i, diff_i, n);
    }

    for (ll i = 0; i < m; i++)
    {
        ll op;
        scanf("%lld", &op);
        if (op == 1)
        {
            ll x, y, k;
            scanf("%lld %lld %lld", &x, &y, &k);
            x_to_y_all_add(x, y, k, n);
        }
        else
        {
            ll x, y;
            scanf("%lld %lld", &x, &y);
            printf("%lld\n", get_x_to_y_val_sum(x, y));
        }
    }
}