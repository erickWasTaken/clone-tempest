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

vec2 vec2_mul(vec2 a, float s){
    return (vec2){
        a.x * s,
        a.y * s
    };
}

float cross(vec2 a, vec2 b){
    return a.x * b.y - b.x * a.y;
}

float vec2_magnitude(vec2 v){
    return sqrt(v.x * v.x + v.y * v.y); 
}

vec2 vec2_norm(vec2 v){
    float mag = vec2_magnitude(v);
    return (vec2){
        v.x / mag,
        v.y / mag
    };
}

vec2 vec2_perp(vec2 a, vec2 b){
    vec2 v ={
        b.x - a.x, 
        b.y - a.y
    };

    float mag = vec2_magnitude(v);

    return (vec2){
        -v.y / mag,
         v.x / mag
    };
}
