// vim: sts=2
/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 dated June, 1991, or
   (at your option) version 3 dated 29 June, 2007.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/* Basic checks for generic options */
#include "test.h"

/* Because dnsmasq uses die() function to report failures,
 * unsupported options cannot be tested now. */

static void test_option(void **state)
{
  char *argv[] = {
	  ARGV_START,
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
