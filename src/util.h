#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <string.h>

#define SWAP(a, b)                  \
    do{                             \
        int type = sizeof((*(a)));  \
        char temp[sizeof(type)];    \
        memcpy(temp, (a), type);    \
        (*(a)) = (*(b));            \
        memcpy((b), temp, type);    \
    }while(0);

#endif
