#include <SDL.h>

uint8_t* wav_buffer;
uint32_t wav_len;
SDL_AudioSpec wav_spec,received;

struct note_to_play{
    Uint8 *data;
    Uint32 len;
    Uint32 offset;
    uint32_t max_len;
    };

void fill_audio(void *user_data,Uint8 *stream,int len);
//void play_audio(char *music_path,SDL_AudioSpec *wav_spec, SDL_AudioSpec *received,struct note_to_play *note,uint8_t *wav_buffer,uint32_t wav_len);

