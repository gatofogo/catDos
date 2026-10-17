#ifndef screen_h
#define screen_h
#include <vector>
#include <string>
class screen{
public:
    int screen_width=0;
    int screen_height=0;

    std::vector<char> front_screen;
    std::vector<char> back_screen;
    std::vector<int> front_screen_color;
    std::vector<int> back_screen_color;
    void clear();
    void redraw(int terminal_witdh, int terminal_height);
    void draw_text_in(int colum,int row, std::string text, int witdh_terminal);
    void set_color(int colum, int row, int color, int witdh_terminal);
};
#endif