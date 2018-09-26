
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

class Solution {
public:
    bool is_dig(char ch)
    {
        return ('0' <= ch && ch <= '9');
    }
    bool isNumeric(char* string)
    {
        if (string[0] == '\0')
            return false;
        bool dot = false;
        bool e = false;
        char prech = '\0';  // 
        int k = 0;
        while (string[k] != '\0')
        {
            // 根据前后字符判定
            if (string[k] == '+' || string[k] == '-')
            {
                if (!(
                    (prech == '\0' || prech == 'e' || prech == 'E') && string[k+1] != '\0'
                      ))
                    return false;
            }
            else if (string[k] == 'e' || string[k] == 'E')
            {
                if (!(
                    !e && is_dig(prech) && string[k+1] != '\0'
                    ))
                    return false;
                e = true;
            }
            else if (string[k] == '.')
            {
                if (!(
                    !dot
                    && !e
                    && (is_dig(prech) || prech == '+' || prech == '-')
                    && string[k+1] != '\0'
                    ))
                    return false;
                dot = true;
            }
            else if (is_dig(string[k]))
            { }
            else
            {
                return false;
            }
            prech = string[k++];
        }
        return true;
    }

};

int main()
{

}
