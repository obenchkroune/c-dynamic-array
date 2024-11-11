#include "greatest.h"
#include "test_utils.h"

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(string_suite);
    RUN_SUITE(dynamic_array_suite);
    GREATEST_MAIN_END();
}
