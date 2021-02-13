#include <kernel/gdt.h>
#include "gdt.h"

#define GDT_ALLOCATION_SIZE 5

extern void gdt_flush(uint32_t);

static void gdt_set_entry(uint32_t, uint32_t, uint32_t, uint8_t, uint8_t);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

void init_gdt(void) {
    gdt_ptr.limit = sizeof(gdt_entries) - 1;
    gdt_ptr.base  = (uint32_t) gdt_entries;

    gdt_set_entry(0, 0, 0, 0, 0);                // Null segment
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    gdt_flush((uint32_t)(&gdt_ptr));
}

static void gdt_set_entry(uint32_t entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt_entries[entry].base_lower = (base & 0xFFFF);
    gdt_entries[entry].base_middle = ( base >> 16) & 0xFF;
    gdt_entries[entry].base_upper = (base >> 24) & 0xFF;

    gdt_entries[entry].limit_lower = (limit & 0xFFFF);
    gdt_entries[entry].granularity = (limit >> 16) & 0x0F;

    gdt_entries[entry].granularity |= granularity & 0xF0;
    gdt_entries[entry].access = access;
}
