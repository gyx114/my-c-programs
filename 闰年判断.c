#include <stdio.h>
int isrun(int x);
int main()
{
    int x;
    scanf("%d", &x);
    printf("%d", isrun(x));

    return 0;
}

int isrun(int x)
{
    if ((x % 4 == 0 && x % 100 != 0) || x % 400 == 0)
        return 1;
    else
        return 0;
}