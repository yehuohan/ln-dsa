
#include <iostream>
#include <stack>
using std::stack;

class Solution
{
public:
    void push(int node) {
        while (!this->stack1.empty())
        {
            stack2.push(stack1.top());
            stack1.pop();
        }
        stack1.push(node);
        while (!this->stack2.empty())
        {
            stack1.push(stack2.top());
            stack2.pop();
        }
    }

    int pop() {
        int val = stack1.top();
        stack1.pop();
        return val;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};

int main()
{
    Solution su;
    su.push(10);
    su.push(50);
    std::cout << su.pop() << std::endl;
    std::cout << su.pop() << std::endl;

}
