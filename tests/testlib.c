// vim: sts=2
#include "dnsmasq.h"

/* dhcp-common.c */
int lookup_dhcp_opt(int prot, char *name)
{
  return -1;
}

int lookup_dhcp_len(int prot, int val)
{
  return 0;
}

char *strip_hostname(char *hostname)
{
  return NULL;
}

void display_opts(void)
{}

#ifdef HAVE_DHCP6
void display_opts6(void)
{}
#endif


/* network.c */
void mark_servers(int flag)
{}
void cleanup_servers(void)
{}
int fix_fd(int fd)
{
  return 1;
}

/* inotify.c */
#ifdef HAVE_INOTIFY
void set_dynamic_inotify(int flag, int total_size, struct crec **rhash, int revhashsz)
{}
#endif

/* dnsmasq.c */
void send_event(int fd, int event, int data, char *msg)
{}
