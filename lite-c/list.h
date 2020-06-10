
/*!
 * @file list.h
 * @brief 链表简单实现
 *
 */

#define _offsetof(type, member)  \
    ((size_t)(&((type *)0)->member))

#define _node_to_struct(ptr, type, member)    \
    ((type *)((char *)(ptr) - _offsetof(type, member)))

typedef struct list_node {
    struct list_node* prev;
    struct list_node* next;
} list_node_t;

static inline void list_init(list_node_t* li) {
    li->prev = li->next = li;
}

static inline void __list_add(list_node_t* ln, list_node_t* prev, list_node_t* next) {
    prev->next = next->prev = ln;
    ln->next = next;
    ln->prev = prev;
}

static inline void list_add_prev(list_node_t* li, list_node_t* ln) {
    __list_add(ln, li->prev, li);
}

static inline void list_add_next(list_node_t* li, list_node_t* ln) {
    __list_add(ln, li, li->next);
}

static inline void __list_del(list_node_t* prev, list_node_t* next) {
    prev->next = next;
    next->prev = prev;
}

static inline void list_del(list_node_t* ln) {
    __list_del(ln->prev, ln->next);
}
