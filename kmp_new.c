#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1000005

char s1[MAX_LEN];
char s2[MAX_LEN];

int len_s1, len_s2;

// 给s2生成next数组,存储每个前缀 s 的最长 border t 的长度
//  定义一个字符串 s 的 border 为 s 的一个非 s 本身的子串 t，满足 t 既是 s 的前缀，又是 s 的后缀。
int *generate_next()
{
    int *next = (int *)malloc(len_s2 * sizeof(int));
    next[0] = 0;
    for (int i = 1; i < len_s2; i++)
    {
        if (next[i - 1] == 0)
        {
            if (s2[i] == s2[0])
            {
                next[i] = 1;
            }
            else
            {
                next[i] = 0;
            }
        }

        else
        {
            if (s2[i] == s2[next[i - 1]])
            {
                next[i] = next[i - 1] + 1;
            }
            else
            {
                next[i] = 0;
                int j = i;
                while (j != 0)
                {
                    j = next[j - 1];
                    if (s2[j] == s2[i])
                    {
                        next[i] = j + 1;
                        break;
                    }
                }
            }
        }
    }
    return next;
}

int main()
{

    scanf("%s", s1);
    scanf("%s", s2);
    len_s1 = strlen(s1);
    len_s2 = strlen(s2);
    int *next = generate_next();
    int j = 0;
    for (int i = 0; i < len_s1;)
    {

        if (s1[i] == s2[j])
        {

            if (j == len_s2 - 1)
            {
                printf("%d\n", i - len_s2 + 2);
                i++;
                j = next[j];
            }

            else
            {
                j++;
                i++;
            }
        }
        else
        {
            if (j == 0)
            {
                i++;
            }
            else
            {
                j = next[j - 1];
            }
        }
    }

    for (int i = 0; i < len_s2; i++)
    {
        printf("%d ", next[i]);
    }

    return 0;
}
