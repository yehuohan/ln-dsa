//==============================================================================
/*!
 * @file list.h
 * @brief 链表结构
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================


#ifndef DSAS_LIST_H
#define DSAS_LIST_H

#include "share/swap.h"
#include "share/compare.h"

namespace dsa
{

/*!
 * @addtogroup LList
 *
 * @{
 */

template <typename T> struct ListNode;
template <typename T, typename CMP = dsa::Less<T>> class List;

/*!
 * @name List类型
 * @{
 */
template <typename T>
using ListNodePtr = dsa::ListNode<T>*;

//template <typename T, typename CMP = dsa::Less<T>>
//using ListIterator = typename dsa::List<T,CMP>::Iterator;
/*! @} */


/*!
 * @brief ListNode struct
 *
 */
template <typename T>
struct ListNode
{
    T   data;
    ListNode<T>*   prev;
    ListNode<T>*   next;

    ListNode() : prev(nullptr), next(nullptr) {}
    ListNode(T ele, ListNode<T>* p = nullptr, ListNode<T>* n = nullptr)
        :data(ele), prev(p), next(n){}

    /** 插入一个prev节点 */
    ListNode<T>* insert_prev(const T& ele)
    {
        ListNode<T>* node = new ListNode(ele);
        node->prev = this->prev;
        node->next = this;
        this->prev->next = node;
        this->prev = node;
        return node;
    }

    /** 插入一个next节点 */
    ListNode<T>* insert_next(const T& ele)
    {
        ListNode<T>* node = new ListNode(ele);
        node->prev = this;
        node->next = this->next;
        this->next->prev = node;
        this->next = node;
        return node;
    }
};


/*!
 * @brief List class
 *
 */
template <typename T, typename CMP>
class List
{
public:

/*!
 * @brief List<T,CMP>::Iterator class
 *
 */
class Iterator
{
public:
    Iterator(ListNodePtr<T> node = nullptr) : m_cur(node) {}

    /** 重写*，获取List节点数据 */
    T& operator*(){return this->m_cur->data;}

    /** 重写= */
    Iterator& operator= (const Iterator& itr) {this->m_cur = itr.m_cur; return *this;}

    /** 重写== */
    bool operator== (const Iterator& itr) const {return this->m_cur == itr.m_cur;}
    /** 重写！= */
    bool operator!= (const Iterator& itr) const {return this->m_cur != itr.m_cur;}

    /** 重写前置++ */
    Iterator& operator++() {this->m_cur = this->m_cur->next; return *this;}
    /** 重写前置-- */
    Iterator& operator--() {this->m_cur = this->m_cur->prev; return *this;}

    /** 重写后置++ */
    Iterator operator++(int) {Iterator old = *this; this->m_cur = this->m_cur->next; return old;}
    /** 重写后置-- */
    Iterator operator--(int) {Iterator old = *this; this->m_cur = this->m_cur->prev; return old;}

private:
    ListNodePtr<T> m_cur;
};

public:
    List();
    ~List() {this->clear(); delete this->header; delete this->tailer;}

    int             clear();
    int             size() const {return this->m_size;}
    bool            is_empty() const {return !bool(this->m_size);}
    /** 判断节点p是否可以合法访问 */
    bool            is_valid(ListNodePtr<T> p) const {return (p && p != this->header && p != this->tailer);}

    T               remove(ListNodePtr<T> p);
    int             remove(int n, ListNodePtr<T> p);
    /** 第一个节点的Iterator */
    Iterator        begin() {return Iterator(this->front());};
    //ListIterator<T,CMP> begin() {return ListIterator<T,CMP>(this->front());}
    /** 尾部哨兵节点的Iterator */
    Iterator        end() {return Iterator(this->tailer);}
    //ListIterator<T,CMP> end() {return ListIterator<T,CMP>(this->tailer);}
    /** 第一个节点 */
    ListNodePtr<T>  front() {return this->header->next;}
    /** 第一个const节点 */
    const ListNodePtr<T> front() const {return this->header->next;}
    /** 最后一个节点 */
    ListNodePtr<T>  back() {return this->tailer->prev;}
    /** 最后一个const节点 */
    const ListNodePtr<T> back() const {return this->tailer->prev;}
    /** 插入元素到第一个节点 */
    ListNodePtr<T>  push_front(const T& ele) {this->m_size++; return this->header->insert_next(ele);}
    /** 插入元素到最后一个节点 */
    ListNodePtr<T>  push_back(const T& ele) {this->m_size++; return this->tailer->insert_prev(ele);}
    /** 插入到节点的前面 */
    ListNodePtr<T>  insert_before(ListNodePtr<T> p, const T& ele) {this->m_size++; return p->insert_prev(ele);}
    /** 插入到节点的后面 */
    ListNodePtr<T>  insert_after(ListNodePtr<T> p, const T& ele) {this->m_size++; return p->insert_next(ele);}
    /** 按序插入，可插入重复元素 */
    ListNodePtr<T>  insert_multi_byorder(const T& ele) {return this->insert_after(this->search(ele), ele);}
    /** 按序插入，不可插入重复元素，返回元素节点指针 */
    ListNodePtr<T>  insert_byorder(const T& ele)
    {
        ListNodePtr<T> node = this->search(ele);
        if (node->data == ele)
            return node;
        return this->insert_after(node, ele);
    }

    T& operator[](int index);
    const T& operator[](int index) const;

    /** 在链表中find */
    ListNodePtr<T>  find(const T& ele) const {return this->find(ele, this->m_size, this->tailer);}
    ListNodePtr<T>  find(const T& ele, int n, ListNodePtr<T> p) const;
    /** 在链表中search */
    ListNodePtr<T>  search(const T& ele) const {return this->search(ele, this->m_size, this->tailer);}
    ListNodePtr<T>  search(const T& ele, int n, ListNodePtr<T> p) const;

    int             deduplicate();
    int             uniquify();

    /** 选出整个链表的最大元素指针 */
    ListNodePtr<T>  select_max() {return this->select_max(this->header->next, this->m_size);}
    ListNodePtr<T>  select_max(ListNodePtr<T> p, int n);
    /** 对所有元素排序 */
    void            sort() {this->quick_sort(this->front(), this->back()->next);}
    void            selection_sort(ListNodePtr<T> p, int n);
    void            insertion_sort(ListNodePtr<T> p , int n);
    void            quick_sort(ListNodePtr<T>, ListNodePtr<T>);
    ListNodePtr<T>  partition(ListNodePtr<T>, ListNodePtr<T>);

    template <typename VST> void traverse(VST& visit);

protected:
    int             m_size;
    ListNodePtr<T>  header;         /**< 头哨兵节点，不存数据 */
    ListNodePtr<T>  tailer;         /**< 尾哨兵节点，不存数据 */
    CMP             cmp;
};


/*! @} */


/*!
 * @brief 初始化链表
 *
 * @param None
 * @return
 * @retval None
 */
template <typename T, typename CMP>
List<T,CMP>::List()
{
    this->header = new ListNode<T>;
    this->tailer = new ListNode<T>;
    this->header->next = this->tailer;
    this->header->prev = nullptr;
    this->tailer->prev = this->header;
    this->tailer->next = nullptr;
    this->m_size = 0;
}

/*!
 * @brief 清除所有节点
 *
 * 这里根据m_size来删除所有节点，故m_size一定得准确。
 *
 * @param None
 * @return 返回被清除的节点数
 * @retval None
 */
template <typename T, typename CMP>
int List<T,CMP>::clear()
{
    int old_size = this->m_size;
    while(this->m_size > 0)
        remove(this->header->next);
    return old_size;
}

/*!
 * @brief 删除一个节点
 *
 * @param p: 待删除节点
 * @return 返回被删除节点的数据
 * @retval None
 */
template <typename T, typename CMP>
T List<T,CMP>::remove(ListNodePtr<T> p)
{
    T data = p->data;
    p->next->prev = p->prev;
    p->prev->next = p->next;
    this->m_size --;
    delete p;
    return data;
}

/*!
 * @brief 移除p前面的n个元素
 *
 * 在p的前n个元素，即范围为[p-n, p)，即p-1, p-2 ... p-n；
 *
 * @param n: 要移除的元素个数，0 <= n <= size
 * @param p: 查找的起点，可以为tailer
 * @return
 * @retval None
 */
template <typename T, typename CMP>
int List<T,CMP>::remove(int n, ListNodePtr<T> p)
{
    int cnt = 0;
    ListNodePtr<T> last = p->prev;
    while(cnt++ < n)
    {
        last = last->prev;
        delete last->next;
        this->m_size--;
    }
    last->next = p;
    last->next->prev = last;
    return n;
}

/*!
 * @brief 重载[]运算符，实现下标索引
 *
 * @param index: 下标，范围为[0, size)
 * @return 返回节点数据的引用
 * @retval None
 */
template <typename T, typename CMP>
T& List<T,CMP>::operator[](int index)
{
    ListNodePtr<T> p = this->front();
    while(index-- > 0) p = p->next;
    return p->data;
}

/*!
 * @brief 重载[]运算符，实现下标索引
 *
 * 此函数用于const List调用。
 *
 * @param index: 下标，范围为[0, size)
 * @return 返回节点数据的引用
 * @retval None
 */
template <typename T, typename CMP>
const T& List<T,CMP>::operator[](int index) const
{
    ListNodePtr<T> p = this->front();
    while(index-- > 0) p = p->next;
    return p->data;
}

/*!
 * @brief 查找元素
 *
 * <pre>
 * 在p的前n个元素，即范围为[p-n, p)，即p-1, p-2 ... p-n；
 *
 * 在p的前n个元素中查找ele；
 * 因为必定会遍历到所有的前n个元素，故find的时间复杂度为O(n)。
 * 所以返回的结果：要么是找到元素，要么没有找到。
 * </pre>
 *
 * @param ele: 需要查找的元素
 * @param n: ele的前n个元素范围，0 <= n <= size
 * @param p: 查找的起点，可以为tailer
 * @return 找到则返回node，未找到则返回nullptr
 * @retval None
 */
template <typename T, typename CMP>
ListNodePtr<T> List<T,CMP>::find(const T& ele, int n, ListNodePtr<T> p) const
{
    while (n-- > 0)
    {
        p = p->prev;
        if (dsa::is_equal(ele, p->data, this->cmp))
            return p;
    }
    return nullptr;
}

/*!
 * @brief 查找元素
 *
 * <pre>
 * 在p的前n个元素，即范围为[p-n, p)，即p-1, p-2 ... p-n；
 *
 * 在p的前n个元素中查找ele；
 * 因为最后需要返回不大于ele的最大元素，故p的前n个元素必须是有序的。
 *
 * 返回的值可以为header，即List中没有不大于ele的元素。
 * </pre>
 *
 * @param ele: 待查找的元素
 * @param n: ele的前n个元素范围，0 <= n <= size
 * @param p: 查找的起点，可以为tailer
 * @return 不大于ele的最大元素，可以为header
 * @retval None
 */
template <typename T, typename CMP>
ListNodePtr<T> List<T,CMP>::search(const T& ele, int n, ListNodePtr<T> p) const
{
    while (n-- >= 0)
    {
        p = p->prev;
        if (dsa::less_equal(p->data, ele, this->cmp))
            break;
    }
    return p;
}

/*!
 * @brief 无序列表唯一化，思路和无序向量唯一化相同
 *
 * @param None
 * @return 返回重复的元素总数
 * @retval None
 */
template <typename T, typename CMP>
int List<T,CMP>::deduplicate()
{
    int old_size = this->m_size;
    int cnt = 0;
    ListNodePtr<T> p = this->header;
    while(p != this->back())
    {
        // 在p的前面查找p->data
        p = p->next;
        ListNodePtr<T> f = this->find(p->data, cnt, p);
        f ? (this->remove(f)) : cnt ++;
        continue;
    }
    return old_size - this->m_size;
}

/*!
 * @brief 有序列表唯一化，思路和有序向量唯一化相同
 *
 * @param None
 * @return 返回重复的元素总数
 * @retval None
 */
template <typename T, typename CMP>
int List<T,CMP>::uniquify()
{
    int old_size = this->m_size;
    ListNodePtr<T> p = this->front();
    int cnt = 0;
    while(p != this->back())
    {
        if (dsa::is_equal(p->data, p->next->data, this->cmp))
            cnt ++;
        else
        {
            // 一次性移除p前面相同的cnt个p->data
            if (cnt > 0) this->remove(cnt, p);
            cnt = 0;
        }
        p = p->next;
    }
    if (cnt > 0) this->remove(cnt, p);
    return old_size - this->m_size;
}

/*!
 * @brief 选择排序
 *
 * <pre>
 * 在p的后n个元素，即范围为[p, p+n)，即p+0, p+1 ... p+n-1；
 * 故p不能为header，p+n可以为tailer；
 *
 * 对p的后n个元素进行选择排序；
 * 排序元素包含p，故p不能为header，且排序元素也不能包含tailer；
 *
 * [    m       ][i          ]
 *  ------------  -----------
 *  待排序区间W   已排序区间S
 *  不断的从W中选出最大者m，放入S的第一个位置i处
 * </pre>
 *
 * @param p: 起始节点
 * @param n: 节点p开始的n个元素，要求 index(p)+n <= size
 * @return
 * @retval None
 */
template <typename T, typename CMP>
void List<T,CMP>::selection_sort(ListNodePtr<T> p, int n)
{
    // 待排序区间(head, tail)
    ListNodePtr<T> head = p->prev;
    ListNodePtr<T> tail = p;
    for(int i = 0; i < n; i ++)
        tail = tail->next;
    while(1 < n)
    {
        this->insert_before(tail, this->remove(this->select_max(head->next, n)));
        // 有序区间 +1
        tail = tail->prev;
        n--;
    }
}

/*!
 * @brief 取最大节点
 *
 * <pre>
 * 在p的后n个元素，即范围为[p, p+n)，即p+0, p+1 ... p+n-1；
 * 故p不能为header，p+n可以为tailer；
 *
 * 选出从p的后n个元素中的最大者；
 * </pre>
 *
 * @param p: 起始节点
 * @param n: 节点p开始的n个元素
 * @return
 * @retval None
 */
template <typename T, typename CMP>
ListNodePtr<T> List<T,CMP>::select_max(ListNodePtr<T> p, int n)
{
    ListNodePtr<T> max = p;
    for( ListNodePtr<T> cur = p; 1 < n; n--)
    {
        cur = cur->next;
        if (dsa::greater_equal(cur->data, max->data, this->cmp))
            max = cur;
    }
    return max;
}

/*!
 * @brief 插入排序
 *
 * <pre>
 * 在p的后n个元素，即范围为[p, p+n)，即p+0, p+1 ... p+n-1；
 * 故p不能为header，p+n可以为tailer；
 *
 * 对位于p的后n个元素进行插入排序；
 *
 * [       i    ][e          ]
 *  ------------  -----------
 *  已排序区间S   待排序区间W
 *
 * 不断将W中第一个元素e，插入到S中位置i处；
 * i为S中元素不大于e的最大元素的位置
 *
 * </pre>
 *
 * @param p: 起始节点
 * @param n: 节点p开始的n个元素，要求 index(p)+n <= size
 * @return
 * @retval None
 */
template <typename T, typename CMP>
void List<T,CMP>::insertion_sort(ListNodePtr<T> p , int n)
{
    for(int r = 0; r < n; r++)
    {
        // search返回不大于p->data的位置
        // r之前的为有序区间，r之后的为待排序区间
        this->insert_after(this->search(p->data, r, p), p->data);
        // p已经插入到区间S中，所以p在指下next节点前，要删除原来在区间W中的节点p
        p = p->next;
        this->remove(p->prev);
    }
}

/*!
 * @brief 快速排序
 *
 * @param ns,ne: 排序的起始点和结束点，排序范围[ns,ne)
 * @return
 * @retval None
 */
template <typename T, typename CMP>
void List<T,CMP>::quick_sort(ListNodePtr<T> ns, ListNodePtr<T> ne)
{
    if (ns == ne || ns == ne->prev)
        return;
    ListNodePtr<T> nm = this->partition(ns, ne->prev);
    this->quick_sort(ns, nm);
    this->quick_sort(nm->next, ne);
}

/*!
 * @brief 快速排序(quick_sort)轴点构造算法
 *
 * <pre>
 * 轴点可选取范围为[lo, hi]，与quick_sort的约定有所不同。
 * 轴点：左侧元素[lo, mi) <= 轴点元素mi <= 右侧元素(mi, hi]
 *
 * 根据轴点的确定过程，可知快速排序前后，可能打乱相同元素间的相对顺序；
 * 即快速排序是不稳定的。
 *
 * (1)基本形式
 * [p][    ][i     j][    ]
 *     ----           ----
 *      L              R
 * 比较候选轴点p和i和j，将i和j不断的归入到L或R中；
 *
 * (2)变种形式
 * [p][      q][i       ][k----------]
 *    --------  --------
 *        L        R
 * 不断的比较候选轴点p和k
 * p <= k : k归入R中；
 * p > k : k归入L中，即交换i和k，L的长度+1；
 * 最终交换p和q，q做为最终的轴点。
 *
 * </pre>
 *
 * @param ns,ne: 轴点查找范围，为[ns,ne]
 * @return
 * @retval None
 */
template <typename T, typename CMP>
ListNodePtr<T> List<T,CMP>::partition(ListNodePtr<T> ns, ListNodePtr<T> ne)
{
#if(0)
    // 基本形式
    T pivot = ns->data;
    while(ns != ne)
    {
        while(ns != ne && dsa::less_equal(pivot, ne->data, this->cmp)) ne = ne->prev;
        ns->data = ne->data;
        while(ns != ne && dsa::greater_equal(pivot, ns->data, this-cmp)) ns = ns->next;
        ne->data = ns->data;
    }
    ns->data = pivot;
    return ns;
#else
    // 变种形式
    ListNodePtr<T> p = ns;
    ListNodePtr<T> s = ns;
    while(s != ne)
    {
        s = s->next;
        if (this->cmp(s->data, ns->data))
        {
            p = p->next;
            dsa::swap(p->data, s->data);
        }
    }
    dsa::swap(p->data, ns->data);
    return p;
#endif
}

/*!
 * @brief 遍历List
 *
 * @param visit: 访问函数
 * @return
 * @retval None
 */
template <typename T, typename CMP>
template <typename VST>
void List<T,CMP>::traverse(VST& visit)
{
    ListNodePtr<T> s = this->front();
    while(s != this->tailer)
    {
        visit(s->data);
        s = s->next;
    }
}

} /* dsa */

#endif /* ifndef DSAS_LIST_H */
