
#include <stdio.h>
#include <malloc.h>


typedef struct ListNode
{
    int val;
    struct ListNode *next;
}ListNode;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
    struct ListNode* ret = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* n = ret;
    struct ListNode* a = l1;
    struct ListNode* b = l2;
    int in = 0;

    n->val = a->val + b->val;
    in = (n->val >= 10) ? (n->val -= 10, 1) : 0;
    a = a->next;
    b = b->next;

    while(a && b)
    {
        n->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        n->next->val = a->val + b->val + in;
        in = (n->next->val >= 10) ? (n->next->val -= 10, 1) : 0;
        n = n->next;
        a = a->next;
        b = b->next;
    }
    while(a)
    {
        n->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        n->next->val = a->val + in;
        in = (n->next->val >= 10) ? (n->next->val -= 10, 1) : 0;
        n = n->next;
        a = a->next;
    }
    while(b)
    {
        n->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        n->next->val = b->val + in;
        in = (n->next->val >= 10) ? (n->next->val -= 10, 1) : 0;
        n = n->next;
        b = b->next;
    }
    if (in)
    {
        n->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        n->next->val = 1;
        n = n->next;
    }
    n->next = NULL;

    return ret;
}


int main(void)
{
    ListNode a0, a1, a2;
    a0.val = 2; a0.next = &a1;
    a1.val = 4; a1.next = &a2;
    a2.val = 3; a2.next = NULL;

    ListNode b0, b1, b2;
    b0.val = 5; b0.next = &b1;
    b1.val = 6; b1.next = &b2;
    b2.val = 4; b2.next = NULL;

    ListNode* ret = addTwoNumbers(&a0, &b0);
    ListNode* n = ret;
    while(n)
    {
        printf("%d  ", n->val);
        n = n->next; 
    }
    n = ret;
    while(n)
    {
        free(ret);
        n = n->next; 
    }
    return 0;
}
