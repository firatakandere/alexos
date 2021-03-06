#ifndef _ARCH_I386_IDT_H
#define _ARCH_I386_IDT_H

#include <stdint.h>
#include "isr.h"

struct idt_entry_struct {
    uint16_t offset_lower;
    uint16_t selector;
    uint8_t zero;
    uint8_t type;
    uint16_t offset_upper;
};
typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

void register_interrupt_handler(int num, isr_t handler);

#endif