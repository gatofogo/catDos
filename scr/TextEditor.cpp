#include "Node.h"
#include "utils.h"
#include "input.h"

void TextEditor::update() {
    if(input->has_key()){
        cursor.x_ant=cursor.x;
        cursor.y_ant=cursor.y;
        int key=input->get_key();
        if(key==0||key==224){
            key=input->get_key();
            switch (key)
            {
            case 75: cursor.x--; break;
            case 72: cursor.y--; break;
            case 77: cursor.x++; break;
            case 80: cursor.y++; break;
            }
            if(!file.empty()){
                cursor.y=clamp(cursor.y,0,(int)file.size()-1);
                cursor.x=clamp(cursor.x,0,file[cursor.y].size());
            }
        }else{
            if(!file.empty()){
                cursor.y=clamp(cursor.y,0,(int)file.size()-1);
                cursor.x=clamp(cursor.x,0,file[cursor.y].size());
            }
            if(file.empty()){file.push_back(" "); cursor.y=0; cursor.x=0;}
            if(key==8){
                if (cursor.x>0){
                    file[cursor.y].erase(cursor.x-1,1);
                    cursor.x--;
                }else if(cursor.y!=0){
                    file[cursor.y-1]+=file[cursor.y];
                    file.erase(file.begin()+cursor.y);
                }
            }else if(key==13){
                file.insert(file.begin()+cursor.y,file[cursor.y].substr(0,cursor.x));
                cursor.y+=1;
                file[cursor.y]=file[cursor.y].substr(cursor.x);
                cursor.x=0; //ele fica no inicio da nova linha
            }else if(key==19){
                if(!aonde_salvar.empty()){
                    std::ofstream write_file(aonde_salvar);
                    std::string text_temp=file[0];
                    for(int i=1; i<(int)file.size(); i++){
                        text_temp=text_temp+"\n"+file[i];
                    }
                    write_file << text_temp; //ele não está escrevendo o arquivo, ver isso depois
                    write_file.close();
                }
            }else{
                file[cursor.y].insert(cursor.x,std::string(1,(char)key));
                cursor.x++;
            }
        }
        if(!file.empty()){
            cursor.y=clamp(cursor.y,0,(int)file.size()-1);
            cursor.x=clamp(cursor.x,0,file[cursor.y].size());
        }
    }
}
void TextEditor::render(screen& tela, int x, int y) {
    if(file.empty()){return;}
    cursor.y=clamp(cursor.y,0,(int)file.size()-1);
    cursor.x=clamp(cursor.x,0,file[cursor.y].size());
    cursor.y_ant=clamp(cursor.y_ant,0,(int)file.size()-1);
    cursor.x_ant=clamp(cursor.x_ant,0,file[cursor.y_ant].size());
    //colocando um +2 por causa do 'n. '
    //pq +2 n +3? é pq quero que a cor fique atras do lugar de escrever, não na frente
    int char_num_cursor=std::to_string(cursor.y).size()+2-1;//-1 para deslocamento e para entendimento
    tela.set_color(cursor.x+x+border_thickness+char_num_cursor,cursor.y+y+border_thickness,int(36),tela.screen_width); 
    tela.set_color(cursor.x_ant+x+border_thickness+char_num_cursor,cursor.y_ant+y+border_thickness,int(37),tela.screen_width);
    for(size_t i=0; i<=file.size(); i++){ 
        if((int)i>=height){break;}
        if(i==file.size()){
            std::string linha=std::string(" ")*std::max(width,0);
            tela.draw_text_in(x+border_thickness,y+i+border_thickness,linha,tela.screen_width);
            break;
        }
        int char_num=std::to_string(i).size()+2;
        std::string linha=file[i].substr(0,width-border_thickness*2-char_num);//esse -3 é o 'n. '
        linha=std::to_string(i)+". "+linha+(std::string(" ")*std::max(width-(int)linha.size()-3,0));
        tela.draw_text_in(x+border_thickness,y+i+border_thickness,linha,tela.screen_width); //tinha um +1 no x kk
    }
    for(int i=0; i<width; i++){
        for(int l=0; l<height; l++){
            if(i<border_thickness || l<border_thickness || i>width-border_thickness-1 || l>height-border_thickness-1){ //sim
                tela.set_color(x+i,y+l,31,tela.screen_width);
                tela.draw_text_in(x+i,y+l,border_char,tela.screen_width);
            }
        }
    }
}