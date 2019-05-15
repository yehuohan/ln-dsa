
#include "usestl.h"
#include <deque>

void container_deque(void)
{
    PutTitle("\nContainer deque begin.\n");

    // 双端队列
    // 随机访问:O(1)
    // 在front/back插入或移除元素：O(1)
    // 插入或移除元素：O(n)
    std::deque<int> dq;
    dq.push_back(0); dq.push_back(1); dq.push_back(2);
    dq.push_front(10);

    for (auto& it:dq)
    {
        PutContent(it);
    }

    PutTitle("\nContainer deque end.\n");
}
