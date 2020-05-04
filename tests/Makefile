
all: options_test

CFLAGS=-O2 -Wall -ggdb
SRC=../src
CPPFLAGS=-I$(SRC)
LIBS=-lcmocka

DNSMASQ_OBJS=$(SRC)/option.o $(SRC)/log.o $(SRC)/util.o $(SRC)/poll.o
TESTCORE=testcore.o testlib.o
TEST_OBJS=option_test.o

options_test: option_test.o $(TESTCORE) $(DNSMASQ_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $+ $(LIBS)

clean:
	rm -f $(TESTCORE) $(TEST_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<
