
#include <iostream>
#include <cstdio>
#include <vector>

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
    void travPreOrder(BinNode* node, bool flg)
    {
        if (!node) return;
        if (flg)
            std::cout << " ";
        std::cout << node->key;
        this->travPreOrder(node->left, true);
        this->travPreOrder(node->right, true);
    }
}BinNode;

class BinTree
{
protected:
    BinNode*    m_root;
    int         m_size;

public:
    BinTree() : m_root(nullptr){};
    void    fromInPost(int* in, int* post, int num);
    void    createSubTree(const std::vector<int>& in,
                            const std::vector<int>& post,
                            BinNode*& root);
    void    travPreOrder();
};

int     getInPost(int*& in, int*& post);


int main(int argc, char *argv[])
{
    int* sin;       // inorder
    int* spost;     // postorder
    int num = getInPost(sin, spost);

    BinTree tree;
    tree.fromInPost(sin, spost, num);
    tree.travPreOrder();

    delete[] sin;
    delete[] spost;
    return 0;
}

int getInPost(int*& in, int*& post)
{
    int num;
    std::cin >> num;
    in = new int[num];
    post = new int[num];

    for (int k = 0; k < num; k ++)
        std::cin >> post[k];
    for (int k = 0; k < num; k ++)
        std::cin >> in[k];

    return num;
}

void createSubTree()
{

}

void BinTree::fromInPost(int* in, int* post, int num)
{
    this->m_root = new BinNode(post[num-1]);
    std::vector<int> vin;
    std::vector<int> vpost;
    for (int k = 0; k < num; k++)
    {
        vin.push_back(in[k]);
        vpost.push_back(post[k]);
    }
    this->createSubTree(vin, vpost, this->m_root);
}

void BinTree::createSubTree(const std::vector<int>& in,
                            const std::vector<int>& post,
                            BinNode*& root)
{
    unsigned int iD;
    for (unsigned int k = 0; k < in.size(); k++) {
        if (in[k] == post[post.size()-1]) {
            iD = k;
            break;
        }
    }

    std::vector<int> lin, rin;
    std::vector<int> lpost, rpost;

    for (unsigned int k = 0; k < iD; k++){
        lin.push_back(in[k]);
        lpost.push_back(post[k]);
    }
    for (unsigned int k = iD+1; k < in.size(); k++){
        rin.push_back(in[k]);
        rpost.push_back(post[k-1]);
    }

    if (!lpost.empty()){
        BinNode* left = root->insertLeft(lpost[lpost.size()-1]);
        this->createSubTree(lin, lpost, left);
    }
    if (!rpost.empty()){
        BinNode* right = root->insertRight(rpost[rpost.size()-1]);
        this->createSubTree(rin, rpost, right);
    }
}

void BinTree::travPreOrder()
{
    std::cout << "Preorder: ";
    if (this->m_root)
        this->m_root->travPreOrder(this->m_root, false);
}
