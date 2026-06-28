#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "./viewer.h"
#include "../renderer.h"
#include "../texture.h"
#include "../meth.h"

#define COLOR (0xffffff88)

lineshader shader = dashed_line;

float _time;
float _deltatime;

vec2* vertices;
int* indices;

int vcount;
int idxcount;

int scrn_x;
int scrn_y;

uint32_t dashed_line(float t){
    int segs = 10;
    
    uint32_t res = ((int)(t * segs) % 2) ? COLOR : BG;

    return res;
}

uint32_t solidcolor_line(float t){
    return COLOR;
}

bool module_init(int width, int height){
    scrn_x = width;
    scrn_y = height;

    vec2 tmp[] = {
        (vec2){             // A
            width / 2,
            (height / 4) * 1
        },
        (vec2){             // B
            (width / 4) * 1,
            (height / 4) * 3
        },                  
        (vec2){             // C
            (width / 4) * 3,
            (height / 4) * 3
        },
    };

    int idx[] = {
        0, 1,
        0, 2,
        1, 2
    };

    vcount = sizeof(tmp) / sizeof(vec2);
    vertices = (vec2*)malloc(sizeof(vec2) * vcount);

    idxcount = sizeof(idx) / sizeof(int);
    indices = (int*)malloc(sizeof(int) * idxcount);

    if(!vertices || !indices) return false;

    for(int i = vcount; i--; vertices[i] = tmp[i]);
    for(int i = idxcount; i--; indices[i] = idx[i]);

    return true;
}

void module_input(SDL_Event evt){
    switch(evt.type){
        case SDL_KEYDOWN:
                switch(evt.key.keysym.sym){
                    case SDLK_a:
                        break;

                    case SDLK_d:
                        break;

                    case SDLK_w:
                        break;

                    case SDLK_s:
                        break;
                }
            break;
    }
}

void module_update(float time, float deltatime){
    _time = time;
    _deltatime = deltatime;
}

void module_render(colorbuffer* cbuffer){
    float ang = (M_TAU / 20) * _time / 1000.0f;
    vec3 axis = {0, 0, ang};
    vec2 origin = {scrn_x / 2, scrn_y / 2};

    vec2 mesh[vcount];
    for(int i = vcount; i--; mesh[i] = vertices[i]);

    for(int i = vcount; i--; ){
        vec3 vert = {
            mesh[i].x,
            mesh[i].y,
            1.0f
        };

        // printf("\x1B[2J\n");
        // printf("\x1B[H\n");
        //
        // printf("vert before transformations:\nx: %.2f, y: %.2f, z: %.2f\n", vert.x, vert.y, vert.z);

        mat3 model = id_matrix();
        translate((vec2){-origin.x, -origin.y}, &model);

        vec3 res = mat_vec_mul(model, vert);

        rotate(axis, &model);
        translate((vec2){origin.x, origin.y}, &model);

        res = mat_vec_mul(model, res);

        // printf("vert after transformations:\nx: %.2f, y: %.2f, z: %.2f\n", res.x, res.y, res.z);

        mesh[i].x = res.x;
        mesh[i].y = res.y;
    }

    draw_sdf(cbuffer, mesh, indices, idxcount, 6.0f, COLOR);
}
