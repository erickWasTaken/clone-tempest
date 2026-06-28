#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include "./texture.h"
#include "meth.h"

#define BG  (0xff000000)

typedef uint32_t (*lineshader)(float t);

void draw_pixel(colorbuffer* cbuffer, int x, int y, uint32_t color);
void draw_line(colorbuffer* cbuffer, int ax, int ay, int bx, int by, lineshader shader);
void draw_line_mesh(colorbuffer* cbuffer, vec2 a, vec2 b, float width, uint32_t color);

void draw_triangle(colorbuffer* cbuffer, vec2 a, vec2 b, vec2 c, uint32_t color);
void draw_circle(colorbuffer* cbuffer, vec2 p, int size, uint32_t color);
void draw_sdf(colorbuffer* cbuffer, vec2* vertices, int* indices, int vertcount, int indexcount, float thickness, uint32_t color);

#endif
