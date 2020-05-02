
all: options_test

CFLAGS=-O2 -Wall -ggdb
SRC=../src
CPPFLAGS=-I$(SRC)
LIBS=-lcmocka

DNSMASQ_OBJS=$(SRC)/option.o $(SRC)/log.o $(SRC)/util.o

options_test: testcore.o option_test.o $(DNSMASQ_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $+ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<
