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

uint32_t solidcolor_line(float t){
    return COLOR;
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

    // draw_triangle(cbuffer, a, b, c, COLOR); 
    
    draw_line(cbuffer, a.x, a.y, b.x, b.y, solidcolor_line);
    vec2 p = vec2_mul(vec2_perp(a, b), 10);
    draw_line(cbuffer, a.x, a.y, (a.x + p.x), (a.y + p.y), solidcolor_line);

    draw_line(cbuffer, b.x, b.y, c.x, c.y, solidcolor_line);
    p = vec2_mul(vec2_perp(b, c), 10);
    draw_line(cbuffer, b.x, b.y, (b.x + p.x), (b.y + p.y), solidcolor_line);

    draw_line(cbuffer, c.x, c.y, a.x, a.y, solidcolor_line);
    p = vec2_mul(vec2_perp(c, a), 10);
    draw_line(cbuffer, c.x, c.y, (c.x + p.x), (c.y + p.y), solidcolor_line);

}

