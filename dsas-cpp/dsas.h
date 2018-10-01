
//==============================================================================
/*!
 * @file dsas.h
 * @brief DSAS头文件
 *
 * @date
 * @version
 * @author yehuohan, yehuohan@qq.com, yehuohan@gmail.com
 * @copyright
 */
//==============================================================================



//==============================================================================
/*!
 * @mainpage Data Struct and Algorithm

DSAS是数据结构与算法的学习过程。

 */
//==============================================================================



//==============================================================================

/*!
 * @defgroup Linear Linear Struct
 *
 * 线性数据结构，包括向量，队列，栈，队列，串，字典等
 *
 * @{
 */

/*!
 * @defgroup LArray Array
 * 数组
 * @{
 * @}
 */
/*!
 * @defgroup LVector Vector
 * 向量
 * @{
 * @}
 */
/*!
 * @defgroup LList List
 * 链表
 * @{
 * @}
 */
/*!
 * @defgroup LStack Stack
 * 栈
 * @{
 * @}
 */
/*!
 * @defgroup LQueue QUeue
 * 队列
 * @{
 * @}
 */
/*!
 * @defgroup LPQ Priority Queue
 * 优先级队列
 * @{
 * @}
 */
/*!
 * @defgroup LString String
 * 串结构
 * @{
 * @}
 */
/*!
 * @defgroup LBitmap Bitmap Struct
 *
 * Bitmap结构
 *
 * @{
 * @}
 */
/*!
 * @defgroup LHash Hash Struct
 *
 * 散列结构
 *
 * @{
 * @}
 */

/*!
 * @}
 */


/*!
 * @defgroup Tree Tree Struct
 *
 * 树模块，包括二叉树、b-树等相关算法
 *
 * @{
 */

/*!
 * @defgroup TBinaryTree Binary Tree
 * 二叉树
 * @{
 * @}
 */
/*!
 * @defgroup TBinarySearchTree Binary Search Tree
 * 二叉搜索树
 * @{
 * @}
 */
/*!
 * @defgroup TAvlTree Avl Tree
 * Avl平衡二叉搜索树
 * @{
 * @}
 */
/*!
 * @defgroup TSplayTree Splay Tree
 * 伸展树
 * @{
 * @}
 */
/*!
 * @defgroup TRedBlackTree RedBlack Tree
 * 红黑树
 * @{
 * @}
 */
/*!
 * @defgroup TBTree B-Tree
 * B-树
 * @{
 * @}
 */
/*!
 * @defgroup TKDTree K-D Tree
 * k-d树
 * @{
 * @}
 */

/*!
 * @}
 */


/*!
 * @defgroup Graph Graph Struct
 *
 * 图结构模块
 *
 * @{
 * @}
 */


/*!
 * @defgroup Share Share Data and Struct
 *
 * 共享类和数据
 *
 * @{
 * @}
 */


/*!
 * @defgroup Example Examples of dsas
 *
 * 数据结构的运用实例
 *
 * @{
 * @}
 */

//==============================================================================


#ifndef _DSAS_H
#define _DSAS_H

#include "share/macro.h"
#include "share/entry.h"
#include "share/swap.h"
#include "share/rand.h"
#include "share/time.h"
#include "share/prime.h"
#include "share/compare.h"
#include "share/algorithm.h"

#include "array.h"
#include "vector.h"
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "priority_queue.h"
#include "pq_list.h"
#include "pq_complete_heap.h"
#include "pq_left_heap.h"
#include "string.h"
#include "bitmap.h"
#include "hash.h"

#include "binary_node.h"
#include "binary_tree.h"
#include "binary_search_tree.h"
#include "avl_tree.h"
#include "splay_tree.h"
#include "b_node.h"
#include "b_tree.h"
#include "redblack_tree.h"
#include "kdtree.h"

#include "graph.h"
#include "graph_matrix.h"

#endif /* ifndef _DSAS_H */
