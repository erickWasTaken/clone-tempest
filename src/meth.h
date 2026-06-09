#ifndef METH_H
#define METH_H

#include <math.h>

#define M_TAU (M_PI * 2)

typedef struct{
    float x, y;
}vec2;

vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_sum(vec2 a, vec2 b);
vec2 vec2_mul(vec2 a, float s);

vec2 vec2_norm(vec2 v);
vec2 vec2_perp(vec2 a, vec2 b);

float cross(vec2 a, vec2 b);
float vec2_magnitude(vec2 v);

float vec2_dot(vec2 a, vec2 b);

#endif
