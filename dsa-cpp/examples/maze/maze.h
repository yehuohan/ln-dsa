//==============================================================================
/*!
 * @file maze.h
 * @brief 使用栈结构走迷宫
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef DSAS_MAZE_H
#define DSAS_MAZE_H

#include "../../stack.h"
#include "../../share/rand.h"

namespace dsa
{

/*!
 * @addtogroup Example
 *
 * @{
 */

#define MAZE_MAX    20      /**< 最大迷宫尺寸 */

/** 迷宫格状态 */
typedef enum
{
    Available,      /**< 原始可走的 */
    Route,          /** 在当前路径上的 */
    BackTracked,    /** 所有方向均尝试失败后回溯过的 */
    Wall            /**< 不可使用的（墙） */
}CellStatus;

/** 迷宫格相对方向 */
typedef enum
{
    Unknown,    /**< 未定 */
    East,       /**< 东  */
    South,      /**< 南 */
    West,       /**< 西 */
    North,      /**< 北 */
    NoWay       /**< 无路可通 */
}CellDirection;

/** 迷宫格 */
typedef struct
{
    int             x;          /**< 行 */
    int             y;          /**< 列 */
    CellStatus      status;
    CellDirection   incoming;   /**< 进入方向 */
    CellDirection   outgoing;   /**< 走出方向 */
}Cell;

/** 获取dir的下一个方向，顺序为东南西北(ESWN) */
inline CellDirection next_direction(CellDirection dir) {return CellDirection(dir + 1);}


/*!
 * @brief 迷宫类
 *
 */
class MazeBase
{
private:
    Cell**      m_cells;        /**< 迷宫 */
    Cell*       m_start;        /**< 起点宫格 */
    Cell*       m_goal;         /**< 终点宫格 */
    int         m_size;         /**< 迷宫尺寸 */

private:
    void    init(int num);
    bool    check_neighbor(Cell* cell) const;
    Cell*   goto_neighbor(Cell* cell);

public:
    MazeBase(int num = MAZE_MAX) : m_size(num){init(m_size); new_maze();}
    ~MazeBase()
    {
        for (int k = 0; k < m_size; k ++)
            delete[] m_cells[k];
        if (m_cells) delete[] m_cells;
    }

    void    new_maze();
    bool    go();

protected:
    const Cell* cells(int row, int col) const {return &m_cells[row][col];}
    const Cell* cell_start() const {return m_start;}
    const Cell* cell_goal()  const {return m_goal;}
    int         cell_size()  const {return m_size;}

    /** 显示迷宫 */
    virtual void print_maze(){};
};

/*! @} */
} /* dsa */

#endif /* ifndef DSAS_MAZE_H */
