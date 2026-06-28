#include <math.h>
#include <float.h>

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

float vec2_dot(vec2 a, vec2 b){
    return a.x * b.x + a.y * b.y;
}

void get_boundingbox(float* left, float* right, float* top, float* bottom, vec2* vertices, int vertcount){
    *left   = FLT_MAX; 
    *right  = -FLT_MAX; 
    *top    = FLT_MAX; 
    *bottom = -FLT_MAX; 

    for(int i = vertcount; i--; ){ // the condition argument might be evaluated after the arithmetic inside it
        vec2 c = vertices[i];

        if(c.x < *left)   *left = c.x;
        if(c.x > *right)  *right = c.x;
        if(c.y < *top)    *top = c.y;
        if(c.y > *bottom) *bottom = c.y;
    }
}

float distance_to_line(vec2 a, vec2 b, vec2 p, float r){
    vec2 ab = vec2_sub(b, a);
    vec2 ap = vec2_sub(p, a);

    float scale = MIN(1, MAX(0, vec2_dot(ap, ab) / vec2_dot(ab, ab)));
    vec2 v = vec2_sub(ap, vec2_mul(ab, scale));
    return vec2_dot(v, v) - r;
}

mat3 id_matrix(){
    return (mat3){
        (vec3){1.0f, 0.0f, 0.0f},
        (vec3){0.0f, 1.0f, 0.0f},
        (vec3){0.0f, 0.0f, 1.0f},
    };
}

void scale(vec3 scale, mat3* mat){
    mat3 s_mat = {
        (vec3){scale.x, 0.0f, 0.0f},
        (vec3){0.0f, scale.y, 0.0f},
        (vec3){0.0f, 0.0f, scale.z},
    };

    *mat = mat_mat_mul(*mat, s_mat);
}

void rotate(vec3 rot, mat3* mat){
    mat3 rx_mat = {
        (vec3){1.0f, 0.0f, 0.0f},
        (vec3){0.0f, cos(rot.x), -sin(rot.x)},
        (vec3){0.0f, sin(rot.x), cos(rot.x)},
    };

    mat3 ry_mat = {
        (vec3){cos(rot.y),  0.0f, sin(rot.y)},
        (vec3){0.0f,        1.0f,       0.0f},
        (vec3){-sin(rot.y), 0.0f, cos(rot.y)},
    };

    mat3 rz_mat = {
        (vec3){cos(rot.z),  -sin(rot.z), 0.0f},
        (vec3){sin(rot.z),  cos(rot.z),  0.0f},
        (vec3){0.0f,        0.0f,        1.0f},
    };

    mat3 rot_mat = mat_mat_mul(ry_mat, rz_mat);
    rot_mat = mat_mat_mul(rot_mat, rx_mat);

    *mat = mat_mat_mul(*mat, rot_mat);
}

void translate(vec2 trans, mat3* mat){
    vec3* row = mat->row;

    row[0].z = trans.x;
    row[1].z = trans.y;
}

mat3 mat_mat_mul(mat3 a, mat3 b){
    mat3 res = id_matrix();

    for(int j = 0; j < 3; j++){
        res.row[j].x = 
            a.row[j].x * b.row[0].x +
            a.row[j].y * b.row[1].x + 
            a.row[j].z * b.row[2].x ;

        res.row[j].y = 
            a.row[j].x * b.row[0].y +
            a.row[j].y * b.row[1].y + 
            a.row[j].z * b.row[2].y ;

        res.row[j].z = 
            a.row[j].x * b.row[0].z +
            a.row[j].y * b.row[1].z + 
            a.row[j].z * b.row[2].z ;
    }

    return res;
}

vec3 mat_vec_mul(mat3 mat, vec3 vec){
    vec3 res = {0};

    res.x = 
        mat.row[0].x * vec.x +
        mat.row[0].y * vec.y +
        mat.row[0].z * vec.z ;

    res.y = 
        mat.row[1].x * vec.x +
        mat.row[1].y * vec.y +
        mat.row[1].z * vec.z ;

    res.z = 
        mat.row[2].x * vec.x +
        mat.row[2].y * vec.y +
        mat.row[2].z * vec.z ;

    return res;
}

