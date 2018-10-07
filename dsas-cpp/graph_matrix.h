
//==============================================================================
/*!
 * @file graph_matrix.h
 * @brief Grahp邻接矩阵类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _GRAPH_MATRIX_H
#define _GRAPH_MATRIX_H

#include "vector.h"
#include "queue.h"
#include "graph.h"

namespace dsa
{

/*!
 * @addtogroup Graph
 *
 * @{
 */


/*!
 * @brief 邻接矩阵类
 *
 * 用邻接矩阵表示一幅图，以及进行图操作。
 *
 */
template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te>
{
private:
    dsa::Vector<VertexPtr<Tv> > m_v;                /**< 顶点集 */
    dsa::Vector<dsa::Vector<EdgePtr<Te> > > m_e;    /**< 边集 */

    /** 重置顶点和边 */
    void reset()
    {
        // 重置项点
        for (int i = 0; i < this->m_vnum; i ++)
        {
            this->m_v[i]->status = VStatus::UnDiscovered;
            this->m_v[i]->d_time = -1;
            this->m_v[i]->f_time = -1;
            this->m_v[i]->parent = -1;
            this->m_v[i]->priority = INIT_PRIORITY;
            // 重量边
            for (int j = 0; j < this->m_vnum; j ++)
            {
                if (this->exist_edge(i,j))
                    this->m_e[i][j]->status = EStatus::UnDetermined;
            }
        }
    }

public:
    GraphMatrix()
    {
        this->m_vnum = 0;
        this->m_enum = 0;
    }

    ~GraphMatrix()
    {
        for (int j = 0; j < this->m_vnum; j ++)
            for(int k = 0; k < this->m_vnum; k++)
                if (this->m_e[j][k])
                    delete this->m_e[j][k];
    }

    // 基本数据获取
    int     vertex_size() {return this->m_vnum;} const
    Tv      vertex_data(int i) {return this->m_v[i]->data;}
    int     vertex_indeg(int i) {return this->m_v[i]->in_deg;}
    int     vertex_outdeg(int i) {return this->m_v[i]->out_deg;}
    VStatus vertex_status(int i) {return this->m_v[i]->status;}
    int     vertex_ftime(int i) {return this->m_v[i]->f_time;}
    int     vertex_dtime(int i) {return this->m_v[i]->d_time;}
    int     vertex_parent(int i) {return this->m_v[i]->parent;}
    int     vertex_priority(int i) {return this->m_v[i]->priority;}
    int     edge_size() {return this->m_enum;} const
    Te      edge_data(int i, int j) {return this->m_e[i][j]->data;}
    int     edge_weight(int i, int j) {return this->m_e[i][j]->weight;}
    EStatus edge_status(int i, int j) {return this->m_e[i][j]->status;}

    // 顶点遍历
    int     next_nbr(int i, int j);
    int     first_nbr(int i);

    // 顶点操作
    virtual int     insert_vertex(const Tv& vertex);
    virtual Tv      remove_vertex(int i);

    // 边操作
    virtual bool    exist_edge(int i, int j);
    virtual void    insert_edge(const Te& edge, int w, int i, int j);
    virtual Te      remove_edge(int i, int j);

    // 图的搜索
    void    bfs(int s);
    void    BFS(int vindex, int& clock);
    void    dfs(int s);
    void    DFS(int vindex, int& clock);
    void    dijkstra(int s);
};

/*! @} */


/*!
 * @brief 枚举顶点i的所有邻接顶点
 *
 * @param i: 顶点i
 * @param j: 开始枚举的顶点
 * @return 返回与顶点i邻接的顶点下标，如果不存在，则返回-1
 * @retval None
 */
template <typename Tv, typename Te>
int GraphMatrix<Tv, Te>::next_nbr(int i, int j)
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
int GraphMatrix<Tv, Te>::first_nbr(int i)
{
    return this->next_nbr(i, this->m_vnum);
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
        && (this->m_e[i][j] != nullptr));
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

    this->m_e[i][j] = new Edge<Te>(edge, w);
    this->m_enum++;

    // 修改出度与入度
    this->m_v[i]->out_deg++;
    this->m_v[j]->in_deg++;
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
    Te old = this->m_e[i][j]->data;
    delete this->m_e[i][j];
    this->m_e[i][j] = nullptr;
    this->m_enum--;

    // 修改出度与入度
    this->m_v[i]->out_deg--;
    this->m_v[j]->in_deg--;

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
        this->m_e[j].push_back(nullptr);
    // 顶点数量加1
    this->m_vnum++;
    // 邻接矩阵插入一行
    this->m_e.push_back(dsa::Vector<EdgePtr<Te> >(this->m_vnum, this->m_vnum, nullptr));
    // 插入顶点
    VertexPtr<Tv> vt = new Vertex<Tv>(vertex);
    return this->m_v.push_back(vt);
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
            delete this->m_e[i][j];
            // 头部(终点)顶点 j 的入度减1
            this->m_v[j]->in_deg--;
        }
    }
    // 删除第i行
    this->m_e.remove(i);
    this->m_vnum--;

    for(int j = 0; j < this->m_vnum; j++)
    {
        // 删除顶点的入边
        if (this->exist_edge(j,i))
        {
            // 删除边，并且每行删除对应顶点 i 的元素
            delete this->m_e[j].remove(i);
            // 尾部(起点)顶点 j 的出度减1
            this->m_v[j]->out_deg--;
        }
    }

    Tv old = this->m_v[i]->data;
    delete this->m_v.remove(i);
    return old;
}

/*!
 * @brief 广度优先搜索（全图遍历）
 *
 * 通过bfs，会将全图的连通/可达分量标记成BFS树。
 * bsf的时间复杂度为O(n+e)+O(n+2e)=O(n+e)，其中n和e分别代表顶点和边的数量。
 *
 * @param s: 起始顶点。
 * @return
 * @retval None
 */
template <typename Tv, typename Te>
void GraphMatrix<Tv,Te>::bfs(int s)
{
    this->reset();
    int clock = 0;
    int v = s;
    do
    {
        if (this->m_v[v]->status == VStatus::UnDiscovered)
            this->BFS(v, clock);
        v = ++v % this->m_vnum;     // 按序号顺序访问所有顶点
    } while (s != v);
}

/*!
 * @brief 广度优先搜索（对图中的一个连通/可达分量遍历）
 *
 * 通过BFS标记出一棵以vindex为根的BFS树；BFS树整体上较短且宽。
 *
 * @param vindex: 顶点下标。
 * @param clock: 时间标签，用于判定顶点访问的先后顺序。可以通过顶点的VStatus状态，判断边是属于Tree还是Cross。
 * @return
 * @retval None
 */
template <typename Tv, typename Te>
void GraphMatrix<Tv,Te>::BFS(int vindex, int& clock)
{
    this->m_v[vindex]->status = VStatus::Discovered;

    dsa::Queue<int> q;
    q.enqueue(vindex);
    while(!q.is_empty())
    {
        int v = q.dequeue();
        this->m_v[v]->d_time = ++clock;

        for (int k = this->first_nbr(v); k > -1 ; k = this->next_nbr(v, k))
        {
            if (VStatus::UnDiscovered == this->m_v[k]->status)
            {
                this->m_v[k]->status = VStatus::Discovered;
                q.enqueue(k);       // 在队列中的顶点处理Discovered状态
                this->m_v[k]->parent = v;
                this->m_e[v][k]->status = EStatus::Tree;
                                    // 将边引入Tree中（处于Discovered均为引入Tree中）
            }
            else
            {
                this->m_e[v][k]->status = EStatus::Cross;
                                    // 若已在队列中，或是已经访问完毕，则将边引入Cross边中
            }
        }

        this->m_v[v]->status = VStatus::Visited;
    }
}

/*!
 * @brief 深度优先搜索（全图遍历）
 *
 * dsf的时间复杂度为O(n+e)，其中n和e分别代表顶点和边的数量。
 *
 * @param s: 起始顶点。
 * @return
 * @retval None
 */
template <typename Tv, typename Te>
void GraphMatrix<Tv,Te>::dfs(int s)
{
    this->reset();
    int clock = 0;
    int v = s;
    do
    {
        if (this->m_v[v]->status == VStatus::UnDiscovered)
            this->DFS(v, clock);
        v = ++v % this->m_vnum;     // 按序号顺序访问所有顶点
    }while (s != v);
}

/*!
 * @brief 深度优先搜索（对图中的一个连通/可达分量遍历）
 *
 * 通过BFS标记出一棵DFS树；DFS树整体上较长且窄。
 *
 * @param vindex: 顶点下标。
 * @param clock: 时间标签，用于判定顶点访问的先后顺序。可以根据项点的d_time来判断边是Backward还是Forward。
 * @return
 * @retval None
 */
template <typename Tv, typename Te>
void GraphMatrix<Tv,Te>::DFS(int vindex, int& clock)
{
    this->m_v[vindex]->status = VStatus::Discovered;
    this->m_v[vindex]->d_time = ++clock;

    for (int k = this->first_nbr(vindex); k > -1 ; k = this->next_nbr(vindex, k))
    {
        switch(this->m_v[k]->status)
        {
            case VStatus::UnDiscovered:
                this->m_e[vindex][k]->status = EStatus::Tree;
                this->m_v[k]->parent = vindex;
                this->DFS(k, clock);        // 通过递归实现
                break;
            case VStatus::Discovered:
                this->m_e[vindex][k]->status = EStatus::Backward;
                break;
            case VStatus::Visited:
                this->m_e[vindex][k]->status = (this->m_v[vindex]->d_time < this->m_v[k]->d_time) ?
                                            EStatus::Forward : EStatus::Cross;
                break;
        }
    }

    this->m_v[vindex]->status = VStatus::Visited;
    this->m_v[vindex]->f_time = ++clock;
}

/*!
 * @brief Dijkstra最短路径算法
 *
 * Dijkstra算法可以计算顶点s到其余各点的最短路径及长度，所有最短路径可以组成一棵树。
 * 注意：图中边的权重需要为正。
 *
 * @param s: 起始顶点。
 * @return
 * @retval None
 */
template <typename Tv, typename Te>
void GraphMatrix<Tv,Te>::dijkstra(int s)
{
    this->reset();
    // 用priority表示距离的优先级，距离越小，优先级越高，优先并入最短路径
    this->m_v[s]->priority = 0;
    for (int i = 0; i < this->m_vnum; i ++)
    {
        this->m_v[s]->status = VStatus::Visited;
        // 连接最短路径成树
        if (-1 != this->m_v[s]->parent)
            this->m_e[this->m_v[s]->parent][s]->status = EStatus::Tree;
        // 遍历顶点s的邻接顶点
        for (int j = this->first_nbr(s); j > -1; j = this->next_nbr(s, j))
        {
            if (this->m_v[j]->status == VStatus::UnDiscovered
                    && this->m_v[j]->priority > this->m_v[j]->priority + this->m_e[s][j]->weight)
            {
                // 更新s到j的距离
                this->m_v[j]->priority = this->m_v[s]->priority + this->m_e[s][j]->weight;
                this->m_v[j]->parent = s;
            }

        }
        // 遍历查找下一个最近的顶点
        for (int min = INIT_PRIORITY, j = 0; j < this->m_vnum; j ++)
        {
            if (this->m_v[j]->status == VStatus::UnDiscovered
                    && min > this->m_v[j]->priority)
            {
                min = this->m_v[j]->priority;
                s = j;
            }
        }
    }
}

} /* dsa */

#endif /* ifndef _GRAPH_MATRIX_H */
