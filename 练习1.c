#include <stdio.h>
int main()
{

    int a;
    scanf("%d", &a);
    int i, j, k;
    int count = 0;
    for (i = a; i <= a + 3; i++)
    {
        for (j = a; j <= a + 3; j++)
        {
            for (k = a; k <= a + 3; k++)
            {
                if (i != j && j != k && k != i)
                {
                    count += 1;
                    printf("%d%d%d", i, j, k);

                    if (count % 6 == 0)
                    {
                        printf("\n");
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }
    }

    return 0;
}