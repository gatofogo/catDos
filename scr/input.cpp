#include "input.h"
#include <conio.h>

int WinInput::get_key(){
    return _getch();
}
bool WinInput::has_key(){
    return _kbhit();
}