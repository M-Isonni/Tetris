#include "tetris.h"

void Rotate(tetramino_t tet[TETRAMINO_NUM]){
    int i=0;
    for(;i<TETRAMINO_NUM;i++){ 
        int x=tet[i].posX-tet[0].posX;
        int y = tet[i].posY-tet[0].posY;
        y*=-1;
        int new_coord_x=(int)(round(x*cos(M_PI/2)-y*sin(M_PI/2)));
        int new_coord_y=(int)(round(x*sin(M_PI/2)+y*cos(M_PI/2)));
        new_coord_y*=-1;
        new_coord_x+=tet[0].posX;
        new_coord_y+=tet[0].posY;        
        tet[i].posX= new_coord_x;
        tet[i].posY=new_coord_y;
    }
}
