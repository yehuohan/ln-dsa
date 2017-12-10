
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

#define INI_MAX

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

/*!
 * @brief 顶点类
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
 * 有向图：所有边为有向边
 * 无向图：所有边为无向边
 * 混合图：既有有向边，也有无向边
 *
 * 路径：一系列顶点构成的序列 P = <v0,v1,v2,v3,...vk>
 * 路径长度：|P|=k
 * 环路：v0 = vk
 *
 * </pre>
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

protected:
    int m_vnum;         /**< 顶点数量 */
    int m_enum;         /**< 边数量 */

};

/*! @} */
}

#endif /* ifndef GRAPH_H */
