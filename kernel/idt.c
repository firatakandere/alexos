#include <stddef.h>

#include "system.h"
#include "memory.h"

#define IDT_ENTRY_LIMIT 256

// idt entry definition
typedef struct idt_entry
{
  uint16_t base_low;
  uint16_t sel;
  uint8_t reserved;
  uint8_t flags;
  uint16_t base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr
{
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idt_ptr_t;

idt_entry_t idt[IDT_ENTRY_LIMIT];
idt_ptr_t idtp;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
  if (num >= IDT_ENTRY_LIMIT)
    return; // not allowed

  idt[num].base_low = (base & 0xFFFF);
  idt[num].base_high = (base >> 16) & 0xFFFF;

  idt[num].sel = sel;
  idt[num].reserved = 0;
  idt[num].flags = flags;
}

void idt_install(void)
{
  idtp.limit = (sizeof(idt_entry_t) * IDT_ENTRY_LIMIT) - 1;
  idtp.base = &idt;

  memset(&idt, 0, sizeof(idt_entry_t) * IDT_ENTRY_LIMIT);

  idt_load();
}
