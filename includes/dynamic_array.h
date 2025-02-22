#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>
#include <stdlib.h>

typedef struct array_header {
    size_t capacity;
    size_t used;
    size_t type_size;
} ArrayHeader;

/**
 * @brief Initializes a new dynamic array.
 *
 * This function allocates memory for a dynamic array along with an initial block for one element.
 * The array is configured to hold elements of the specified size.
 *
 * @param type_size The size in bytes of each element to be stored in the array.
 * @return void* A pointer to the allocated array area, or NULL if memory allocation fails.
 */
void *array_init(size_t type_size);

/**
 * @brief Destroys the dynamic array.
 *
 * This function frees the memory allocated for the dynamic array, including its header.
 *
 * @param arr Pointer to the dynamic array to destroy.
 */
#define array_destroy(arr) free((ArrayHeader *)arr - 1)

/**
 * @brief Inserts an element into the dynamic array at a specified position.
 *
 * This function inserts a single element into the dynamic array at the given position.
 * If the specified position is greater than the current number of elements, the element is
 * appended. The function may reallocate memory if the array lacks sufficient capacity.
 *
 * @param arr Pointer to the dynamic array.
 * @param el Pointer to the element to insert.
 * @param pos The index at which to insert the element.
 * @return int Returns 0 on success or a negative value if the insertion fails.
 */
int array_insert(void *arr, void *el, size_t pos);

/**
 * @brief Inserts a range of elements into the dynamic array at a specified position.
 *
 * This function takes a contiguous block of elements defined by the range [begin, end)
 * and inserts them into the dynamic array at the given position.
 * If the insertion position is beyond the current element count, the new elements are appended.
 * Memory reallocation may occur if the array does not have sufficient capacity.
 *
 * @param arr Pointer to the dynamic array.
 * @param begin Pointer to the beginning of the block of elements to insert.
 * @param end Pointer to the end of the block of elements to insert (non-inclusive).
 * @param pos The index at which to insert the new elements.
 * @return int Returns 0 on success or -1 if reallocation fails.
 */
int array_insert2(void *arr, void *begin, void *end, size_t pos);

/**
 * @brief Appends an element to the end of the dynamic array.
 *
 * This function adds a single element at the end of the dynamic array.
 * Memory is reallocated if necessary to accommodate the new element.
 *
 * @param arr Pointer to the dynamic array.
 * @param el Pointer to the element to be appended.
 * @return int Returns 0 on success or a negative value if the operation fails.
 */
#define array_push_back(arr, el) array_insert(arr, el, ((ArrayHeader *)*(void **)arr - 1)->used)

/**
 * @brief Appends a range of elements to the end of the dynamic array.
 *
 * This function appends a contiguous block of elements defined by the range [begin, end)
 * to the dynamic array. Internally, the function determines the current array size
 * and uses it as the insertion point.
 * Memory reallocation is performed if needed.
 *
 * @param arr Pointer to the dynamic array.
 * @param begin Pointer to the beginning of the range of elements to append.
 * @param end Pointer to the end of the range of elements to append (non-inclusive).
 * @return int Returns 0 on success or -1 if reallocation fails.
 */
#define array_push_back2(arr, begin, end) \
    array_insert2(arr, begin, end, ((ArrayHeader *)*(void **)arr - 1)->used)

/**
 * @brief Inserts an element at the beginning of the dynamic array.
 *
 * This function adds a new element at the beginning of the dynamic array.
 * All existing elements are shifted to make room for the new element.
 * Memory reallocation is performed internally if needed.
 *
 * @param arr Pointer to the dynamic array.
 * @param el Pointer to the element to insert.
 * @return int Returns 0 on success or a negative value if the insertion fails.
 */
#define array_push_front(arr, el) array_insert(arr, el, 0)

/**
 * @brief Inserts a range of elements at the beginning of the dynamic array.
 *
 * This function inserts a contiguous block of elements defined by the range [begin, end)
 * at the beginning of the dynamic array. Existing elements are shifted accordingly.
 * Memory reallocation may occur if the array capacity is exceeded.
 *
 * @param arr Pointer to the dynamic array.
 * @param begin Pointer to the beginning of the block of elements to insert.
 * @param end Pointer to the end of the block of elements to insert (non-inclusive).
 * @return int Returns 0 on success or -1 if reallocation fails.
 */
#define array_push_front2(arr, begin, end) array_insert2(arr, begin, end, 0)

/**
 * @brief Retrieves the number of elements currently stored in the dynamic array.
 *
 * @param arr Pointer to the dynamic array.
 * @return size_t The number of elements in the dynamic array.
 */
#define array_size(arr) ((ArrayHeader *)arr - 1)->used

/**
 * @brief Removes an element from the dynamic array at a specified index.
 *
 * This function deletes the element at the given index and shifts all subsequent elements
 * to fill the gap. If the index is out of bounds, the function does nothing.
 *
 * @param arr Pointer to the dynamic array.
 * @param idx The index of the element to remove.
 */
void array_erase(void *arr, size_t idx);

#endif
