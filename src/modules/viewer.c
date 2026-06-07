#include <stdint.h>

#include "./viewer.h"
#include "../renderer.h"
#include "../texture.h"
#include "../meth.h"

#define COLOR (0xffffff88)

lineshader shader = dashed_line;

uint32_t dashed_line(float t){
    int segs = 10;
    
    uint32_t res = ((int)(t * segs) % 2) ? COLOR : BG;

    return res;
}

void module_render(colorbuffer* cbuffer){
    int width  = cbuffer->width;
    int height = cbuffer->height;

    vec2 a = {
        width / 2,
        (height / 4) * 1
    };

    vec2 b = {
        (width / 4) * 1,
        (height / 4) * 3
    };

    vec2 c = {
        (width / 4) * 3,
        (height / 4) * 3
    };

    draw_triangle(cbuffer, a, b, c, COLOR); 
    draw_circle(cbuffer, a, 10, 1- COLOR);
    draw_circle(cbuffer, b, 10, 1- COLOR);
    draw_circle(cbuffer, c, 10, 1- COLOR);
}
