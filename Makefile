# dnsmasq is Copyright (c) 2000-2021 Simon Kelley
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; version 2 dated June, 1991, or
#  (at your option) version 3 dated 29 June, 2007.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#    
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

# NOTE: Building the i18n targets requires GNU-make 


# Variables you may well want to override.

PREFIX        = /usr/local
BINDIR        = $(PREFIX)/sbin
MANDIR        = $(PREFIX)/share/man
LOCALEDIR     = $(PREFIX)/share/locale
BUILDDIR      = $(SRC)
DESTDIR       = 
CFLAGS        = -Wall -W -O2
LDFLAGS       = 
COPTS         = 
RPM_OPT_FLAGS = 
LIBS          = 

#################################################################

# pmake way. (NB no spaces to keep gmake 3.82 happy)
top!=pwd
# GNU make way.
top?=$(CURDIR)

INSTALL    = install
MSGMERGE   = msgmerge
MSGFMT     = msgfmt
XGETTEXT   = xgettext

include $(top)/Makefile.config

objs = cache.o rfc1035.o util.o option.o forward.o network.o \
       dnsmasq.o dhcp.o lease.o rfc2131.o netlink.o dbus.o bpf.o \
       helper.o tftp.o log.o conntrack.o dhcp6.o rfc3315.o \
       dhcp-common.o outpacket.o radv.o slaac.o auth.o ipset.o \
       domain.o dnssec.o blockdata.o tables.o loop.o inotify.o \
       poll.o rrfilter.o edns0.o arp.o crypto.o dump.o ubus.o \
       metrics.o hash_questions.o

hdrs = dnsmasq.h config.h dhcp-protocol.h dhcp6-protocol.h \
       dns-protocol.h radv-protocol.h ip6addr.h metrics.h

all : $(BUILDDIR)
	@cd $(BUILDDIR) && $(MAKE) \
 top="$(top)" \
 build_cflags="$(all_cflags)" \
 build_libs="$(all_libs)"  \
 -f $(top)/Makefile dnsmasq 

mostly_clean :
	rm -f $(BUILDDIR)/*.mo $(BUILDDIR)/*.pot 
	rm -f $(BUILDDIR)/.copts_* $(BUILDDIR)/*.o $(BUILDDIR)/dnsmasq.a $(BUILDDIR)/dnsmasq

clean : mostly_clean
	rm -f $(BUILDDIR)/dnsmasq_baseline
	rm -f core */core
	rm -f *~ contrib/*/*~ */*~

check: all
	$(MAKE) -C tests check

install : all install-common

install-common :
	$(INSTALL) -d $(DESTDIR)$(BINDIR)
	$(INSTALL) -d $(DESTDIR)$(MANDIR)/man8
	$(INSTALL) -m 644 $(MAN)/dnsmasq.8 $(DESTDIR)$(MANDIR)/man8 
	$(INSTALL) -m 755 $(BUILDDIR)/dnsmasq $(DESTDIR)$(BINDIR)

all-i18n : $(BUILDDIR)
	@cd $(BUILDDIR) && $(MAKE) \
 top="$(top)" \
 i18n=-DLOCALEDIR=\'\"$(LOCALEDIR)\"\' \
 build_cflags="$(all_cflags)" \
 build_libs="$(all_libs)"  \
 -f $(top)/Makefile dnsmasq
	for f in `cd $(PO); echo *.po`; do \
		cd $(top) && cd $(BUILDDIR) && $(MAKE) top="$(top)" -f $(top)/Makefile $${f%.po}.mo; \
	done

install-i18n : all-i18n install-common
	cd $(BUILDDIR); $(top)/bld/install-mo $(DESTDIR)$(LOCALEDIR) $(INSTALL)
	cd $(MAN); ../bld/install-man $(DESTDIR)$(MANDIR) $(INSTALL)

merge : 
	@cd $(BUILDDIR) && $(MAKE) top="$(top)" -f $(top)/Makefile dnsmasq.pot
	for f in `cd $(PO); echo *.po`; do \
		echo -n msgmerge $(PO)/$$f && $(MSGMERGE) --no-wrap -U $(PO)/$$f $(BUILDDIR)/dnsmasq.pot; \
	done

# Canonicalise .po file.
%.po : 
	@cd $(BUILDDIR) && $(MAKE) -f $(top)/Makefile dnsmasq.pot
	mv $(PO)/$*.po $(PO)/$*.po.orig && $(MSGMERGE) --no-wrap $(PO)/$*.po.orig $(BUILDDIR)/dnsmasq.pot >$(PO)/$*.po; 

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# rules below are helpers for size tracking

baseline : mostly_clean all
	@cd $(BUILDDIR) && \
	   mv dnsmasq dnsmasq_baseline

bloatcheck : $(BUILDDIR)/dnsmasq_baseline mostly_clean all
	@cd $(BUILDDIR) && \
           $(top)/bld/bloat-o-meter dnsmasq_baseline dnsmasq; \
           size dnsmasq_baseline dnsmasq

# rules below are targets in recursive makes with cwd=$(BUILDDIR)

$(copts_conf): $(hdrs)
	@rm -f *.o .copts_*
	@echo "$(COPTS)" > $@

$(objs:.o=.c) $(hdrs):
	ln -s $(SRC)/$@ .

$(objs): $(copts_conf) $(hdrs)

.c.o:
	$(CC) $(CFLAGS) $(COPTS) $(i18n) $(build_cflags) $(RPM_OPT_FLAGS) -c $<	

dnsmasq : $(objs)
	@echo "COPTS: $(COPTS) file:$(copts_conf)"
	$(CC) $(LDFLAGS) -o $@ $(objs) $(build_libs) $(LIBS) 

dnsmasq.pot : $(objs:.o=.c) $(hdrs)
	$(XGETTEXT) -d dnsmasq --foreign-user --omit-header --keyword=_ -o $@ -i $(objs:.o=.c)

%.mo : $(top)/$(PO)/%.po dnsmasq.pot
	$(MSGMERGE) -o - $(top)/$(PO)/$*.po dnsmasq.pot | $(MSGFMT) -o $*.mo -

.PHONY : all clean mostly_clean install install-common all-i18n install-i18n merge baseline bloatcheck
