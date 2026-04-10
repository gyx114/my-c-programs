#include <stdio.h>
int main()
{
    char str[103];
    scanf("%s", str);
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 0x61 && str[i] <= 0x7A)
        {
            printf("%c", str[i] - 32);
        }
        else
        {
            printf("%c", str[i]);
        }
        i++;
    }

    return 0;
}