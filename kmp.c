#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1000005

char s1[MAX_LEN];
char s2[MAX_LEN];
int len_s1;
int len_s2;

int *generate_next(int len)
{
    int *next = (int *)malloc((len + 1) * sizeof(int));

    next[1] = 0;
    int j = 0;
    for (int i = 2; i <= len; i++)
    {
        while (j > 0 && s2[i] != s2[j + 1])
        {
            j = next[j];
        }
        if (s2[i] == s2[j + 1])
        {
            j++;
        }
        next[i] = j;
    }
    return next;
}

int main()
{
    s1[0] = '.';
    s2[0] = '.';
    scanf("%s", s1 + 1);
    scanf("%s", s2 + 1);
    len_s1 = strlen(s1) - 1;
    len_s2 = strlen(s2) - 1;

    int *next = generate_next(len_s2);

    int now = 1;
    for (int i = 1; i <= len_s1; i++)
    {
        if (now == 1 && s1[i] != s2[now])
        {
            continue;
        }
        while (now > 1 && s1[i] != s2[now])
        {
            now = next[now - 1] + 1;
        }

        // now处字母匹配成功
        if (s1[i] == s2[now])
        {
            if (now == len_s2)
            {
                printf("%d\n", i - len_s2 + 1);
                now = next[now] + 1;
            }
            else
            {
                now++;
            }
        }
    }

    for (int i = 1; i <= len_s2; i++)
    {
        printf("%d ", next[i]);
    }

    return 0;
}