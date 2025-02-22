#include "dynamic_array.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void *array_init(size_t type_size) {
    ArrayHeader *arr = malloc(sizeof(ArrayHeader) + type_size);
    if (!arr) return NULL;
    arr->capacity  = 1;
    arr->type_size = type_size;
    arr->used      = 0;
    bzero(arr + 1, type_size);
    return arr + 1;
}

int array_insert(void *arr, void *el, size_t pos) {
    void       **ptr = (void **)arr;
    ArrayHeader *h   = (ArrayHeader *)*ptr - 1;

    if (pos > h->used) {
        pos = h->used;
    }
    if (h->capacity <= h->used) {
        h->capacity = h->capacity * 2 + 1;
        h           = realloc(h, sizeof(ArrayHeader) + h->capacity * h->type_size);
        if (!h) {
            return -1;
        }
        *ptr = h + 1;
    }
    memmove(*ptr + h->type_size * (pos + 1), *ptr + h->type_size * pos,
            (h->used - pos) * h->type_size);
    memcpy(*ptr + h->type_size * pos, el, h->type_size);
    h->used += 1;
    return 0;
}

int array_insert2(void *arr, void *begin, void *end, size_t pos) {
    void       **ptr      = (void **)arr;
    ArrayHeader *h        = (ArrayHeader *)*ptr - 1;
    size_t       el_count = (end - begin) / h->type_size;
    if (pos > h->used) pos = h->used;
    while (h->capacity <= h->used + el_count) {
        h->capacity = h->capacity * 2 + 1;
    }
    h = realloc(h, sizeof(ArrayHeader) + h->capacity * h->type_size);
    if (!h) return -1;
    *ptr = h + 1;
    memmove(*ptr + h->type_size * (pos + el_count), *ptr + h->type_size * pos,
            (h->used - pos) * h->type_size);
    memcpy(*ptr + h->type_size * pos, begin, el_count * h->type_size);
    h->used += el_count;
    return 0;
}

void array_erase(void *p, size_t idx) {
    ArrayHeader *h = (ArrayHeader *)p - 1;
    if (idx >= h->used) return;
    memmove(p + idx * h->type_size, p + (idx + 1) * h->type_size,
            (h->used - idx - 1) * h->type_size);
    h->used -= 1;
}
