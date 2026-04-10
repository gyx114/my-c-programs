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


int compare(const void*a,const void*b){
    return (*((int*)a)-*((int*)b));
}



struct ListNode* mergeLists(struct ListNode *list1, struct ListNode *list2) {
    

    struct ListNode* tmp=list1;
    struct ListNode* pre=NULL;   
    while (tmp!=NULL)
    {   pre=tmp;
        tmp=tmp->next;
    }
    pre->next=list2;
    
    tmp=list1;
    int nums[2048];
    int cnt=0;
    while (tmp!=NULL)
    {
        nums[cnt++]=tmp->val;
        tmp=tmp->next;
    }
    qsort(nums,cnt,sizeof(int),compare);
    

    tmp=list1;
    int k=0;
    while (tmp!=NULL)
    {

        tmp->val=nums[k++];
        tmp=tmp->next;
    }
    






    return list1;
}