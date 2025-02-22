#include "dynamic_array.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void *_array_init(size_t type_size) {
    ArrayHeader *arr = malloc(sizeof(ArrayHeader) + type_size);
    if (!arr) return NULL;
    arr->capacity  = 1;
    arr->type_size = type_size;
    arr->used      = 0;
    bzero(arr + 1, type_size);
    return arr + 1;
}
