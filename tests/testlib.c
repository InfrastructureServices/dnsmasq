// vim: sts=2
/* dnsmasq is Copyright (c) 2000-2020 Simon Kelley

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

/*
 * Generic required calls, faking original functions without functional body.
 */
#include "dnsmasq.h"

/* inotify.c */
#ifdef HAVE_INOTIFY
void set_dynamic_inotify(int flag, int total_size, struct crec **rhash, int revhashsz)
{}
#endif

/* dnsmasq.c */
void send_event(int fd, int event, int data, char *msg)
{}
void queue_event(int event)
{}
int icmp_ping(struct in_addr addr)
{
  return 0;
}
void send_alarm(time_t event, time_t now)
{}
int delay_dhcp(time_t start, int sec, int fd, uint32_t addr, unsigned short id)
{
  return 0;
}

/* ipset.c / tables.c */
int add_to_ipset(const char *setname, const union all_addr *ipaddr, int flags, int remove)
{
  return -1;
}

/* auth.c */
size_t answer_auth(struct dns_header *header, char *limit, size_t qlen, time_t now, union mysockaddr *peer_addr,
		   int local_query, int do_bit, int have_pseudoheader)
{
  return 0;
}
int in_zone(struct auth_zone *zone, char *name, char **cut)
{
  return 0;
}

/* slaac.c */
time_t periodic_slaac(time_t now, struct dhcp_lease *leases)
{
  return 0;
}

void slaac_add_addrs(struct dhcp_lease *lease, time_t now, int force)
{}
void slaac_ping_reply(struct in6_addr *sender, unsigned char *packet, char *interface, struct dhcp_lease *leases)
{}

/* helper.c */
#ifdef HAVE_SCRIPT
void queue_script(int action, struct dhcp_lease *lease, char *hostname, time_t now)
{}
void queue_arp(int action, unsigned char *mac, int maclen, int family, union all_addr *addr)
{}
#endif

void clear_cache_and_reload(time_t now)
{}
