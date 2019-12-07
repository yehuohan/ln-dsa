
#include <assert.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>

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
 * @brief 边类型（无向，有向）
 *
 */
typedef enum { UnDirected, Directed } EType;

/*!
 * @brief 图顶点
 *
 */
typedef struct Vertex
{
    int     data;
    VStatus status;
}Vertex;
typedef Vertex* VertexPtr;

/*!
 * @brief 图边
 *
 */
typedef struct Edge
{
    int     data;
    EStatus status;
}Edge;
typedef Edge* EdgePtr;

/*!
 * @brief 图结构
 *
 */
typedef struct Graph
{
    Vertex* v;
    EdgePtr** e;
    int v_num;
    int e_num;
}Graph;
typedef Graph* GraphPtr;

/*!
 * @brief 访问顶点函数
 *
 */
typedef void(*FuncVisitV)(Vertex*);

/*!
 * @brief 访问边函数
 *
 */
typedef void(*FuncVisitE)(Vertex*);


void graph_init(Graph* g, int v_num);
void graph_free(Graph* g);
void graph_vertex_reset(Graph* g);
void graph_edge_reset(Graph* g);
void graph_edge_add(Graph* g, const Edge* e, int vs, int ve, EType type);
int graph_edge_exit(const Graph* g, int vs, int ve);
static void DFS(Graph* g, int v, FuncVisitV f);
void graph_dfs(Graph* g, int s, FuncVisitV f);


/*!
 * @brief 初始化图
 *
 * @param v_num: 顶点数
 * @param v_num: 边数
 */
void graph_init(Graph* g, int v_num)
{
    g->v_num = v_num;
    g->e_num = 0;
    g->v = (Vertex*)malloc(sizeof(Vertex) * v_num);
    g->e = (EdgePtr**)malloc(sizeof(EdgePtr*) * v_num);
    for (int k = 0; k < v_num; k ++)
    {
        g->e[k] = (EdgePtr*)malloc(sizeof(EdgePtr) * v_num);
        /*for (int j = 0; j < v_num; j ++)*/
        /*    g->e[k][j] = NULL;          */
        memset(g->e[k], 0, sizeof(EdgePtr) * v_num);
    }
}

/*!
 * @brief 释放图
 *
 */
void graph_free(Graph* g)
{
    free(g->v);
    for (int k = 0; k < g->v_num; k ++)
    {
        for (int j = 0; j < g->v_num; j ++)
        {
            if (g->e[k][j] != NULL)
                free(g->e[k][j]);
        }
        free(g->e[k]);
    }
    free(g->e);
}

/*!
 * @brief 初始化顶点
 */
void graph_vertex_reset(Graph* g)
{
    for (int k = 0; k < g->v_num; k ++)
        g->v[k].status = UnDiscovered;
}

/*!
 * @brief 初始化边
 */
void graph_edge_reset(Graph* g)
{
    for (int k = 0; k < g->v_num; k ++)
    {
        for (int j = 0; j < g->v_num; j ++)
        {
            if (g->e[k][j] != NULL)
                g->e[k][j]->status = UnDetermined;
        }
    }
}

/*!
 * @brief 添加边
 *
 * @param e: 边
 * @param vs: 起始顶点
 * @param ve: 终顶点
 * @param type: 有向边或无向边
 */
void graph_edge_add(Graph* g, const Edge* e, int vs, int ve, EType type)
{
    assert(0 <= vs && vs < g->v_num);
    assert(0 <= ve && ve < g->v_num);
    assert(vs != ve);
    g->e[vs][ve] = (Edge*)malloc(sizeof(Edge));
    g->e[vs][ve]->data = e->data;
    g->e[vs][ve]->status = e->status;
    if (type == UnDirected)
    {
        g->e[ve][vs] = (Edge*)malloc(sizeof(Edge));
        g->e[ve][vs]->data = e->data;
        g->e[ve][vs]->status = e->status;
    }
    g->e_num ++;
}

int graph_edge_exit(const Graph* g, int vs, int ve)
{
    assert(0 <= vs && vs < g->v_num);
    assert(0 <= ve && ve < g->v_num);
    return (g->e[vs][ve] != NULL);
}

/*!
 * @brief 深度优先搜索
 *
 */
static void DFS(Graph* g, int v, FuncVisitV f)
{
    if (f)
        f(&g->v[v]);
    g->v[v].status = Visited;

    // 查找v为起点的边
    for (int k = 0; k < g->v_num; k ++)
    {
        if (graph_edge_exit(g, v, k))
        {
            switch (g->v[k].status)
            {
                case UnDiscovered:
                    DFS(g, k, f);
                    break;
                case Discovered:
                case Visited:
                    break;
            }
        }
    }
}

/*!
 * @brief 深度优先搜索
 *
 * @param s: 搜索起始顶点
 * @param f: 顶点访问函数
 *
 */
void graph_dfs(Graph* g, int s, FuncVisitV f)
{
    assert(0 <= s && s < g->v_num);
    int v = s;
    do
    {
        if (g->v[v].status == UnDiscovered)
            DFS(g, v, f);
        v = (v+1) % g->v_num;
    }while(s != v);
}

/*!
 * @brief 广度优先搜索
 *
 */
static void BFS(Graph* g, int v, FuncVisitV f)
{
    // 用长数组临时代码队列
    int* q = (int*)malloc(sizeof(int) * g->v_num);
    int qin = 0, qout = 0; 
    q[qin++] = v;
    while (qout < qin)
    {
        v = q[qout++];
        for (int k = 0; k < g->v_num; k ++)
        {
            if (g->e[v][k] != NULL)
            {
                if (g->v[k].status == UnDiscovered)
                {
                    g->v[k].status = Discovered;
                    q[qin++] = k;
                }
            }
        }
        if (f)
            f(&g->v[v]);
        g->v[v].status = Visited;
    }
    free(q);
}

/*!
 * @brief 广度优先搜索
 *
 * @param s: 搜索起始顶点
 * @param f: 顶点访问函数
 *
 */
void graph_bfs(Graph* g, int s, FuncVisitV f)
{
    assert(0 <= s && s < g->v_num);
    int v = s;
    do
    {
        if (g->v[v].status == 0)
            BFS(g, v, f);
        v = (v+1) % g->v_num;
    }while(s != v);
}

/*!
 * @brief Dijkstra最短路径算法
 *
 * Dijkstra算法可以计算顶点s到其余各点的最短路径及长度。
 * 注意：图中边的权重需要为正。
 *
 * @param s: 起始顶点。
 * @param dist: 保存s到各顶点最短距离的数据。
 * @return
 * @retval None
 */
void graph_dijkstra(Graph* g, int s, int dist[])
{
    // 初始化s到各顶点的距离为无限大
    for (int k = 0; k < g->v_num; k ++)
        dist[k] = INT_MAX;
    dist[s] = 0;
    // 找出s到各顶点的最短距离（共v_num个）
    int v = s;
    for (int i = 0; i < g->v_num; i ++)
    {
        g->v[v].status = Visited;
        // 遍历v的邻接顶点
        for (int k = 0; k < g->v_num; k ++)
        {
            if (graph_edge_exit(g, v, k) && g->v[k].status == UnDiscovered)
            {
                // s->k的距离 > s->v的距离 + v->k距离
                if (dist[k] > dist[v] + g->e[v][k]->data)
                    dist[k] = dist[v] + g->e[v][k]->data;
            }
        }
        // 遍历查找下一个最近的顶点
        for (int min = INT_MAX, k = 0; k < g->v_num; k ++)
        {
            if (g->v[k].status == UnDiscovered && min > dist[k])
            {
                min = dist[k];
                v = k;
            }
        }
    }
}

void graph_print(const Graph* g)
{
    printf("%3c", ' ');
    for (int k = 0; k < g->v_num; k ++)
    {
        printf("%5d", k);
    }
    printf("\n");
    for (int k = 0; k < g->v_num; k ++)
    {
        printf("%3d", k);
        for (int j = 0; j < g->v_num; j ++)
        {
            if (k == j)
                printf("%5c", '.');
            else
            {
                if (graph_edge_exit(g, k, j))
                    printf("%5d", g->e[k][j]->data);
                else
                    printf("%5c", ' ');
            }
        }
        printf("\n");
    }
}

void visit_vertex(Vertex* v)
{
    printf("%d ", v->data);
}

int main()
{
    const int N = 5;
    Graph g;
    Edge e = {.data = 0, .status = UnDetermined};
    graph_init(&g, N);

    /*
        0   1   2   3   4
    0   .
    1   6   .
    2   4   1   .
    3       3       .
    4   7       9   5   .
    */
    for (int k = 0; k < g.v_num; k ++)
        g.v[k].data = k + 10;
    e.data = 6; graph_edge_add(&g, &e, 0, 1, UnDirected);
    e.data = 4; graph_edge_add(&g, &e, 0, 2, UnDirected);
    e.data = 7; graph_edge_add(&g, &e, 0, 4, UnDirected);
    e.data = 1; graph_edge_add(&g, &e, 1, 2, UnDirected);
    e.data = 3; graph_edge_add(&g, &e, 1, 3, UnDirected);
    e.data = 9; graph_edge_add(&g, &e, 2, 4, UnDirected);
    e.data = 5; graph_edge_add(&g, &e, 3, 4, UnDirected);

    graph_print(&g);

    printf("\ndfs from 4\n");
    graph_vertex_reset(&g);
    graph_dfs(&g, 4, visit_vertex); // 4 0 1 2 3

    printf("\nbfs from 1\n");
    graph_vertex_reset(&g);
    graph_bfs(&g, 1, visit_vertex); // 1 0 2 3 4

    printf("\ndijkstra from 2\n");
    int dist[N];
    graph_vertex_reset(&g);
    graph_dijkstra(&g, 2, dist);
    for (int k = 0; k < N; k ++)
        printf("%2d ", k);          // 0 1 2 3 4
    printf("\n");
    for (int k = 0; k < N; k ++)
        printf("%2d ", dist[k]);    // 4 1 0 4 9

    graph_free(&g);
    return 0;
}
