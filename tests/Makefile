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

# Do not optimize too much. dnsmasq object files are optimized already
# but tests need easier debugging by default
CFLAGS=-O0 -Wall -ggdb
SRC=../src
CPPFLAGS=-I$(SRC)
LIBS=-lcmocka

DNSMASQ_OBJS=$(SRC)/option.o $(SRC)/log.o $(SRC)/util.o $(SRC)/poll.o \
		  $(SRC)/cache.o $(SRC)/network.o $(SRC)/netlink.o $(SRC)/dhcp-common.o \
		  $(SRC)/dhcp.o $(SRC)/dhcp6.o $(SRC)/rfc2131.o $(SRC)/rfc3315.o \
		  $(SRC)/rfc1035.o $(SRC)/forward.o $(SRC)/loop.o $(SRC)/lease.o \
		  $(SRC)/domain.o $(SRC)/radv.o $(SRC)/outpacket.o $(SRC)/arp.o $(SRC)/blockdata.o \
		  $(SRC)/edns0.o $(SRC)/dump.o
TESTCORE=testcore.o testlib.o
TESTCORE_SRCS=test.h testcore.c testlib.c

TEST_OBJS=option_test.o dhcp_test.o
TEST_SRCS=option_test.c dhcp_test.c
TESTS=option_test dhcp_test

all: src $(TESTS)

src:
	$(MAKE) -C $(SRC)/..

option_test: option_test.o $(TESTCORE) $(DNSMASQ_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $+ $(LIBS)

dhcp_test: dhcp_test.o $(TESTCORE) $(DNSMASQ_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $+ $(LIBS)

# Debian still does not have kyua package
# https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=766577
# To simplify testing now, omit kyua
kyua: $(TESTS)
	CMOCKA_MESSAGE_OUTPUT=TAP kyua test

test: $(TESTS)
	for TEST in $(TESTS); do echo $$TEST:; ./$$TEST || exit 1; done

check: test

clean:
	rm -f $(TESTCORE) $(TEST_OBJS) $(TESTS)

cscope.out: $(TESTCORE_SRCS) $(TEST_SRCS)
	cscope -R -b -s $(SRC)

tags: cscope.out

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<
