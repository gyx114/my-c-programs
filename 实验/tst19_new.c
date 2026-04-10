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

int compare(const void *a, const void *b)
{

    return ((*(struct ListNode **)a)->val - (*(struct ListNode **)b)->val);
}

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize)
{
    // TODO: 补全代码
    struct ListNode *tmp = lists[0];
    int cnt = 0;
    struct ListNode *tmp_pre = NULL;
    for (int i = 0; i < listsSize; i++)
    {
        while (tmp != NULL)
        {
            tmp_pre = tmp;
            cnt++;
            tmp = tmp->next;
        }
        if (i < listsSize - 1)
        {
            tmp_pre->next = lists[i + 1];
            tmp = lists[i + 1];
        }
        else
            tmp_pre->next = NULL;
    }

    tmp = lists[0];
    struct ListNode *arr[cnt + 1];
    for (int i = 0; i < cnt; i++)
    {
        arr[i] = tmp;
        tmp = tmp->next;
    }
    arr[cnt] = NULL;

    qsort(arr, cnt, sizeof(struct ListNode *), compare);

    for (int i = 0; i < cnt; i++)
    {
        arr[i]->next = arr[i + 1];
    }

    return arr[0];
}