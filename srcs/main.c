#include <assert.h>
#include <stdio.h>

#include "dynamic_array.h"

// examples
int main(void) {
    // Create a dynamic array for integers.
    int *arr = array_init(sizeof(int));
    assert(arr != NULL);

    // Append values 0 through 4.
    for (int i = 0; i < 5; i++) {
        assert(array_push_back(&arr, &i) == 0);
    }
    printf("After push_back, size: %zu\n", array_size(arr));
    for (size_t i = 0; i < array_size(arr); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Insert 42 at index 2.
    int insert_value = 42;
    assert(array_insert(&arr, &insert_value, 2) == 0);
    printf("After insertion at index 2, size: %zu\n", array_size(arr));
    for (size_t i = 0; i < array_size(arr); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Erase element at index 3.
    array_erase(arr, 3);
    printf("After erasing index 3, size: %zu\n", array_size(arr));
    for (size_t i = 0; i < array_size(arr); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Append a range of values using push_back2.
    int extra_values[] = {100, 200, 300};
    assert(array_push_back2(&arr, extra_values, extra_values + 3) == 0);
    printf("After push_back2, size: %zu\n", array_size(arr));
    for (size_t i = 0; i < array_size(arr); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Destroy the array.
    array_destroy(arr);
    return 0;
}
