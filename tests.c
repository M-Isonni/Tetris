#define SDL_MAIN_HANDLED
#include "aiv_unit_test.h"
#include "tetris.h"

#define TETRIS_SETUP(width,height) tetramino_t tet[TETRAMINO_NUM];\
tetris_map_t map;\
tetris_map_init(&map,width,height);\
tetramino_spawn(tet,&map,0);

TEST(tetramino_spawn)
{
	TETRIS_SETUP(1,1);
	ASSERT_THAT(tet[0].posY==-1);
}

TEST(tetramino_move_down)
{
	TETRIS_SETUP(1,1);	
	tetramino_move_down(tet,&map);
	tetramino_move_down(tet,&map);
	ASSERT_THAT(tet[0].posY==0);
}

TEST(tetris_map_init)
{
	TETRIS_SETUP(1,1);
	ASSERT_THAT(map.cell[0]==0);
}

TEST(tetris_busy_cell)
{
	TETRIS_SETUP(1,1);
	tetramino_t tet2[TETRAMINO_NUM];
	tetramino_spawn(tet2,&map,0);	
	tetramino_move_down(tet,&map);
	tetramino_move_down(tet,&map);
	tetramino_move_down(tet2,&map);
	ASSERT_THAT(tet2[0].posY==-1)
}

TEST(move_left)
{
	TETRIS_SETUP(1,1);	
	tetramino_move_left(tet,&map);
	tetramino_move_left(tet,&map);	
	ASSERT_THAT(tet[0].posX==0);
}

TEST(block_at_max_height){
	TETRIS_SETUP(1,1);
	tetramino_move_down(tet,&map);
	tetramino_move_down(tet,&map);
	tetramino_move_down(tet,&map);
	SDL_Log("%d",map.cell[0]);
	ASSERT_THAT(map.cell[0]==1);

}

TEST(drop_down){
	TETRIS_SETUP(1,2);
	tetramino_move_down(tet,&map);
	tetramino_move_down(tet,&map);
	//map.cell[1]is now 1, check block at max height test
	drop_down(&map,1);
	//dropdown changes it to 0 and cell below to 1; cell below is out of the cell array so i'm checking he current cell to be 0
	ASSERT_THAT(map.cell[1]==0);

}

TEST(check_full_line){
	TETRIS_SETUP(1,1);
	tetramino_move_down(tet,&map);
	tetris_check_full_line(&map);
	ASSERT_THAT(map.cell[0]==0);
}

int main(int argc, char **argv)
{
	RUN_TEST(tetramino_spawn);
	RUN_TEST(tetramino_move_down);
	RUN_TEST(tetris_map_init);
	RUN_TEST(tetris_busy_cell);
	RUN_TEST(move_left);
	RUN_TEST(check_full_line);
	RUN_TEST(block_at_max_height);
	RUN_TEST(drop_down);
	PRINT_TEST_RESULTS();
	return 0;
}
