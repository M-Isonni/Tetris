#include <SDL.h>
#include <string.h>
#include <stdlib.h>

#define TETRAMINO_DEAD -1
#define TETRAMINO_OK 0
#define TETRAMINO_NUM 4

int is_running;

typedef struct Color{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    }Color_t;

Color_t current_color;

typedef struct tetramino{      
    int posX;  
    int posY;
} tetramino_t;

typedef struct tetris_map{    
    int width;
    int height;
    int *cell;
}tetris_map_t;

int tetramino_move_down(tetramino_t *tet,tetris_map_t *map);

void tetramino_spawn(tetramino_t *tet, tetris_map_t *map, int force_random);

void spawn_I(tetramino_t tet[TETRAMINO_NUM], tetris_map_t *map);

void tetris_map_init(tetris_map_t *tetris_map, int width,int height);

void tetramino_draw(tetramino_t *tet, SDL_Renderer *renderer,int size);

void manage_inputs (SDL_Event *event, tetramino_t *tet,tetris_map_t *map,Color_t *map_colors);

void tetris_map_draw(tetris_map_t *map, SDL_Renderer *renderer, int size, Color_t * map_colors);

void tetramino_move_left(tetramino_t *tet, tetris_map_t *map);

void tetramino_move_right(tetramino_t *tet, tetris_map_t *map);

void tetris_check_full_line(tetris_map_t *map);

void drop_down(tetris_map_t *map,int first_deleted_row);

void casual_color(Color_t *current_color);

void map_colors_init(Color_t *color,tetris_map_t *map);

void Rotate(tetramino_t tet[TETRAMINO_NUM]);