#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/alexos.kernel isodir/boot/alexos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "AlexOS" {
        multiboot /boot/alexos.kernel
}
EOF
grub-mkrescue -o alexos.iso isodir
