#include "test_utils.h"

#include "greatest.h"
#include <stdio.h>
#include <string.h>
#include "../dynamic_string.h"
#include "../dynamic_array.h"

TEST test_string_create(void) {
    t_string* str = string_create("Hello");
    ASSERT(str != NULL);
    ASSERT(str->data != NULL);
    ASSERT_EQ(str->length, 5);
    ASSERT_STR_EQ(str->data, "Hello");
    string_destroy(str);

    // Test empty string
    str = string_create("");
    ASSERT(str != NULL);
    ASSERT(str->data != NULL);
    ASSERT_EQ(str->length, 0);
    string_destroy(str);

    PASS();
}

TEST test_string_copy(void) {
    t_string* str1 = string_create("Test");
    t_string* str2 = string_copy(str1);
    
    ASSERT(str2 != NULL);
    ASSERT(str2 != str1);
    ASSERT(str2->data != str1->data);
    ASSERT_EQ(str2->length, str1->length);
    ASSERT_STR_EQ(str2->data, str1->data);

    string_destroy(str1);
    string_destroy(str2);
    PASS();
}

TEST test_string_concat(void) {
    t_string* str1 = string_create("Hello ");
    t_string* str2 = string_create("World");
    t_string* result = string_concat(str1, str2);

    ASSERT(result != NULL);
    ASSERT_EQ(result->length, str1->length + str2->length);
    ASSERT_STR_EQ(result->data, "Hello World");

    string_destroy(str1);
    string_destroy(str2);
    string_destroy(result);
    PASS();
}

TEST test_string_length(void) {
    t_string* str = string_create("Test String");
    ASSERT_EQ(string_length(str), 11);
    
    string_destroy(str);
    PASS();
}

TEST test_string_compare(void) {
    t_string* str1 = string_create("Hello");
    t_string* str2 = string_create("Hello");
    t_string* str3 = string_create("World");

    ASSERT_EQ(string_compare(str1, str2), 0);
    ASSERT(string_compare(str1, str3) < 0);
    ASSERT(string_compare(str3, str1) > 0);

    string_destroy(str1);
    string_destroy(str2);
    string_destroy(str3);
    PASS();
}

TEST test_string_substring(void) {
    t_string* str = string_create("Hello World");
    t_string* sub = string_substring(str, 6, 5);

    ASSERT(sub != NULL);
    ASSERT_EQ(sub->length, 5);
    ASSERT_STR_EQ(sub->data, "World");

    string_destroy(str);
    string_destroy(sub);
    PASS();
}

SUITE(string_suite) {
    RUN_TEST(test_string_create);
    RUN_TEST(test_string_copy);
    RUN_TEST(test_string_concat);
    RUN_TEST(test_string_length);
    RUN_TEST(test_string_compare);
    RUN_TEST(test_string_substring);
}
