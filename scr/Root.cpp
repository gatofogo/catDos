#include "node.h"
void draw_childs(Node* node, screen& tela, int x, int y){
    for(size_t i=0; i<node->childs.size(); i++){
        node->childs[i]->render(tela, x+node->childs[i]->x, y+node->childs[i]->y);
        draw_childs(node->childs[i], tela, x+node->childs[i]->x, y+node->childs[i]->y);
    }
}
void update_childs(Node* node){
    for(size_t i=0; i<node->childs.size(); i++){
        node->childs[i]->update();
        update_childs(node->childs[i]);
    }
}
void Root::render(screen& tela, int x, int y){
    for(size_t i=0; i<childs.size(); i++){
        childs[i]->render(tela, x+childs[i]->x, y+childs[i]->y);
        draw_childs(childs[i], tela, x+childs[i]->x, y+childs[i]->y);
    }
}
void Root::update(){
    for(size_t i=0; i<childs.size(); i++){
        childs[i]->update();
        update_childs(childs[i]);
    }
}