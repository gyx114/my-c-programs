#include <stdio.h>
int main()
{
    int a, b;
    char standard;
    while (1)
    {
        if (scanf("%d", &a))
        {
            scanf("%d", &b);
            printf("a=%d b=%d standard=%c\n", a, b, standard);
        }
        else
        {
            scanf("%c", &standard);
            scanf("%d %d", &a, &b);
            printf("a=%d b=%d standard=%c\n", a, b, standard);
        }
    }

    return 0;
}