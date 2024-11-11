#include "greatest.h"
#include "test_utils.h"

TEST test_array_create(void) {
    t_array* arr = array_init(ARRAY_INITIAL_CAPACITY, sizeof(int));
    ASSERT(arr != NULL);
    ASSERT(arr->array != NULL);
    ASSERT_EQ(arr->size, 0);
    ASSERT_EQ(arr->capacity, ARRAY_INITIAL_CAPACITY);
    ASSERT_EQ(arr->element_size, sizeof(int));
    arr->destroy(arr);
    PASS();
}

TEST test_array_push(void) {
    t_array* arr = array_init(ARRAY_INITIAL_CAPACITY, sizeof(int));
    int values[] = {1, 2, 3, 4, 5};
    
    for (size_t i = 0; i < 5; i++) {
        arr->append(arr, &values[i]);
        ASSERT_EQ(arr->size, i + 1);
    }

    for (int i = 0; i < 5; i++) {
        int* val = arr->get(arr, i);
        ASSERT_EQ(*val, values[i]);
    }

    arr->destroy(arr);
    PASS();
}

TEST test_array_remove(void) {
    t_array* arr = array_init(ARRAY_INITIAL_CAPACITY, sizeof(int));
    int values[] = {1, 2, 3};
    
    for (int i = 0; i < 3; i++) {
        arr->append(arr, &values[i]);
    }

    arr->remove(arr, arr->size - 1);
    ASSERT_EQ(arr->size, 2);
    int* val = arr->get(arr, arr->size - 1);
    ASSERT_EQ(*val, 2);

    arr->destroy(arr);
    PASS();
}

TEST test_array_get(void) {
    t_array* arr = array_init(ARRAY_INITIAL_CAPACITY, sizeof(char));
    char values[] = {'a', 'b', 'c'};
    
    for (int i = 0; i < 3; i++) {
        arr->append(arr, &values[i]);
    }

    char* val = arr->get(arr, 1);
    ASSERT_EQ(*val, 'b');

    arr->destroy(arr);
    PASS();
}

TEST test_array_capacity_growth(void) {
    t_array* arr = array_init(2, sizeof(int));  // Start with small capacity
    size_t initial_capacity = arr->capacity;
    

    // Fill beyond initial capacity
    for (size_t i = 0; i < initial_capacity + 1; i++) {
        arr->append(arr, &(int){1});
    }

    ASSERT(arr->capacity > initial_capacity);
    arr->destroy(arr);
    PASS();
}

SUITE(dynamic_array_suite) {
    RUN_TEST(test_array_create);
    RUN_TEST(test_array_push);
    RUN_TEST(test_array_remove);
    RUN_TEST(test_array_get);
    RUN_TEST(test_array_capacity_growth);
}
