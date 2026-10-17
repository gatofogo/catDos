#include "screen.h"
#include <vector>
#include <windows.h>
#include <cstdint>
#include <iostream>

void screen::clear(){
    back_screen.assign(screen_width*screen_height, ' ');
    front_screen.assign(screen_width*screen_height, '\0');

    back_screen_color.assign(screen_width*screen_height, 37);
    front_screen_color.assign(screen_width*screen_height, 0);
}
void screen::redraw(int terminal_witdh, int terminal_height){ //vamos ignorar que o terminal height existe né?... é legal
    bool cursor=false;
    for(size_t i=0; i<back_screen.size(); i++){
        if(back_screen[i]!=front_screen[i] or back_screen_color[i]!=front_screen_color[i]){
            int row = i / terminal_witdh;
            int col = i % terminal_witdh;

            if(!cursor){
                std::cout << "\033[" << (row+1) << ";" << (col+1) << "H";
            }
            if (back_screen[i]==' '){
                std::cout << ' ';
            }else{
                std::cout << "\033["<<back_screen_color[i]<<"m" << back_screen[i];
            }
            front_screen_color[i]=back_screen_color[i];
            front_screen[i]=back_screen[i];
            if((int)i%terminal_witdh+1>=terminal_witdh){
                cursor=false;
            }else{
                cursor=true;
            }
        }else{
            cursor=false;
        }
    }
    std::cout << "\033[0m";
    std::cout.flush();
}
void screen::draw_text_in(int colum,int row, std::string text, int witdh_terminal){
    for(size_t i=0; i<text.length(); i++){
        if(colum+(int)i>=witdh_terminal){return;}
        if(row*witdh_terminal>=(int)back_screen.size()){return;}
        back_screen[colum+row*witdh_terminal+(int)i]=text[(int)i];
    }
}
void screen::set_color(int colum, int row, int color, int witdh_terminal){
    if(colum>=witdh_terminal){return;}
    if(row*witdh_terminal>=(int)back_screen.size()){return;}
    back_screen_color[colum+row*witdh_terminal]=color;
}