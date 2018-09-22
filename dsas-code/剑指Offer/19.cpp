
#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> printMatrix(std::vector<std::vector<int> > matrix)
    {
        std::vector<int> vec;
        int w0 = 0, w1 = matrix[0].size() - 1;
        int h0 = 0, h1 = matrix.size() - 1;
        while (w0 <= w1 && h0 <= h1)
        {
            // left -> right
            //if (w0 <= w1 && h0 <= h1)
            {
                for (int k = w0; k <= w1; k ++)
                    vec.push_back(matrix[h0][k]);
            }
            h0 ++;

            // top -> bottom
            if (w0 <= w1 && h0 <= h1)
            {
                for (int k = h0; k <= h1; k ++)
                    vec.push_back(matrix[k][w1]);
            }
            w1 --;

            if (w0 <= w1 && h0 <= h1)
            {
                for (int k = w1; k >= w0; k --)
                    vec.push_back(matrix[h1][k]);
            }
            h1 --;

            if (w0 <= w1 && h0 <= h1)
            {
                for (int k = h1; k >= h0; k --)
                    vec.push_back(matrix[k][w0]);
            }
            w0 ++;
        }

        return vec;
    }
};

int main()
{
    std::vector<std::vector<int>> matrix(0, std::vector<int>(4));
    std::vector<int> vec(4);
    vec[0] = 1; vec[1] = 2; vec[2] = 3; vec[3] = 4;
    matrix.push_back(vec);
    vec[0] = 5; vec[1] = 6; vec[2] = 7; vec[3] = 8;
    matrix.push_back(vec);
    vec[0] = 9; vec[1] = 10; vec[2] = 11; vec[3] = 12;
    matrix.push_back(vec);
    vec[0] = 13; vec[1] = 14; vec[2] = 15; vec[3] = 16;
    matrix.push_back(vec);


    Solution su;
    for (auto& it:su.printMatrix(matrix))
        std::cout << it << ", ";
}
