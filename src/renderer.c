#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "texture.h"
#include "renderer.h"
#include "util.h"

#define THICKNESS (4)

void draw_pixel(colorbuffer* cbuffer, int x, int y, uint32_t color){
    int width = cbuffer->width;
    int height = cbuffer->height;

    if(x < 0 || x >= width || y < 0 || y >= height) return;
    cbuffer->buffer[y * width + x] = color;
}

void draw_rect(colorbuffer* cbuffer, int x, int y, int size, uint32_t color){
    for(int i = size; i--; )
        for(int j = size; j--; )
            draw_pixel(cbuffer, x + i, y + j, color);
}

void draw_line(colorbuffer* cbuffer, int ax, int ay, int bx, int by, uint32_t color){
    int steep = abs(by - ay) > abs(bx - ax);

    if(steep){
        SWAP(&ax, &ay);
        SWAP(&bx, &by);
    }

    if(ax > bx){
        SWAP(&ax, &bx);
        SWAP(&ay, &by);
    }

    int y = ay;
    int error = 0;
    for(int x = ax; x <= bx; x++){
        // if(steep) draw_pixel(cbuffer, y, x, color);
        // else draw_pixel(cbuffer, x, y, color);
        
        if(steep) draw_rect(cbuffer, y, x, THICKNESS, color);
        else draw_rect(cbuffer, x, y, THICKNESS, color);

        error += 2 * abs(by - ay);
        if(error){
            y += by > ay ? 1 : -1;
            error -= 2 * (bx - ax);
        }
    }
}   

