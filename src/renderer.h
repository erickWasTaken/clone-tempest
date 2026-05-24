#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include "./texture.h"

#define BG  (0xffffffff)

typedef uint32_t (*lineshader)(float t);

void draw_pixel(colorbuffer* cbuffer, int x, int y, uint32_t color);
void draw_line(colorbuffer* cbuffer, int ax, int ay, int bx, int by, lineshader shader);

#endif
