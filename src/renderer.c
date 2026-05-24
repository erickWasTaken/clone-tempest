#include <stdint.h>

#include "texture.h"
#include "renderer.h"

void draw_pixel(colorbuffer* cbuffer, int x, int y, uint32_t color){
    int width = cbuffer->width;
    int height = cbuffer->height;

    if(x < 0 || x >= width || y < 0 || y >= height) return;
    cbuffer->buffer[y * width + x] = color;
}

void draw_line(colorbuffer* cbuffer, int ax, int ay, int bx, int by, uint32_t color){

}
