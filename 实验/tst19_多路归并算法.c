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

void sort(struct ListNode **lists, int listsSize, struct ListNode **p, int start)
{
    int is_finished = 1;

    for (int i = 0; i < listsSize; i++)
    {
        if (lists[i] != NULL)
        {
            is_finished = 0;
            break;
        }
    }
    if (is_finished)
        return;
    else
    {

        int min = 2e9;
        int finally_min_idx;
        for (int i = 0; i < listsSize; i++)
        {
            if (lists[i] == NULL)
            {
                continue;
            }
            else if (lists[i]->val < min)
            {
                finally_min_idx = i;
                min = lists[i]->val;
                p[start] = lists[i];
            }
        }
        //"首节点"被选中的链表需要push第二节点作为"首节点"
        lists[finally_min_idx] = lists[finally_min_idx]->next;
        sort(lists, listsSize, p, start + 1);
    }
}

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize)
{
    // TODO: 补全代码

    int len_of_listnode[listsSize];
    for (int i = 0; i < listsSize; i++)
    {
        struct ListNode *tmp = lists[i];
        int cnt = 0;
        while (tmp != NULL)
        {
            cnt++;
            tmp = tmp->next;
        }
        len_of_listnode[i] = cnt;
    }

    int total_sum = 0;
    for (int i = 0; i < listsSize; i++)
    {
        total_sum += len_of_listnode[i];
    }

    struct ListNode *p[total_sum + 1];
    p[total_sum] = NULL;
    sort(lists, listsSize, p, 0);

    for (int i = 0; i < total_sum; i++)
    {
        p[i]->next = p[i + 1];
    }

    return p[0];
}