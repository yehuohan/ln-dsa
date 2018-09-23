
#include <iostream>

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};

class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        /* 复制链表中的random指针怎么确定？
        原链表：      a-b-c-d-e
                         \_/

                              /-------\
        复制节点：    a-a'-b-b'-c-c'-d-d'-e-e'
                            \_______/
        b'->random = b->random->next
        */

        if (!pHead) return NULL;

        RandomListNode* p = pHead;

        // 复制 label 和 next
        while (p)
        {
            RandomListNode* node = new RandomListNode(p->label);
            node->next = p->next;
            p->next = node;
            p = node->next;
        }

        // 复制random
        p = pHead;
        while (p)
        {
            p->next->random = (p->random)? p->random->next : NULL;
            p = p->next->next;
        }

        // 拆分复制链表，同时保持原链表不变
        RandomListNode* head_clone = pHead->next;
        p = pHead;
        while (p)
        {
            RandomListNode* node = p->next;
            p->next = node ? node->next : NULL;
            p = node;
        }

        return head_clone;
    }
};

int main()
{
    RandomListNode p1(1),p2(2),p3(3),p4(4),p5(5);
    p1.next = &p2;
    p2.next = &p3;
    p3.next = &p4;
    p4.next = &p5;

    Solution su;
    RandomListNode* head = su.Clone(&p1);
    while(head)
    {
        std::cout << head->label << ',';
        head = head->next;
    }
    std::cout << '\n';
    head = &p1;
    while(head)
    {
        std::cout << head->label << ',';
        head = head->next;
    }

}
