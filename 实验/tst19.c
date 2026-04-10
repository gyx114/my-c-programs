#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize);

int main()
{
    int n;
    scanf("%d", &n); // 读取链表的数量

    // 动态分配链表数组的空间
    struct ListNode **lists = malloc(n * sizeof(struct ListNode *));

    for (int i = 0; i < n; ++i)
    {
        int listSize;
        scanf("%d", &listSize); // 读取单个链表的大小

        struct ListNode *head = NULL;
        struct ListNode *current = NULL;

        // 读取链表的所有节点值
        for (int j = 0; j < listSize; j++)
        {
            int num;
            scanf("%d", &num);

            struct ListNode *node = malloc(sizeof(struct ListNode));
            node->val = num;
            node->next = NULL;

            if (head == NULL)
            {
                head = node;
                current = node;
            }
            else
            {
                current->next = node;
                current = node;
            }
        }
        lists[i] = head;
    }
    struct ListNode *mergedList = mergeKLists(lists, n);
    struct ListNode *tmp = mergedList;
    while (tmp != NULL)
    {
        printf("%d ", tmp->val);
        tmp = tmp->next;
    }

    return 0;
}

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize)
{
    // TODO: 补全代码

    struct ListNode *tmp = lists[0];
    struct ListNode *tmp_pre = NULL;

    for (int i = 0; i < listsSize - 1; i++)
    {
        while (tmp != NULL)
        {
            tmp_pre = tmp;
            tmp = tmp->next;
        }
        tmp_pre->next = lists[i + 1];
        tmp = tmp_pre->next;
    }

    int cnt = 0;
    tmp = lists[0];
    while (tmp != NULL)
    {
        cnt++;
        tmp = tmp->next;
    }

    struct ListNode *p[cnt + 1];
    tmp = lists[0];
    int k = 0;
    while (tmp != NULL)
    {
        p[k++] = tmp;
        tmp = tmp->next;
    }
    p[k] = NULL;

    struct ListNode *head;
    tmp = lists[0];
    int premin = tmp->val;
    struct ListNode *pre_arr = lists[0];
    while (tmp != NULL)
    {
        if (tmp->val < premin)
        {
            premin = tmp->val;
            pre_arr = tmp;
        }
        tmp = tmp->next;
    }
    head = pre_arr;

    struct ListNode *now_arr = NULL;

    for (int i = 1; i < cnt; i++)
    {
        tmp = p[0];
        int min = 1e9;
        int q = 0;
        while (tmp != NULL)
        {
            if (tmp->val < min && tmp->val > premin)
            {
                min = tmp->val;
                now_arr = tmp;
            }
            tmp = p[++q];
        }

        pre_arr->next = now_arr;
        pre_arr = now_arr;
        premin = min;
    }
    pre_arr->next = NULL;

    return head;
}