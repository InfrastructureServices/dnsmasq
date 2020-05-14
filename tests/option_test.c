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

/** Test parsing hexadecimal mac addresses and wildcard compare. */
static void test_hex(void **status)
{
  char hex1[] = "7-11:22:33:44:55:66";
  char invalid2[] = "hello";
  char hex3[] = "11:22:*";
  char hex4[] = "11:*:33:*:55:*";
  unsigned char data1[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 };
  unsigned char out[16];
  int r;
  unsigned int mask=0;
  int type=0;

  (void)status;

  memset(out, 0, sizeof(out));
  r = parse_hex(hex1, out, sizeof(out), &mask, &type);
  assert_int_equal(r, 6);
  assert_memory_equal(data1, out, sizeof(data1));
  assert_int_equal(mask, 0);
  assert_int_equal(type, 7);

  memset(out, 0, sizeof(out));
  r = parse_hex(invalid2, out, sizeof(out), NULL, NULL);
  assert_int_equal(r, -1);

  memset(out, 0, sizeof(out));
  r = parse_hex(hex3, out, sizeof(out), &mask, &type);
  assert_int_equal(r, 3);
  assert_memory_equal(data1, out, 2);
  assert_int_equal(mask, 0x01);
  assert_int_equal(type, 0);
  r = memcmp_masked(out, data1, r, mask);
  assert_int_equal(r, 3);

  memset(out, 0, sizeof(out));
  r = parse_hex(hex4, out, sizeof(out), &mask, &type);
  assert_int_equal(r, 6);
  assert_int_equal(mask, 0x15);
  assert_int_equal(type, 0);
  r = memcmp_masked(out, data1, r, mask);
  assert_int_equal(r, 4);

  assert_string_equal("11:22:33:44:55:66", print_mac((char *)out, data1, sizeof(data1)));
}

int main(int argc, char *argv[])
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_option),
    cmocka_unit_test(test_hex),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
