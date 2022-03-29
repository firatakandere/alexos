PROJECTS = kernel
PROJECTS_CLEAN = $(addsuffix .clean,$(PROJECTS))
PROJECTS_DEBUG = $(addsuffix .debug,$(PROJECTS))

.PHONY: all debug $(PROJECTS) $(PROJECTS_CLEAN) $(PROJECTS_DEBUG) iso debug-iso clean

all: $(PROJECTS)

debug: $(PROJECTS_DEBUG)

$(PROJECTS):
	$(MAKE) -C $@

$(PROJECTS_CLEAN):
	$(MAKE) -C $(basename $@) clean

$(PROJECTS_DEBUG):
	$(MAKE) -C $(basename $@) debug

iso: all isopack

debug-iso: debug isopack

isopack:
	mkdir -p isodir/boot/grub
	cp kernel/alexos.bin isodir/boot/alexos.bin
	cp boot/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o alexos.iso isodir

clean: $(PROJECTS_CLEAN)
	rm -rf isodir
	rm -rf alexos.iso
	
