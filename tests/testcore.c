// vim: sts=2
#include "test.h"
#include <unistd.h>

struct daemon *daemon = NULL;

/* basic initialization taken from dnsmasq.c */
void testcore_main(int argc, char **argv)
{
  rand_init();

  if (daemon)
    free(daemon);
  optind=1;
  read_opts(argc, argv, "unittest");

#ifdef HAVE_LINUX_NETWORK
  daemon->kernel_version = kernel_version();
#endif

  if (daemon->edns_pktsz < PACKETSZ)
    daemon->edns_pktsz = PACKETSZ;

  /* Min buffer size: we check after adding each record, so there must be
     memory for the largest packet, and the largest record so the
     min for DNS is PACKETSZ+MAXDNAME+RRFIXEDSZ which is < 1000.
     This might be increased is EDNS packet size if greater than the minimum. */
  daemon->packet_buff_sz = daemon->edns_pktsz + MAXDNAME + RRFIXEDSZ;
  daemon->packet = safe_malloc(daemon->packet_buff_sz);

  daemon->addrbuff = safe_malloc(ADDRSTRLEN);
  if (option_bool(OPT_EXTRALOG))
    daemon->addrbuff2 = safe_malloc(ADDRSTRLEN);
  daemon->pipe_to_parent = -1;

}
