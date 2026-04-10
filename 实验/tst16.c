#include <stdio.h>

void swift(int n, int p, char *ans);

int main()
{

    int n;
    scanf("%X", &n);
    char ans[100];

    for (int i = 2; i <= 15; i++)
    {
        swift(n, i, ans);
    }
}

void swift(int n, int p, char *ans)
{
    char tmp;
    int cnt = 0;
    while (n != 0)
    {
        tmp = '0' + n % p;
        if (tmp - '0' >= 10)
        {
            tmp = 'A' + tmp - '0' - 10;
        }

        ans[cnt] = tmp;
        n /= p;
        cnt++;
    }

    for (int i = cnt - 1; i >= 0; i--)
    {
        printf("%c", ans[i]);
    }
    printf("\n");
}