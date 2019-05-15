
/*
[编程题] 交错01串

时间限制：1秒
空间限制：32768K

如果一个01串任意两个相邻位置的字符都是不一样的,我们就叫这个01串为交错01串。例如: "1","10101","0101010"都是交错01串。
小易现在有一个01串s,小易想找出一个最长的连续子串,并且这个子串是一个交错01串。小易需要你帮帮忙求出最长的这样的子串的长度是多少。

输入描述:
输入包括字符串s,s的长度length(1 ≤ length ≤ 50),字符串中只包含'0'和'1'

输出描述:
输出一个整数,表示最长的满足要求的子串长度。

输入例子1:
111101111

输出例子1:
3
*/


#include <iostream>
#include <string>

int calc_longest_sub01(const std::string& s, int n)
{
    int len = 0;
    int max_len = 0;
    for (int k = 1; k < s.size(); k ++)
    {
        if (s[k] == '1' || s[k] == '0')
        {
            if (s[k-1] != s[k])
            {
                std::cout << s[k];
                len ++;
            }
            else
            {
                if (len > max_len) max_len = len;
                len = 0;
            }
        }
    }
    if (len > max_len) max_len = len;
    return max_len + 1;
}

int main(int argc, char *argv[])
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::string s("1010101");
    int length = 7;
    //std::cin >> s;
    //std::cin >> length;
    std::cout << calc_longest_sub01(s, length);
    
    return 0;
}
