#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "./meth.h"

typedef struct{
   vec3* pos; 
   int* indices;
   int vertcount;
   int facecount;
   mat3 mat;
}polygon;

typedef enum{
    POLY_TRIANGLE,
    POLY_QUAD
}poly_primitive;

polygon* load_polygonfile(const char* filepath);
polygon* load_polygonprimitive(poly_primitive primitive);

#endif
