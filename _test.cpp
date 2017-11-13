

#include <iostream>
#include "dsalib.h"

void print_node(int data)
{
    std::cout << data << "    ";
}

void test_vector();
void test_list();
void test_stack();
void test_queue();
void test_bt();
void test_graph();
void test_bst();
void test_avl();
void test_splay();
void test_btree();

//(int argc, char** argv)
int main()
{
    test_btree();
    //test_splay();
    //test_avl();
    //test_bst();
    //test_graph();
    //test_bt();
    //test_queue();
    //test_stack();
    //test_list();
    //test_vector();

    return 0;
}


void test_vector()
{
    dsa::Vector<int> vec_i;
    vec_i.push_back(-121);
    vec_i.push_back(10);
    vec_i.push_back(10);
    vec_i.push_back(10);
    vec_i.push_back(123);
    vec_i.push_back(238);
    vec_i.push_back(8009);
    vec_i.push_back(13);
    vec_i.push_back(80);
    vec_i.push_back(123);
    vec_i.push_back(123);
    vec_i.push_back(238);
    vec_i.push_back(8009);
    vec_i.push_back(238);
    vec_i.push_back(80);
    vec_i.push_back(80);
    vec_i.push_back(8009);
    vec_i.push_back(8009);
    vec_i.push_back(13);
    vec_i.push_back(13);
    vec_i.push_back(8009);
    vec_i[0] = -99999999;
    vec_i.insert(1, -3952);

    std::cout << "Find: " << vec_i.find(-3953,0, vec_i.size()) << std::endl;

    vec_i.merge_sort(0, vec_i.size());
    //vec_i.bubble_sort(0, vec_i.size());
    vec_i.uniquify();

    std::cout << "Print:\n";
    for(unsigned int k = 0; k < vec_i.size(); k ++)
    {
        std::cout << vec_i[k] << std::endl;
    }
    std::cout << "search:\n";
    std::cout << vec_i.bin_search(8009, 0, vec_i.size()) << std::endl;
}

void test_list()
{
    dsa::List<int> lst_i;
    lst_i.push_front(1000);
    lst_i.insert_before(lst_i.first(), -1000);
    lst_i.push_back(-1);
    lst_i.push_back(20);
    lst_i.push_back(-20);
    lst_i.push_back(920);
    lst_i.push_back(9020);

    lst_i.remove(lst_i.first());
    //lst_i.selection_sort(lst_i.first(), lst_i.size());
    lst_i.insertion_sort(lst_i.first(), lst_i.size());

    std::cout << "Iterator: \n";
    dsa::List<int>::iterator iter = lst_i.begin();
    std::cout << *iter << std::endl;
    iter++;
    std::cout << *iter << std::endl << std::endl;

    std::cout << "Size: " << lst_i.size() << std::endl;

    dsa::ListNode<int>* p = lst_i.first();
    while(p->next)
    {
        std::cout << p->data << std::endl;
        p = p->next;
    }
}

void test_stack()
{
    dsa::Stack<int> sta_i;
    if(sta_i.is_empty())
        std::cout << "Is empty" << std::endl;
    sta_i.push(100);
    sta_i.push(999);
    sta_i.push(-10000);
    std::cout << sta_i.size() << std::endl;
    std::cout << sta_i.top() << std::endl;
    std::cout << sta_i.pop() << std::endl;
    sta_i.clear();
    if(sta_i.is_empty())
        std::cout << "Is empty" << std::endl;
}

void test_queue()
{
    dsa::Queue<int> que_i;
    que_i.enqueue(12);
    que_i.enqueue(12392);
    que_i.enqueue(-19212);
    que_i.enqueue(-1000);

    std::cout << "Size : " << que_i.size() << std::endl;
    std::cout << "Front: " << que_i.front() << std::endl;
    std::cout << "Rear : " << que_i.rear() << std::endl;

    std::cout << "\n" << que_i.dequeue() << std::endl;

    std::cout << "Size : " << que_i.size() << std::endl;
    std::cout << "Front: " << que_i.front() << std::endl;
    std::cout << "Rear : " << que_i.rear() << std::endl;
}

void test_bt()
{
    dsa::BinTree<int> tint(9);
    tint.insert_left(tint.root(), 5);
    tint.insert_left(tint.root()->left, 1);
    tint.insert_right(tint.root()->left, 7);
    tint.insert_left(tint.root()->left->right, 6);
    tint.insert_right(tint.root(), 18);

    tint.insert_left(tint.root()->right, 12);
    tint.insert_right(tint.root()->right, 28);
/*
 *       9
 *   5       18
 * 1   7  12    28
 *    6
 *
 */
    std::cout << "Size: "<< tint.size() << std::endl;
    std::cout << "Is Empty: "<< tint.is_empty() << std::endl;

    std::cout << "先序遍历：\n";
    tint.root()->traverse_DLR(print_node);
    std::cout << std::endl;

    std::cout << "中序遍历：\n";
    tint.root()->traverse_LDR(print_node);
    std::cout << std::endl;

    std::cout << "后序遍历：\n";
    tint.root()->traverse_LRD(print_node);
    std::cout << std::endl;

    std::cout << "层次遍历：\n";
    tint.root()->traverse_LO(print_node);
    std::cout << std::endl;

    dsa::Vector<int> pre;
    pre.push_back(9);
    pre.push_back(5);
    pre.push_back(1);
    pre.push_back(7);
    pre.push_back(6);
    pre.push_back(18);
    pre.push_back(12);
    pre.push_back(28);
    dsa::Vector<int> in;
    in.push_back(1);
    in.push_back(5);
    in.push_back(6);
    in.push_back(7);
    in.push_back(9);
    in.push_back(12);
    in.push_back(18);
    in.push_back(28);
    dsa::BinTree<int> bt;
    construct_bintree(pre, in, bt);

    std::cout << "Size: " << bt.root()->size() << std::endl;
    std::cout << "重构后序遍历：\n";
    bt.root()->traverse_LRD(print_node);
    std::cout << std::endl;
    std::cout << "重构层次遍历：\n";
    bt.root()->traverse_LO(print_node);
    std::cout << std::endl;
}

void test_graph()
{
    dsa::GraphMatrix<int, float> gm;

    int v0 = gm.insert_vertex(100);
    int v1 = gm.insert_vertex(700);
    int v2 = gm.insert_vertex(900);
    gm.remove_vertex(v2);
    v2 = gm.insert_vertex(1200);
    int v3 = gm.insert_vertex(9999);

    std::cout << "Vertex: \n";
    std::cout << v0 << " " << v1 << " " << v2 << " " << v3 << "\n";
    std::cout << gm.get_vertex_data(v0) << std::endl;
    std::cout << gm.get_vertex_data(v1) << std::endl;
    std::cout << gm.get_vertex_data(v2) << std::endl;
    std::cout << gm.get_vertex_data(v3) << std::endl;

    gm.insert_edge(0.13, 10, v0, v1);
    gm.insert_edge(0.25, 20, v0, v2);
    gm.insert_edge(0.37, 30, v0, v3);
    gm.insert_edge(0.99, 40, v2, v3);

    int clock = 0;
    gm.BFS(v0, clock);
    gm.DFS(v0, clock);

    std::cout << "Edge: \n";
    std::cout << "EdgeNum: " << gm.get_edge_size() << std::endl;
    std::cout << gm.get_edge_data(v0,v3) << "   " << gm.get_edge_weight(v0,v3) << std::endl;

    std::cout << "v1's first neighbor: " << gm.first_nbr(v0) << std::endl;
    std::cout << "v1's next: " << gm.next_nbr(v0, v2) << std::endl;

    gm.remove_edge(v0,v3);
    std::cout << "EdgeNum: " << gm.get_edge_size() << std::endl;
}

void test_bst()
{
    //dsa::BinSearchTree<dsa::Entry<int, char> > bst;
    dsa::BinSearchTree<int> bst;
    bst.insert(1);
    bst.insert(10);
    bst.insert(980);
    bst.insert(128);
    bst.insert(-31);
    bst.insert(69);
    bst.insert(-870);
    bst.insert(370);
    bst.insert(1370);
    bst.insert(-80);

    dsa::BinNode<int>* r = bst.search(10);
    if (r)
    {
        std::cout << r->data << std::endl;
    }
    if (bst.remove(10))
    {
        std::cout << "Remove 10\n";
    }
    if (!bst.remove(10))
    {
        std::cout << "Remove nothing\n";
    }

    bst.root()->traverse_LDR(print_node);
}

void test_avl()
{
    dsa::AvlTree<int> at;
    at.insert(9);
    at.insert(-13);
    at.insert(-610);
    at.insert(379);
    at.insert(129);
    at.insert(180);
    at.insert(-80);
    at.insert(-300);
    at.insert(999);

    at.root()->traverse_LDR(print_node);
    std::cout << "\n";

    at.remove(-13);
    at.remove(-80);

    at.root()->traverse_LDR(print_node);
}

void test_splay()
{
    dsa::SplayTree<int> st;

    st.insert(10);
    st.insert(82);
    st.insert(-7);
    st.insert(270);
    st.insert(39);
    st.insert(-99);

    st.search(-7);       // 找到目标会进行splay
    std::cout << st.root()->data << std::endl;
    st.search(88);       // 没有找到目标同样会进行splay
    std::cout << st.root()->data << std::endl;

    st.remove(-7);
    std::cout << st.root()->data << std::endl;
    st.remove(88);
    std::cout << st.root()->data << std::endl;

    std::cout << "中序遍历:" << std::endl;
    st.root()->traverse_LDR(print_node);
    std::cout << std::endl;
    std::cout << st.root()->data << std::endl;
}

void test_btree()
{
    dsa::BTree<unsigned int> bt(3);

    //            *77*
    //      *20*        *203*
    // *2*10*  *28*  *90*   *303*
    bt.insert(10) ; bt.insert(20) ; bt.insert(28);
    bt.insert(2)  ; bt.insert(90) ; bt.insert(77);
    bt.insert(203); bt.insert(303);

    dsa::BTNode<unsigned int>* node = bt.search(90);
    if (node)
    {
        for (int k = 0; k < node->key.size(); k++)
            std::cout << node->key[k] << std::endl;
    }

#if (1)
    //        *20*77*
    // *2*10*  *28*  *203*303*
    bt.remove(90);

    //     *10*77*
    // *2*  *20*  *203*303*
    bt.remove(28);

    //     *10*203*
    // *2*  *77*  *303*
    bt.remove(20);
#endif

    std::cout << "Print" << std::endl;
    dsa::Queue<dsa::BTNode<unsigned int>*> qn;
    qn.enqueue(bt.root());
    int num[10] = {1};
    int idx = 0, cnt = 0;
    while(!qn.is_empty())
    {
        dsa::BTNode<unsigned int>* x = qn.dequeue();
        for (int k = 0; k < x->key.size(); k++)
            std::cout << "  " << x->key[k];
        std::cout << "[" << x->key.size() << "-" << x->child.size() << "] ";
        for (int k = 0; k < x->child.size(); k++)
            if (x->child[k])
                qn.enqueue(x->child[k]);

        num[idx+1] += x->child.size();  // 输出当前层节点x时，同时累加下一层的节点数
        cnt++;
        if (cnt >= num[idx])
        {
            std::cout << std::endl;
            idx++;
            cnt = 0;
        }
    }
}
