
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


namespace dsa
{

/*!
 * @addtogroup Graph
 *
 * @{
 */

template<typename Te> struct Edge;
template<typename Tv> struct Vertex;

/*!
 * @name 定义类型别名
 * @{
 */
template<typename Te>
using EdgePtr = struct Edge<Te>*;

template<typename Tv>
using VertexPtr = struct Vertex<Tv>*;

/*! @} */


/*!
 * @brief 顶点状态
 *
 */
typedef enum { UnDiscovered, Discovered, Visited } VStatus;

/*!
 * @brief 边状态
 *
 */
typedef enum { UnDetermined, Tree, Cross, Forward, Backward } EStatus;


#define INIT_PRIORITY 2147483647        // 

/*!
 * @brief 顶点类
 *
 */
template<typename Tv>
struct Vertex
{
    Tv      data;
    int     in_deg;     /**< 入度 */
    int     out_deg;    /**< 出度 */
    VStatus status;     /**< 顶点的状态 */
    int     d_time;     /**< 仿问开始时间 */
    int     f_time;     /**< 仿问结束时间 */
    int     parent;     /**< 图的支撑树中的父节点 */
    int     priority;   /**< 优先级参数，一般数越小，优先级越高 */

    Vertex(const Tv& d):
        data(d), in_deg(0), out_deg(0),
        status(UnDiscovered), d_time(-1), f_time(-1),parent(-1), priority(INIT_PRIORITY)
    {}
};

/*!
 * @brief 边类
 *
 */
template<typename Te>
struct Edge
{
    Te      data;       /**< 数据 */
    int     weight;     /**< 权重 */
    EStatus status;     /**< 类型 */

    Edge(const Te& d, int w):
        data(d), weight(w),
        status(UnDetermined)
    {}
};


/*!
 * @brief 图类
 * Tv为顶点数据，Te为边数据。
 *
 * <pre>
 *
 * G = (V, E)，图为顶点和边的集合
 * n = |V|，顶点数
 * e = |E|，边数
 *
 * 邻接关系：v与v之间
 * 关联关系：v与e之间
 *
 * 无向边：A---B---C
 * 有向边：A<---B<--->C
 *
 * 有向图：所有边为有向边，因为是有向边的连接，所以能得到可达分量
 * 无向图：所有边为无向边，通过无向边的连接，可得到连通分量
 * 混合图：既有有向边，也有无向边
 *
 * 路径：一系列顶点构成的序列 P = <v0,v1,v2,v3,...vk>
 * 路径长度：|P|=k
 * 环路：v0 = vk
 *
 * </pre>
 *
 */
template <typename Tv, typename Te>
class Graph
{
private:

protected:
    int m_vnum;         /**< 顶点数量 */
    int m_enum;         /**< 边数量 */

public:
    virtual int     insert_vertex(const Tv&) = 0;
    virtual Tv      remove_vertex(int) = 0;
    virtual bool    exist_edge(int, int) = 0;
    virtual void    insert_edge(const Te&, int, int, int) = 0;
    virtual Te      remove_edge(int, int) = 0;
};

/*! @} */

} /* dsa */

#endif /* ifndef GRAPH_H */
