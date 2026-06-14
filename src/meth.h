#ifndef METH_H
#define METH_H

#include <math.h>
#include <float.h>

#define M_TAU (M_PI * 2)
#define MIN(a, b)  ((b) < (a) ? (b) : (a))
#define MAX(a, b)  ((b) > (a) ? (b) : (a))

typedef struct{
    float x, y;
}vec2;

typedef struct{
    float x, y, z;
}vec3;

typedef struct{
    vec3 row[3];
}mat3;

vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_sum(vec2 a, vec2 b);
vec2 vec2_mul(vec2 a, float s);

vec2 vec2_norm(vec2 v);
vec2 vec2_perp(vec2 a, vec2 b);

float cross(vec2 a, vec2 b);
float vec2_magnitude(vec2 v);

float vec2_dot(vec2 a, vec2 b);

void get_boundingbox(float* left, float* right, float* top, float* bottom, vec2* vertices, int vertcount);
float distance_to_line(vec2 a, vec2 b, vec2 p, float r);

mat3 id_matrix();

void scale(vec3 scale, mat3* mat);
void rotate(vec3 rot, mat3* mat);
void translate(vec3 trans, mat3* mat);

mat3 mat_mat_mul(mat3 a, mat3 b);
vec3 mat_vec_mul(mat3 mat, vec3 vec);

#endif
