#include <stddef.h>
#include "multiboot2.h"

#ifndef PHYS_MMNGR_H
#define PHYS_MMNGR_H

#define PAGE_MASK 0xFFFFF000
#define PAGE_FLAG_MASK 0xFFF
#define PAGE_SIZE 0x1000
#define PAGE_STACK_ENTRIES_PER_PAGE 0x400

uintptr_t pmm_alloc_page();
void pmm_free_page(uintptr_t page);
void pmm_init(multiboot_tag_basic_meminfo_t *tag);

#endif // PHYS_MMNGR_H