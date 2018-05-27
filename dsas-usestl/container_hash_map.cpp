
#include "usestl.h"
#include <unordered_map>
#include <utility>

/*!
 * @brief hash索引
 *
 */
void container_hash_map(void)
{
    PutTitle("\nContainer hash map begin.\n");

    int arr[] = {3, 5, 2, 3, 8, 2, 3};
    int size = sizeof(arr) / sizeof(int);
    std::unordered_map<int, int> ii;
    std::unordered_multimap<int, int> iim;

    // 插入键值对
    for (int k = 0; k < size; k ++)
    {
        // 用map统计频数
        if (ii.count(arr[k]))
            ii[arr[k]] += 1;
        else
            ii[arr[k]] = 1;

        // 用multimap映射下标
        iim.insert(std::pair<int, int>(arr[k], k));
    }

    // 输出
    PutTitle("unordered map count:\n");
    for (const auto& it:ii)
        PutContent("key: " << it.first << ", value(count): " << it.second << std::endl);
    PutTitle("unordered multimap index:\n");
    for (const auto& it:iim)
        PutContent("key: " << it.first << ", value(index): " << it.second << std::endl);
    PutTitle("unordered multimap count:\n");
    for (int k = 0; k < size; k ++)
        PutContent("key: " << arr[k] << ", count: " << iim.count(arr[k])<< std::endl);
    std::unordered_multimap<int, int>::iterator result = iim.find(5);
    if (result != iim.end())
        PutContent("find result: " << result->first << ' ' << result->second);

    PutTitle("\nContainer hash map end.\n");
}
