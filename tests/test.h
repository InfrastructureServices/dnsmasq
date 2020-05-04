#pragma once

#include "dnsmasq.h"

#include <setjmp.h>
#include <cmocka.h>


#define ARRAY_SIZE(a)  (sizeof(a)/sizeof((a)[0]))
#define ARGV_START "dnsmasq", "-C", "/dev/null"

void testcore_main(int argc, char **argv);
