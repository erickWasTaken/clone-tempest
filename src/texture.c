#include <stdint.h>
#include <stdlib.h>

#include "./texture.h"

colorbuffer* create_colorbuffer(int width, int height){
    colorbuffer* res;
    res = (colorbuffer*)malloc(sizeof(colorbuffer));
    res->buffer = (uint32_t*)malloc(sizeof(uint32_t) * width * height);
    res->width  = width;
    res->height = height;

    return res;
}

void clear_color(colorbuffer* cbuffer, uint32_t color){
    int width  = cbuffer->width;
    int height = cbuffer->height;

    for(int i = width * height; i--; )
        cbuffer->buffer[i] = color;
}
