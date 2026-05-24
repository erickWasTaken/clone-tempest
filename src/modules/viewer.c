#include <stdint.h>

#include "./viewer.h"
#include "../renderer.h"
#include "../texture.h"

#define S_WIDTH  (1280)
#define S_HEIGHT (720)

void module_render(colorbuffer* cbuffer){
    int ax = S_WIDTH / 2;
    int ay = (S_HEIGHT / 4) * 1;

    int bx = (S_WIDTH / 4) * 3;
    int by = (S_HEIGHT / 4) * 3;

    draw_line(cbuffer, ax, ay, bx, by, 0xff0000ff);

    ax = bx;
    ay = by;

    bx = (S_WIDTH / 4) * 1;

    draw_line(cbuffer, ax, ay, bx, by, 0xff0000ff);

    ax = bx;
    ay = by;

    bx = S_WIDTH / 2;
    by = (S_HEIGHT / 4) * 1;

    draw_line(cbuffer, ax, ay, bx, by, 0xff0000ff);
}
