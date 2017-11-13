//==============================================================================
/*!
 * @file b_tree.h
 * @brief b-tree类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _B_TREE_H
#define _B_TREE_H

#include "b_node.h"

namespace dsa
{

/*!
 * @addtogroup Tree
 * @{
 */

/*!
 * @brief b-tree类
 *
 * <pre>
 *
 * 对于叶节点(以5阶b-tree为例)：
 * key       [0]  [1]  [2]  [3]     -> 最低层叶节点
 * child  [0]  [1]  [2]  [3]  [4]   -> 叶节点的子节点为external nodes，
 *                                     即只是在vector(child)有一个BTNode指针，值为nullptr;
 *                                     也只有external nodes指向nullptr。
 *
 *           r                      ---
 *          / \                      |
 *         /   \     internal nodes  |
 *        /     \                    |
 *       /_______\   (__为叶节点)   ---
 *      |||||||||||  external nodes  |
 *                                  ---
 * </pre>
 */
template <typename T>
class BTree
{
protected:
    int m_size;                     /**< 关键码总数 */
    int m_order;                    /**< 阶次，也即最多分支数为m_order，每个节点关键码最多m_order-1 */
    dsa::BTNode<T>* m_root;         /**< 根节点 */
    dsa::BTNode<T>* m_hot;          /**< search最后访问的非空节点位置 */

    void solve_overflow(BTNode<T>*);
    void solve_underflow(BTNode<T>*);

public:
    BTree(int order = 3) : m_size(0), m_order(order){ this->m_root = new BTNode<T>(); }
    //~BTree(){if (m_root) ;}
    BTNode<T>*  search(const T& e);
    bool        insert(const T& e);
    bool        remove(const T& e);

    BTNode<T>*  root(){return this->m_root;};
};


/*!
 * @brief 使用分裂修复上溢
 *
 * <pre>
 * 取中位数分裂，s = ⌊m/2⌋ (即向下取整，m为b-tree的阶)，如下图所示：
 * 即m为奇数时，s为key正中间位置，m为偶数时，s为key均分后左侧的最后一个位置。
 * *[k0]*[k1]*[k2]* ... *[k(m-1)]*
 *                   |
 *                   V
 * *[k0]*[k1]*k(s-1)] * [ks] * [k(s+1)]* ... *[k(m-1)]*
 * ------------------   ----   -----------------------
 * 作为ks左子节点   上移至父节点         作为ks右子节点
 *
 * 以4阶b-tree为例，演示分裂操作：
 * 将[3]上移至父节点
 *     *[0]*[10]*             *[0]*[3]*[10]*
 *      /  \                     /     \
 *     r    \   s     =>        /       \
 *           \ /               /         \
 *  *[1]*[2]*[3]*[5]*     *[1]*[2]*    *[5]*
 *  -----------------     ---------    -----
 *     原node节点       分裂后的node   新节点rc
 * 新的左右子节点的分支数分别为2和3(2+3=5>4)，均会满足>=⌈m/2⌉=2
 *
 * s之后(即[3]之后的*和[])的关键码和分支节点将转移到rc中;
 * 根节点上溢时，分裂出的新根节点，且新的根节点只有2个分支;
 * 根据分裂特性，可知非叶节点的子节点不可指向nullptr。
 *
 * </pre>
 *
 * @param node: 可能发生上溢的节点
 * @return
 * @retval None
 */
template <typename T>
void BTree<T>::solve_overflow(BTNode<T>* node)
{
    // 根据分支数判断是否上溢
    if (node->child.size() <= this->m_order)
        return;

    // 判断是否为根节点
    BTNode<T>* p = node->parent;
    if (!p)
    {
        // 在在根节点上溢时，树高度会增加
        this->m_root = p = new BTNode<T>(); // BTNode默认构造函数，在没关键码时有一个指向nullptr子节点
        p->child[0] = node;
        node->parent = p;
    }

    // 转移node中s之后关键码和分支节点，追加到新节点rc中
    // 即转移示意图中的 *[5]* 部分
    int s = this->m_order / 2;              // 确定上移的节点位置
    BTNode<T>* rc = new BTNode<T>();        // BTNode默认构造函数，在没关键码时有一个指向nullptr子节点
    rc->child.clear();                      // 清除第一个默认添加的nullptr子节点
    for (int k = s + 1; k < node->key.size(); k ++)
    {
        rc->key.push_back(node->key[k]);
        rc->child.push_back(node->child[k]);
    }
    rc->child.push_back(node->child[node->child.size()-1]); // 分支节点数比关键码数多1
    if (rc->child[0])                       // 非叶节点的子节点均在存(不为nullptr)
    {
        for (int k = 0; k < rc->child.size(); k ++)
            rc->child[k]->parent = rc;      // 更新父节点，rc即在p->child中
    }
    node->key.remove(s+1, node->key.size());// 移除原节点node中的关键码和分支
    node->child.remove(s+1, node->child.size());

    // 上移目标关键码
    // 即上移示意图的中 [3]
    int r = p->key.search(node->key[s]);    // 确定移至父节点的位置
    p->key.insert(r+1, node->key.remove(s));
    p->child.insert(r+2, rc);               // 连接节点，p->child[r+2]现在指向rc
    rc->parent = p;

    solve_overflow(p);
}

/*!
 * @brief 修复下溢
 *
 * <pre>
 *
 * 以4阶b-tree为例，分支数应>=2，关键码数应>=1
 *
 * 通过旋转(向左侧子节点借)修复下溢(#也是子节点，方便对比观看)：
 *        r-1  y  r
 *          \ /  /
 *      *[0]*[5]*[10]*            *[0]*[3]*[10]*
 *         /    \                    /     \
 *        /      \      =>          /       \
 *       /        \                /         \
 * *[1]*[2]*[3]#   *         *[1]*[2]*     #[5]*
 *                ---                       /
 *            下溢节点node                 y
 * 旋转前后，节点#均在[3]和[5]之间
 *
 * 通过合并修复下溢：
 *             y  r
 *            /  /
 *      *[0]*[5]#[10]*         *[0]*[10]*
 *         /    \                  |
 *        /      \      =>         |
 *       /        \                |
 *    *[1]*        *            *[1]*[5]*
 *                ---
 *            下溢节点node
 * 合并后，将删除节点#
 *
 * </pre>
 *
 * @param None
 * @return
 * @retval None
 */
template <typename T>
void BTree<T>::solve_underflow(BTNode<T>* node)
{
    int order_floor = (this->m_order+1)/2;
    if (node->child.size() >= order_floor)
        return;

    BTNode<T>* p = node->parent;
    if (!p)
    {
        if ((0 == node->key.size()) && node->child[0])  // 根节点不含关键码(即没有数据了)
        {
            // 在在根节点下溢时，树高度会下降
            this->m_root = node->child[0];
            this->m_root->parent = nullptr;
            node->child[0] = nullptr;
            delete node;
        }
        return;
    }

    // 获取node在父节点中的位置，这里不能用search，因为node是指针，在vector中是无序的
    // r在p->child的左右两侧，必有一侧存在
    int r = p->child.find(node);

    // 尝试旋转
    if (r > 0)
    {
        // 尝试旋转，向左侧子节点借
        BTNode<T>* s = p->child[r-1];       // p->child和node均为p的节点，node不为nullptr，其它的child也必定不为nullptr
        if (s->child.size() > order_floor)
        {
            //int y = r-1;
            node->key.push_front(p->key[r-1]);
            node->child.push_front(s->child.remove(s->child.size()-1));
            p->key[r-1] = s->key.remove(s->key.size()-1);
            return;
        }
    }
    if (r + 1 < p->child.size())
    {
        // 尝试旋转，向右侧子节点借
        BTNode<T>* s = p->child[r+1];       // p->child和node均为p的节点，node不为nullptr，其它的child也必定不为nullptr
        if(s->child.size() > order_floor)
        {
            //int y = r;
            node->key.push_back(p->key[r]);
            node->child.push_back(s->child.remove(0));
            p->key[r] = s->key.remove(0);
            return;
        }
    }

    // 使用合并
    if (r > 0)
    {
        // 左侧存在
        BTNode<T>* s = p->child[r-1];       // p->child和node均为p的节点，node不为nullptr，其它的child也必定不为nullptr
        //int y = r-1;

        s->key.push_back(p->key.remove(r-1));
        p->child.remove(r);

        for (int k = 0; k < node->key.size(); k++)
            s->key.push_back(node->key[0]);
        //while(!node->key.is_empty())
        //    s->key.push_back(node->key.remove(0));

        for (int k = 0; k < node->child.size(); k++)
        {
            if (node->child[k])
                node->child[k]->parent = s;
            s->child.push_back(node->child[k]);
        }
        //while(!node->child.is_empty())
        //{
        //    if (node->child[0])
        //        node->child[0]->parent = s;
        //    s->child.push_back(node->child.remove(0));
        //}

        // 为什么要clear，即为什么要置m_size为0，直接delete不就好了？
        node->key.clear();
        node->child.clear(); //不用while，需要clear
        delete node;
    }
    else
    {
        // 右侧存在
        BTNode<T>* s = p->child[r+1];       // p->child和node均为p的节点，node不为nullptr，其它的child也必定不为nullptr
        //int y = r;

        s->key.push_front(p->key.remove(r));
        p->child.remove(r);

        for (int k = 0; k < node->key.size(); k++)
            s->key.insert(k, node->key[k]);
        //while(!node->key.is_empty())
        //    s->key.push_front(node->key.remove(node->key.size()-1));

        for (int k = 0; k < node->child.size(); k++)
        {
            if (node->child[k])
                node->child[k]->parent = s;
            s->child.insert(k, node->child[k]);
        }
        //while(!node->child.is_empty())
        //{
        //    if (node->child[node->child.size()-1])
        //        node->child[node->child.size()-1]->parent = s;
        //    s->child.push_front(node->child.remove(node->child.size()-1));
        //}

        // 为什么要clear，即为什么要置m_size为0，直接delete不就好了？
        node->key.clear();
        node->child.clear(); //不用while，需要clear
        delete node;
    }

    solve_underflow(p);
}

/*!
 * @brief b-tree查找
 *
 * <pre>
 *               r      r+1
 *                \     /
 * key       [k]  [k]  [k]
 * child  [c]  [c]  [c]  [c]
 *                  /
 *                r+1
 * 若key.search(e)返加r，若key[r]！= e，则有key[r] <= e < k[r+1]
 * 故继续向child[r+1]继续查找
 * </pre>
 *
 * @param e: 查找目标
 * @return
 * @retval nullptr: 没有找到目标，因为是逐层查找，故最后m_hot一定指向一个叶节点。
 */
template <typename T>
BTNode<T>* BTree<T>::search(const T& e)
{
    BTNode<T>* node = this->m_root;
    this->m_hot = nullptr;
    while(node)
    {
        int r = node->key.search(e);        // 根据有序性查找，返回不大于查找目标的下标
                                            // 在insert使用BTree::search时，即可按序插入
        if (0 <= r && e == node->key[r]) return node;   // 找到目标
        this->m_hot = node;
        node = node->child[r+1];            // 原理请看函数说明中的迭代查找示意图
        // 无论是否找到目标，child[r+1]都为m_hot的子节点
    }
    return nullptr;
}

/*!
 * @brief 插入节点
 *
 * <pre>
 * m_hot插入新节点示意图
 *
 *               r      r+1(新插入关键码，作为m_hot的一部分)
 *                \     /
 * key       [k]  [k]  [k] ...
 * child  [c]  [c]  [c]  [c] ...
 *                  /     \
 *                r+1     r+2(新插入子节点，作为external node)
 * 注：这里r为vector.search返回的，可以为-1，即表示新节点将插入到第0个位置
 *
 * </pre>
 *
 * @param e: 待插入节点关键码
 * @return
 * @retval None
 */
template <typename T>
bool BTree<T>::insert(const T& e)
{
    BTNode<T>* node = this->search(e);
    if (node) return false;

    // 找到关键码e在m_hot插入的位置
    int r = this->m_hot->key.search(e);
    this->m_hot->key.insert(r+1, e);
    this->m_hot->child.push_back(nullptr); // 因为叶节点所有子节点为nullptr，故插在任意位置均可
    this->m_size++;

    this->solve_overflow(this->m_hot);

    return true;
}

/*!
 * @brief 删除节点
 *
 * @param e: 待删除目标
 * @return
 * @retval None
 */
template <typename T>
bool BTree<T>::remove(const T& e)
{
    BTNode<T>* node = this->search(e);
    if (!node) return false;

    int r = node->key.search(e);
    if (node->child[0])
    {
        // node不是叶节点，则e右侧必有子节点
        BTNode<T>* u = node->child[r+1];
        while(node->child[0]) u = u->child[0];  // 迭代至e的后继(后继必定是叶节点)
        node->key[r] = u->key[0];   // 将u->key[0]与待删除e交换位置
        //u->key[0] = e;              // 赋不赋值无所谓，反正要删除
        node = u;                   // node重新指向包含待删除目标e的叶节点u
        r = 0;                      // r也指向e在node->key中的下标
    }

    // 如果待删除目标e在叶节点中，直接删除
    node->key.remove(r);
    node->child.remove(node->child.size() - 1); // 因为叶节点所有子节点为nullptr，故随便删除一个即可
    this->m_size--;

    this->solve_underflow(node);
    return true;
}

/*! @} */
} /* dsa */

#endif /* ifndef _B_TREE_H */
