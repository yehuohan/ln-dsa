
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
 * @addtogroup TBinaryTree
 * @{
 */

/*!
 * @name 节点相关宏
 * @{
 */

#define BN_Stature(x)       ((x) ? (x)->height : -1)     /**<  节点高度（与“空树高度为-1”的约定相统一） */
#define BN_IsRoot(x)        (!((x).parent))
#define BN_IsLeftChild(x)   (((x).parent) && (&(x)==(x).parent->left))
#define BN_IsRightChild(x)  (((x).parent) && (&(x)==(x).parent->right))
#define BN_IsLeaf           (!((x).left) && !((x).right))
#define BN_HasParent(x)     ((x).parent)
#define BN_HasLeftChild(x)  ((x).left)
#define BN_HasRightChild(x) ((x).right)
#define BN_HasChild(x)      ((x).left || (x).right)
#define BN_HasBothChild(x)  ((x).left && (x).right)

/** 获取节点x在父节点中的孩子节点指针引用，用于设置父节点的孩子节点，m_root为BinTree中的根节点 */
#define RefFromParent(x)    (BN_IsRoot(x) ? this->m_root : (BN_IsLeftChild(x) ? (x).parent->left : (x).parent->right))

#define BN_IsBlack(x)       (!(x) || (dsa::RBColor::Black == (x)->color))   // 红黑树external nodes均为黑
#define BN_IsRed(x)         (!BN_IsBlack(x))                                // 非黑即红

/** 检测黑高度是否正确 */
#define BN_BlackHeightUpdated(x) ( \
   ( BN_Stature((x).left) == BN_Stature((x).right)) && \
   ((x).height == ( BN_IsRed(&x) ? BN_Stature((x).left) : BN_Stature((x).left )+1)))

/*! @} */


/*!
 * @name 类型定义与声明
 * @{
 */

/** 红黑节点 */
typedef enum
{
    Red,
    Black
}RBColor;

template <typename T> struct BinNode;

/** 二叉树节点指针类型 */
template <typename T>
using BinNodePtr = struct BinNode<T>*;

/*! @} */


/*!
 * @brief 二叉树节点
 *
 */
template <typename T> struct BinNode
{
    BinNodePtr<T> parent;
    BinNodePtr<T> left;
    BinNodePtr<T> right;
    T             data;
    int           height;
    int           npl;        /**< Null Path Length */
    RBColor       color;

    BinNode()
        : parent(nullptr), left(nullptr), right(nullptr), height(0), npl(1),color(RBColor::Red) {}
    BinNode(const T& e, BinNodePtr<T> p = nullptr, BinNodePtr<T> ll = nullptr, BinNodePtr<T> rr = nullptr,
            int h = 0, int n = 1, RBColor c = RBColor::Red)
        : data(e), parent(p), left(ll), right(rr), height(h), npl(n), color(c) {}

    /** 插入左子节点 */
    BinNodePtr<T> insert_left(const T& e) {return this->left = new BinNode(e, this);}
    /** 插入右子节点 */
    BinNodePtr<T> insert_right(const T& e) {return this->right = new BinNode(e, this);}
    /** 获取子树节点数量 */
    int size()
    {
        int sum = 1;
        if(this->left) sum += this->left->size();
        if(this->right) sum += this->right->size();
        return sum;
    }

    BinNodePtr<T> successor();

    // 遍历算法
    template <typename VST> void traverse_DLR(VST& visit);      // 先序
    template <typename VST> void traverse_LDR(VST& visit);      // 中序
    template <typename VST> void traverse_LRD(VST& visit);      // 后序
    template <typename VST> void traverse_LO(VST& visit);       // 层次

    // 运算符重写
    bool operator<  (const BinNode& bn) {return this->data < bn.data;}
    bool operator>  (const BinNode& bn) {return bn.data < this->data;}
    bool operator== (const BinNode& bn) {return !(this->data < bn.data || bn.data < this->data);}
    bool operator!= (const BinNode& bn) {return  (this->data < bn.data || bn.data < this->data);}

    //BinNodePtr<T> zig();                  // 顺时针旋转
    //BinNodePtr<T> zag();                  // 逆时针旋转
};

template <typename T, typename VST> static void traverse_DLR_iteration(BinNodePtr<T> node, VST& visit);
template <typename T, typename VST> static void traverse_DLR_recursion(BinNodePtr<T> node, VST& visit);
template <typename T, typename VST> static void traverse_LDR_iteration(BinNodePtr<T> node, VST& visit);
template <typename T, typename VST> static void traverse_LDR_recursion(BinNodePtr<T> node, VST& visit);
template <typename T, typename VST> static void traverse_LRD_iteration(BinNodePtr<T> node, VST& visit);
template <typename T, typename VST> static void traverse_LRD_recursion(BinNodePtr<T> node, VST& visit);

/*! @} */


/*!
 * @brief 获取中序遍历下当前节点的直接后继节点
 * <pre>
 * 有右子树：r为当前节点，d为r的直接后继
 *    r
 *   / \
 *  L   a
 *     / \
 *    d   c
 *     \
 *      b
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
 * </pre>
 * @param None
 * @return 返回直接后继节点
 * @retval None
 */
template <typename T>
BinNodePtr<T> BinNode<T>::successor()
{
    BinNodePtr<T> s = this;
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
 * @brief 先序(preorder)遍历
 *
 * <pre>
 * (1) 基本顺序
 *     D
 *    / \
 *   L   R
 * 先序遍历： D --> L --> R
 *
 * (2) 通过迭代实现：
 *          d
 *        /   \
 *      l1    r1 /
 *     / \      / => 对任何以d为根节点的子树，执行以下过程（称之为DLR过程）：
 *   l2  r2    /     因为先访问D(即d,l1,l2)，所以在访问D的过程中，将R(r1,r2)按斜线方向入栈；
 *                   将出栈的节点R，当成新的子树d节点，执行DLR过程；
 *
 * 先序遍历    : d - l1 - l2 - r2 - r1
 * d - l1 - l2 : 从d开始，沿着left一直visit下去（注意将right入栈）；
 * r2 - r1     : 看成一个Stack，r2最后入栈，但最先访问；
 *               访问r2时，同样从r2开始，沿着left一直visit下去（注意将right入栈）；
 * </pre>
 *
 * @param node: 节点指针
 * @param visit: 遍历函数
 * @return
 * @retval None
 */
template <typename T, typename VST>
static void traverse_DLR_iteration(BinNodePtr<T> node, VST& visit)
{
    dsa::Stack<BinNodePtr<T> > s;
    s.push(node);
    while (!s.is_empty())
    {
        node = s.pop();             // pop出右子节点
        while (node)
        {
            visit(node->data);
            s.push(node->right);    // 右子节点入栈
            node = node->left;
        }
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
static void traverse_DLR_recursion(BinNodePtr<T> node, VST& visit)
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
 * @brief 中序(inorder)遍历
 *
 * <pre>
 * (1) 基本顺序
 *     D
 *    / \
 *   L   R
 * 先序遍历： L --> D --> R
 *
 * (2) 通过迭代实现：
 *        /    d
 *       /   /   \
 *      /  l1    r1
 *     /  / \
 *    / l2  r2
 *   / => 对任何以d为根节点的子树，执行以下过程（称之为LDR过程）：
 *        因为需要访问完L后才能访问D，故先将L(d,l1,l2)按斜线方向入栈（即沿left入栈）；
 *        每个出栈的节点，先访问，再转向R(r2,r1)，再将R当成新子树的根节点d，执行LDR过程；
 *
 * 中序遍历  : l2 - l1 - r2 - d - r1
 * Stack示例 : 将L一直入栈，直至栈为 [d - l1 - l2>，然后弹出l2，访问l2，转向l2->right；
 *             l2->right为nullptr，故不需要将L入栈，继续弹出l1，访问l1，转向l1->right；
 *             l1->right不为nullptr，故需要将L入栈，然后......；
 *             一直重复上述过程即可；
 * </pre>
 *
 * @param node: 节点指针
 * @param visit: 遍历函数
 * @return
 * @retval None
 */
template <typename T, typename VST>
static void traverse_LDR_iteration(BinNodePtr<T> node, VST& visit)
{
    dsa::Stack<BinNodePtr<T> > s;
    while(1)
    {
        while(node)
        {
            s.push(node);       // 将L入栈
            node = node->left;
        }
        if (s.is_empty()) break;
        node = s.pop();
        visit(node->data);      // 访问D
        node = node->right;     // 转到R (R可以为nullptr)
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
static void traverse_LDR_recursion(BinNodePtr<T> node, VST& visit)
{
    if(!node) return;
    traverse_LDR_recursion(node->left, visit);
    visit(node->data);
    traverse_LDR_recursion(node->right, visit);
}

/*!
 * @brief 中序(inorder)遍历接口
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
 * <pre>
 * (1) 基本顺序
 *     D
 *    / \
 *   L   R
 * 先序遍历： L --> R --> D
 *
 * (2) 通过迭代实现：
 *        /    d
 *       /   /   \
 *      /  l1    r1
 *     /  / \
 *    / l2  r2
 *   / => 对任何以d为根节点的子树，执行以下过程（称之为LRD过程）：
 *        因为需要访问完L后才能访问R，访问完R后才能访问D，故先将L(d,l1,l2)按斜线方向入栈（即沿left入栈）；
 *        对每个出栈的节点，<1>如果：没有右子树，或者右子树已经访问完毕，则访问之，然后继续弹出节点，继续<1>过程；
 *                          <2>否则：转向R(r2,r1)，再将R当成新子树的根节点d，执行LRD过程；
 *
 * 后序遍历  : l2 - r2 - l1 - r1 - d
 *
 * </pre>
 *
 * @param node: 节点指针
 * @param visit: 遍历函数
 * @return
 * @retval None
 */
template <typename T, typename VST>
static void traverse_LRD_iteration(BinNodePtr<T> node, VST& visit)
{
    dsa::Stack<BinNodePtr<T> > s;
    BinNodePtr<T> last_visited = nullptr;

    while(node)
    {
        s.push(node); node = node->left; // 将L入栈
    }
    while(!s.is_empty())
    {
        node = s.pop();
        // LRD中的D节点能被访问的前提是：无右子树或右子树已被访问过
        if (!node->right || node->right == last_visited )
        {
            visit(node->data);
            last_visited = node;
        }
        else
        {
            // 将LRD中的D重新入栈，等待右子树被访问完
            s.push(node);
            node = node->right;
            while(node)
            {
                s.push(node); node = node->left; // 将L入栈
            }
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
static void traverse_LRD_recursion(BinNodePtr<T> node, VST& visit)
{
    if(!node) return;
    traverse_LRD_recursion(node->left, visit);
    traverse_LRD_recursion(node->right, visit);
    visit(node->data);
}

/*!
 * @brief 后序(postorder)遍历接口
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
 * <pre>
 * 通过迭代实现：
 *             d
 *           /   \
 *         l1    r1
 *        / \
 *      l2  r2
 *
 * 层次遍历  : d - l1 - r1 - l2 - r2
 * 将遍历的顺序，看成一个队列：d最先入队，故最先访问；
 *                             r2最后入队，最后访问；
 * </pre>
 *
 * @param visit: 遍历函数
 * @return
 * @retval None
 */
template <typename T>
template <typename VST>
void BinNode<T>::traverse_LO(VST& visit)
{
    dsa::Queue<BinNodePtr<T> > q;
    BinNodePtr<T> node = this;
    q.enqueue(node);
    while(!q.is_empty())
    {
        node = q.dequeue();
        visit(node->data);
        if(node->left) q.enqueue(node->left);
        if(node->right) q.enqueue(node->right);
    }
}

} /* dsa */

#endif /* ifndef _BINARY_NODE_H */
