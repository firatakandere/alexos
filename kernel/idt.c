#include <stddef.h>

#include "system.h"

// idt entry definition
typedef struct idt_entry
{
  unsigned short base_low;
  unsigned short sel;
  unsigned char reserved;
  unsigned char flags;
  unsigned short base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr
{
  unsigned short limit;
  unsigned int base;
} __attribute__((packed)) idt_ptr_t;

idt_entry_t idt[256];
idt_ptr_t idtp;

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
  idt[num].base_low = (base & 0xFFFF);
  idt[num].base_high = (base >> 16) & 0xFFFF;

  idt[num].sel = sel;
  idt[num].reserved = 0;
  idt[num].flags = flags;
}

// @todo move this away
void* memset(void* bufptr, int value, size_t size)
{
  unsigned char* buf = (unsigned char*) bufptr;
  for (size_t i = 0; i < size; ++i)
    buf[i] = (unsigned char) value;
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
