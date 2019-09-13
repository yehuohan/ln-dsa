
#include "usestl.h"
#include <list>

/*!
 * @brief 双向链表
 *
 */
void container_list(void)
{
    PutTitle("\nContainer list begin.\n");

    std::list<int> li;

    // 访问元素
    li.push_front(10);
    li.push_back(3);
    li.push_back(1);
    li.push_back(5);
    li.push_back(-1);

    // 输出
    PutTitle("list:\n");
    for (auto it:li)
        PutContent(it);
    li.sort();
    PutTitle("\nlist sort:\n");
    for (auto it:li)
        PutContent(it);

    PutTitle("\nContainer list end.\n");
}
