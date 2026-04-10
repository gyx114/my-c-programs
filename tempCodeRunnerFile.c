#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main()
{
    int a, b;
    char c[20];
    scanf("%d %d %s", &a, &b, c);

    int len = strlen(c);
    int len_zheng = len;
    int is_float = 0;
    for (int i = 0; i < len; i++)
    {
        if (c[i] == '.')
        {
            len_zheng = i;
            is_float = 1;
            break;
        }
    }
    // 整数部分

    int tmp = 0;
    int q = 1;
    for (int i = 0; i < len_zheng; i++)
    {
        char x = c[len_zheng - i - 1];
        int y;
        if (x >= '0' && x <= '9')
        {
            y = x - '0';
        }
        else
        {
            y = x - 'a' + 10;
        }
        tmp += y * q;
        q *= a;
    }
    if (tmp == 0)
    {
        printf("0");
    }
    else
    {
        int l_zheng = 0;
        char zheng[20];
        while (tmp != 0)
        {
            int wei = tmp % b;
            char x;
            if (wei >= 0 && wei <= 9)
            {
                x = wei + '0';
            }
            else
            {
                x = wei - 10 + 'a';
            }
            zheng[l_zheng++] = x;
            tmp /= b;
        }
        for (int i = 0; i < l_zheng; i++)
        {
            printf("%c", zheng[l_zheng - 1 - i]);
        }
    }
    if (is_float)
    {
        printf(".");

        double tmp_xiao = 0;
        int p = a;
        int len_xiao = len - len_zheng - 1;
        for (int i = 0; i < len_xiao; i++)
        {
            char cur = c[len_zheng + i + 1];
            int shi;
            if (cur >= '0' && cur <= '9')
            {
                shi = cur - '0';
            }
            else
            {
                shi = cur - 'a' + 10;
            }
            tmp_xiao += (double)shi / (double)p;
            p *= a;
        }

        char xiao[20];
        int l_xiao = 0;
        while (tmp_xiao > 1e-9)
        {

            int x = (int)(tmp_xiao * b);
            char gyx;
            if (x >= 0 && x <= 9)
            {
                gyx = x + '0';
            }
            else
            {
                gyx = x - 10 + 'a';
            }
            xiao[l_xiao++] = gyx;
            tmp_xiao = tmp_xiao * b - x;
            if (l_xiao == 8)
            {
                break;
            }
        }
        xiao[l_xiao] = '\0';

        printf("%s", xiao);
    }
}
