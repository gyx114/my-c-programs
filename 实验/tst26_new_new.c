#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *mergeLists(struct ListNode *list1, struct ListNode *list2);
void printList(struct ListNode *head);
struct ListNode *createList(int listSize);

int main()
{
    int listSize;
    scanf("%d", &listSize); // 读取单个链表的大小
    // printf("%d", listSize);
    struct ListNode *list1 = createList(listSize);

    scanf("%d", &listSize); // 读取单个链表的大小
    struct ListNode *list2 = createList(listSize);

    // 归并排序链表
    struct ListNode *result = mergeLists(list1, list2);

    // 输出排序后的链表
    printList(result);
}

struct ListNode *createList(int listSize)
{
    struct ListNode *head = NULL;
    struct ListNode *current = NULL;

    // 读取链表的所有节点值
    for (int j = 0; j < listSize; j++)
    {
        int num;
        scanf("%d", &num);

        struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
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
    return head;
}

void printList(struct ListNode *head)
{
    struct ListNode *current = head;
    while (current != NULL)
    {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}
struct ListNode *mergeLists(struct ListNode *list1, struct ListNode *list2)
{
    struct ListNode *head = NULL;
    struct ListNode *tail = NULL;
    if (list1->val < list2->val)
    {
        head = list1;
        list1 = list1->next;
    }
    else
    {
        head = list2;
        list2 = list2->next;
    }
    tail = head;
    while (1)
    {
        struct ListNode *tmp = NULL;
        if (list1 == NULL)
        {
            tmp = list2;
            tail->next = tmp;
            tail = tail->next;
            break;
        }
        else if (list2 == NULL)
        {
            tmp = list1;
            tail->next = tmp;
            tail = tail->next;
            break;
        }
        else
        {
            if (list1->val < list2->val)
            {
                tmp = list1;
                list1 = list1->next;
                tail->next = tmp;
                tail = tail->next;
            }
            else
            {
                tmp = list2;
                list2 = list2->next;
                tail->next = tmp;
                tail = tail->next;
            }
        }
    }
    return head;
}
