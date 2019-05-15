
#include "usestl.h"
#include <queue>
#include <cstring>

/*!
 * @brief 队列节点
 *
 */
typedef struct node_s
{
    int id;
    std::string name;
}node_t;

/*!
 * @brief 优先级比较
 *
 */
struct cmp
{
    bool operator() (const node_t& a, const node_t& b)
    {
        // < : 最大优先
        // > : 最小优先
        int k = 0;
        while (1)
        {
            if (k >= a.name.size())
                return false;   // as a > b
            if (k >= b.name.size())
                return true;    // as a < b
            if (a.name[k] == b.name[k])
                k ++;
            else
                return (a.name[k] > b.name[k]);
        }
        //return a.id < b.id;
    }
};

/*!
 * @brief 优先级队列
 *
 */
void container_priority_queue(void)
{
    PutTitle("\nContainer priority queue begin.\n");

    // 自定优先级队列的容器，以及优先级比较函数
    std::priority_queue<node_t, std::vector<node_t>, cmp> pq;
    pq.push(node_t({.id=0, .name="buy"}));
    pq.push(node_t({.id=1, .name="alice"}));
    pq.push(node_t({.id=2, .name="lucy"}));
    pq.push(node_t({.id=3, .name="camy"}));
    pq.push(node_t({.id=4, .name="emily"}));
    pq.push(node_t({.id=4, .name="buyly"}));

    while (!pq.empty())
    {
        PutContent(pq.top().name << std::endl);
        pq.pop();
    }

    PutTitle("\nContainer priority queue end.\n");
}
