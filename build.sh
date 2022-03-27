#!/bin/sh

i686-elf-as boot.S -o boot.o
i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o alexos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

mkdir -p isodir/boot/grub
cp alexos.bin isodir/boot/alexos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o alexos.iso isodir
