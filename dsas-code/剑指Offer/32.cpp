
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using std::vector;
using std::string;

class Solution {
public:
    string PrintMinNumber(vector<int> numbers) {
        std::string str;
        std::vector<std::string> num_str;

        for (int k = 0; k < numbers.size(); k ++)
            num_str.push_back(std::to_string(numbers[k]));


        std::sort(num_str.begin(), num_str.end(), [](std::string a, std::string b){
                return a+b < b+a;
            });

        for (auto it:num_str)
            str += it;

        return str;
    }
};

int main()
{
    int a[] = {3, 32, 321};
    std::vector<int> vec(a, a+3);
    Solution su;
    std::cout << su.PrintMinNumber(vec);
}
