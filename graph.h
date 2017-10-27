
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
