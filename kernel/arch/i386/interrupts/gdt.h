#ifndef _ARCH_I386_GDT_H
#define _ARCH_I386_GDT_H

#include <stdint.h>

#define GDT_BASE_LOWER( base ) (base & 0xFFFF)
#define GDT_BASE_MIDDLE( base ) ((base >> 16) & 0xFF)
#define GDT_BASE_UPPER( base ) ((base >> 24) & 0xFF)

#define GDT_LIMIT_LOWER( limit ) (limit & 0xFFFF)
#define GDT_LIMIT_UPPER( limit ) ((limit >> 16) & 0x0F)
#define GDT_GRANULARITY( granularity ) (granularity & 0xF0)

struct gdt_entry_struct {
    uint16_t limit_lower;
    uint16_t base_lower;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_upper;
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;




#endif
