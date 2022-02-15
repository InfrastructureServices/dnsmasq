#!/bin/sh

eval $(rpm -E %set_build_flags)

# used by google:
# -O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link
CFLAGS_EXTRA=" -O1 -fno-omit-frame-pointer -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link"

# Remove unsupported clang flags
export CC=clang
CFLAGS="$(echo "$CFLAGS" | sed -e 's/-flto=auto /-flto /' -e 's/-ffat-lto-objects / /' -e 's, -specs=[^ ]\+,,g') $CFLAGS_EXTRA"
CXXFLAGS="$(echo "$CFLAGS" | sed -e 's/-flto=auto /-flto /' -e 's/-ffat-lto-objects / /' -e 's, -specs=[^ ]\+,,g')"


export CFLAGS CXXFLAGS
export LDFLAGS

export OSS_CFLAGS="$CFLAGS"

export SRC="$(pwd)"
export OUT="$SRC"
#export LIB_FUZZING_ENGINE="$(rpm -ql compiler-rt | grep "clang_rt.fuzzer-$(arch)" | head -1)"
export LIB_FUZZING_ENGINE="-fsanitize=fuzzer,address"
