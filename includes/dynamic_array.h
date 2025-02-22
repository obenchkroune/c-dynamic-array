#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t type_size;
    size_t capacity;
    size_t used;
} ArrayHeader;

/**
 * _array_init - Initializes a new dynamic array.
 * @type_size: Size of the element type.
 *
 * Returns a pointer to the newly allocated array memory.
 */
void *_array_init(size_t type_size);

/**
 * array_init - Macro to initialize a dynamic array for a given type.
 * Usage: array_init(T)
 */
#define array_init(T) _array_init(sizeof(T));

/**
 * array_destroy - Macro to free the dynamic array.
 * Usage: array_destroy(arr)
 */
#define array_destroy(arr) free((ArrayHeader *)arr - 1)

/**
 * array_insert - Macro to insert an element at a specified position.
 * Usage: array_insert(arr, el, pos)
 * Inserts element 'el' at index 'pos', adjusting capacity if needed.
 */
#define array_insert(arr, el, pos)                                            \
    do {                                                                      \
        ArrayHeader *h       = (ArrayHeader *)arr - 1;                        \
        size_t       pos_cpy = pos > h->used ? h->used : pos;                 \
        if (h->capacity <= h->used) {                                         \
            h->capacity = h->capacity * 2 + h->type_size;                     \
            h = realloc(h, sizeof(ArrayHeader) + h->capacity * h->type_size); \
            if (!h) {                                                         \
                arr = NULL;                                                   \
                break;                                                        \
            }                                                                 \
            arr = (void *)(h + 1);                                            \
        }                                                                     \
        memmove(arr + pos_cpy + 1, arr + pos_cpy,                             \
                h->type_size * (h->used - pos_cpy));                          \
        memcpy(arr + pos_cpy, &el, h->type_size);                             \
        h->used += 1;                                                         \
    } while (0)

/**
 * array_insert2 - Macro to insert a range of elements at a specified position.
 * Usage: array_insert2(arr, begin, end, pos)
 * Inserts elements in the range [begin, end) at index 'pos' and adjusts
 * capacity.
 */
#define array_insert2(arr, begin, end, pos)                               \
    do {                                                                  \
        ArrayHeader *h        = (ArrayHeader *)arr - 1;                   \
        size_t       el_count = (end - begin);                            \
        size_t       pos_cpy  = pos > h->used ? h->used : pos;            \
        while (h->capacity <= h->used + el_count) {                       \
            h->capacity = h->capacity * 2 + 1;                            \
        }                                                                 \
        h = realloc(h, sizeof(ArrayHeader) + h->capacity * h->type_size); \
        if (!h) {                                                         \
            arr = NULL;                                                   \
            break;                                                        \
        }                                                                 \
        arr = (void *)(h + 1);                                            \
        memmove(arr + pos_cpy + el_count, arr + pos_cpy,                  \
                (h->used - pos_cpy) * h->type_size);                      \
        memcpy(arr + pos_cpy, begin, el_count * h->type_size);            \
        h->used += el_count;                                              \
    } while (0)

/**
 * array_push_back - Macro to insert an element at the end of the array.
 * Usage: array_push_back(arr, el)
 */
#define array_push_back(arr, el) \
    array_insert(arr, el, ((ArrayHeader *)arr - 1)->used)

/**
 * array_push_back2 - Macro to insert a range of elements at the end of the
 * array. Usage: array_push_back2(arr, begin, end)
 */
#define array_push_back2(arr, begin, end) \
    array_insert2(arr, begin, end, ((ArrayHeader *)arr - 1)->used)

/**
 * array_push_front - Macro to insert an element at the beginning of the array.
 * Usage: array_push_front(arr, el)
 */
#define array_push_front(arr, el) array_insert(arr, el, 0)

/**
 * array_push_front2 - Macro to insert a range of elements at the beginning of
 * the array. Usage: array_push_front2(arr, begin, end)
 */
#define array_push_front2(arr, begin, end) array_insert2(arr, begin, end, 0)

/**
 * array_size - Macro to get the number of elements in the dynamic array.
 * Usage: array_size(arr)
 */
#define array_size(arr) ((ArrayHeader *)arr - 1)->used

/**
 * array_erase - Macro to remove an element at a specified index.
 * Usage: array_erase(arr, idx)
 * Erases the element at index 'idx' and shifts remaining elements.
 */
#define array_erase(arr, idx)                                                  \
    do {                                                                       \
        ArrayHeader *h = (ArrayHeader *)arr - 1;                               \
        if (idx >= h->used) break;                                             \
        memmove(arr + idx, arr + idx + 1, (h->used - idx - 1) * h->type_size); \
        h->used -= 1;                                                          \
    } while (0)

#endif
