#include <stdio.h>

int pow_int(int a, int b)
{
    int tmp = 1;
    if (b == 0)
        return 1;
    for (int i = 0; i < b; i++)
    {
        tmp *= a;
    }
    return tmp;
}

int main()
{

    int a, b;
    scanf("%d %d", &a, &b);
    char c[200];
    scanf("%s", c);

    int c_dec = 0;
    int len = 0;
    while (c[len] != '\0')
    {
        len++;
    }

    int num;
    for (int i = 0; i < len; i++)
    {
        if (c[i] >= 'a')
        {
            num = 10 + c[i] - 'a';
        }
        else
            num = c[i] - '0';
        c_dec += (pow_int(a, len - 1 - i) * num);
    }

    int cnt = 0;
    char c_b[5000];
    int tmp;
    char tmp_char;
    while (c_dec != 0)
    {
        tmp = c_dec % b;
        c_dec /= b;
        if (tmp >= 10)
            tmp_char = 'a' + tmp - 10;
        else
            tmp_char = '0' + tmp;

        c_b[cnt] = tmp_char;
        cnt++;
    }
    for (int i = cnt - 1; i >= 0; i--)
    {
        printf("%c", c_b[i]);
    }

    return 0;
}