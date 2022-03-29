#include <stddef.h>

#include "system.h"

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

idt_entry_t idt[256];
idt_ptr_t idtp;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
  idt[num].base_low = (base & 0xFFFF);
  idt[num].base_high = (base >> 16) & 0xFFFF;

  idt[num].sel = sel;
  idt[num].reserved = 0;
  idt[num].flags = flags;
}

// @todo move this away
void* memset(void* bufptr, int32_t value, size_t size)
{
  uint8_t* buf = (uint8_t*) bufptr;
  for (size_t i = 0; i < size; ++i)
    buf[i] = (uint8_t) value;
  return bufptr;
}

void idt_install(void)
{
  idtp.limit = (sizeof(idt_entry_t) * 256) - 1;
  idtp.base = &idt;

  memset(&idt, 0, sizeof(idt_entry_t) * 256);

  // todo: list isrs here

  idt_load();
}
