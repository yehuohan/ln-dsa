
#include <iostream>
#include <fstream>
#include <stack>

char**  getFileLines(const char* str, int& num);
int     getNodeData(char* str);

typedef struct BinNode
{
    int key;
    BinNode* parent;
    BinNode* left;
    BinNode* right;

    BinNode() : parent(nullptr), left(nullptr), right(nullptr){}
    BinNode(int e, BinNode* p = nullptr) : key(e), parent(p), left(nullptr), right(nullptr){}
    BinNode* insertLeft(int e) {return this->left = new BinNode(e, this);}
    BinNode* insertRight(int e) {return this->right = new BinNode(e, this);}
    void travPostOrder(BinNode* node, bool flg)
    {
        if (!node) return;
        this->travPostOrder(node->left, true);
        this->travPostOrder(node->right, true);
        std::cout << node->key;
        if (flg)
            std::cout << " ";
    }
}BinNode;

class BinTree
{
protected:
    BinNode*    m_root;
    int         m_size;

public:
    BinTree() : m_root(nullptr){};
    void    fromInOrder(char** lines, const int num);
    void    travPostOrder();
};


int main(int argc, char *argv[])
{
    int num;
    char** fd = getFileLines("test.txt", num);

    BinTree tree;
    tree.fromInOrder(fd, num);
    tree.travPostOrder();

    return 0;
}

char** getFileLines(const char* str, int& num)
{
    const int mc = 10;
    char line[mc];
    std::fstream fin;
    fin.open(str, std::ios_base::in);
    fin.getline(line, mc);
    //std::cin.getline(line, mc);

    // Get N
    num = 0;
    for(int k = 0; k < mc; k ++)
    {
        if (line[k] == '\0')
            break;
        num *= 10;
        num += int(line[k] - '0');
    }

    // Read 2N lines
    char** ll = new char*[2*num];
    for (int k = 0; k < 2*num; k ++)
    {
        *(ll+k) = new char[mc]; 
        fin.getline(*(ll+k), mc);
        //std::cin.getline(*(ll+k), mc);
    }
    fin.close();

    return ll;
}

int getNodeData(char* str)
{
    // Node data is from 1 to N
    // Pop : return 0
    if (str[3] == '\0')
        return 0;
    // Push : return node data
    int num = int(str[5] - '0');
    if (str[6] != '\0')
    {
        num *= 10;
        num += int(str[6] - '0');
    }
    return num;
}

void BinTree::fromInOrder(char** lines, const int num)
{
    if (!lines)
        return;

    std::stack<BinNode*> s;
    BinNode* node = nullptr;
    BinNode* popnode = nullptr;
    int flg, tmp;
    for (int k = 0; k < 2*num; k ++)
    {
        tmp = getNodeData(*(lines+k));
        if (tmp)
        {
            if (!this->m_root)
            {
                this->m_root = new BinNode(tmp);
                node = this->m_root;
            }
            else
            {
                if (flg)
                {
                    // Last is Pop
                    popnode->insertRight(tmp);
                    node = popnode->right;
                }
                else
                {
                    // Last is Push
                    node->insertLeft(tmp);
                    node = node->left;
                }
            }
            // Push
            s.push(node);
            flg = 0;
        }
        else
        {
            popnode = s.top();
            // Pop
            flg = 1;
            s.pop();
        }
    }
}

void BinTree::travPostOrder()
{
    if (this->m_root)
        this->m_root->travPostOrder(this->m_root, false);
}
