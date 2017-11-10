
//==============================================================================
/*!
 * @file binary_node.h
 * @brief 二叉结点类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _BINARY_NODE_H
#define _BINARY_NODE_H

#include "stack.h"
#include "queue.h"

namespace dsa
{

/*!
 * @addtogroup Tree
 * @{
 */

/*!
 * @name 节点相关宏
 * @{
 */

#define BN_Stature(x)       ((x) ? (x)->height : -1)     //节点高度（与“空树高度为-1”的约定相统一）
#define BN_IsRoot(x)        (!((x).parent))
#define BN_IsLeftChild(x)   (((x).parent) && (&(x)==(x).parent->left))
#define BN_IsRightChild(x)  (((x).parent) && (&(x)==(x).parent->right))
#define BN_IsLeaf           (!((x).left) && !((x).right))
#define BN_HasParent(x)     ((x).parent)
#define BN_HasLeftChild(x)  ((x).left)
#define BN_HasRightChild(x) ((x).right)
#define BN_HasChild(x)      ((x).left || (x).right)
#define BN_HasBothChild(x)  ((x).left && (x).right)

/** 获取父节点的孩子节点指针，用于设置父节点的孩子节点，m_root为BinTree中的根节点 */
#define PtrChildOfParent(x)     (BN_IsRoot(x) ? this->m_root : (BN_IsLeftChild(x) ? (x).parent->left : (x).parent->right))

/*! @} */


/*!
 * @brief 二叉树节点
 *
 */
template <typename T> struct BinNode
{
    BinNode<T>* parent;
    BinNode<T>* left;
    BinNode<T>* right;
    T           data;
    int         height;

    BinNode() 
    {
        this->height = 0;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }

    BinNode(const T& e, BinNode<T>* p = nullptr) : data(e), parent(p)
    {
        this->height = 0;
        this->left = nullptr;
        this->right = nullptr;
    }

    /*!
     * @brief 插入左子节点
     *
     * @param e: 节点数据
     * @return BinNode指针
     * @retval None
     */
    BinNode<T>* insert_left(const T& e)
        { return this->left = new BinNode(e, this); }

    /*!
     * @brief 插入右子节点
     *
     * @param e: 节点数据
     * @return BinNode指针
     * @retval None
     */
    BinNode<T>* insert_right(const T& e)
        { return this->right = new BinNode(e, this); }

    /*!
     * @brief 获取子树节点数量
     *
     * @param None
     * @return
     * @retval None
     */
    int size()
    {
        int sum = 1;
        if(this->left) sum += this->left->size();
        if(this->right) sum += this->right->size();
        return sum;
    }

    BinNode<T>* successor();

    // 遍历算法
    template <typename VST> void traverse_DLR(VST& visit);      // 先序
    template <typename VST> void traverse_LDR(VST& visit);      // 中序
    template <typename VST> void traverse_LRD(VST& visit);      // 后序
    template <typename VST> void traverse_LO(VST& visit);       // 层次

    // 运算符重写
    bool operator< ( BinNode const& bn ) { return data < bn.data; }
    bool operator> ( BinNode const& bn ) { return data > bn.data; }
    bool operator== ( BinNode const& bn ) { return data == bn.data; }
    bool operator!= ( BinNode const& bn ) { return data != bn.data; }

    //BinNode<T>* zig();                  // 顺时针旋转
    //BinNode<T>* zag();                  // 逆时针旋转
};

/*!
 * @brief 获取中序遍历下当前节点的直接后继节点
 *
 * 有右子树：r为当前节点，d为r的直接后继
 *    r
 *   / \
 *  L   a
 *     / \
 *    b   c
 *     \
 *      d
 *
 * 无右子树：r为当前节点，d为r的直接后继
 *        e
 *       / \
 *      d  R
 *     / \
 *    b   c
 *   / \
 *  a   r
 *     /
 *    L
 *
 * @param None
 * @return 返回直接后继节点
 * @retval None
 */
template <typename T>
BinNode<T>* BinNode<T>::successor()
{
    BinNode<T>* s = this;
    if (this->right)
    {
        s = this->right;
        while(s->left) s = s->left;     //为右子树中最靠左（最小）的节点
    }
    else
    {
        //或者为“将当前节点包含于其左子树中的最低祖先”
        if (s->parent && s->parent->right == s) s = s->parent;
        s = s->parent;
    }
    return s;
}


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
static void visit_along_left_brach(BinNode<T>* x, VST& visit, dsa::stack<BinNode<T>* >& s)
{
    while(x)
    {
        visit(x->data);
        s.push(x->right);   // 右子树入栈，pop时，则从最低端右子树开始visit
        x = x->left;
    }
}

/*!
 * @brief 先序(preorder)遍历
 *
 * 通过迭代实现
 *
 * @param node: 节点指针
 * @param visit: 遍历函数
 * @return
 * @retval None
 */
template <typename T, typename VST>
void traverse_DLR_iteration(BinNode<T>* node, VST& visit)
{
    dsa::stack<BinNode<T>*> s;
    while(1)
    {
        visit_along_left_brach(node, visit, s);
        if(s.is_empty()) break;
        node = s.pop();    // pop出右子树，用以visit以右子树为root的左子树
    }
}

/*!
 * @brief 先序(preorder)遍历
 *
 * 通过递归实现
 *
 * @param node: 节点指针
 * @param visit: 遍历函数
 * @return
 * @retval None
 */
template <typename T, typename VST>
void traverse_DLR_recursion(BinNode<T>* node, VST& visit)
{
    if(!node) return;
    visit(node->data);
    traverse_DLR_recursion(node->left, visit);
    traverse_DLR_recursion(node->right, visit);
}

/*!
 * @brief 先序(preorder)遍历接口
 *
 * @param visit: 遍历函数
 * @return
 * @retval None
 */
template <typename T>
template<typename VST>
void BinNode<T>::traverse_DLR(VST& visit)
{
    //traverse_DLR_recursion(this, visit);
    traverse_DLR_iteration(this, visit);
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
static void go_along_left_branch(BinNode<T>* x, dsa::stack<BinNode<T>*>& s)
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
void traverse_LDR_iteration(BinNode<T>* node, VST& visit)
{
    dsa::stack<BinNode<T>*> s;
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
}

/*!
 * @brief 中序(inorder)遍历
 *
 * @param node: 节点指针
 * @param visit: 遍历函数
 * @return
 * @retval None
 */
template <typename T, typename VST>
void traverse_LDR_recursion(BinNode<T>* node, VST& visit)
{
    if(!node) return;
    traverse_LDR_recursion(node->left, visit);
    visit(node->data);
    traverse_LDR_recursion(node->right, visit);
}

/*!
 * @brief 中序(inorder)遍历
 *
 * @param visit: 遍历函数
 * @return
 * @retval None
 */
template <typename T>
template<typename VST>
void BinNode<T>::traverse_LDR(VST& visit)
{
    //traverse_LDR_recursion(this, visit);
    traverse_LDR_iteration(this, visit);
}


/*!
 * @brief 后序(postorder)遍历
 *
 * @param node: 节点指针
 * @param visit: 遍历函数
 * @retval None
 */
template <typename T, typename VST>
void traverse_LRD_iteration(BinNode<T>* node, VST& visit)
{
    dsa::stack<BinNode<T>*> s;
    BinNode<T>* last_node = nullptr;

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
}

/*!
 * @brief 后序(postorder)遍历
 *
 * @param node: 节点指针
 * @param visit: 遍历函数
 * @retval None
 */
template <typename T, typename VST>
void traverse_LRD_recursion(BinNode<T>* node, VST& visit)
{
    if(!node) return;
    traverse_LRD_recursion(node->left, visit);
    traverse_LRD_recursion(node->right, visit);
    visit(node->data);
}

/*!
 * @brief 后序(postorder)遍历
 *
 * @param visit: 遍历函数
 * @return
 * @retval None
 */
template <typename T>
template <typename VST>
void BinNode<T>::traverse_LRD(VST& visit)
{
    //traverse_LRD_recursion(this, visit);
    traverse_LRD_iteration(this, visit);
}


/*!
 * @brief 层次遍历(LayerOrder)
 *
 * @param visit: 遍历函数
 * @return
 * @retval None
 */
template <typename T>
template <typename VST>
void BinNode<T>::traverse_LO(VST& visit)
{
    dsa::queue<BinNode<T>*> q;
    q.enqueue(this);
    while(!q.is_empty())
    {
        BinNode<T>* x = q.dequeue();
        visit(x->data);
        if(x->left) q.enqueue(x->left);
        if(x->right) q.enqueue(x->right);
    }
}


/*! @} */

// namespace dsa end
}

#endif /* ifndef _BINARY_NODE_H */
