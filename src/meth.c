#include <math.h>

#include "meth.h"

vec2 vec2_sub(vec2 a, vec2 b){
    return (vec2){
        a.x - b.x,
        a.y - b.y
    };
}

vec2 vec2_sum(vec2 a, vec2 b){
    return (vec2){
        a.x + b.x,
        a.y + b.y
    };
}

float cross(vec2 a, vec2 b){
    return a.x * b.y - b.x * a.y;
}
