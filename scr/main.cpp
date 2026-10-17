#ifdef _WIN32
#include <windows.h>
#endif
#include <vector>
#include <fstream>

#include "utils.h"
#include "terminal.h"
#include "screen.h"
#include "Node.h"
#include "input.h"

int main(){
    #ifdef _WIN32
    HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode=0;
    GetConsoleMode(hOut, &mode);
    mode |=ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, mode)) {
        std::cout << "Erro ao ativar ANSI\n";
    }
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif
    std::cout << "caminho do arquivo que queira editar(vasio para não salvar):";
    std::string algo="";
    std::cin >> algo;

    terminal term;
    screen tela;

    Root root; //a ordem de execução e rederização é o index

    //buffers
    std::vector<int> terminal_size_ant=term.get_terminal_size();

    tela.screen_width=terminal_size_ant[1];
    tela.screen_height=terminal_size_ant[0];
    tela.clear();
    root.render(tela, 0, 0);
    TextEditor editor;
    #ifdef _WIN32
    editor.input=new WinInput;
    #endif
    editor.x=0;
    editor.y=0;
    if(!algo.empty()){
        std::ifstream file_read(algo);
        std::string linha="";
        while (std::getline(file_read,linha)) {
            if(linha.length()==0){
                editor.file.push_back("");
            }else{
                if(linha[linha.length()-1]=='\r'){
                    editor.file.push_back(linha.substr(0,linha.length()-1));
                }else{
                    editor.file.push_back(linha);
                }
            }
        }
        file_read.close();
    }else{
        editor.file.push_back("editor legal");
    }
    editor.aonde_salvar=algo;
    editor.width=40;
    editor.height=20;
    root.childs.push_back(&editor);
    root.width=terminal_size_ant[1];
    root.height=terminal_size_ant[0]; //essa parte vou colocar dentro do root dps
    while (true)
    {
        std::vector<int> terminal_size=term.get_terminal_size();
        if(terminal_size!=terminal_size_ant){
            terminal_size_ant=terminal_size;
            tela.screen_width=terminal_size[1];
            tela.screen_height=terminal_size[0];
            tela.clear();
            root.width=terminal_size[1];
            root.height=terminal_size[0];
            root.childs[0]->width=root.width;
            root.childs[0]->height=root.height; //essa tbm
        }
        root.update();
        root.render(tela, 0, 0);
        tela.redraw(terminal_size[1],terminal_size[0]);


        #ifdef _WIN32
        Sleep(16);
        #endif
    }
    return 0;
}
/*

ofstream MyFile("filename.txt");

  // Write to the file
  MyFile << "Files can be tricky, but it is fun enough!";

  // Close the file
  MyFile.close();
*/