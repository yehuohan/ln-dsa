
#include <assert.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

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
    int     weight;
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
    g->e[vs][ve]->weight = e->weight;
    g->e[vs][ve]->status = e->status;
    if (type == UnDirected)
    {
        g->e[ve][vs] = (Edge*)malloc(sizeof(Edge));
        g->e[ve][vs]->data = e->data;
        g->e[ve][vs]->weight = e->weight;
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
    g->v[v].status = Discovered;
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
                    printf("%5c", '#');
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
    Graph g;
    Edge e = {.data = 0, .weight = 0, .status = UnDetermined};
    graph_init(&g, 5);

    /*
        0   1   2   3   4
    0   .
    1   #   .
    2       #   .
    3       #       .
    4   #               .
    */
    for (int k = 0; k < g.v_num; k ++)
        g.v[k].data = k + 10;
    graph_edge_add(&g, &e, 0, 1, UnDirected);
    graph_edge_add(&g, &e, 0, 4, UnDirected);
    graph_edge_add(&g, &e, 1, 2, UnDirected);
    graph_edge_add(&g, &e, 1, 3, UnDirected);

    graph_print(&g);

    printf("\ndfs from 4\n");
    graph_vertex_reset(&g);
    graph_dfs(&g, 4, visit_vertex);   // 4 0 1 2 3

    printf("\ndfs from 1\n");
    graph_vertex_reset(&g);
    graph_dfs(&g, 1, visit_vertex);   // 1 0 4 2 3

    graph_free(&g);
    return 0;
}
