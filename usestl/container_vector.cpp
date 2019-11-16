
#include "usestl.h"
#include <iostream>
#include <vector>

/*!
 * @brief 动态数组
 *
 */
void container_vector(void)
{
    PutTitle("\nContainer vector begin.\n");

    // 1. 生成vector
    int arr[] = {3, 2, 1, 5, 4};
    std::vector<int> vec1(arr, arr+5);  // 从数组生成vector
    std::vector<int> vec2(5, 0);        // 生成vector时，初始5个值为0元素

    // 2. 访问元素
    vec2.front() = -1;
    vec2.at(1) = 1;
    vec2.pop_back();
    vec2.push_back(-10);

    // 输出结果
    PutTitle("vec1:\n");
    for (int k = 0; k < 5; k ++)
        PutContent(vec1[k] << ' ');

    PutTitle("\nvec2:\n");
    for (int k = 0; k < 5; k ++)
        PutContent(vec2[k] << ' ');

    PutTitle("\nContainer vector end.\n");
}
