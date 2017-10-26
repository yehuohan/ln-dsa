

#include <iostream>
#include "dsalib.h"

void print_node(int data)
{
    std::cout << data << "    ";
}

//(int argc, char** argv)
int main()
{

/* graph test */
#if(0)
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

#endif

/* tree test */
#if(0)
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

    dsa::vector<int> pre;
    pre.push_back(9);
    pre.push_back(5);
    pre.push_back(1);
    pre.push_back(7);
    pre.push_back(6);
    pre.push_back(18);
    pre.push_back(12);
    pre.push_back(28);
    dsa::vector<int> in;
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

#endif

/* queue test */
#if(0)
    dsa::queue<int> que_i;
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
#endif

/* stack test */
#if(0)
    dsa::stack<int> sta_i;
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
#endif

/* list test */
#if(0)
    dsa::list<int> lst_i;
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
    dsa::list<int>::iterator iter = lst_i.begin();
    std::cout << *iter << std::endl;
    iter++;
    std::cout << *iter << std::endl << std::endl;

    std::cout << "Size: " << lst_i.size() << std::endl;

    dsa::list_node<int>* p = lst_i.first();
    while(p->next)
    {
        std::cout << p->data << std::endl;
        p = p->next;
    }

    return 0;
#endif

/* vector test */
#if(0)
    dsa::vector<int> vec_i;
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

    return 0;
#endif

}
