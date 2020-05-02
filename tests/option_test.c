#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <cmocka.h>

void read_opts(int argc, char **argv, char *compile_opts);

static void test_option(void **state)
{
  (void) state;
}

int main(int argc, char *argv[])
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_option),
  };
  
  return cmocka_run_group_tests(tests, NULL, NULL);
}
