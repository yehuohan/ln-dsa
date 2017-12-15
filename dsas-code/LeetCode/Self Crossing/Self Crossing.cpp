
#include <iostream>

class Solution {
public:
	bool isSelfCrossing(vector<int>& x) {
		int n = x.size();
		if (n < 4)
			return false;
		
		for (int i = 3; i < n; i++)
		{
			//只有三种情况相交
			if (x[i] >= x[i - 2] 
				&& x[i - 1] <= x[i - 3]) 
				return true;  
				// Case 1: current line crosses the line 3 steps ahead of it
				// 即先增大后减小
			else if (i >= 4 
				&& x[i - 1] == x[i - 3] 
				&& x[i] + x[i - 4] >= x[i - 2]) 
				return true; 
				// Case 2: current line crosses the line 4 steps ahead of it
				// 即成矩形
			else if (i >= 5 
				&& x[i - 2] >= x[i - 4] 
				&& x[i] + x[i - 4] >= x[i - 2] 
				&& x[i - 1] <= x[i - 3] 
				&& x[i - 1] + x[i - 5] >= x[i - 3]) 
				return true;  
				// Case 3: current line crosses the line 6 steps ahead of it
				// 即先增大后减小
		}
		return false;
	}
};

int main()
{
    return 0;
}
