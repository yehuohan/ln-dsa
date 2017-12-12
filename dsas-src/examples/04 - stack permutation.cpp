
#include <iostream>
#include "../stack.h"


//==============================================================================
/*!
 * @brief check whether a is one stack permutation of b by enumeration
 *
 * 枚举法：对于 B 中任三个元素下标，1 <= i < j < k <= n，若 A 有 ..k...i...j.. 的顺序
 *         则 A 必定不是 B 的stack permutation
 * 这里设定a[], b[]中存储的是元素的下标，即元素均在[0,n)范围内
 *
 * @param a[],n sequence a and its length, [a, b, c, ... ,>
 * @param b[],n sequence b and its length, <1, 2, 3, ... ,]
 * @return true or false
 * @retval None
 */
//==============================================================================
bool is_sp_enumeration(int a[], int b[], int n)
{
    return false;
}

//==============================================================================
/*!
 * @brief check whether a is one stack permutation of b by simulation
 *
 * 通过混洗操作模拟，看能否由 b 得到 a
 *
 * @param a[],n sequence a and its length, [a, b, c, ... ,>
 * @param b[],n sequence b and its length, <1, 2, 3, ... ,]
 * @return true or false
 * @retval None
 */
//==============================================================================
bool is_sp_simulation(int a[], int b[], int n)
{
    dsa::Stack<int> s;

    int k = 0, i = 0;
    while(k < n)
    {
        // 对于b，一直向s入栈
        s.push(b[k++]);

        // 对于a，只要s.top()与最底元素相同，则s出栈
        while(!s.is_empty() && s.top() == a[i])
        {
            s.pop();
            i++;
        }
    }
    // 若s为空，则 a 为 b 的一个stack permutation
    return s.is_empty();
}



int main(void)
{
    int n = 6;
    int a[] = {2, 3, 1, 4, 6, 5};
    int b[] = {1, 2, 3, 4, 5, 6};

    std::cout << (is_sp_simulation(a, b, n) ? "True" : "False") << std::endl;

    return 0;
}
