#include "tetris.h"

// static void _draw_rect_internal(SDL_Renderer *renderer, SDL_Rect *rect, Uint8 r, Uint8 g, Uint8 b)
// {
//     SDL_SetRenderDrawColor(renderer, r, g, b, 255);
//     SDL_RenderDrawRect(renderer, rect);
// }

void map_colors_init(Color_t *color,tetris_map_t *map){
    color= malloc(sizeof(uint8_t)*3*map->height*map->width);
    memset(color,0,sizeof(uint8_t) *3*map->height*map->width);
}

void tetramino_draw(tetramino_t tet[TETRAMINO_NUM],SDL_Renderer *renderer,int size){
    int i=0;
    for(;i<TETRAMINO_NUM;i++){        
        SDL_Rect rect;
        rect.x=tet[i].posX*size;
        rect.y= tet[i].posY*size;
        rect.w=size;
        rect.h=size;
        SDL_SetRenderDrawColor(renderer,current_color.r,current_color.g,current_color.b,255);
        SDL_RenderDrawRect(renderer,&rect);
    }
}

void tetris_map_draw(tetris_map_t *map, SDL_Renderer *renderer, int size, Color_t *map_colors)
{     
    int y, x;
    for (y = 0; y < map->height; y++)
    {
        for (x = 0; x < map->width; x++)
        {
            int index = map->width * y + x;
            if (map->cell[index] != 0)
            {               
                SDL_SetRenderDrawColor(renderer,map_colors[index].r,map_colors[index].g,map_colors[index].b,255);
                SDL_Rect rect;
                rect.x = x * size;
                rect.y = y * size;
                rect.h = size;
                rect.w = size;
                //_draw_rect_internal(renderer, &rect, 255, 255, 255);
                SDL_RenderFillRect(renderer,&rect);
            }
        }
    }
}