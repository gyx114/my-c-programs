#include <stdio.h>
#include <math.h>
int main()
{

    int a, b;
    scanf("%d %d", &a, &b);
    char c[20];
    scanf("%s", c);

    int len_zheng = 0;
    int len_xiao = 0;
    int len_total = 0;
    while (c[len_total] != '\0')
    {
        if (c[len_total] == '.')
            len_zheng = len_total;
        len_total++;
    }

    len_xiao = len_total - 1 - len_zheng;

    int zheng_dec = 0;
    int num;
    for (int i = 0; i < len_zheng; i++)
    {
        if (c[i] >= 'a')
            num = 10 + c[i] - 'a';
        else
            num = c[i] - '0';
        zheng_dec += pow(a, len_zheng - 1 - i) * num;
    }

    double xiao_dec = 0;
    for (int i = len_zheng + 1; i < len_total; i++)
    {
        if (c[i] >= 'a')
            num = 10 + c[i] - 'a';
        else
            num = c[i] - '0';
        xiao_dec += (pow(a, len_zheng - i) * num);
    }

    char zheng_b[50];
    char xiao_b[50];

    int tmp;
    char tmp_char;
    int len_zheng_b = 0;
    int len_xiao_b = 0;

    if (zheng_dec == 0)
    {
        zheng_b[len_zheng_b++] = '0';
    }
    else
    {
        while (zheng_dec != 0)
        {
            tmp = zheng_dec % b;
            zheng_dec /= b;
            if (tmp >= 10)
                tmp_char = 'a' + tmp - 10;
            else
                tmp_char = '0' + tmp;
            zheng_b[len_zheng_b] = tmp_char;
            len_zheng_b++;
        }
    }

    int max_xiao_iter = 12; // maximum digits for safety
    while (xiao_dec > 1e-12 && len_xiao_b < max_xiao_iter)
    {
        tmp = (int)(xiao_dec * b);
        xiao_dec = xiao_dec * b - tmp;
        if (tmp >= 10)
            tmp_char = 'a' + tmp - 10;
        else
            tmp_char = '0' + tmp;
        xiao_b[len_xiao_b] = tmp_char;
        len_xiao_b++;
    }

    for (int i = len_zheng_b - 1; i >= 0; i--)
    {
        printf("%c", zheng_b[i]);
    }

    int is_all_zero = 1;
    for (int i = 0; i < len_xiao_b; i++)
    {
        if (xiao_b[i] != '0')
        {
            is_all_zero = 0;
            break;
        }
    }

    if (!is_all_zero)
    {
        printf(".");
        for (int i = 0; i < len_xiao_b; i++)
        {
            printf("%c", xiao_b[i]);
            if (i == 7)
                break;
        }
    }

    return 0;
}
