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

#if 0
/* dhcp-range, stored in daemon->dhcp */
/*
(gdb) p *context
$23 = {
  lease_time = 3600,
  addr_epoch = 0,
  netmask = {
    s_addr = 16777215
  },
  broadcast = {
    s_addr = 4279246508
  },
  local = {
    s_addr = 17833644
  },
  router = {
    s_addr = 17833644
  },
  start = {
    s_addr = 84942508
  },
  end = {
    s_addr = 504372908
  },
  start6 = {
    __in6_u = {
      __u6_addr8 = '\000' <repeats 15 times>,
      __u6_addr16 = {0, 0, 0, 0, 0, 0, 0, 0},
      __u6_addr32 = {0, 0, 0, 0}
    }
  },
  end6 = {
    __in6_u = {
      __u6_addr8 = '\000' <repeats 15 times>,
      __u6_addr16 = {0, 0, 0, 0, 0, 0, 0, 0},
      __u6_addr32 = {0, 0, 0, 0}
    }
  },
  local6 = {
    __in6_u = {
      __u6_addr8 = '\000' <repeats 15 times>,
      __u6_addr16 = {0, 0, 0, 0, 0, 0, 0, 0},
      __u6_addr32 = {0, 0, 0, 0}
    }
  },
  prefix = 0,
  if_index = 0,
  valid = 0,
  preferred = 0,
  saved_valid = 0,
  ra_time = 0,
  ra_short_period_start = 0,
  address_lost_time = 0,
  template_interface = 0x0,
  flags = 0,
  netid = {
    net = 0x0,
    next = 0x0
  },
  filter = 0x0,
  next = 0x0,
  current = 0x0
}
*/

/* Request from dhclient over IPv4 */
/*
(gdb) p hwaddr[0]
$8 = 58 ':'
(gdb) p hwaddr[1]
$9 = 26 '\032'
(gdb) p hwaddr[2]
$10 = 162 '\242'
(gdb) p hwaddr[3]
$11 = 54 '6'
(gdb) p hwaddr[4]
$12 = 37 '%'
(gdb) p hwaddr[5]
$13 = 73 'I'
(gdb) p hwaddr[6]
$14 = 0 '\000'

#0  find_config (configs=0x0, context=context@entry=0x55f4f6004750, clid=clid@entry=0x0, clid_len=clid_len@entry=0,
    hwaddr=hwaddr@entry=0x55f4f60061cc ":\032\242\066%I", hw_len=6, hw_type=1, hostname=0x0, tags=0x7fffc9d51240)
    at dhcp-common.c:382

(gdb) p /x *(struct dhcp_packet *)dnsmasq_daemon->dhcp_packet.iov_base
$18 = {
  op = 0x2,
  htype = 0x1,
  hlen = 0x6,
  hops = 0x0,
  xid = 0x31505f32,
  secs = 0x0,
  flags = 0x0,
  ciaddr = {
    s_addr = 0x0
  },
  yiaddr = {
    s_addr = 0x0
  },
  siaddr = {
    s_addr = 0x0
  },
  giaddr = {
    s_addr = 0x0
  },
  chaddr = {0x3a, 0x1a, 0xa2, 0x36, 0x25, 0x49, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  sname = {0x0 <repeats 64 times>},
  file = {0x0 <repeats 128 times>},
  options = {0x63, 0x82, 0x53, 0x63, 0x35, 0x1, 0x3, 0x32, 0x4, 0xac, 0x1e, 0x10, 0x1d, 0x37, 0xd, 0x1, 0x1c, 0x2, 0x79, 0xf,
    0x6, 0xc, 0x28, 0x29, 0x2a, 0x1a, 0x77, 0x3, 0xff, 0x0 <repeats 283 times>}
}
*/
#endif
#if 0
  iov.iov_len = dhcp_reply(parm.current, ifr.ifr_name, iface_index, (size_t)sz,
			   now, unicast_dest, loopback, &is_inform, pxe_fd, iface_addr, recvtime);
#endif
#if 0
  struct dhcp_packet pkt_data = {
	  .op=2, .htype=1, .hlen=6, .hops=0,
	  .xid=0x31505f32,
	  .secs=0, .flags=0,
	  { INADDR_ANY },
	  { INADDR_ANY },
	  { INADDR_ANY },
	  { INADDR_ANY },
	  .chaddr = {0x3a, 0x1a, 0xa2, 0x36, 0x25, 0x49, 0x0, },
	  .sname = {0, },
	  .file =  {0, },
	  .options = { 0x63, 0x82, 0x53, 0x63, 0x35, 0x1, 0x3, 0x32, 0x4, 0xac, 0x1e, 0x10, 0x1d, 0x37, 0xd,
		  0x1, 0x1c, 0x2, 0x79, 0xf, 0x6, 0xc, 0x28, 0x29, 0x2a, 0x1a, 0x77, 0x3, 0xff, 0x0, },
  };
  unsigned char hwaddr[] = { 58, 26, 126, 54, 37, 73, 0 };
#endif

#define ZERO_OR_RETURN(expr, d) do { \
				      (d) = (expr); \
				      if ((d) != 0) \
					return (d); \
				 } while (0)

static int compare_netid(const struct dhcp_netid *f1, const struct dhcp_netid *f2)
{
  int d;
  while (f1 && f2) {
    ZERO_OR_RETURN(strcmp(f1->net, f2->net), d);
    f1 = f1->next;
    f2 = f2->next;
  }
  return ((f1 != NULL) - (f2 != NULL));
}

#if 0
static int compare_hwaddr_wild(const struct hwaddr_config *hw1, const struct hwaddr_config *hw2)
{
  int d;
  while (hw1 && hw2)
    {
      ZERO_OR_RETURN((hw1->wildcard_mask == 0) - (hw2->wildcard_mask == 0), d);
      ZERO_OR_RETURN(hw1->wildcard_mask - hw2->wildcard_mask, d);
      ZERO_OR_RETURN(hw1->hwaddr_type - hw2->hwaddr_type, d);
      ZERO_OR_RETURN(hw1->hwaddr_len - hw2->hwaddr_len, d);
      ZERO_OR_RETURN(memcmp(hw1->hwaddr, hw2->hwaddr, hw1->hwaddr_len), d);

      hw1 = hw1->next;
      hw2 = hw2->next;
  }
  return ((hw1 != NULL) - (hw2 != NULL));
}

static int compare_hwaddr_nowild(const struct hwaddr_config *hw1, const struct hwaddr_config *hw2)
{
  int d;
  while (hw1 && hw2)
    {
      ZERO_OR_RETURN((hw1->wildcard_mask == 0) - (hw2->wildcard_mask == 0), d);
      if (hw1->wildcard_mask != 0)
	return 0;
      ZERO_OR_RETURN(hw1->hwaddr_type - hw2->hwaddr_type, d);
      ZERO_OR_RETURN(hw1->hwaddr_len - hw2->hwaddr_len, d);
      ZERO_OR_RETURN(memcmp(hw1->hwaddr, hw2->hwaddr, hw1->hwaddr_len), d);

      hw1 = hw1->next;
      hw2 = hw2->next;
  }
  return ((hw1 != NULL) - (hw2 != NULL));
}
#endif

static int compare_hwaddr(const struct hwaddr_config *hw1, const struct hwaddr_config *hw2)
{
  int d;
  while (hw1 && hw2)
    {
      ZERO_OR_RETURN((hw1->wildcard_mask == 0) - (hw2->wildcard_mask == 0), d);
      ZERO_OR_RETURN(hw1->hwaddr_type - hw2->hwaddr_type, d);
      ZERO_OR_RETURN(hw1->hwaddr_len - hw2->hwaddr_len, d);
      ZERO_OR_RETURN(memcmp(hw1->hwaddr, hw2->hwaddr, hw1->hwaddr_len), d);

      hw1 = hw1->next;
      hw2 = hw2->next;
  }
  return ((hw1 != NULL) - (hw2 != NULL));
}

static int compare_dhcp_config(const struct dhcp_config *c1, const struct dhcp_config *c2)
{
  int d;

  ZERO_OR_RETURN(compare_netid(c1->filter, c2->filter), d);
  ZERO_OR_RETURN( ((c1->flags & CONFIG_CLID) != 0) - ((c2->flags & CONFIG_CLID) != 0), d);
  ZERO_OR_RETURN(c1->clid_len - c2->clid_len, d);
  if (c1->clid_len > 0)
    {
      ZERO_OR_RETURN(memcmp(c1->clid, c2->clid, c1->clid_len), d);
    }

  ZERO_OR_RETURN(compare_hwaddr(c1->hwaddr, c2->hwaddr), d);
  ZERO_OR_RETURN(((c1->flags & CONFIG_NAME) != 0) - ((c2->flags & CONFIG_NAME) != 0), d);
  if ((c1->flags & CONFIG_NAME) != 0)
    {
      ZERO_OR_RETURN(strcmp(c1->hostname, c2->hostname), d);
    }

  return 0;
}

#undef ZERO_OR_RETURN

static int compare_config_ptr(const void *c1, const void *c2)
{
  return -compare_dhcp_config(*((const struct dhcp_config **)c1),
			     *((const struct dhcp_config **)c2));
}

static size_t dhcp_config_count(const struct dhcp_config *cfg)
{
  size_t count = 0;
  for ( ; cfg; cfg = cfg->next)
    ++count;
  return count;
}

static void dhcp_config_sort_array(struct dhcp_config **configs,
			       struct dhcp_config **cfga, size_t count)
{
  struct dhcp_config *cfg = NULL;
  size_t i=0;

  for (i = 0, cfg= *configs; cfg && i < count; i++, cfg = cfg->next)
    cfga[i] = cfg;

  qsort(cfga, count, sizeof(cfga[0]), &compare_config_ptr);

  *configs = cfg = cfga[0];
  for (i=1; i<count; i++, cfg = cfg->next)
    cfg->next = cfga[i];
  cfg->next = NULL;
}

static void dhcp_config_sort(struct dhcp_config **configs)
{
  struct dhcp_config **cfga;
  size_t count = 0;

  count = dhcp_config_count(*configs);
  if (count == 0)
    return;

  cfga = safe_malloc(count*sizeof(struct dhcp_config));
  memset(cfga, 0, count*sizeof(*cfga));
  dhcp_config_sort_array(configs, cfga, count);

  free(cfga);
}

#if 0
#define CFG_TYPE(type) ,(type)
#else
/* This is a hack to check original code without config flags */
#define CFG_TYPE(type)
#endif

static void test_dhcp_ipv4(void **state)
{
  char *argv[] = {
	  ARGV_START,
	  "--dhcp-range=192.168.1.5,192.168.1.10,10",
	  "--dhcp-host=192.168.1.13,only-host",
	  "--dhcp-host=11:22:33:44:55:66,192.168.1.12,mac-host",
	  "--dhcp-host=tag:eth0,11:22:33:44:55:66,192.168.1.14,tag-host",
  };

  unsigned char *clid = NULL;
  int clid_len = 0;
  struct dhcp_context *context;
  struct dhcp_config *config = NULL;
  struct hwaddr_config defined_client = {
	6, 1, { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x0 }, 0, NULL,
  };
  struct hwaddr_config undefined_client = {
	6, 1, { 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x0 }, 0, NULL,
  };
  struct dhcp_netid eth0 = { "eth0", NULL };

  (void) state;

  testcore_main(ARRAY_SIZE(argv), argv);

  context = daemon->dhcp;

  assert_true(context);
  config = find_config(daemon->dhcp_conf, context, clid, clid_len,
		       defined_client.hwaddr, defined_client.hwaddr_len,
		       defined_client.hwaddr_type, NULL, &eth0 CFG_TYPE(CONFIG_ADDR));
  assert_true(config);
  assert_string_equal(config->hostname, "tag-host");
  config = find_config(daemon->dhcp_conf, context, clid, clid_len,
		       defined_client.hwaddr, defined_client.hwaddr_len,
		       defined_client.hwaddr_type, NULL, NULL CFG_TYPE(CONFIG_ADDR));
  assert_true(config);
  assert_string_equal(config->hostname, "mac-host");
  config = find_config(daemon->dhcp_conf, context, clid, clid_len,
		       undefined_client.hwaddr, undefined_client.hwaddr_len,
		       undefined_client.hwaddr_type, NULL, NULL CFG_TYPE(CONFIG_ADDR));
  assert_false(config);
  config = find_config(daemon->dhcp_conf, context, clid, clid_len,
		       undefined_client.hwaddr, undefined_client.hwaddr_len,
		       undefined_client.hwaddr_type, "only-host", NULL CFG_TYPE(CONFIG_ADDR));
  assert_true(config);
  assert_string_equal(config->hostname, "only-host");
  assert_false(config->hwaddr);
}

static void test_dhcp_ipv6(void **state)
{
  char *argv[] = {
	  ARGV_START,
	  "--dhcp-range=fd27:807d:181c:fb81::d000,fd27:807d:181c:fb81::dfff,64,10",
	  "--dhcp-host=11:22:33:44:55:66,[fd27:807d:181c:fb81::d12],mac-host",
	  "--dhcp-host=tag:eth0,11:22:33:44:55:66,[fd27:807d:181c:fb81::d12],tag-host",
	  "--dhcp-host=[fd27:807d:181c:fb81::d13],only-host",
  };

  unsigned char *clid = NULL;
  int clid_len = 0;
  struct dhcp_context *context;
  struct dhcp_config *config = NULL;
  struct hwaddr_config defined_client = {
	6, 1, { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x0 }, 0, NULL,
  };
  struct hwaddr_config undefined_client = {
	6, 1, { 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x0 }, 0, NULL,
  };
  struct dhcp_netid eth0 = { "eth0", NULL };

  testcore_main(ARRAY_SIZE(argv), argv);

  context = daemon->dhcp6;

  assert_true(context);
  config = find_config(daemon->dhcp_conf, context, clid, clid_len,
		       defined_client.hwaddr, defined_client.hwaddr_len,
		       defined_client.hwaddr_type, NULL, &eth0 CFG_TYPE(CONFIG_ADDR));
  assert_true(config);
  assert_string_equal(config->hostname, "tag-host");
  config = find_config(daemon->dhcp_conf, context, clid, clid_len,
		       defined_client.hwaddr, defined_client.hwaddr_len,
		       defined_client.hwaddr_type, NULL, NULL CFG_TYPE(CONFIG_ADDR));
  assert_true(config);
  assert_string_equal(config->hostname, "mac-host");
  config = find_config(daemon->dhcp_conf, context, clid, clid_len,
		       undefined_client.hwaddr, undefined_client.hwaddr_len,
		       undefined_client.hwaddr_type, NULL, NULL CFG_TYPE(CONFIG_ADDR));
  assert_false(config);
  config = find_config(daemon->dhcp_conf, context, clid, clid_len,
		       undefined_client.hwaddr, undefined_client.hwaddr_len,
		       undefined_client.hwaddr_type, "only-host", NULL CFG_TYPE(CONFIG_ADDR));
  assert_true(config);
  assert_string_equal(config->hostname, "only-host");
  assert_false(config->hwaddr);
}

static void test_dhcp_mixed(void **state)
{
  char *argv[] = {
	  ARGV_START,
	  "--dhcp-range=192.168.1.5,192.168.1.10,10",
	  "--dhcp-host=11:22:33:44:55:66,192.168.1.12,mac-host4",
	  "--dhcp-host=192.168.1.13,only-host",
	  "--dhcp-range=fd27:807d:181c:fb81::d000,fd27:807d:181c:fb81::dfff,64,10",
	  "--dhcp-host=11:22:33:44:55:66,[fd27:807d:181c:fb81::d12],mac-host6",
	  "--dhcp-host=tag:eth0,11:22:33:44:55:66,192.168.1.14,[fd27:807d:181c:fb81::d12],tag-host",
	  "--dhcp-host=[fd27:807d:181c:fb81::d13],only-host",
	  "--dhcp-host=tag:eth0, 66:55:44:33:22:11, [fd27:807d:181c:fb81::d12], alt-host",
	  "--dhcp-host=de:ad:*:*:be:ef, [fd27:807d:181c:fb81::d15], wildmac-host",
  };
  unsigned char *clid = NULL;
  int clid_len = 0;
  struct dhcp_config *config = NULL;
  struct hwaddr_config defined_client = {
	6, 1, { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x0 }, 0, NULL,
  };
  struct hwaddr_config undefined_client = {
	6, 1, { 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x0 }, 0, NULL,
  };
  struct hwaddr_config alt = {
	6, 1, { 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x0 }, 0, NULL,
  };
  struct hwaddr_config wildmac = {
	6, 1, { 0xde, 0xad, 0x44, 0x33, 0xbe, 0xef, 0x0 }, 0, NULL,
  };
  struct dhcp_netid eth0 = { "eth0", NULL };

  testcore_main(ARRAY_SIZE(argv), argv);

  assert_true(daemon->dhcp);
  assert_true(daemon->dhcp6);

  dhcp_config_sort(&daemon->dhcp_conf);

  config = find_config(daemon->dhcp_conf, daemon->dhcp, clid, clid_len,
		       defined_client.hwaddr, defined_client.hwaddr_len,
		       defined_client.hwaddr_type, NULL, NULL CFG_TYPE(CONFIG_ADDR));
  assert_true(config);
  assert_string_equal(config->hostname, "mac-host4");
  config = find_config(daemon->dhcp_conf, daemon->dhcp6, clid, clid_len,
		       defined_client.hwaddr, defined_client.hwaddr_len,
		       defined_client.hwaddr_type, NULL, NULL CFG_TYPE(CONFIG_ADDR6));
  assert_true(config);
  assert_string_equal(config->hostname, "mac-host6");
  config = find_config(daemon->dhcp_conf, daemon->dhcp, clid, clid_len,
		       undefined_client.hwaddr, undefined_client.hwaddr_len,
		       undefined_client.hwaddr_type, NULL, NULL CFG_TYPE(CONFIG_ADDR));
  assert_false(config);
  config = find_config(daemon->dhcp_conf, daemon->dhcp6, clid, clid_len,
		       undefined_client.hwaddr, undefined_client.hwaddr_len,
		       undefined_client.hwaddr_type, NULL, NULL CFG_TYPE(CONFIG_ADDR6));
  assert_false(config);
  config = find_config(daemon->dhcp_conf, daemon->dhcp, clid, clid_len,
		       undefined_client.hwaddr, undefined_client.hwaddr_len,
		       undefined_client.hwaddr_type, "only-host", NULL CFG_TYPE(CONFIG_ADDR));
  assert_true(config);
  assert_string_equal(config->hostname, "only-host");
  assert_false(config->hwaddr);
  config = find_config(daemon->dhcp_conf, daemon->dhcp6, clid, clid_len,
		       undefined_client.hwaddr, undefined_client.hwaddr_len,
		       undefined_client.hwaddr_type, "only-host", NULL CFG_TYPE(CONFIG_ADDR6));
  assert_true(config);
  assert_string_equal(config->hostname, "only-host");
  assert_false(config->hwaddr);

  config = find_config(daemon->dhcp_conf, daemon->dhcp, clid, clid_len,
		       undefined_client.hwaddr, undefined_client.hwaddr_len,
		       undefined_client.hwaddr_type, "tag-host", &eth0 CFG_TYPE(CONFIG_ADDR));
  assert_true(config);
  assert_string_equal(config->hostname, "tag-host");
  config = find_config(daemon->dhcp_conf, daemon->dhcp6, clid, clid_len,
		       undefined_client.hwaddr, undefined_client.hwaddr_len,
		       undefined_client.hwaddr_type, "tag-host", &eth0 CFG_TYPE(CONFIG_ADDR6));
  assert_true(config);
  assert_string_equal(config->hostname, "tag-host");

  /* Intentionally search wrong address type */
  config = find_config(daemon->dhcp_conf, daemon->dhcp, clid, clid_len,
		       alt.hwaddr, alt.hwaddr_len,
		       alt.hwaddr_type, NULL, &eth0 CFG_TYPE(CONFIG_ADDR));
  assert_null(config);
  config = find_config(daemon->dhcp_conf, daemon->dhcp6, clid, clid_len,
		       alt.hwaddr, alt.hwaddr_len,
		       alt.hwaddr_type, NULL, &eth0 CFG_TYPE(CONFIG_ADDR));
  assert_non_null(config);
  assert_string_equal(config->hostname, "alt-host");

  config = find_config(daemon->dhcp_conf, daemon->dhcp6, clid, clid_len,
		       wildmac.hwaddr, wildmac.hwaddr_len,
		       wildmac.hwaddr_type, NULL, NULL CFG_TYPE(CONFIG_ADDR6));
  assert_non_null(config);
  assert_string_equal(config->hostname, "wildmac-host");
}

static char **argv_test_hosts(unsigned int hosts_count, int *done_count)
{
  char *argv_start[] = { ARGV_START, };
  size_t start_items = ARRAY_SIZE(argv_start);
  unsigned int i;
  char template[128];
  char **argv;
  unsigned int hi, lo;

  argv= safe_malloc(sizeof(argv_start) + sizeof(char *)*hosts_count+1);
  memcpy(argv,argv_start, sizeof(argv_start));

  for (i=0; i<hosts_count; i++) {
    hi = i/255;
    lo = i%255;
    snprintf(template, sizeof(template),
      "--dhcp-host=11:22:33:44:%02x:%02x,192.168.%d.%d,only-host%03d",
      hi, lo, hi, lo, i);
    argv[start_items+i] = strdup(template);
  }

  argv[start_items+i] = NULL;
  if (done_count)
    *done_count = start_items+i;
  return argv;
}

static void test_dhcp_speedtest(void **state)
{
  size_t hosts_count = 200;
  size_t repeats = 1000;
  size_t host, repeat;
  char **argv;
  int argc;
  struct hwaddr_config conf_template = {
	6, 1, { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x0 }, 0, NULL,
  };
  struct dhcp_config *config;

  if (getenv("SPEEDTEST_HOSTS"))
    {
      hosts_count = strtoul(getenv("SPEEDTEST_HOSTS"), NULL, 10);
    }
  if (getenv("SPEEDTEST_REPEATS"))
    {
      repeats = strtoul(getenv("SPEEDTEST_REPEATS"), NULL, 10);
    }
  argv = argv_test_hosts(hosts_count, &argc);
  testcore_main(argc, argv);

  for (repeat=0; repeat<repeats; repeat++) {
    for (host=0; host<hosts_count; host++) {
      conf_template.hwaddr[4] = (unsigned char) (host/255);
      conf_template.hwaddr[5] = (unsigned char) (host%255);

      config = find_config(daemon->dhcp_conf, daemon->dhcp, NULL, 0,
			  conf_template.hwaddr, conf_template.hwaddr_len,
			  conf_template.hwaddr_type, NULL, NULL CFG_TYPE(CONFIG_ADDR));
      assert_non_null(config);
    }
  }
}

int main(int argc, char *argv[])
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_dhcp_ipv4),
    cmocka_unit_test(test_dhcp_ipv6),
    cmocka_unit_test(test_dhcp_mixed),
    cmocka_unit_test(test_dhcp_speedtest),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
