#!/usr/bin/python
# Copyright (c) 2024 Petr Menšík <pemensik@redhat.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 dated June, 1991, or
# (at your option) version 3 dated 29 June, 2007.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#
# Small wrapper in python around swig generated dnsmasq module

import enum
import dnsmasq

def dnsmasq_make_flags(name):
   v = vars(dnsmasq)
   return enum.Flag(name, dict([(i, v[i]) for i in v if i.startswith(name+'_')]))

def dnsmasq_make_enum(name):
   v = vars(dnsmasq)
   return enum.Enum(name, dict([(i, v[i]) for i in v if i.startswith(name+'_')]))

ACTOPM  = dnsmasq_make_enum("ACTION")
OPT     = dnsmasq_make_enum("OPT")
EVENT   = dnsmasq_make_enum("EVENT")
TXT_STAT= dnsmasq_make_enum("TXT_STAT")
T       = dnsmasq_make_enum("T")

AH      = dnsmasq_make_flags("AH")
CONFIG  = dnsmasq_make_flags("CONFIG")
CONTEXT = dnsmasq_make_flags("CONTEXT")
DHOPT   = dnsmasq_make_flags("DHOPT")
DNSSEC_FAIL = dnsmasq_make_flags("DNSSEC_FAIL")
DUMP    = dnsmasq_make_flags("DUMP")
F       = dnsmasq_make_flags("F")
FREC    = dnsmasq_make_flags("FREC")
LEASE   = dnsmasq_make_flags("LEASE")
INAME   = dnsmasq_make_flags("INAME")
IFACE   = dnsmasq_make_flags("IFACE")
SERV    = dnsmasq_make_flags("SERV")

