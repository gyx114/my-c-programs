#include <stdio.h>
#include <math.h>
#include <string.h>

int add_point_and_get_int_len(int *len, char *num);
void right_move(int step, int *len, char *num);

int main()
{

    int n, m;
    char num1[50];
    memset(num1, '0', 50);
    char num2[50];
    memset(num2, '0', 50);
    scanf("%d", &n);
    scanf("%s", num1);
    scanf("%d", &m);
    scanf("%s", num2);
    num1[n] = '0';
    num2[m] = '0';
    int len_int_a, len_int_b;
    len_int_a = add_point_and_get_int_len(&n, num1);
    len_int_b = add_point_and_get_int_len(&m, num2);
    int len_xiao_a = n - 1 - len_int_a;
    int len_xiao_b = m - 1 - len_int_b;

    if (len_int_a > len_int_b)
    {
        int step = len_int_a - len_int_b;
        right_move(1, &n, num1);
        right_move(step + 1, &m, num2);
    }
    else
    {
        int step = len_int_b - len_int_a;
        right_move(1, &m, num2);
        right_move(step + 1, &n, num1);
    }

    int max_len_xiao = len_xiao_a;
    if (len_xiao_b > len_xiao_a)
        max_len_xiao = len_xiao_b;

    int len_int_finally = n - len_xiao_a - 1;

    char ans[len_int_finally + 1 + max_len_xiao];

    int tmp = 0, remain = 0, jinwei = 0;
    for (int i = len_int_finally + max_len_xiao; i > len_int_finally; i--)
    {
        tmp = (num1[i] - '0') + (num2[i] - '0') + jinwei;
        jinwei = tmp / 10;
        remain = tmp % 10;

        ans[i] = remain + '0';
    }

    ans[len_int_finally] = '.';

    for (int i = len_int_finally - 1; i >= 0; i--)
    {
        tmp = (num1[i] - '0') + (num2[i] - '0') + jinwei;
        jinwei = tmp / 10;
        remain = tmp % 10;

        ans[i] = remain + '0';
    }
    ans[len_int_finally + 1 + max_len_xiao] = '\0';

    int begin = 0;

    // 判断首位是否为0
    if (ans[0] == '0')
        begin = 1;

    // 判断是否是整数及最低位
    int end = len_int_finally - 1;
    for (int i = len_int_finally + 1; ans[i] != '\0'; i++)
    {
        if (ans[i] != '0')
            end = i;
    }

    for (int i = begin; i <= end; i++)
    {
        printf("%c", ans[i]);
    }

    return 0;
}

int add_point_and_get_int_len(int *len, char *num)
{

    for (int i = 0; i < *len; i++)
    {
        if (num[i] == '.')
            return i;
    }
    num[*len] = '.';
    (*len)++;
    return (*len - 1);
}

void right_move(int step, int *len, char *num)
{
    for (int i = *len - 1; i >= 0; i--)
    {
        num[i + step] = num[i];
    }
    for (int i = 0; i < step; i++)
    {
        num[i] = '0';
    }

    (*len) += step;
}