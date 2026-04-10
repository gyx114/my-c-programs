#include <stdio.h>
int main()
{

    int n;
    char s[60];
    scanf("%d", &n);
    scanf("%s", s);
    int i = 0;

    while (n >= 26)
    {
        n -= 26;
    }

    while (s[i] != '\0')
    {
        if (s[i] + n > 122)
        {
            s[i] = s[i] + n - 122 - 1 + 97;
        }
        else
            s[i] = s[i] + n;
        i++;
    }

    printf("%s", s);

    return 0;
}