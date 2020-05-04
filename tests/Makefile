
all: options_test

CFLAGS=-O2 -Wall -ggdb
SRC=../src
CPPFLAGS=-I$(SRC)
LIBS=-lcmocka

DNSMASQ_OBJS=$(SRC)/option.o $(SRC)/log.o $(SRC)/util.o $(SRC)/poll.o
DNSMASQ_DHCP_OBJS=$(SRC)/cache.o $(SRC)/network.o $(SRC)/netlink.o $(SRC)/dhcp-common.o \
		  $(SRC)/dhcp.o $(SRC)/dhcp6.o $(SRC)/rfc2131.o $(SRC)/rfc3315.o \
		  $(SRC)/rfc1035.o $(SRC)/forward.o $(SRC)/loop.o $(SRC)/lease.o \
		  $(SRC)/domain.o $(SRC)/radv.o $(SRC)/outpacket.o $(SRC)/arp.o $(SRC)/blockdata.o \
		  $(SRC)/edns0.o $(SRC)/dump.o
TESTCORE=testcore.o testlib.o
TEST_OBJS=option_test.o

all: options_test dhcp_test

options_test: option_test.o testlib-dhcp.o testlib-network.o $(TESTCORE) $(DNSMASQ_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $+ $(LIBS)

dhcp_test: dhcp_test.o $(TESTCORE) $(DNSMASQ_OBJS) $(DNSMASQ_DHCP_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $+ $(LIBS)

clean:
	rm -f $(TESTCORE) $(TEST_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<
