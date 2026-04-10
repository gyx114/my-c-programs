#include <stdio.h>
int main()
{

    int n;
    scanf("%d", &n);
    char str[1000000];
    for (int i = 0; i < n; i++)
    {
        scanf(" %[^\n]", str);
        printf("%s\n", str);
    }

    return 0;
}