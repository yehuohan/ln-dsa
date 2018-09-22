
#include <iostream>
#include <vector>


class Solution {

private:
    std::vector<int> s;
    std::vector<int> m;

public:
    void push(int value) {
        s.push_back(value);
        if (m.empty() || value < m[m.size()-1])
            m.push_back(value);
    }
    void pop() {
        if (this->top() == m[m.size() - 1])
            m.pop_back();
        s.pop_back();
    }
    int top() {
        return s[s.size() - 1];
    }
    int min() {
        return m[m.size() - 1];
    }
};


int main()
{

}
