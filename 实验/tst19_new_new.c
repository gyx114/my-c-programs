#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize)
{

    struct ListNode *sorted_nodes[(int)1e6];
    int min_idx = 0;
    int cnt = 0;

    while (1) // 先写死，再找跳出条件
    {
        int min = 1e9;
        min_idx = -1;
        for (int i = 0; i < listsSize; i++)
        {
            if (lists[i] == NULL)
            {
                continue;
            }
            else if (lists[i]->val < min)
            {
                min = lists[i]->val;
                min_idx = i;
            }
        }

        if (min_idx == -1)
        {
            break;
        }

        else
        {
            sorted_nodes[cnt++] = lists[min_idx];
            lists[min_idx] = lists[min_idx]->next;
        }
        // 避免了lists[-1]访问问题
    }

    for (int i = 0; i < cnt - 1; i++)
    {
        sorted_nodes[i]->next = sorted_nodes[i + 1];
    }
    sorted_nodes[cnt - 1]->next = NULL;
    return sorted_nodes[0];
}

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

    return 0;
}
