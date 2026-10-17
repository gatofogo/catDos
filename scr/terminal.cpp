#include "terminal.h"
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif

std::vector<int> terminal::get_terminal_size(){
    #ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int colums, rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    colums=csbi.srWindow.Right-csbi.srWindow.Left+1;
    rows=csbi.srWindow.Bottom-csbi.srWindow.Top+1;
    return {rows, colums};
    #endif
}
