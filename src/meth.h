#ifndef METH_H
#define METH_H

#include <math.h>

#define M_TAU (M_PI * 2)

typedef struct{
    float x, y;
}vec2;

vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_sum(vec2 a, vec2 b);

float cross(vec2 a, vec2 b);

#endif
