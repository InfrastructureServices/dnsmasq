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
