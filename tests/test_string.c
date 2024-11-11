#include "test_utils.h"

#include "greatest.h"
#include <stdio.h>
#include <string.h>
#include "../dynamic_string.h"
#include "../dynamic_array.h"

TEST test_string_create(void) {
    t_string* str = string_init("Hello");
    ASSERT(str != NULL);
    ASSERT(str->data != NULL);
    ASSERT_EQ(str->length, 5);
    ASSERT_STR_EQ(str->data, "Hello");
    str->destroy(str);

    // Test empty string
    str = string_init("");
    ASSERT(str != NULL);
    ASSERT(str->data != NULL);
    ASSERT_EQ(str->length, 0);
    str->destroy(str);

    PASS();
}

TEST test_string_copy(void) {
    t_string* str1 = string_init("Test");
    t_string* str2 = str1->copy(str1);
    
    ASSERT(str2 != NULL);
    ASSERT(str2 != str1);
    ASSERT(str2->data != str1->data);
    ASSERT_EQ(str2->length, str1->length);
    ASSERT_STR_EQ(str2->data, str1->data);

    str1->destroy(str1);
    str2->destroy(str2);
    PASS();
}

TEST test_string_concat(void) {
    t_string* str1 = string_init("Hello ");
    t_string* str2 = string_init("World");
    t_string* result = str1->concat(str1, str2);

    ASSERT(result != NULL);
    ASSERT_EQ(result->length, str1->length + str2->length);
    ASSERT_STR_EQ(result->data, "Hello World");

    str1->destroy(str1);
    str2->destroy(str2);
    result->destroy(result);
    PASS();
}

TEST test_string_length(void) {
    t_string* str = string_init("Test String");
    ASSERT_EQ(str->length, 11);
    
    str->destroy(str);
    PASS();
}

TEST test_string_compare(void) {
    t_string* str1 = string_init("Hello");
    t_string* str2 = string_init("Hello");
    t_string* str3 = string_init("World");

    ASSERT_EQ(str1->compare(str1, str2), 0);
    ASSERT(str1->compare(str1, str3) < 0);
    ASSERT(str3->compare(str3, str1) > 0);

    str1->destroy(str1);
    str2->destroy(str2);
    str3->destroy(str3);
    PASS();
}

TEST test_string_substring(void) {
    t_string* str = string_init("Hello World");
    t_string* sub = str->substring(str, 6, 5);

    ASSERT(sub != NULL);
    ASSERT_EQ(sub->length, 5);
    ASSERT_STR_EQ(sub->data, "World");

    str->destroy(str);
    sub->destroy(sub);
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
