#include <kernel/gdt.h>
#include "gdt.h"

#define GDT_ALLOCATION_SIZE 5

extern void gdt_flush(uint32_t);

static void gdt_set_entry(uint32_t, uint32_t, uint32_t, uint8_t, uint8_t);

gdt_entry_t gdt_entries[GDT_ALLOCATION_SIZE];
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
    gdt_entries[entry].base_lower = GDT_BASE_LOWER(base);
    gdt_entries[entry].base_middle = GDT_BASE_MIDDLE(base);
    gdt_entries[entry].base_upper = GDT_BASE_UPPER(base);

    gdt_entries[entry].limit_lower = GDT_LIMIT_LOWER(limit);
    gdt_entries[entry].granularity = GDT_LIMIT_UPPER(limit);

    gdt_entries[entry].granularity |= GDT_GRANULARITY(granularity);
    gdt_entries[entry].access = access;
}
