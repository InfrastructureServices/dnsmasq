#pragma once

#include "dnsmasq.h"

#include <setjmp.h>
#include <cmocka.h>


#define ARRAY_SIZE(a)  (sizeof(a)/sizeof((a)[0]))

void testcore_main(int argc, char **argv);
