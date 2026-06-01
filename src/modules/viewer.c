#include <stdint.h>

#include "./viewer.h"
#include "../renderer.h"
#include "../texture.h"

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

    int ax = width / 2;
    int ay = (height / 4) * 1;

    int bx = (width / 4) * 3;
    int by = (height / 4) * 3;

    draw_line(cbuffer, ax, ay, bx, by, shader);

    ax = bx;
    ay = by;

    bx = (width / 4) * 1;

    draw_line(cbuffer, ax, ay, bx, by, shader);

    ax = bx;
    ay = by;

    bx = width / 2;
    by = (height / 4) * 1;

    draw_line(cbuffer, ax, ay, bx, by, shader);
}
