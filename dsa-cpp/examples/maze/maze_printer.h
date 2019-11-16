//==============================================================================
/*!
 * @file maze_printer.h
 * @brief 迷宫输出
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef DSAS_MAZE_PRINTER_H
#define DSAS_MAZE_PRINTER_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <thread>
#include <chrono>
#include "maze.h"

namespace dsa
{

/*!
 * @addtogroup Example
 *
 * @{
 */

/*!
 * @brief 打印迷宫
 *
 */
class MazePrinter : public MazeBase
{
private:
    static const char* ch_back;
    static const char* ch_wall;
    static const char* ch_goal;
    static const char* ch_start;
    static const char* pattern[5][5];

protected:
    /** 显示迷宫 */
    virtual void print_maze()
    {
        std::system("cls");
        std::printf("  ");
        // 输出列坐标
        for (int k = 0; k < this->cell_size(); k++)
            (k < 10) ? std::printf("%2X", k) : std::printf(" %c", 'A' - 10 + k);
        std::printf("\n");
        // 输出迷宫
        for (int i = 0; i < this->cell_size(); i++)
        {
            // 输出行坐标
            (i < 10) ? std::printf("%2X", i) : std::printf(" %c", 'A' - 10 + i);
            // 输出宫格
            for (int j = 0; j < this->cell_size(); j++)
            {
                if (this->cell_goal() == cells(i,j))
                    std::printf("%s", this->ch_goal);
                else if (this->cell_start() == cells(i,j))
                    std::printf("%s", this->ch_start);
                else
                    switch (this->cells(i,j)->status)
                    {
                        case dsa::CellStatus::Available:
                            std::printf("%s", "  ");
                            break;
                        case dsa::CellStatus::BackTracked:
                            std::printf("%s", this->ch_back);
                            break;
                        case dsa::CellStatus::Wall:
                            std::printf("%s", this->ch_wall);
                            break;
                        case dsa::CellStatus::Route:
                            std::printf("%s", this->pattern[cells(i,j)->outgoing][cells(i,j)->incoming]);
                            break;
                    }
            }
            std::printf("\n");
        } // for j
        // 等待时间
        //std::getchar();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } // for i

public:
    MazePrinter(int num = MAZE_MAX) : MazeBase(num) {}
};

const char* MazePrinter::ch_back = "○";
const char* MazePrinter::ch_wall = "█";
const char* MazePrinter::ch_goal = "﹩";
const char* MazePrinter::ch_start = "＠";
const char* MazePrinter::pattern[5][5] = {
    {"┼", "┼" , "┼" , "┼" , "┼" },
    {"┼", "  ", "┌" , "─" , "└" },
    {"┼", "┌" , "  ", "┐" , "│" },
    {"┼", "─" , "┐" , "  ", "┘" },
    {"┼", "└" , "│" , "┘" , "  "}
};

/*! @} */
} /* dsa */

#endif /* ifndef DSAS_MAZE_PRINTER_H */
