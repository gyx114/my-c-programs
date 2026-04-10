#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *createList(int a[], int n);

struct ListNode *sortList(struct ListNode *head);

void output(struct ListNode *head);

struct ListNode *insertNode(struct ListNode *head, int n);

struct ListNode *removeNode(struct ListNode *head, int n);

int main()
{
    int a[10000];
    int n, ins, rm;
    scanf("%d", &n);
    scanf("%d", &ins);
    scanf("%d", &rm);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    struct ListNode *list = createList(a, n);
    output(list);
    list = sortList(list);
    output(list);
    list = insertNode(list, ins);
    output(list);
    list = removeNode(list, rm);
    output(list);
    return 0;
}

struct ListNode *createList(int a[], int n)
{
    // TODO: 填写创建链表的函数
    struct ListNode *head;
    head = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->val = a[0];
    struct ListNode *tmp = head;
    for (int i = 1; i < n; i++)
    {
        tmp->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        tmp = tmp->next;
        tmp->val = a[i];
    }
    tmp->next = NULL;

    return head;
}

struct ListNode *sortList(struct ListNode *head)
{
    // TODO: 填写链表排序的函数
    int a[1024];
    struct ListNode *tmp = head;
    int cnt = 0;
    while (tmp->next != NULL)
    {
        a[cnt++] = tmp->val;
        tmp = tmp->next;
    }
    a[cnt++] = tmp->val;
    for (int i = cnt - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j] > a[j + 1])
            {
                int x = a[j];
                a[j] = a[j + 1];
                a[j + 1] = x;
            }
        }
    }

    tmp = head;
    for (int i = 0; i < cnt; i++)
    {
        tmp->val = a[i];
        tmp = tmp->next;
    }

    return head;
}
void output(struct ListNode *head)
{
    // TODO: 填写输出每个节点值的函数
    struct ListNode *tmp = head;
    while (tmp->next != NULL)
    {
        printf("%d\n", tmp->val);
        tmp = tmp->next;
    }
    printf("%d\n", tmp->val);
}

struct ListNode *insertNode(struct ListNode *head, int n)
{
    // 插入值
    struct ListNode *p = (struct ListNode *)malloc(sizeof(struct ListNode));
    p->val = n;
    p->next = NULL;

    // 插入到头结点之前
    if (head == NULL || n <= head->val)
    {
        p->next = head;
        return p;
    }

    struct ListNode *tmp = head;
    while (tmp->next != NULL && n > tmp->next->val)
    {
        tmp = tmp->next;
    }
    // 插入到 tmp 和 tmp->next 之间
    p->next = tmp->next;
    tmp->next = p;

    return head;
}
struct ListNode *removeNode(struct ListNode *head, int n)
{
    // TODO: 填写删除链表中指定值的函数

    if (head == NULL)
        return head;

    // Special case: remove head
    if (head->val == n)
    {
        struct ListNode *tmp = head->next;
        free(head);
        return tmp;
    }

    struct ListNode *prev = head;
    struct ListNode *curr = head->next;
    while (curr != NULL)
    {
        if (curr->val == n)
        {
            prev->next = curr->next;
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    // 如果没找到，则不做任何操作

    return head;
}