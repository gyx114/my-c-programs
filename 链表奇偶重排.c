struct ListNode *rearrange_list(struct ListNode *head)
{
    if (!head)
        return head;
    else if (!head->next)
        return head;
    else if (!head->next->next)
        return head;
    else
    {
        struct ListNode *head_ji = head;
        struct ListNode *head_ou = head->next;
        struct ListNode *tmp_ou = head->next;

        while (head_ji && tmp_ou && tmp_ou->next)
        {
            head_ji->next = tmp_ou->next;
            head_ji = head_ji->next;
            tmp_ou->next = head_ji->next;
            tmp_ou = tmp_ou->next;
        }
        head_ji->next = head_ou;
        return head;
    }
}
