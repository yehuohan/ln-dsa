
#include "maze.h"

namespace dsa
{

/*!
 * @brief 生成迷宫
 *
 * @param None
 * @return
 * @retval None
 */
void MazeBase::new_maze()
{
    for (int i = 0; i < m_size; i ++)
    {
        for (int j = 0; j < m_size; j ++)
        {
            m_cells[i][j].x = i;    // 行
            m_cells[i][j].y = j;    // 列
            m_cells[i][j].status = CellStatus::Wall;
            m_cells[i][j].incoming = CellDirection::Unknown;
            m_cells[i][j].outgoing = CellDirection::Unknown;
        }
    }

    dsa::rand_init();
    // 初始化可用迷宫单元
    for (int i = 1; i < m_size-1; i ++)
    {
        for (int j = 1; j < m_size-1; j ++)
        {
            if (dsa::rand_n(10) >= 4)   // 75%可用
                m_cells[i][j].status = CellStatus::Available;
        }
    }

    // 生成起点和终点迷宫单元
    m_start = &m_cells[dsa::rand_n(m_size-2) + 1][dsa::rand_n(m_size-2) + 1];
    m_goal  = &m_cells[dsa::rand_n(m_size-2) + 1][dsa::rand_n(m_size-2) + 1];
    m_start->status = CellStatus::Available;
    m_goal->status  = CellStatus::Available;
}

/*!
 * @brief 走迷宫
 *
 * @param None
 * @return
 * @retval None
 */
bool MazeBase::go()
{
    if (m_start->status != CellStatus::Available
        || m_goal->status != CellStatus::Available)
        return false;

    // 用栈结构记录路径
    dsa::Stack<Cell*> path;
    // 路径起点
    m_start->incoming = CellDirection::Unknown;
    m_start->status = CellStatus::Route;
    path.push(m_start);
    do
    {
        this->print_maze();     // 输出迷宫
        Cell* c = path.top();
        if (c == m_goal)
            return true;        // 找到目标

        // 依次探索迷宫单元的4个方向
        // 跳出while的条件：c的4个neighbor方向均“走过” 或 找到一个“可走”的neighbor
        while (c->outgoing < CellDirection::NoWay)
        {
            c->outgoing = next_direction(c->outgoing);
            if (check_neighbor(c))
                break;          // 找到一个“可走”的neighbor
        }

        if (CellDirection::NoWay <= c->outgoing)
        {
            // c的4个neighbor方向均“走过”
            c->status = CellStatus::BackTracked;
            c = path.pop();
        }
        else
        {
            // c的neighbot为“可走”状态
            c = goto_neighbor(c);
            c->outgoing = CellDirection::Unknown;
            c->status = CellStatus::Route;
            path.push(c);
        }
    } while(!path.is_empty());

    return false;
}

/*!
 * @brief 初始化迷宫
 *
 */
void MazeBase::init(int num)
{
    m_cells = new Cell*[num];
    for (int k = 0; k < num; k ++)
        m_cells[k] = new Cell[num];
}

/*!
 * @brief 根据cell的走出的方向，检测邻接的单元格是否可用。
 *
 * <pre>
 * cell的x,y的范围均为(0,m_size)
 * outgoing = E,S,W,N:
 *         [N]
 *          |
 *  [W] - [cell] - [E]
 *          |
 *         [S]
 *  E : y+1
 *  S : x+1
 *  W : y-1
 *  N : x-1
 * <pre>
 *
 * @param cell: 当前迷宫单元格
 * @return
 * @retval None
 */
bool MazeBase::check_neighbor(Cell* cell) const
{
    switch (cell->outgoing)
    {
        case CellDirection::East : return bool(m_cells[cell->x][cell->y+1].status == CellStatus::Available);
        case CellDirection::South: return bool(m_cells[cell->x+1][cell->y].status == CellStatus::Available);
        case CellDirection::West : return bool(m_cells[cell->x][cell->y-1].status == CellStatus::Available);
        case CellDirection::North: return bool(m_cells[cell->x-1][cell->y].status == CellStatus::Available);
        default: return false;
    }
}

/*!
 * @brief 转到cell的邻接单元格
 *
 * 根据当前cell的走出的方向，转到邻接的单元格next，且next的incoming方向即为cell。
 *
 * @param cell: 当前迷宫单元格
 * @return
 * @retval None
 */
Cell* MazeBase::goto_neighbor(Cell* cell)
{
    Cell* next;
    switch (cell->outgoing)
    {
        case CellDirection::East : next = &m_cells[cell->x][cell->y+1]; next->incoming = CellDirection::West ; break;
        case CellDirection::South: next = &m_cells[cell->x+1][cell->y]; next->incoming = CellDirection::North; break;
        case CellDirection::West : next = &m_cells[cell->x][cell->y-1]; next->incoming = CellDirection::East ; break;
        case CellDirection::North: next = &m_cells[cell->x-1][cell->y]; next->incoming = CellDirection::South; break;
        default: next = nullptr;
    }
    return next;
}

} /* dsa */
