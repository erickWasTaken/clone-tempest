#ifndef VIEWER_H
#define VIEWER_H

#include <stdint.h>
#include <stdbool.h>

#include "../texture.h"

uint32_t dashed_line(float t);

bool module_init(int width, int height);
void module_input(SDL_Event evt);
void module_update(float time, float deltatime);
void module_render(colorbuffer* cbuffer);

#endif
