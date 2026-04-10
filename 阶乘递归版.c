#include <stdio.h>
int sum = 1;
void jiecheng(int x)
{

    if (x == 1)
    {
        printf("%d", sum);
    }

    else
    {
        sum *= x;
        jiecheng(x - 1);
    }
}

int main()
{

    int a;
    scanf("%d", &a);

    jiecheng(a);

    return 0;
}
