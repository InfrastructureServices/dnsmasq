// vim: sts=2
#include "test.h"

/* Because dnsmasq uses die() function to report failures,
 * unsupported options cannot be tested now. */

static void test_option(void **state)
{
  char *argv[] = {
	  "--test",
	  "--user=dnsmasq",
	  "--group=dnsmasq",
	  "--domain=test",
	  "--log-queries",
  };
  (void) state;

  testcore_main(ARRAY_SIZE(argv), argv);
  assert_string_equal(daemon->username, "dnsmasq");
  assert_string_equal(daemon->groupname, "dnsmasq");
  assert_true(option_bool(OPT_LOG));
  assert_false(option_bool(OPT_EXTRALOG));
}

int main(int argc, char *argv[])
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_option),
  };
  
  return cmocka_run_group_tests(tests, NULL, NULL);
}
