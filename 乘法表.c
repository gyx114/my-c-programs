#include <stdio.h>
int main()
{

    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            printf("%d*%d=%d", j, i, j * i);

            if (j == i)
            {
                printf("\n");
            }
            else
            {
                if (j * i >= 10)
                {
                    printf("  ");
                }
                else
                {
                    printf("   ");
                }
            }
        }
    }

    return 0;
}
