#!/bin/sh

grep -E '^(#|typedef)' dnsmasq.h > dnsmasq-defines.h
swig -python dnsmasq.i
gcc $(pkg-config --cflags --libs python3-embed) -fPIC -shared dnsmasq_wrap.c metrics.c -o _dnsmasq.so
