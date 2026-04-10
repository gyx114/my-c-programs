#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUM_OF_ALPHABET 26
#define MAX_LEN 1000000

typedef struct a
{
    char val;
    int cnt_of_end;
    // 26个英文字母，children数组开26个就行
    struct a *children[SUM_OF_ALPHABET];
} node;

node *head;

void add_str(char *str)
{
    node *now = head;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        node *p = now->children[str[i] - 'a'];
        if (!p)
        {
            p = (node *)malloc(sizeof(node));
            p->val = str[i];
            p->cnt_of_end = 0;
            for (int j = 0; j < SUM_OF_ALPHABET; j++)
            {
                p->children[j] = NULL;
            }

            // 记得把p存到children中！
            // 因为 p 和 now->children[str[i] - 'a'] 是两个指针！
            // 虽然给p malloc了，但是 now->children[str[i] - 'a'] 依旧为NULL
            now->children[str[i] - 'a'] = p;
        }

        if (i == len - 1)
        {
            p->cnt_of_end += 1;
        }
        now = p;
    }
}

int check(char *str)
{
    node *now = head;
    int len = strlen(str);
    int cnt = 0;
    for (int i = 0; i < len; i++)
    {
        node *p = now->children[str[i] - 'a'];
        if (p)
        {
            if (p->cnt_of_end)
            {
                cnt += (p->cnt_of_end);
            }
        }

        else
        {
            break;
        }
        now = p;
    }

    return cnt;
}

int main()
{

    head = (node *)malloc(sizeof(node));
    for (int i = 0; i < SUM_OF_ALPHABET; i++)
    {
        head->children[i] = NULL;
    }

    head->val = 0;

    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
    {
        char str_i[MAX_LEN];
        scanf("%s", str_i);
        add_str(str_i);
    }

    for (int i = 0; i < m; i++)
    {
        char a[MAX_LEN];
        scanf("%s", a);
        printf("%d\n", check(a));
    }

    return 0;
}