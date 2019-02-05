#include "tetris.h"
#include <math.h>

//NOT STATIC IN ORDER TO RUN TESTS
void spawn_I(tetramino_t tet[TETRAMINO_NUM], tetris_map_t *map){
    int i=0;
    for(;i<TETRAMINO_NUM;i++){       
        tet[i].posX=map->width/2;
        tet[i].posY=-1-i;        
    }
}
static void spawn_L(tetramino_t tet[TETRAMINO_NUM], tetris_map_t *map){          
        tet[0].posX=map->width/2;
        tet[0].posY=-1; 
        tet[1].posX=tet[0].posX-1; 
        tet[1].posY=tet[0].posY;
        tet[2].posX=tet[1].posX;
        tet[2].posY=tet[1].posY-1;
        tet[3].posX=tet[1].posX;
        tet[3].posY=tet[2].posY-1;
}
static void spawn_quad(tetramino_t tet[TETRAMINO_NUM], tetris_map_t *map){
        tet[0].posX=map->width/2;
        tet[0].posY=-1; 
        tet[1].posX=tet[0].posX-1; 
        tet[1].posY=tet[0].posY;
        tet[2].posX=tet[0].posX;
        tet[2].posY=tet[0].posY-1;
        tet[3].posX=tet[1].posX;
        tet[3].posY=tet[0].posY-1;
}
static void spawn_T(tetramino_t tet[TETRAMINO_NUM], tetris_map_t *map){
    tet[0].posX=map->width/2;
        tet[0].posY=-1; 
        tet[1].posX=tet[0].posX-1; 
        tet[1].posY=tet[0].posY;
        tet[2].posX=tet[0].posX+1;
        tet[2].posY=tet[0].posY;
        tet[3].posX=tet[0].posX;
        tet[3].posY=tet[0].posY-1;
}
static void spawn_Z(tetramino_t tet[TETRAMINO_NUM], tetris_map_t *map){
    tet[0].posX=map->width/2;
        tet[0].posY=-1; 
        tet[1].posX=tet[0].posX-1; 
        tet[1].posY=tet[0].posY;
        tet[2].posX=tet[0].posX+1;
        tet[2].posY=tet[0].posY-1;
        tet[3].posX=tet[0].posX;
        tet[3].posY=tet[0].posY-1;
}

void tetramino_spawn(tetramino_t tet[TETRAMINO_NUM], tetris_map_t *map, int force_random)
{
    int randomic_spawner;
    casual_color(&current_color);
    if(force_random==-1){
     randomic_spawner=rand()%5;    
    }
    else{
        randomic_spawner=force_random;
    }
    switch (randomic_spawner){
            case 0:               
                spawn_I(tet,map);
                break;
            case 1:                
                spawn_L(tet,map);
                break;
            case 2:
                spawn_quad(tet,map);
                break;
            case 3:
                spawn_T(tet,map);
                break;
            case 4:
                spawn_Z(tet,map);
                break;
    } 
}

int tetramino_move_down(tetramino_t tet[TETRAMINO_NUM], tetris_map_t *map)
{   
    int i;
    int can_move = 1;
    for (i = 0; i < TETRAMINO_NUM; i++)
    {
        int current_index = map->width * tet[i].posY + tet[i].posX;
        int next_index = map->width * (tet[i].posY + 1) + tet[i].posX;
        if (tet[i].posY + 1 >= map->height)
        {
            map->cell[current_index] = 1;            
            can_move=0;
            //return TETRAMINO_DEAD;
        }
        if(can_move&&tet[i].posY>=-1)
        {
            if (map->cell[next_index] == 0)
            {
                can_move=1;
            }
            else
            {  
                map->cell[current_index] = 1;
                can_move=0;                
            }
        }
        else if(!can_move){
            map->cell[current_index] = 1;
        }
    }

    if (!can_move){        
        i=0;
        for(;i<TETRAMINO_NUM;i++){            
            int current_index = map->width * tet[i].posY + tet[i].posX;        
            map->cell[current_index] = 1;
        }      
        return TETRAMINO_DEAD;
    }

    if(can_move)
    for (i = 0; i < TETRAMINO_NUM; i++)
    {
        tet[i].posY += 1;
    }

    return TETRAMINO_OK;
}

void tetramino_move_left(tetramino_t tet[TETRAMINO_NUM], tetris_map_t *map){
    int i=0;
    int can_move=1;
    for(;i<TETRAMINO_NUM;i++)
    {       
        int current_index = map->width * tet[i].posY + tet[i].posX;
        int next_index = map->width * (tet[i].posY) + tet[i].posX-1;
        
        if(current_index%map->width==0)
        {
            can_move=0;
            return;
        }
        if(tet[i].posY>=-1){

            if(map->cell[next_index]!=0){           
                can_move=0;
                return;
            }        
        }
    }   
    
    if (can_move){
        i=0;
     for(;i<TETRAMINO_NUM;i++)
        {
            tet[i].posX-=1;
        } 
    }
}

void tetramino_move_right(tetramino_t tet[TETRAMINO_NUM], tetris_map_t *map){   
    int i=0;
    int can_move=1;
    for(;i<TETRAMINO_NUM;i++)
    {   
        int next_index = map->width * (tet[i].posY) + tet[i].posX+1;
        
        if(next_index%map->width==0)
        {
            can_move=0;
            return;
        }
        if(tet[i].posY>=-1){
            if(map->cell[next_index]!=0){           
                can_move=0;
                return;
            }        

        }
    }   
    
    if (can_move){
        i=0;
     for(;i<TETRAMINO_NUM;i++)
        {
            tet[i].posX+=1;
        } 
    }
}

void tetris_map_init(tetris_map_t *tetris_map, int width,int height){
    tetris_map->cell = malloc(sizeof(int)*height*width);    
    tetris_map->height=height;
    tetris_map->width=width;
    memset(tetris_map->cell,0,sizeof(int) * height*width); 
      
}

void tetris_check_full_line(tetris_map_t *map){
    int y, x;
    int deleted_rows=0;
    int first_deleted_row=-1;
    for (y = map->height-1; y >= 0; y--)
    {
        for (x = 0; x < map->width; x++)
        {
            int index = map->width * y + x;
            if(map->cell[index]==0)
            {
                break;
            }
            else if(x==map->width-1){
                index = map->width * y;
                for(int i =0;i<map->width;i++){
                    index = map->width * y + i;
                    memset(&map->cell[index],0,sizeof(int));
                }
                if(first_deleted_row==-1){
                    first_deleted_row=y;
                }
                deleted_rows++;                
            }
        }
    }
    int i=0;
    for(;i<deleted_rows;i++){
        drop_down(map,first_deleted_row);
    }
}

void drop_down(tetris_map_t *map, int fisrt_deleted_row){
    int y, x;
    for (y = map->height-1; y >=0; y--)
    {
        if(y>=fisrt_deleted_row){
            continue;
        }
        for (x = 0; x < map->width; x++)
        {
            int next_index = map->width * (y+1) + x;
            int index = map->width * y + x;
            if (map->cell[index] != 0)
            {
               map->cell[index] =0;
               map->cell[next_index]=1;
            }
        }
    }
}

void casual_color(Color_t *current_color){
    int random_int=rand()%5;
    switch(random_int){
        case 1:
        current_color->r=255;
        current_color->g=0;
        current_color->b=0;
        break;
        case 2:
        current_color->r=255;
        current_color->g=255;
        current_color->b=0;
        break;
        case 3:
        current_color->r=0;
        current_color->g=255;
        current_color->b=0;
        break;
        case 4:
        current_color->r=0;
        current_color->g=0;
        current_color->b=255;        
        break;
        case 5:
        current_color->r=255;
        current_color->g=0;
        current_color->b=255;
        break;

    }
}