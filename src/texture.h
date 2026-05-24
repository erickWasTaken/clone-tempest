#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>

typedef struct{
    int width;
    int height;
    uint32_t* buffer;
}colorbuffer;

colorbuffer* create_colorbuffer(int width, int height);
void clear_color(colorbuffer* cbuffer, uint32_t color);

#endif
