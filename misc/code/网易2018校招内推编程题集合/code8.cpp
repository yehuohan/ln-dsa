
/*

[编程题] 小易喜欢的数列

时间限制：1秒
空间限制：32768K

小易非常喜欢拥有以下性质的数列:
1、数列的长度为n
2、数列中的每个数都在1到k之间(包括1和k)
3、对于位置相邻的两个数A和B(A在B前),都满足(A <= B)或(A mod B != 0)(满足其一即可)
例如,当n = 4, k = 7
那么{1,7,7,2},它的长度是4,所有数字也在1到7范围内,并且满足第三条性质,所以小易是喜欢这个数列的
但是小易不喜欢{4,4,4,2}这个数列。小易给出n和k,希望你能帮他求出有多少个是他会喜欢的数列。

输入描述:
输入包括两个整数n和k(1 ≤ n ≤ 10, 1 ≤ k ≤ 10^5)

输出描述:
输出一个整数,即满足要求的数列个数,因为答案可能很大,输出对1,000,000,007取模的结果。

输入例子1:
2 2

输出例子1:
3
*/

#include <iostream>
#include <vector>

/*!
 * @brief count_num
 * 排列组合
 */
int count_num(int n, int k)
{
    const int mod = 1000000007;

    std::vector<std::vector<int>> state;
    for (int i = 0; i <= n; i ++)
        state.push_back(std::vector<int>(k + 1, 0));

    // 长度为1，且以i结尾的合法数列均只有1个
    for (int i = 1; i <= k; i ++)
        state[1][i] = 1;

    // 求取长度为i，且以j结尾的合法数列个数
    for (int i = 2; i <= n; i ++)
    {
        // 长度为i-1的合法数列共sum个
        int sum = 0;
        for (int j = 1; j <= k; j ++)
            sum = (sum + state[i-1][j]) % mod;

        // 长度为i，且以j结层的合法数列有state[i][j]个
        for (int j = 1; j <= k; j ++)
        {
            state[i][j] = sum;
            // 减去不合法的数列(A%B==0的组合???)
            for (int q = j*2; q <= k; q += j)
                state[i][j] = (state[i][j] - state[i-1][q] + mod) % mod;
        }
    }

    // 对长度为n，且以i结尾的合法数列求和
    int count = 0;
    for (int i = 1; i <= k; i ++)
        count = (count + state[n][i]) % mod;

    return count;
}

int main(int argc, char *argv[])
{
    int n = 2, k = 2;
    //std::cin >> n >> k;
    std::cout << count_num(n, k);
    return 0;
}
