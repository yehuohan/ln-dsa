
#include <iostream>
#include "maze.h"
#include "maze_printer.h"

int main()
{
    dsa::MazePrinter mzp;
    if (mzp.go())
        std::cout << "\nRoute found\n";
    else
        std::cout << "\nRoute not found\n";
    std::getchar();
    return 0;
}
