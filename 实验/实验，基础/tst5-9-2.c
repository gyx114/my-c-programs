#include <stdio.h>
int main()
{
    char str[100000];
    scanf("%s", str);
    int cnt = 0;
    while (str[cnt] != '\0')
    {
        cnt++;
    }

    if (str[cnt - 2] != 'a' && str[cnt - 2] != 'e' && str[cnt - 2] != 'i' && str[cnt - 2] != 'o' && str[cnt - 2] != 'u' && str[cnt - 1] == 'y')
    {
        str[cnt - 1] = 'i';
        str[cnt] = 'e';
        str[cnt + 1] = 's';
        str[cnt + 2] = '\0';
    }

    else if (str[cnt - 1] == 's' || str[cnt - 1] == 'x' || str[cnt - 1] == 'o' || (str[cnt - 2] == 'c' && str[cnt - 1] == 'h') || (str[cnt - 2] == 's' && str[cnt - 1] == 'h'))
    {
        str[cnt] = 'e';
        str[cnt + 1] = 's';
        str[cnt + 2] = '\0';
    }

    else
    {
        str[cnt] = 's';
        str[cnt + 1] = '\0';
    }

    printf("%s", str);

    return 0;
}