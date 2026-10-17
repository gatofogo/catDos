#ifndef Node_h
#define Node_h
#include <vector>
#include <iostream>
#include <fstream>
#include "screen.h"
#include "input.h"

struct editor_cursor {
    int x;
    int y;
    int x_ant; // ant de antigo
    int y_ant;
};
class Node {
public:
    std::vector<Node*>childs;
    int x;
    int y;
    int width=0;
    int height=0;
    virtual void update() {}
    virtual void render(screen& tela, int x, int y) = 0;
    virtual ~Node() {}
};
void draw_childs(Node* node, screen& tela, int x, int y);
void update_childs(Node* node);
class Root : public Node {
public:
    void render(screen& tela, int x, int y) override;
    void update() override;
};
class TextEditor : public Node {
public:
    std::vector<std::string> file;
    std::string aonde_salvar;
    editor_cursor cursor{0,0,0,0};
    int border_thickness=1;
    std::string border_char="#";
    Input* input=nullptr;

    void update() override;
    void render(screen& tela, int x, int y) override;
};
#endif