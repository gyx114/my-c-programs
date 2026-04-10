#include <stdio.h>

struct good
{
    int No;       /// 物品编号
    float weight; // 物品重量
    float value;  // 物品价值
    float pw;     // 物品单位重量的价值； pw=value/weight;
};

void greedy(struct good goods[], int n, int max_weight);
int main()
{

    int n, max_weight;
    scanf("%d %d", &n, &max_weight);
    struct good goods[n];
    for (int i = 0; i < n; i++)
    {
        goods[i].No = i;
        scanf("%f %f", &(goods[i].weight), &(goods[i].value));
        goods[i].pw = goods[i].value / goods[i].weight;
    }

    greedy(goods, n, max_weight);

    return 0;
}

void greedy(struct good goods[], int n, int max_weight)
{

    // pw降序排列
    int tmp_no;
    float tmp_weight, tmp_value, tmp_pw;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (goods[j].pw < goods[j + 1].pw)
            {
                tmp_no = goods[j].No;
                tmp_weight = goods[j].weight;
                tmp_value = goods[j].value;
                tmp_pw = goods[j].pw;

                goods[j].No = goods[j + 1].No;
                goods[j].weight = goods[j + 1].weight;
                goods[j].value = goods[j + 1].value;
                goods[j].pw = goods[j + 1].pw;

                goods[j + 1].No = tmp_no;
                goods[j + 1].weight = tmp_weight;
                goods[j + 1].value = tmp_value;
                goods[j + 1].pw = tmp_pw;
            }
        }
    }

    int cur_weight = 0;
    int cur_value = 0;
    for (int i = 0; i < n; i++)
    { // 重量超了，输出
        if (cur_weight + goods[i].weight > max_weight)
        {
            printf("%d\n%d", cur_weight, cur_value);
            return;
        }
        else
        {
            cur_weight += goods[i].weight;
            cur_value += goods[i].value;
        }
    }

    // 骗你的，不超也输出
    printf("%d\n%d", cur_weight, cur_value);
}