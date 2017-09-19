
//==============================================================================
/*!
 * @file graph.h
 * @brief 图类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================


#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"

namespace dsa
{

/*!
 * @addtogroup Graph
 * 
 * @{
 */


#define INI_MAX

/*!
 * @brief 顶点状态
 *
 */
typedef enum
{
    UnDiscovered,
    Discovered,
    Visited
} VStatus;

/*!
 * @brief 边状态
 *
 */
typedef enum
{
    UnDetermined,
    Tree,
    Cross,
    Forward,
    Backward
} EStatus;

/*!
 * @brief 顶点类
 *
 */
template<typename Tv> 
struct Vertex
{
    Tv data;
    int in_deg;             /**< 入度 */
    int out_deg;            /**< 出度 */
    VStatus status;
    int d_time, f_time;
    int parent;
    int priority;

    Vertex(const Tv& d):
        data(d), in_deg(0), out_deg(0), status(UnDiscovered),
        d_time(-1), f_time(-1),parent(-1),
        priority(INI_MAX)
    {}
};

/*!
 * @brief 边类
 *
 */
template<typename Te> 
struct Edge
{
    Te data;            /**< 数据 */
    int weight;         /**< 权重 */
    EStatus status;     /**< 类型 */

    Edge(const Te& d, int w):
        data(d), weight(w), status(UnDetermined)
    {}
};

/*!
 * @brief 图类
 *
 */
template <typename Tv, typename Te> 
class Graph
{
private:
    void reset(){}

public:
    int m_vnum;         /**< 顶点数量 */
    int m_enum;         /**< 边数量 */

};

/*!
 * @brief 邻接矩阵类
 *
 */
template <typename Tv, typename Te> 
class GraphMatrix : public Graph<Tv, Te>
{
private:
    dsa::vector<Vertex<Tv>* > m_V;                  /**< 顶点集 */
    dsa::vector<dsa::vector<Edge<Te>*> > m_E;       /**< 边集 */

public:
    /*!
     * @brief 邻接矩阵构造函数
     *
     * @param None
     * @return
     * @retval None
     */
    GraphMatrix()
    {
        this->m_vnum = 0;
        this->m_enum = 0;
    }

    ~GraphMatrix()
    {
        for (int j = 0; j < this->m_vnum; j ++)
            for(int k = 0; k < this->m_vnum; k++)
                if (this->m_E[j][k])
                    delete this->m_E[j][k];
    }

    // 基本数据获取
    int     get_vertex_size() {return this->m_vnum;} const
    Tv      get_vertex_data(int i) {return this->m_V[i]->data;}
    int     get_vertex_in_deg(int i) {return this->m_V[i]->in_deg;}
    int     get_vertex_out_deg(int i) {return this->m_V[i]->out_deg;}
    int     get_edge_size() {return this->m_enum;} const
    Te      get_edge_data(int i, int j) {return this->m_E[i][j]->data;}
    int     get_edge_weight(int i, int j) {return this->m_E[i][j]->weight;}

    // 顶点操作
    int     next_neighbor(int i, int j);
    int     first_neighbor(int i);

    int     insert_vertex(const Tv& vertex);
    Tv      remove_vertex(int i);

    // 边操作
    bool    exist_edge(int i, int j);
    void    insert_edge(const Te& edge, int w, int i, int j);
    Te      remove_edge(int i, int j);
};


/*!
 * @brief 枚举顶点i的所有邻接顶点
 *
 * @param i: 顶点i
 * @param j: 开始枚举的顶点
 * @return 返回与顶点i邻接的顶点下标
 * @retval None
 */
template <typename Tv, typename Te> 
int GraphMatrix<Tv, Te>::next_neighbor(int i, int j)
{
    while( (-1 < j) && !this->exist_edge(i, --j));
    return j;
}

/*!
 * @brief 获取顶点i的第一个有效邻接顶点
 *
 * @param i: 顶点i
 * @return 顶点i的第一个有效邻接顶点
 * @retval None
 */
template <typename Tv, typename Te> 
int GraphMatrix<Tv, Te>::first_neighbor(int i)
{
    return this->next_neighbor(i, this->m_vnum);
}

/*!
 * @brief 判断两个顶点间的边是否存在
 *
 * @param i,j: 尾部顶点i(起点)和头部顶点j(终点)
 * @return
 * @retval None
 */
template <typename Tv, typename Te> 
bool GraphMatrix<Tv, Te>::exist_edge(int i, int j)
{
    return ((0 <= i) && (i < this->m_vnum) 
        && (0 <= j) && (j < this->m_vnum)
        && (this->m_E[i][j] != nullptr));
}

/*!
 * @brief 插入边
 *
 * @param edge: 边数据
 * @param w: 权重
 * @param i,j: 尾部顶点i(起点)和头部顶点j(终点)
 * @return
 * @retval None
 */
template <typename Tv, typename Te> 
void GraphMatrix<Tv, Te>::insert_edge(const Te& edge, int w, int i, int j)
{
    if (this->exist_edge(i,j)) return;

    this->m_E[i][j] = new Edge<Te>(edge, w);
    this->m_enum++;

    // 修改出度与入度
    this->m_V[i]->out_deg++;
    this->m_V[j]->in_deg++;
}

/*!
 * @brief 删除边
 *
 * @param i,j: 尾部顶点i(起点)和头部顶点j(终点)
 * @return 边数据
 * @retval None
 */
template <typename Tv, typename Te> 
Te GraphMatrix<Tv,Te>::remove_edge(int i, int j)
{
    Te old = this->m_E[i][j]->data;
    delete this->m_E[i][j];
    this->m_E[i][j] = nullptr;
    this->m_enum--;

    // 修改出度与入度
    this->m_V[i]->out_deg--;
    this->m_V[j]->in_deg--;

    return old;
}

/*!
 * @brief 插入顶点，返加编号
 *
 * @param vertex: 顶点数据
 * @return 返回编号
 * @retval None
 */
template <typename Tv, typename Te> 
int GraphMatrix<Tv,Te>::insert_vertex(const Tv& vertex)
{
    // 每行增加一个元素
    for (int j = 0; j < this->m_vnum; j++)
        this->m_E[j].push_back(nullptr);
    // 顶点数量加1
    this->m_vnum++;
    // 邻接矩阵插入一行
    this->m_E.push_back(dsa::vector<Edge<Te>* >(this->m_vnum,this->m_vnum, nullptr));
    // 插入顶点
    Vertex<Tv>* vt = new Vertex<Tv>(vertex);
    return this->m_V.push_back(vt);
}

/*!
 * @brief 删除顶点
 *
 * @param i: 顶点编号
 * @return 返回顶点值
 * @retval None
 */
template <typename Tv, typename Te> 
Tv GraphMatrix<Tv,Te>::remove_vertex(int i)
{
    for(int j = 0; j < this->m_vnum; j++)
    {
        // 删除顶点的出边
        if (this->exist_edge(i,j))
        {
            delete this->m_E[i][j];
            // 头部(终点)顶点 j 的入度减1
            this->m_V[j]->in_deg--;
        }
    }
    // 删除第i行
    this->m_E.remove(i);
    this->m_vnum--;

    for(int j = 0; j < this->m_vnum; j++)
    {
        // 删除顶点的入边
        if (this->exist_edge(j,i))
        {
            // 删除边，并且每行删除对应顶点 i 的元素
            delete this->m_E[j].remove(i);
            // 尾部(起点)顶点 j 的出度减1
            this->m_V[j]->out_deg--;
        }
    }

    Tv old = this->m_V[i]->data;
    delete this->m_V.remove(i);
    return old;
}

/*! @} */

}

#endif /* ifndef GRAPH_H */
