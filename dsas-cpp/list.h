//==============================================================================
/*!
 * @file list.h
 * @brief List struct
 *
 * List implementation with some basic functions and advanced
 *         functions such as find, search, sort and so on.
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================


#ifndef _LIST_H
#define _LIST_H

namespace dsa
{

/*!
 * @addtogroup LList
 *
 * @{
 */

/*!
 * @brief ListNode struct
 *
 * contain prev node and next node.
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

    ListNode<T>* insert_prev(const T& ele)
    {
        ListNode<T>* node = new ListNode(ele);
        node->prev = this->prev;
        node->next = this;
        this->prev->next = node;
        this->prev = node;
        return node;
    }
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
template <typename T>
class List
{
public:

/*!
 * @brief List iterator class
 *
 */
    class iterator
    {
    public:
        iterator(ListNode<T>* node = nullptr){this->m_cur = node;}

        T operator*(){return this->m_cur->data;}

        // 前置++/--
        iterator operator++(){this->m_cur = this->m_cur->next; return *this;}
        iterator operator--(){this->m_cur = this->m_cur->prev; return *this;}

        // 后置++/--
        iterator operator++(int){iterator old = *this; this->m_cur = this->m_cur->next; return old;}
        iterator operator--(int){iterator old = *this; this->m_cur = this->m_cur->prev; return old;}

    private:
        ListNode<T>* m_cur;
    };

public:
    List();
    ~List(){ this->clear(); delete this->header; delete this->tailer;};

    // basic
    int             clear();
    bool            is_empty() const {return !bool(this->m_size);}
    int             size() const {return this->m_size;}

    T               remove(ListNode<T>* p);
    iterator        begin(){return List<T>::iterator(this->first());}
    iterator        end(){return List<T>::iterator(this->last());}
    ListNode<T>*    first() const {return this->header->next;}
    ListNode<T>*    last() const {return this->tailer->prev;}
    ListNode<T>*    push_front(const T& ele){this->m_size++; return this->header->insert_next(ele);}
    ListNode<T>*    push_back(const T& ele){this->m_size++; return this->tailer->insert_prev(ele);}

    ListNode<T>*    insert_before(ListNode<T>* p, const T& ele) {this->m_size++; return p->insert_prev(ele);}
    ListNode<T>*    insert_after(ListNode<T>* p, const T& ele) {this->m_size++; return p->insert_next(ele);}

    T& operator[](int index) const;

    // find
    ListNode<T>*    find(const T& ele, int n, ListNode<T>* p) const;
    // search
    ListNode<T>*    search(const T& ele, int n, ListNode<T>* p) const;

    // deduplicate
    int             deduplicate();
    // uniquify
    int             uniquify();

    // sort
    void            selection_sort(ListNode<T>* p, int n);
    ListNode<T>*    selection_max(ListNode<T>* p, int n);
    void            insertion_sort(ListNode<T>* p , int n);


protected:
    int             m_size;
    ListNode<T>*    header;         /**< 头哨兵节点，不存数据 */
    ListNode<T>*    tailer;        /**< 尾哨兵节点，不存数据 */
};


/*! @} */


/*!
 * @brief init with null header and tailer
 *
 * @param None
 * @return
 * @retval None
 */
template <typename T>
List<T>::List()
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
 * @brief clear all element except header and tailer
 *
 * @param None
 * @return the size of list before clear
 * @retval None
 */
template <typename T>
int List<T>::clear()
{
    int old_size = this->m_size;
    while(this->m_size > 0)
        remove(this->header->next);
    return old_size;
}

/*!
 * @brief: remove one node
 *
 * @param None
 * @return the deleted element
 * @retval None
 */
template <typename T>
T List<T>::remove(ListNode<T>* p)
{
    T data = p->data;
    p->next->prev = p->prev;
    p->prev->next = p->next;
    this->m_size --;
    delete p;
    return data;
}

/*!
 * @brief: access element by operator[]
 *
 * @param None
 * @return the element of node
 * @retval None
 */
template <typename T>
T& List<T>::operator[](int index) const
{
    ListNode<T>* p = this->header;
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
 * @param ele : 需要查找的元素
 * @param n : ele的前n个元素范围
 * @param p : 查找的起点，可以为tailer
 * @return 找到则返加node，未找到则返加nullptr
 * @retval None
 */
template <typename T>
ListNode<T>* List<T>::find(const T& ele, int n, ListNode<T>* p) const
{
    while(n-- > 0)
        if (ele == (p = p->prev)->data) return p;
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
 * </pre>
 *
 * @param ele : 待查找的元素
 * @param n : ele的前n个元素范围
 * @param p : 查找的起点，可以为tailer
 * @return 不大于ele的最大元素，可以为header
 * @retval None
 */
template <typename T>
ListNode<T>* List<T>::search(const T& ele, int n, ListNode<T>* p) const
{
    while( 0 <= n--)
    {
        if (((p=p->prev)->data) <= ele) break;
    }
    return p;
}

/*!
 * @brief 无序列表唯一化，思路和无序向量唯一化相同
 *
 * @param None
 * @return
 * @retval None
 */
template <typename T>
int List<T>::deduplicate()
{
}

/*!
 * @brief 有序列表唯一化，思路和有序向量唯一化相同
 *
 * @param None
 * @return
 * @retval None
 */
template <typename T>
int List<T>::uniquify()
{
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
 * @param p : 起始节点
 * @param n : 节点p开始的n个元素，要求 index(p)+n <= size
 * @return
 * @retval None
 */
template <typename T>
void List<T>::selection_sort(ListNode<T>* p, int n)
{
    // 待排序区间(head, tail)
    ListNode<T>* head = p->prev;
    ListNode<T>* tail = p;
    for(int i = 0; i < n; i ++)
        tail = tail->next;
    while(1 < n)
    {
        this->insert_before(tail, this->remove(this->selection_max(head->next, n)));
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
 * @param p : 起始节点
 * @param n : 节点p开始的n个元素
 * @return
 * @retval None
 */
template <typename T>
ListNode<T>* List<T>::selection_max(ListNode<T>* p, int n)
{
    ListNode<T>* max = p;
    for( ListNode<T>* cur = p; 1 < n; n--)
    {
        // 应该由用户提供比较函数
        if((cur=cur->next)->data >= max->data)
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
 * @param p : 起始节点
 * @param n : 节点p开始的n个元素，要求 index(p)+n <= size
 * @return
 * @retval None
 */
template <typename T>
void List<T>::insertion_sort(ListNode<T>* p , int n)
{
    for(int r = 0; r < n; r++)
    {
        // search返回不大于p->data的位置
        // r之前的为有序区间，r之后的为待排序区间
        this->insert_after(this->search(p->data, r, p), p->data);
        p = p->next;
        this->remove(p->prev);
    }
}

} /* dsa */


#endif /* ifndef _LIST_H */
