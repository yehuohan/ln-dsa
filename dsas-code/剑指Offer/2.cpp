
#include <iostream>
#include <cstring>

class Solution {
public:
	void replaceSpace(char *str,int length) {
        int cnt = 0;
        char* p = str;
        while (*p != '\0')
        {
            if (*p++ == ' ')
                cnt ++;
        }

        // length包括 "%20" 所占的空间
        int e = length - 1 - cnt*2;
        int k = length - 1;
        p = str;
        while (k > e && e >= 0)
        {
            if (p[e] == ' ')
            {
                p[k--] = '0';
                p[k--] = '2';
                p[k--] = '%';
                e--;
            }
            else
            {
                p[k] = p[e];
                k--;
                e--;
            }

        }
	}
};

int main()
{
    char *str = "we are happy\0xxxxxxx";
    int length = 13 + 4;

    Solution su;
    // 牛客上AC，本地出错~~
    su.replaceSpace(str, length);
    std::cout << str;

    return 0;
}
