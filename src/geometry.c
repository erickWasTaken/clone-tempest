#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "./geometry.h"
#include "./meth.h"

polygon* load_polygonfile(const char* filepath){
    FILE* f = fopen(filepath, "r");  
    if(!f) goto abort;

    int facecount = 0; 
    int vertcount = 0;

    char line[256]; 
    while(fgets(line, sizeof(line), f)){
        if(strncmp(line, "v ", 2) == 0) vertcount ++;
        if(strncmp(line, "f ", 2) == 0) facecount ++;
    }

    fseek(f, 0, SEEK_SET);

    polygon* res = (polygon*)malloc(sizeof(polygon));
    res->pos = (vec3*)malloc(sizeof(vec3) * vertcount);
    res->indices = (int*)malloc(sizeof(int) * facecount * 3);
    res->vertcount = vertcount;
    res->facecount = facecount;
    res->mat = id_matrix();

    int i = 0;
    int j = 0;
    while(fgets(line, sizeof(line), f)){
        if(strncmp(line, "v ", 2) == 0){
            sscanf(
                line, 
                "v %f %f %f", 
                &res->pos[i].x, 
                &res->pos[i].y, 
                &res->pos[i].z
            );

            i++;
        }
        if(strncmp(line, "f ", 2) == 0){
            int a, b, c;
            sscanf(
                    line, 
                    "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", 
                    &a, 
                    &b, 
                    &c 
            );

            res->indices[j++] = a - 1;
            res->indices[j++] = b - 1;
            res->indices[j++] = c - 1;
        }
    }

    return res;

abort:
    printf("unable to load polygon: %s\n", filepath);
    return NULL;
}
