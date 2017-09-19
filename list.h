//==============================================================================
/*!
 * @file list.h
 * @brief list struct
 *
 * list implementation with some basic functions and advanced 
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
 * @addtogroup Linear
 * 
 * @{
 */

/*!
 * @brief list_node struct
 *
 * contain prev node and next node.
 *
 */
template <typename T>
struct list_node
{
    T   data;
    list_node<T>*   prev;
    list_node<T>*   next;

    list_node() {}
    list_node(T ele, list_node<T>* p = nullptr, list_node<T>* n = nullptr)
        :data(ele), prev(p), next(n){}

    list_node<T>* insert_prev(const T& ele)
    {
        list_node<T>* node = new list_node(ele);
        node->prev = this->prev;
        node->next = this;
        this->prev->next = node;
        this->prev = node;
        return node;
    }
    list_node<T>* insert_next(const T& ele)
    {
        list_node<T>* node = new list_node(ele);
        node->prev = this;
        node->next = this->next;
        this->next->prev = node;
        this->next = node;
        return node;
    }
};


/*!
 * @brief list class
 *
 */
template <typename T>
class list
{
public:

/*!
 * @brief list iterator class
 *
 */
    class iterator
    {
    public:
        iterator(list_node<T>* node = nullptr){this->m_cur = node;}

        T operator*(){return this->m_cur->data;}

        // 前置++/--
        iterator operator++(){this->m_cur = this->m_cur->next; return *this;}
        iterator operator--(){this->m_cur = this->m_cur->prev; return *this;}

        // 后置++/--
        iterator operator++(int){iterator old = *this; this->m_cur = this->m_cur->next; return old;}
        iterator operator--(int){iterator old = *this; this->m_cur = this->m_cur->prev; return old;}

    private:
        list_node<T>* m_cur;
    };

public:
    list();
    ~list(){ this->clear(); delete this->header; delete this->trailer;};

    // basic
    int             clear();
    bool            is_empty() const {return !bool(this->m_size);}
    unsigned int    size() const {return this->m_size;}

    T               remove(list_node<T>* p);
    iterator        begin(){return list<T>::iterator(this->first());}
    iterator        end(){return list<T>::iterator(this->last());}
    list_node<T>*   first() const {return this->header->next;}
    list_node<T>*   last() const {return this->trailer->prev;}
    list_node<T>*   push_front(const T& ele){this->m_size++; return this->header->insert_next(ele);}
    list_node<T>*   push_back(const T& ele){this->m_size++; return this->trailer->insert_prev(ele);}

    list_node<T>*   insert_before(list_node<T>* p, const T& ele) {this->m_size++; return p->insert_prev(ele);}
    list_node<T>*   insert_after(list_node<T>* p, const T& ele) {this->m_size++; return p->insert_next(ele);}

    T& operator[](int index) const;

    // find
    list_node<T>*   find(const T& ele, int n, list_node<T>* p) const;
    // search
    list_node<T>*   search(const T& ele, int n, list_node<T>* p) const;

    // deduplicate
    int             deduplicate();
    // uniquify
    int             uniquify();

    // sort
    void            selection_sort(list_node<T>* p, int n);
    list_node<T>*   select_max(list_node<T>* p, int n);
    void            insertion_sort(list_node<T>* p , int n);


protected:

private:
    int     m_size;
    list_node<T>* header;
    list_node<T>* trailer;

};


/*! @} */


/*!
 * @brief init with null header and trailer
 *
 * @param None
 * @return
 * @retval None
 */
template <typename T>
list<T>::list()
{
    this->header = new list_node<T>;
    this->trailer = new list_node<T>;
    this->header->next = this->trailer;
    this->header->prev = nullptr;
    this->trailer->prev = this->header;
    this->trailer->next = nullptr;
    this->m_size = 0;
}

/*!
 * @brief clear all element except header and trailer
 *
 * @param None
 * @return the size of list before clear
 * @retval None
 */
template <typename T>
int list<T>::clear()
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
T list<T>::remove(list_node<T>* p)
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
T& list<T>::operator[](int index) const
{
    list_node<T>* p = this->header;
    while(index-- > 0) p = p->next;
    return p->data;
}

/*!
 * @brief 查找元素
 *
 * 在p的前n个元素中查找ele
 *
 * @param ele : 需要查找的元素
 * @param n : ele的前n个元素范围
 * @param p : 查找的起点
 * @return 找到则返加node，未找到则返加nullptr
 * @retval None
 */
template <typename T>
list_node<T>* list<T>::find(const T& ele, int n, list_node<T>* p) const
{
    while(n-- > 0)
        if (ele == (p = p->prev)->data) return p;
    return nullptr;
}

/*!
 * @brief 查找元素
 *
 * 在p的前n个元素中查找ele
 *
 * @param ele : 需要查找的元素
 * @param n : ele的前n个元素范围
 * @param p : 查找的起点
 * @return 不大于ele的最后者元素
 * @retval None
 */
template <typename T>
list_node<T>* list<T>::search(const T& ele, int n, list_node<T>* p) const
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
int list<T>::deduplicate()
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
int list<T>::uniquify()
{
}

/*!
 * @brief 选择排序
 *
 * 对位于p的连续n个元素进行选择排序
 *
 * @param p : node
 * @param n : node p开始的n个元素，要求 index(p)+n <= size
 * @return
 * @retval None
 */
template <typename T>
void list<T>::selection_sort(list_node<T>* p, int n)
{
    // 待排序区间(head, tail)
    list_node<T>* head = p->prev;
    list_node<T>* tail = p;
    for(int i = 0; i < n; i ++) tail = tail->next;

    while(1 < n)
    {
        this->insert_before( 
                tail, 
                this->remove(this->select_max(head->next, n)));

        // 有序区间 +1
        tail = tail->prev;
        n--;
    }
}

/*!
 * @brief 取最大节点
 *
 * 选出从p开始的n个元素中的最大者
 *
 * @param p : node 
 * @param n : node p开始的n个元素
 * @return
 * @retval None
 */
template <typename T>
list_node<T>* list<T>::select_max(list_node<T>* p, int n)
{
    list_node<T>* max = p;
    for( list_node<T>* cur = p; 1 < n; n--)
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
 * 对位于p的连续n个元素进行插入排序
 *
 * @param p : node
 * @param n : node p开始的n个元素，要求 index(p)+n <= size
 * @return
 * @retval None
 */
template <typename T>
void list<T>::insertion_sort(list_node<T>* p , int n)
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

// namespace dsa end
}


#endif /* ifndef _LIST_H */
