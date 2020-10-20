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

/* DHCP protocol definitions and configuration lookup tests.
 *
 * Because dnsmasq uses die() function to report failures,
 * unsupported options cannot be tested now. */

#include "test.h"
#include <stdlib.h>

static void daemon_allocate()
{
#ifdef HAVE_DNSSEC
  /* copy from main() function */
  if (option_bool(OPT_DNSSEC_VALID))
    {
      /* Note that both /000 and '.' are allowed within labels. These get
	 represented in presentation format using NAME_ESCAPE as an escape
	 character when in DNSSEC mode.
	 In theory, if all the characters in a name were /000 or
	 '.' or NAME_ESCAPE then all would have to be escaped, so the
	 presentation format would be twice as long as the spec.

	 daemon->namebuff was previously allocated by the option-reading
	 code before we knew if we're in DNSSEC mode, so reallocate here. */
      free(daemon->namebuff);
      daemon->namebuff = safe_malloc(MAXDNAME * 2);
      daemon->keyname = safe_malloc(MAXDNAME * 2);
      daemon->workspacename = safe_malloc(MAXDNAME * 2);
      /* one char flag per possible RR in answer section (may get extended). */
      daemon->rr_status_sz = 64;
      daemon->rr_status = safe_malloc(sizeof(*daemon->rr_status) * daemon->rr_status_sz);
    }
#endif
  cache_init();
}

static void daemon_free()
{
#ifdef HAVE_DNSSEC
  if (option_bool(OPT_DNSSEC_VALID))
    {
      free(daemon->namebuff);
      daemon->namebuff = safe_malloc(MAXDNAME);
      free(daemon->keyname);
      free(daemon->workspacename);
      /* one char flag per possible RR in answer section (may get extended). */
      daemon->rr_status_sz = 0;
      free(daemon->rr_status);
    }
#endif
}

#ifdef HAVE_DNSSEC
static void test_dnssec_validation(void **state)
{
  char *argv[] = {
	  ARGV_START,
	  "--dnssec",
	  "--trust-anchor=.,20326,8,2,E06D44B80B8F1D39A95C0B0D7C65D08458E880409BBC683457104237C7F8EC8D",
	  "--log-queries",
  };

  /* dig +dnssec . NS reply */
  struct packet {
    struct dns_header header;
    unsigned char data[513];
  } pkt = {
    .header = {
      0x3121, 0x81, 0xa0, 0x100, 0xe00, 0x0, 0x100
    },
    .data = {
  0x0, 0x0, 0x2, 0x0, 0x1, 0x0, 0x0, 0x2, 0x0, 0x1, 0x0, 0x6, 0xa7, 0xeb, 0x0, 0x14, 0x1, 0x64, 0xc, 0x72, 0x6f, 0x6f, 0x74, 
  0x2d, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x73, 0x3, 0x6e, 0x65, 0x74, 0x0, 0x0, 0x0, 0x2, 0x0, 0x1, 0x0, 0x6, 0xa7, 0xeb, 0x0, 
  0x4, 0x1, 0x65, 0xc0, 0x1e, 0x0, 0x0, 0x2, 0x0, 0x1, 0x0, 0x6, 0xa7, 0xeb, 0x0, 0x4, 0x1, 0x66, 0xc0, 0x1e, 0x0, 0x0, 0x2, 0x0, 
  0x1, 0x0, 0x6, 0xa7, 0xeb, 0x0, 0x4, 0x1, 0x67, 0xc0, 0x1e, 0x0, 0x0, 0x2, 0x0, 0x1, 0x0, 0x6, 0xa7, 0xeb, 0x0, 0x4, 0x1, 0x68, 
  0xc0, 0x1e, 0x0, 0x0, 0x2, 0x0, 0x1, 0x0, 0x6, 0xa7, 0xeb, 0x0, 0x4, 0x1, 0x69, 0xc0, 0x1e, 0x0, 0x0, 0x2, 0x0, 0x1, 0x0, 0x6, 
  0xa7, 0xeb, 0x0, 0x4, 0x1, 0x6a, 0xc0, 0x1e, 0x0, 0x0, 0x2, 0x0, 0x1, 0x0, 0x6, 0xa7, 0xeb, 0x0, 0x4, 0x1, 0x6b, 0xc0, 0x1e, 0x0, 
  0x0, 0x2, 0x0, 0x1, 0x0, 0x6, 0xa7, 0xeb, 0x0, 0x4, 0x1, 0x6c, 0xc0, 0x1e, 0x0, 0x0, 0x2, 0x0, 0x1, 0x0, 0x6, 0xa7, 0xeb, 0x0, 0x4, 
  0x1, 0x6d, 0xc0, 0x1e, 0x0, 0x0, 0x2, 0x0, 0x1, 0x0, 0x6, 0xa7, 0xeb, 0x0, 0x4, 0x1, 0x61, 0xc0, 0x1e, 0x0, 0x0, 0x2, 0x0, 0x1, 
  0x0, 0x6, 0xa7, 0xeb, 0x0, 0x4, 0x1, 0x62, 0xc0, 0x1e, 0x0, 0x0, 0x2, 0x0, 0x1, 0x0, 0x6, 0xa7, 0xeb, 0x0, 0x4, 0x1, 0x63, 0xc0, 
  0x1e, 0x0, 0x0, 0x2e, 0x0, 0x1, 0x0, 0x6, 0xa7, 0xeb, 0x1, 0x13, 0x0, 0x2, 0x8, 0x0, 0x0, 0x7, 0xe9, 0x0, 0x5f, 0x9e, 0x40, 0xd0, 
  0x5f, 0x8d, 0xf, 0x40, 0x66, 0x4, 0x0, 0x6a, 0xc2, 0x2d, 0xda, 0x4b, 0x1d, 0x9f, 0xb, 0x93, 0xbd, 0x6, 0x12, 0xb1, 0xee, 0x48, 
  0x30, 0xd4, 0x66, 0xf, 0xbe, 0xe4, 0x3b, 0xaa, 0xa9, 0xd6, 0xb2, 0x69, 0x73, 0xee, 0x80, 0x11, 0x2b, 0x8e, 0xe6, 0x8a, 0x2d, 0x7, 
  0x4a, 0x82, 0x47, 0xa3, 0x99, 0xb9, 0x61, 0x51, 0x63, 0x80, 0x44, 0xee, 0x48, 0xf0, 0x21, 0x45, 0xed, 0x43, 0x7d, 0x72, 0x15, 0x7d, 
  0x2, 0x75, 0xad, 0x19, 0x87, 0x22, 0xfd, 0x75, 0x61, 0xcb, 0xd0, 0x8a, 0x53, 0x53, 0x89, 0xb6, 0x48, 0xbe, 0x7f, 0x51, 0xbd, 0xcd, 
  0x9f, 0xb0, 0xd0, 0x13, 0x14, 0xe6, 0x13, 0x6a, 0x88, 0x4b, 0x51, 0x34, 0xb, 0x99, 0xe9, 0x40, 0xc0, 0x65, 0xc5, 0xc5, 0x8a, 0x2f, 
  0xc6, 0xc7, 0x70, 0x2a, 0xb8, 0x6c, 0xb3, 0x88, 0x5c, 0xd3, 0x0, 0xe0, 0xb9, 0x6c, 0xc9, 0x77, 0x2, 0x27, 0xd0, 0x66, 0x12, 0x4d, 
  0xa6, 0x85, 0xea, 0x80, 0xfb, 0x54, 0xde, 0x6b, 0x39, 0x33, 0x90, 0x1c, 0xb0, 0x6d, 0xb4, 0xe6, 0xe9, 0x1, 0x41, 0x89, 0xa4, 0x9a, 
  0x82, 0x25, 0xb8, 0xbf, 0x1c, 0xd0, 0x15, 0x61, 0x3b, 0xc, 0x87, 0xbd, 0x2c, 0xa5, 0xb2, 0x72, 0x44, 0x77, 0x28, 0xdc, 0xbb, 0x3d, 
  0xfc, 0x90, 0xcf, 0x2f, 0x80, 0x48, 0x4d, 0xa1, 0x35, 0xd9, 0x65, 0xea, 0xdc, 0xa8, 0x96, 0x8, 0x52, 0x24, 0x3e, 0x8a, 0xa6, 0x44, 
  0x5b, 0xb2, 0xe5, 0x78, 0x3f, 0x77, 0x27, 0x39, 0xb0, 0xf9, 0x83, 0xd0, 0x32, 0xf0, 0x4c, 0x36, 0x58, 0x40, 0x12, 0x3b, 0x52, 0xb6, 
  0xe9, 0xc, 0xe, 0xe5, 0x27, 0xad, 0x4b, 0xc5, 0xaf, 0x84, 0xde, 0xa1, 0x53, 0xbc, 0x17, 0x1, 0x59, 0x8f, 0x11, 0xad, 0xed, 0x5a, 
  0x56, 0x4d, 0xef, 0x3, 0x6c, 0x5c, 0x5a, 0xd9, 0x6f, 0xe0, 0x2e, 0x9, 0xf, 0x37, 0xaf, 0x19, 0xa2, 0xa8, 0xd6, 0x5f, 0xa7, 0x0, 
  0x0, 0x29, 0x4, 0xd0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0
    },
  };
  int r;
  time_t now = 1603186099;
  char name[MAXDNAME*2] = "";
  char keyname[MAXDNAME*2] = "";
  int class = 0x482988;
  int check_unsigned = 1;

  (void) state;

  testcore_main(ARRAY_SIZE(argv), argv);

  daemon_allocate();

  r = dnssec_validate_reply (now, &pkt.header, sizeof(pkt), name, keyname, 
			     &class, check_unsigned, NULL, NULL, NULL);
#if 0
  /* TODO: fill the cache */
  assert_int_equal(r, STAT_SECURE);
#else
  assert_int_equal(r, STAT_NEED_DS);
#endif

  daemon_free();
}
#endif

int main(int argc, char *argv[])
{
  const struct CMUnitTest tests[] = {
#ifdef HAVE_DNSSEC
    cmocka_unit_test(test_dnssec_validation),
#endif
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
