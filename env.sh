#!/bin/bash
export PATH=$HOME/cross/build/bin:$PATH

export MAKE=${MAKE-make}
export HOST=i686-elf

export AS=${HOST}-as
export CC=${HOST}-gcc

export PREFIX=/usr
export BOOTDIR=/boot
export LIBDIR=$PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS='-O2 -g'

export SYSROOT="$(pwd)/sysroot"
export CC="$CC --sysroot=$SYSROOT -isystem=$INCLUDEDIR"
