#include "tetris.h"
#include <math.h>

void manage_inputs (SDL_Event *event, tetramino_t tet[TETRAMINO_NUM],tetris_map_t *map,Color_t *map_colors) {

    
    if(event->type==SDL_KEYDOWN){

        switch(event->key.keysym.scancode){
            case SDL_SCANCODE_LEFT:
             tetramino_move_left(tet,map);
             break;
             case SDL_SCANCODE_RIGHT:
             tetramino_move_right(tet,map);
             break;             
             case SDL_SCANCODE_DOWN:
                if(tetramino_move_down(tet,map)==TETRAMINO_DEAD){
                    int i=0;
			for(;i<TETRAMINO_NUM;i++)
			{
			 	if(tet[0].posY==-1){
			 				is_running=0;
			 			}
				int current_index = map->width * tet[i].posY + tet[i].posX;
       			map_colors[current_index].r=current_color.r;
				map_colors[current_index].g=current_color.g;
				map_colors[current_index].b=current_color.b;
				
			}	
            tetramino_spawn(tet,map,-1);
                   
                }
             break;
             case SDL_SCANCODE_SPACE:
                Rotate(tet);
             break;
             default:
             break;
        }
    }
}

