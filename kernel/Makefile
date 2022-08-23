CFLAGS?=-O2 -g
LDFLAGS?=
LIBS?=

PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lgcc

KERNEL_OBJS = $(patsubst %.c,%.o,$(wildcard */*.c))
KERNEL_OBJS += $(patsubst %.S,%.o,$(wildcard */*.S))

OBJS = $(KERNEL_OBJS)

LINK_LIST = $(LDFLAGS) $(KERNEL_OBJS) $(LIBS)

.PHONY: all clean install install-kernel
.SUFFIXES: .o .c .S

all: alexos.bin

debug: CFLAGS += -g
debug: alexos.bin

alexos.bin: $(OBJS) arch/linker.ld
	$(CC) -T arch/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	#grub-file --is-x86-multiboot alexos.bin

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu99 $(CFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS)

clean:
	rm -f alexos.bin
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-kernel

install-kernel: alexos.bin
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp alexos.bin $(DESTDIR)/$(BOOTDIR)

-include $(OBJS:.o=.d)
