#include <system.h>
#include <gdt.h>

#define GDT_ENTRY_LIMIT 3

// defition of gdt entry
typedef struct gdt_entry
{
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr
{
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

gdt_entry_t gdt[GDT_ENTRY_LIMIT];
gdt_ptr_t gp;

// setup descriptor in the Global Descriptor Table
void gdt_set_gate(int32_t num, uint32_t base, uint64_t limit, uint8_t access, uint8_t gran)
{
  if (num >= GDT_ENTRY_LIMIT)
    return; // not allowed

  // descriptor base address
  gdt[num].base_low = (base & 0xFFFF);
  gdt[num].base_middle = (base >> 16) & 0xFF;
  gdt[num].base_high = (base >> 24) & 0xFF;

  // descriptor limits
  gdt[num].limit_low = (limit & 0xFFFF);
  //gdt[num].granularity = (limit >> 16) & 0x0F;
  gdt[num].granularity |= (gran & 0xF0);
  gdt[num].access = access;
}

void gdt_install(void)
{
  // setup GDT pointer and limit
  gp.limit = (sizeof(gdt_entry_t) * GDT_ENTRY_LIMIT) - 1;
  gp.base = &gdt;

  // null descriptor
  gdt_set_gate(0, 0, 0, 0, 0);

  // code segment
  gdt_set_gate(1,
      0,
      0xFFFFFFFF,
      GDT_DESC(1) | GDT_PRES(1) | GDT_PRIV(0) | GDT_CODE_EO,
      GDT_RES(0) | GDT_LONG(0) | GDT_SIZE(1) | GDT_GRAN(1) | GDT_LIMIT_MASK
      );

  // data segment
  gdt_set_gate(2,
      0,
      0xFFFFFFFF,
      GDT_DESC(1) | GDT_PRES(1) | GDT_PRIV(0) | GDT_DATA_RW,
      GDT_RES(0) | GDT_LONG(0) | GDT_SIZE(1) | GDT_GRAN(1) | GDT_LIMIT_MASK
      );

  gdt_flush();
}
