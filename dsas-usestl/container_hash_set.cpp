
#include "usestl.h"
#include <unordered_set>


/*!
 * @brief hash索引
 *
 */
void container_hash_set(void)
{
    PutTitle("\nContainer hash set begin.\n");

    int arr[] = {3, 5, 2, 3, 8, 2, 3};
    int size = sizeof(arr) / sizeof(int);
    std::unordered_set<int> is;
    std::unordered_multiset<int> ism;

    // 插入元素到集合
    for (int k = 0; k < size; k ++)
    {
        is.insert(arr[k]);
        ism.insert(arr[k]);
    }

    // 查找元素
    auto result = ism.find(8);

    // 输出
    PutTitle("unordered set:\n");
    for (const auto& it:is)
        PutContent(it << ' ');
    PutTitle("\nunordered multiset:\n");
    for (const auto& it:ism)
        PutContent(it << ' ');
    PutTitle("\nfind result:\n");
    if (result != ism.end())
        PutContent("found: " << *result);
    else
        PutContent("not found");

    PutTitle("\nContainer hash set end.\n");
}
