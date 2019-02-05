#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "tetris.h"
#include "audio.h"


#define WIDTH 10
#define HEIGHT 20
#define SIZE WIDTH*HEIGHT

int main(int argc, char **argv)
{
	int timer = 1000;
	uint32_t last_tick =SDL_GetTicks();
	int ret=0;
	is_running=1;

	
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)){
		SDL_Log("init error %s",SDL_GetError());
		ret = -1;
		goto cleanup;
	}

	SDL_Window *window=SDL_CreateWindow("window",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,0);
	if(!window){
		SDL_Log("window error %s",SDL_GetError());
		ret=-1;
		goto cleanup2;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window,0,SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);
	if(!renderer){
		SDL_Log("renderer error %s",SDL_GetError());
		SDL_DestroyWindow(window);
		ret=-1;
		goto cleanup3;
	}

tetris_map_t map;
int width = WIDTH;
int height = HEIGHT;
tetris_map_init(&map,width,height);
tetramino_t tet[TETRAMINO_NUM];
tetramino_spawn(tet,&map,-1);
Color_t map_colors[SIZE];
map_colors_init(map_colors,&map);

struct note_to_play note;
    SDL_memset(&wav_spec,0,sizeof(SDL_AudioSpec));
    SDL_memset(&received,0,sizeof(SDL_AudioSpec));
    SDL_AudioSpec *audio = SDL_LoadWAV("Tetris.wav", &wav_spec, &wav_buffer, &wav_len);
    if(!audio)
    {
        SDL_Log("open device error: %s",SDL_GetError());       
    }      
    note.data= ( Uint8 *) wav_buffer;
    note.offset = 0;
    note.len = wav_len; 
	note.max_len=wav_len;   
    wav_spec.userdata = &note;
    wav_spec.callback = fill_audio;  
	

int device_num = SDL_GetNumAudioDevices(0);  

SDL_AudioDeviceID audio_device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(device_num,0), 0,&wav_spec,&received,0);
    if(!audio_device)
    {
        SDL_Log("open device error: %s",SDL_GetError());       
    }  
SDL_PauseAudioDevice(audio_device,0);

while(is_running)
{
	SDL_Event event;
	uint32_t current_ticks = SDL_GetTicks();
	timer-=current_ticks-last_tick;
	last_tick=current_ticks;	
	if(timer<=0){
		if(tetramino_move_down(tet,&map)==TETRAMINO_DEAD){

			int i=0;
			for(;i<TETRAMINO_NUM;i++)
			{
			 	if(tet[0].posY==-1){
			 				goto cleanup4;
			 			}
				int current_index = map.width * tet[i].posY + tet[i].posX;
        		//int next_index = map.width * (tet[i].posY + 1) + tet[i].posX;
       			map_colors[current_index].r=current_color.r;
				map_colors[current_index].g=current_color.g;
				map_colors[current_index].b=current_color.b;
				
			}	

                    tetramino_spawn(tet,&map,-1);
		}
		timer=1000;
	}

	while(SDL_PollEvent(&event))
	{
		if(event.type==SDL_QUIT)
		{
			goto cleanup4;
		}

		if(event.type==SDL_KEYDOWN){
			manage_inputs(&event,tet,&map,map_colors);
		}
		timer = 1000;
	}
	
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
	//casual_color(renderer);
	tetramino_draw(tet,renderer,30);
	tetris_map_draw(&map,renderer,30,map_colors);
	tetris_check_full_line(&map);
	SDL_RenderPresent(renderer);
}


cleanup4:
	SDL_DestroyRenderer(renderer);
cleanup3:
	SDL_DestroyWindow(window);
cleanup2:
	SDL_Quit();
cleanup:
	return ret;
}
