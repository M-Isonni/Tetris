#include "tetris.h"
#include "audio.h"

void fill_audio(void *user_data,Uint8 *stream,int len){
    struct note_to_play *note = (struct note_to_play *) user_data;   
    if(note->offset>=note->len){
        note->offset=0;
    }
    note->offset += len;   
    Sint16* data = (Sint16*)(note->data + note->offset);
    int data_length = len/sizeof(Sint16);
    uint16_t* buffer = (uint16_t*)stream;

    int i=0;
    for(;i<data_length;i++)
    {
        float value = (float)data[i] / SDL_MAX_SINT16;
        value *= 0.2f;
        value *= SDL_MAX_UINT16;
        buffer[i] = (uint16_t)value;       
    }  
}

