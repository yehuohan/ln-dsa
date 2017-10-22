
//==============================================================================
/*!
 * @file binary_tree.h
 * @brief 二叉树的基本模块类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H value

#include "stack.h"
#include "queue.h"

namespace dsa
{

/*!
 * @addtogroup Tree
 * @{
 */

/*!
 * @brief 二叉树节点
 *
 */
template <typename T> struct bin_node
{
    bin_node<T>* parent;
    bin_node<T>* left;
    bin_node<T>* right;
    T data;
    int height;

    bin_node(const T& e, bin_node<T>* p)
    {
        this->data = e;
        this->parent = p;
        this->left = nullptr;
        this->right = nullptr;
    }

/*!
 * @brief 插入左子节点
 *
 * @param e: 节点数据
 * @return bin_node指针
 * @retval None
 */
    bin_node<T>*     insert_left(const T& e)
        { return this->left = new bin_node(e, this); }

/*!
 * @brief 插入右子节点
 *
 * @param e: 节点数据
 * @return bin_node指针
 * @retval None
 */
    bin_node<T>*     insert_right(const T& e)
        { return this->right = new bin_node(e, this); }

/*!
 * @brief 获取子树节点数量
 *
 * @param None
 * @return
 * @retval None
 */
    int             size()
    {
        int sum = 1;
        if(this->left) sum += this->left->size();
        if(this->right) sum += this->right->size();
        return sum;
    }
};


/*!
 * @brief 二叉树类
 *
 */
template <typename T>
class bin_tree
{
private:
    int             m_size;     /**< 节点数量 */
    bin_node<T>*     m_root;     /**< 树根节点 */

protected:
    virtual int update_height(bin_node<T>* node);    /**< 更新node高度 */
    void        update_height_above(bin_node<T>* node);  /**< 更新node及祖先高度 */

public:
    bin_tree()
    {
        this->m_size = 0;
        this->m_root = nullptr;
    }

    bin_tree(const T& ele)
    {
        this->m_size = 1;
        this->m_root = new bin_node<T>(ele, nullptr);
    }

    int     size() const {return this->m_size;}
    bool    is_empty() const {return !this->m_root;}
    bin_node<T>* create_root(const T& ele) {return this->m_root = new bin_node<T>(ele, nullptr);}
    bin_node<T>* root() {return this->m_root;}
    bin_node<T>* insert_left(bin_node<T>* node, const T& ele);
    bin_node<T>* insert_right(bin_node<T>* node, const T& ele);

    // traverse
};


/*! @} */


/*!
 * @brief 更新node高度
 *
 * @param node: bin_node节点
 * @return 返回节点高度
 * @retval None
 */
template <typename T>
int bin_tree<T>::update_height(bin_node<T>* node)
{
    // 叶子结点没有子结点了，其高度为 1 + (-1) = 0
    int a = node->left ? node->left->height : -1;
    int b = node->right ? node->right->height : -1;
    return node->height = 1 + ((a>=b)?a:b);
}

/*!
 * @brief 更新node及祖先高度
 *
 * @param node: bin_node节点
 * @return
 * @retval None
 */
template <typename T>
void bin_tree<T>::update_height_above(bin_node<T>* node)
{
    while(node)
    {
        update_height(node);
        node = node->parent;
    }
}

/*!
 * @brief 插入左子结点
 *
 * @param node: 新结点的交结点
 * @param ele: 新结点中的数据
 * @return 返回新结点的指针
 * @retval None
 */
template <typename T>
bin_node<T>* bin_tree<T>::insert_left(bin_node<T>* node, const T& ele)
{
    this->m_size ++;
    node->insert_left(ele);
    this->update_height_above(node);    // 新加结点后，高度变化
    return node->left;
}

/*!
 * @brief 插入右子结点
 *
 * @param node: 新结点的交结点
 * @param ele: 新结点中的数据
 * @return 返回新结点的指针
 * @retval None
 */
template <typename T>
bin_node<T>* bin_tree<T>::insert_right(bin_node<T>* node, const T& ele)
{
    this->m_size ++;
    node->insert_right(ele);
    this->update_height_above(node);
    return node->right;
}


/*!
 * @addtogroup Tree
 * 
 * @{
 */


/*!
 * @brief 依次仿问所有左子节点
 *
 * @param x: 节点指针
 * @param visit: 遍历函数
 * @param s: 栈，用于保存右子树
 * @return
 * @retval None
 */
template <typename T, typename VST>
static void visit_along_left_brach(bin_node<T>* x, VST& visit, dsa::stack<bin_node<T>* >& s)
{
    while(x)
    {
        visit(x->data);
        s.push(x->right);   // 右子树入栈，pop时，则从最低端右子树开始visit
        x = x->left;
    }
}

/*!
 * @brief 先序遍历, preorder
 *
 * @param node: 节点指针
 * @param visit: 遍历函数
 * @return
 * @retval None
 */
template <typename T, typename VST>
void traverse_DLR(bin_node<T>* node, VST& visit)
{
#if(0)
    // by recursion
    if(!node) return;
    visit(node->data);
    traverse_DLR(node->left, visit);
    traverse_DLR(node->right, visit);
#else

    // by iteration
    dsa::stack<bin_node<T>*> s;
    while(1)
    {
        visit_along_left_brach(node, visit, s);
        if(s.is_empty()) break;
        node = s.pop();    // pop出右子树，用以visit以右子树为root的左子树
    }
#endif
}


/*!
 * @brief 沿着左子树，将左子树顺序入栈
 * 经过此函数，最后入栈节点的左子树一定为nullptr
 *
 * @param x: 节点指针
 * @param s: 栈，用于保存右子树
 * @return
 * @retval None
 */
template <typename T>
static void go_along_left_branch(bin_node<T>* x, dsa::stack<bin_node<T>*>& s)
{
    while(x)
    {
        s.push(x);
        x = x->left;
    }
}

/*!
 * @brief 中序遍历, inorder
 *
 * @param node: 节点指针
 * @param visit: 遍历函数
 * @return
 * @retval None
 */
template <typename T, typename VST>
void traverse_LDR(bin_node<T>* node, VST& visit)
{
#if(0)
    // by recursion
    if(!node) return;
    traverse_LDR(node->left, visit);
    visit(node->data);
    traverse_LDR(node->right, visit);
#else

    // by iteration
    dsa::stack<bin_node<T>*> s;
    while(1)
    {
        go_along_left_branch(node, s);
        if(s.is_empty()) break;
        node = s.pop();
        visit(node->data);
        // right为null，在go_along_left_branch会直接跳出，下一次将visit LDR中的D
        // right不为null，则下一次将visit LDR中的R
        node = node->right;     
    }
#endif
}


/*!
 * @brief 后序遍历, postorder
 *
 * @param node: 节点指针
 * @param visit: 遍历函数
 * @retval None
 */
template <typename T, typename VST>
void traverse_LRD(bin_node<T>* node, VST& visit)
{
#if(0)
    // by recursion
    if(!node) return;
    traverse_LRD(node->left, visit);
    traverse_LRD(node->right, visit);
    visit(node->data);
#else

    // by iteration
    dsa::stack<bin_node<T>*> s;
    bin_node<T>* last_node = nullptr;

    // 先将左子树节点均入栈
    go_along_left_branch(node, s);
    while(!s.is_empty()) 
    {
        node = s.pop();
        // LRD中的D节点能被访问的前提是：无右子树或右子树已被访问过 
        if(!node->right || node->right == last_node)
        {
            visit(node->data);
            last_node = node;
        }
        else
        {
            // 将LRD中的D重新入栈，等待右子树被访问完
            s.push(node);
            node = node->right;     
            go_along_left_branch(node, s);
        }
    }
#endif
}

/*!
 * @brief 层次遍历(LayerOrder)
 *
 * @param node: 节点指针
 * @param visit: 遍历函数
 * @return
 * @retval None
 */
template <typename T, typename VST>
void traverse_LO(bin_node<T>* node, VST& visit)
{
    dsa::queue<bin_node<T>*> q;
    q.enqueue(node);
    while(!q.is_empty())
    {
        bin_node<T>* x = q.dequeue();
        visit(x->data);
        if(x->left) q.enqueue(x->left);
        if(x->right) q.enqueue(x->right);
    }
}


/*!
 * @brief 根据先序与中序序列重构二叉树的子树
 *
 * @param pre: 先序遍历序列
 * @param in: 中序遍历序列
 * @param node: 二叉树子树节点
 * @return
 * @retval None
 */
template <typename T>
static void construct_bintree_pre_in(const dsa::vector<T>& pre, const dsa::vector<T>& in, dsa::bin_node<T>*& node)
{
    // 查找子树的根节点
    int d_index = in.find(pre[0], 0, in.size());
    dsa::vector<T> l_pre, l_in;        // 左子树先序与中序序列
    dsa::vector<T> r_pre, r_in;        // 右子树先序与中序序列

    // 转移子树的先序与中序，先序与中序长度一样
    for(int k = 0; k < d_index; k ++)
    {
        l_pre.push_back(pre[k+1]);    // 转移左子树先序
        l_in.push_back(in[k]);        // 转移左子树中序
    }
    for(int k = d_index+1; k < in.size(); k++) 
    {
        r_pre.push_back(pre[k]);      // 转移右子树先序
        r_in.push_back(in[k]);        // 转移右子树中序
    }

    // 若子树为空，则不需要继续向下构建
    if(!l_pre.is_empty())
    {
        // 插件子树的根节点
        dsa::bin_node<T>* left = node->insert_left(l_pre[0]);
        // 继续重构左子树与右子树
        construct_bintree_pre_in(l_pre, l_in, left);
    }
    if(!r_pre.is_empty())
    {
        dsa::bin_node<T>* right = node->insert_right(r_pre[0]);
        construct_bintree_pre_in(r_pre, r_in, right);
    }
}

/*!
 * @brief 根据先序与中序序列重构二叉树
 *
 * 可以重构二叉树的条件：
 * (1).已知先序或后序 + 中序
 * (2).已知先序或后序 + 为真二叉树(节点有0或2个子节点，或节点出度为偶数)
 *
 * @param pre: 先序遍历序列
 * @param in: 中序遍历序列
 * @param bt: 二叉树
 * @return
 * @retval None
 */
template <typename T>
void construct_bintree(const dsa::vector<T>& pre, const dsa::vector<T>& in, dsa::bin_tree<T>& bt)
{
    bt.create_root(pre[0]);
    dsa::bin_node<T>* root = bt.root();
    construct_bintree_pre_in(pre, in, root);
}


/*! @} */

// namespace dsa end
}

#endif /* ifndef _BINARY_TREE_H */
