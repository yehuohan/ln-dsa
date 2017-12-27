
#include <iostream>
#include <iomanip>
#include "dsas-cpp/dsas.h"

void print_node(int data) {std::cout << data << "    ";}

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
void test_redblack();
void test_hash();
void test_pq();
void test_leftpq();
void test_string();
void test_sort();

//(int argc, char** argv)
int main()
{
    //test_sort();
    //test_string();
    //test_leftpq();
    //test_pq();
    test_hash();
    //test_redblack();
    //test_btree();
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
    for(int k = 0; k < vec_i.size(); k ++)
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
    lst_i.insert_before(lst_i.front(), -1000);
    lst_i.push_back(-1);
    lst_i.push_back(9020);
    lst_i.push_back(20);
    lst_i.push_back(9020);
    lst_i.push_back(20);
    lst_i.push_back(9020);
    lst_i.push_back(920);
    lst_i.push_back(20);
    lst_i.push_back(-20);
    lst_i.push_back(-20);
    lst_i.push_back(20);
    lst_i.push_back(920);
    lst_i.push_back(920);
    lst_i.remove(lst_i.front());

    std::cout << "Sort: \n";
    //lst_i.selection_sort(lst_i.front(), lst_i.size());
    //lst_i.insertion_sort(lst_i.front(), lst_i.size());
    lst_i.sort();
    lst_i.traverse(print_node);
    std::cout << std::endl;

    dsa::ListNodePtr<int> f = lst_i.find(9020, lst_i.size(), lst_i.back()->next);
    std::cout << "Find: ";
    lst_i.is_valid(f) ? (std::cout << f->data) : std::cout << "nullptr";
    std::cout << std::endl;
    dsa::ListNodePtr<int> s = lst_i.search(-30, lst_i.size(), lst_i.back()->next);
    std::cout << "Search: ";
    lst_i.is_valid(s) ? (std::cout << s->data) : std::cout << "nullptr";
    std::cout << std::endl;
    std::cout << "Size: " << lst_i.size() << std::endl;

    //std::cout << "Deduplicate: " << lst_i.deduplicate() << std::endl;;
    std::cout << "Uniquify: " << lst_i.uniquify() << std::endl;;
    lst_i.traverse(print_node);
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

void test_hash()
{
    dsa::HashTable<int, int> hash;
}

void test_redblack()
{
    dsa::RedBlackTree<unsigned int> rb;
    rb.insert(100);
    rb.insert(200);
    rb.insert(73);
    rb.insert(39);
    rb.insert(139);
    rb.insert(988);
    rb.insert(772);
    rb.insert(9);
    rb.insert(18);
    rb.insert(1008);
    rb.insert(8);
    rb.insert(81);
    rb.insert(281);
    rb.insert(188);

#if 1
    rb.remove(18);
    rb.remove(281);
    rb.remove(100);
    rb.remove(8);
    rb.remove(9);
#endif

    std::cout << "Size: " << rb.size() << std::endl;
    std::cout << "LDR: ";
    rb.root()->traverse_LDR(print_node);
    std::cout << std::endl;

    // 输出二叉树结构
    std::cout << "Print:" << std::endl;
    dsa::Queue<dsa::BinNode<unsigned int>*> qn;
    qn.enqueue(rb.root());
    int num[10] = {1};
    int idx = 0, cnt = 1;
    while(!qn.is_empty())
    {
        dsa::BinNode<unsigned int>* x = qn.dequeue();
        std::cout << x->data
                  << ((BN_IsBlack(x)) ? "_B_" : "_R_")
                  << x->height << "   ";

        if (x->left)
        { num[idx+1] ++; qn.enqueue(x->left); }
        if (x->right)
        { num[idx+1] ++; qn.enqueue(x->right); }

        cnt ++;
        if (cnt >= num[idx])
        {
            std::cout << std::endl;
            idx++;
            cnt = 0;
        }
    }

}

void test_pq()
{
    dsa::PqList<int> pql;
    pql.insert(10);
    pql.insert(1);
    pql.insert(9);
    std::cout << "pql max:" << pql.get_max() << std::endl;
    pql.del_max();
    std::cout << "pql max:" << pql.get_max() << std::endl;

    dsa::PqComplHeap<unsigned int> pq;

    pq.insert(10);
    pq.insert(18);
    pq.insert(38);
    pq.insert(8);
    pq.insert(27);
    pq.insert(2);
    pq.insert(83);
    pq.insert(103);
    pq.insert(1008);

#if 1
    pq.del_max();
#endif

    std::cout << "Print:\n";
    int n = 0;
    for (int k = 0; k < pq.size(); k ++)
    {
        std::cout << pq[k] << "  ";
        if (k+1 >= n)
        {
            std::cout << std::endl;
            n += 2<<k;
        }
    }
}

void test_leftpq()
{
    dsa::PqLeftHeap<int> lh;
    lh.insert(10);
    lh.insert(100);
    lh.insert(-100);
    lh.insert(-180);
    lh.insert(128);
    lh.insert(25);
    lh.insert(555);
    lh.insert(-321);
    lh.insert(777);

    lh.del_max();
    lh.del_max();

    // 输出二叉树结构
    std::cout << "Print:" << std::endl;
    dsa::Queue<dsa::BinNode<int>*> qn;
    qn.enqueue(lh.root());
    int num[10] = {1};
    int idx = 0, cnt = 1;
    while(!qn.is_empty())
    {
        dsa::BinNode<int>* x = qn.dequeue();
        std::cout << x->data
                  <<  " - "
                  << x->npl << "   ";

        if (x->left)
        { num[idx+1] ++; qn.enqueue(x->left); }
        if (x->right)
        { num[idx+1] ++; qn.enqueue(x->right); }

        cnt ++;
        if (cnt >= num[idx])
        {
            std::cout << std::endl;
            idx++;
            cnt = 0;
        }
    }
}

void test_string()
{
    char txt[] = "adoifeachilaiehchixxxabcxxxchiabcdoivja";
    char pat[] =                      "abcxxxchiabc";
    //char pat[] = "ABABxyzABAB";
    char* T = &txt[0];
    char* P = &pat[0];

    int* next    = dsa::build_next(P);
    int* next_im = dsa::build_next_improved(P);
    int* bm      = dsa::build_bc(P);
    int* gs      = dsa::build_gs(P);

    std::cout << "pat:     ";
    for (int k = 0; k < dsa::strlen(P); k++)
        std::cout << std::setw(2) << P[k] << " ";
    std::cout << std::endl;
    std::cout << "next:    ";
    for (int k = 0; k < dsa::strlen(P); k++)
        std::cout << std::setw(2) << next[k] << " ";
    std::cout << std::endl;
    std::cout << "next_im: ";
    for (int k = 0; k < dsa::strlen(P); k++)
        std::cout << std::setw(2) << next_im[k] << " ";
    std::cout << std::endl;
    std::cout << "bm:      ";
    for (int k = 0; k < dsa::strlen(P); k++)
        std::cout << std::setw(2) << bm[(unsigned int)P[k]] << " ";
    std::cout << std::endl;
    std::cout << "gs:      ";
    for (int k = 0; k < dsa::strlen(P); k++)
        std::cout << std::setw(2) << gs[k] << " ";
    std::cout << std::endl;
    delete[] next;
    delete[] next_im;
    delete[] bm;
    delete[] gs;

    std::cout << "Match: \n";
    std::cout << "bf1:   " << dsa::match_bf1(P, T) << "   bf2:  " << dsa::match_bf2(P, T) << std::endl;
    std::cout << "kmp:   " << dsa::match_kmp(P, T) << std::endl;
    std::cout << "bc:    " << dsa::match_bm_bc(P, T) << std::endl;
    std::cout << "bcgs:  " << dsa::match_bm_bcgs(P, T) << std::endl;
}

void test_sort()
{
    dsa::Vector<int> vs;
    for (int k = 0; k < 12; k++)
        vs.push_back(k+1);
    vs.unsort();

    for (int k = 0; k < vs.size(); k++)
        std::cout << std::setw(2) << vs[k] << "  ";

    //vs.bubble_sort(0, vs.size());
    //vs.merge_sort(0, vs.size());
    vs.selection_sort(0, vs.size());
    //vs.quick_sort(0, vs.size());
    
    std::cout << std::endl;
    for (int k = 0; k < vs.size(); k++)
        std::cout << std::setw(2) << vs[k] << "  ";

    std::cout << std::endl;
    int maj;
    if (dsa::majority(vs, maj))
        std::cout << maj << std::endl;
    else
        std::cout << "No majority";

    std::cout << std::endl;
    for (int k = 0; k < vs.size(); k ++)
        std::cout << std::setw(2) << dsa::quick_select(vs, k) << "  ";
}
