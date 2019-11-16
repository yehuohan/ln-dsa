
#include "usestl.h"
#include <vector>
#include <algorithm>

/*!
 * @brief 获取极值
 *
 */
void algorithm_maxmin(void)
{
    PutTitle("\nAlgorithm maxmin begin.\n");

    int arr[] = {2, 5, 1, 4, 3};
    int size = sizeof(arr) / sizeof(int);
    std::vector<int> vec(arr, arr + size);

    // 计算极值
    int max = std::max(arr[0], arr[1]);
    std::vector<int>::iterator iter = std::min_element(vec.begin(), vec.end());
    int min_ele = *iter;

    // 输出
    PutTitle("max:\n");
    PutContent(max);
    PutTitle("\nmin element:\n");
    PutContent(min_ele);

    PutTitle("\nAlgorithm maxmin end.\n");
}
