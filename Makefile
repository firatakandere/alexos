PROJECTS = kernel
PROJECTS_CLEAN = $(addsuffix .clean,$(PROJECTS))

.PHONY: all $(PROJECTS) $(PROJECTS_CLEAN) iso clean

all: $(PROJECTS)

$(PROJECTS):
	$(MAKE) -C $@

$(PROJECTS_CLEAN):
	$(MAKE) -C $(basename $@) clean

iso: all
	mkdir -p isodir/boot/grub
	cp kernel/alexos.bin isodir/boot/alexos.bin
	cp boot/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o alexos.iso isodir

clean: $(PROJECTS_CLEAN)
	rm -rf isodir
	
