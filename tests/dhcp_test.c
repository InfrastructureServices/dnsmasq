// vim: sts=2
#include "test.h"

/* Because dnsmasq uses die() function to report failures,
 * unsupported options cannot be tested now. */

static void test_dhcp_simple(void **state)
{
  char *argv[] = {
	  "--dhcp-range=192.168.1.5,192.168.1.10,10",
	  "--dhcp-host=11:22:33:44:55:66,192.168.1.12,mac-host",
	  "--dhcp-host=192.168.1.13,only-host",
  };

  unsigned char *clid = NULL;
  int clid_len = 0;
  struct dhcp_context *context = daemon->dhcp;
  unsigned char hwaddr[] = { 58, 26, 126, 54, 37, 73, 0 };
#if 0
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

(gdb) p *(struct dhcp_packet *)dnsmasq_daemon->dhcp_packet.iov_base
$16 = {op = 2 '\002', htype = 1 '\001', hlen = 6 '\006', hops = 0 '\000', xid = 827350834, secs = 0, flags = 0, ciaddr = {
    s_addr = 0}, yiaddr = {s_addr = 0}, siaddr = {s_addr = 0}, giaddr = {s_addr = 0}, 
  chaddr = ":\032\242\066%I\000\000\000\000\000\000\000\000\000", sname = '\000' <repeats 63 times>, 
  file = '\000' <repeats 127 times>, 
  options = "c\202Sc5\001\003\062\004\254\036\020\035\067\r\001\034\002y\017\006\f()*\032w\003\377", '\000' <repeats 282 times>}

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
#endif
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
  struct dhcp_packet *mess = &pkt_data;
  struct dhcp_config *config = NULL;

#if 0
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

#endif

  (void) state;
  (void) hwaddr;

  testcore_main(ARRAY_SIZE(argv), argv);

#if 0
  iov.iov_len = dhcp_reply(parm.current, ifr.ifr_name, iface_index, (size_t)sz, 
			   now, unicast_dest, loopback, &is_inform, pxe_fd, iface_addr, recvtime);
#endif
  config = find_config(daemon->dhcp_conf, context, clid, clid_len, 
		       mess->chaddr, mess->hlen, mess->htype, NULL, NULL, CONFIG_ADDR);

  assert_true(config);
}

int main(int argc, char *argv[])
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_dhcp_simple),
  };
  
  return cmocka_run_group_tests(tests, NULL, NULL);
}
