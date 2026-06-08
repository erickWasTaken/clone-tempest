#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "texture.h"
#include "renderer.h"
#include "util.h"
#include "meth.h"

void draw_pixel(colorbuffer* cbuffer, int x, int y, uint32_t color){
    int width = cbuffer->width;
    int height = cbuffer->height;

    if(x < 0 || x >= width || y < 0 || y >= height) return;
    cbuffer->buffer[y * width + x] = color;
}

void draw_line(colorbuffer* cbuffer, int ax, int ay, int bx, int by, lineshader shader){
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

    float c = 1 / (float)(bx-ax);
    float t = 0;
    for(int x = ax; x <= bx; x++){
        uint32_t color = shader(t);
        t += c;

        if(steep) draw_pixel(cbuffer, y, x, color);
        else draw_pixel(cbuffer, x, y, color);

        error += 2 * abs(by - ay);
        if(error){
            y += by > ay ? 1 : -1;
            error -= 2 * (bx - ax);
        }
    }
}   

void draw_line_mesh(colorbuffer* cbuffer, vec2 a, vec2 b, float width, uint32_t color){
    vec2 p = vec2_mul(vec2_perp(a, b), width);
    
    draw_triangle(cbuffer, a, b, vec2_sum(a, p), color);
    draw_triangle(cbuffer, a, b, vec2_sum(b, p), color);
}

void draw_triangle(colorbuffer* cbuffer, vec2 a, vec2 b, vec2 c, uint32_t color){
    if(c.y < a.y){
        SWAP(&c.y, &a.y);
        SWAP(&c.x, &a.x);
    }if(b.y < a.y){
        SWAP(&b.y, &a.y);
        SWAP(&b.x, &a.x);
    }if(c.y < b.y){
        SWAP(&c.y, &b.y);
        SWAP(&c.x, &b.x);
    }

    float area     = cross(vec2_sub(b, a), vec2_sub(c, a)); 
    float ab_slope = vec2_sub(b, a).x / vec2_sub(b, a).y;
    float ac_slope = vec2_sub(c, a).x / vec2_sub(c, a).y;
    float bc_slope = vec2_sub(c, b).x / vec2_sub(c, b).y;

    // if(area > 0) return;

    if(a.y != b.y){
        for(int y = a.y; y < b.y; y++){
            float xstart = a.x + (y - a.y) * ac_slope;
            float xend   = a.x + (y - a.y) * ab_slope;

            if(xend < xstart){
                SWAP(&xend, &xstart);
            }

            for(int x = xstart; x <= xend; x++){
                draw_pixel(cbuffer, x, y, color);
            }
        }
    }

    if(b.y != c.y){
        for(int y = b.y; y <= c.y; y++){
            float xstart = a.x + (y - a.y) * ac_slope;
            float xend   = b.x + (y - b.y) * bc_slope;

            if(xend < xstart){
                SWAP(&xend, &xstart);
            }

            for(int x = xstart; x <= xend; x++){
                draw_pixel(cbuffer, x, y, color);
            }
        }
    }
}

void draw_circle(colorbuffer* cbuffer, vec2 p, int size, uint32_t color){
    for(int y = size * 2; y--; ){
        for(int x = size * 2; x--; ){
            float dx = (x + 0.5f) - size;
            float dy = (y + 0.5f) - size;

            if(dx * dx + dy * dy <= size * size)
                draw_pixel(
                        cbuffer, 
                        (p.x + (x + 0.5f)) - size, 
                        (p.y + (y + 0.5f)) - size, 
                        color
                );
        }
    }
}
