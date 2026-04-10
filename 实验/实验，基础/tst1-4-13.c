#include <stdio.h>

int output(int arr[3][3])
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{

    int a[3][3];
    int b[3][3];
    int a_add_b[3][3];
    int a_jian_b[3][3];
    int a_pls_b[3][3];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &b[i][j]);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            a_add_b[i][j] = a[i][j] + b[i][j];
            a_jian_b[i][j] = a[i][j] - b[i][j];

            a_pls_b[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j];
        }
    }
    int tmp;
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 0; j < i; j++)
        {
            tmp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = tmp;
        }
    }

    output(a_add_b);
    output(a_jian_b);
    output(a_pls_b);
    output(a);

    return 0;
}