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

    // vec2 vertices[] = {
    //     (vec2){             // A
    //         width / 2,
    //         (height / 4) * 1
    //     },
    //     (vec2){             // B
    //         (width / 4) * 1,
    //         (height / 4) * 3
    //     },                  
    //     (vec2){             // B
    //         (width / 4) * 1,
    //         (height / 4) * 3
    //     },   
    //     (vec2){             // C
    //         (width / 4) * 3,
    //         (height / 4) * 3
    //     },
    //     (vec2){             // C
    //         (width / 4) * 3,
    //         (height / 4) * 3
    //     },
    //     (vec2){             // A
    //         width / 2,
    //         (height / 4) * 1
    //     }
    // };

    vec2 vertices[] = {
        (vec2){             // A
            width / 2,
            (height / 4) * 1
        },
        (vec2){             // B
            (width / 4) * 1,
            (height / 4) * 3
        },                  
        (vec2){             // B
            (width / 4) * 1,
            (height / 4) * 3
            },   
        (vec2){             // C
            (width / 4) * 3,
            (height / 4) * 3
        },
        (vec2){             // C
            (width / 4) * 3,
            (height / 4) * 3
        },
        (vec2){             // A
            width / 2,
            (height / 4) * 1
        }
    };

    draw_sdf(cbuffer, vertices, sizeof(vertices) / (sizeof(vec2) * 2), 8.0f, COLOR);
}

