#include <kernel/idt.h>
#include <string.h>
#include <stdio.h>
#include "idt.h"
#include "../io.h"

#define IDT_ALLOCATION_SIZE 256

idt_entry_t idt_entries[IDT_ALLOCATION_SIZE];
idt_ptr_t idt_ptr;

static void idt_set_entry(uint8_t entry, uint32_t base, uint16_t selector, uint8_t type);

void init_idt(void) {
    extern int idt_flush();
    extern int irq0();
    extern int irq1();
    extern int irq2();
    extern int irq3();
    extern int irq4();
    extern int irq5();
    extern int irq6();
    extern int irq7();
    extern int irq8();
    extern int irq9();
    extern int irq10();
    extern int irq11();
    extern int irq12();
    extern int irq13();
    extern int irq14();
    extern int irq15();

    extern void isr0();
    extern void isr1();
    extern void isr2();
    extern void isr3();
    extern void isr4();
    extern void isr5();
    extern void isr6();
    extern void isr7();
    extern void isr8();
    extern void isr9();
    extern void isr10();
    extern void isr11();
    extern void isr12();
    extern void isr13();
    extern void isr14();
    extern void isr15();
    extern void isr16();
    extern void isr17();
    extern void isr18();
    extern void isr19();
    extern void isr20();
    extern void isr21();
    extern void isr22();
    extern void isr23();
    extern void isr24();
    extern void isr25();
    extern void isr26();
    extern void isr27();
    extern void isr28();
    extern void isr29();
    extern void isr30();
    extern void isr31();

    // Remap PIC
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 40);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    memset(idt_entries, 0, sizeof(idt_entries));

    idt_ptr.limit = sizeof(idt_entries) - 1;
    idt_ptr.base = (uint32_t) idt_entries;

    idt_set_entry(0, (uint32_t) isr0, 0x08, 0x8E);
    idt_set_entry(1, (uint32_t) isr1, 0x08, 0x8E);
    idt_set_entry(2, (uint32_t) isr2, 0x08, 0x8E);
    idt_set_entry(3, (uint32_t) isr3, 0x08, 0x8E);
    idt_set_entry(4, (uint32_t) isr4, 0x08, 0x8E);
    idt_set_entry(5, (uint32_t) isr5, 0x08, 0x8E);
    idt_set_entry(6, (uint32_t) isr6, 0x08, 0x8E);
    idt_set_entry(7, (uint32_t) isr7, 0x08, 0x8E);
    idt_set_entry(8, (uint32_t) isr8, 0x08, 0x8E);
    idt_set_entry(9, (uint32_t) isr9, 0x08, 0x8E);
    idt_set_entry(10, (uint32_t) isr10, 0x08, 0x8E);
    idt_set_entry(11, (uint32_t) isr11, 0x08, 0x8E);
    idt_set_entry(12, (uint32_t) isr12, 0x08, 0x8E);
    idt_set_entry(13, (uint32_t) isr13, 0x08, 0x8E);
    idt_set_entry(14, (uint32_t) isr14, 0x08, 0x8E);
    idt_set_entry(15, (uint32_t) isr15, 0x08, 0x8E);
    idt_set_entry(16, (uint32_t) isr16, 0x08, 0x8E);
    idt_set_entry(17, (uint32_t) isr17, 0x08, 0x8E);
    idt_set_entry(18, (uint32_t) isr18, 0x08, 0x8E);
    idt_set_entry(19, (uint32_t) isr19, 0x08, 0x8E);
    idt_set_entry(20, (uint32_t) isr20, 0x08, 0x8E);
    idt_set_entry(21, (uint32_t) isr21, 0x08, 0x8E);
    idt_set_entry(22, (uint32_t) isr22, 0x08, 0x8E);
    idt_set_entry(23, (uint32_t) isr23, 0x08, 0x8E);
    idt_set_entry(24, (uint32_t) isr24, 0x08, 0x8E);
    idt_set_entry(25, (uint32_t) isr25, 0x08, 0x8E);
    idt_set_entry(26, (uint32_t) isr26, 0x08, 0x8E);
    idt_set_entry(27, (uint32_t) isr27, 0x08, 0x8E);
    idt_set_entry(28, (uint32_t) isr28, 0x08, 0x8E);
    idt_set_entry(29, (uint32_t) isr29, 0x08, 0x8E);
    idt_set_entry(30, (uint32_t) isr30, 0x08, 0x8E);
    idt_set_entry(31, (uint32_t) isr31, 0x08, 0x8E);

    idt_set_entry(32, (uint32_t) irq0, 0x08, 0x8E);
    idt_set_entry(33, (uint32_t) irq1, 0x08, 0x8E);
    idt_set_entry(34, (uint32_t) irq2, 0x08, 0x8E);
    idt_set_entry(35, (uint32_t) irq3, 0x08, 0x8E);
    idt_set_entry(36, (uint32_t) irq4, 0x08, 0x8E);
    idt_set_entry(37, (uint32_t) irq5, 0x08, 0x8E);
    idt_set_entry(38, (uint32_t) irq6, 0x08, 0x8E);
    idt_set_entry(39, (uint32_t) irq7, 0x08, 0x8E);
    idt_set_entry(40, (uint32_t) irq8, 0x08, 0x8E);
    idt_set_entry(41, (uint32_t) irq9, 0x08, 0x8E);
    idt_set_entry(42, (uint32_t) irq10, 0x08, 0x8E);
    idt_set_entry(43, (uint32_t) irq11, 0x08, 0x8E);
    idt_set_entry(44, (uint32_t) irq12, 0x08, 0x8E);
    idt_set_entry(45, (uint32_t) irq13, 0x08, 0x8E);
    idt_set_entry(46, (uint32_t) irq14, 0x08, 0x8E);
    idt_set_entry(47, (uint32_t) irq15, 0x08, 0x8E);

    idt_flush((uint32_t)&idt_ptr);
    asm volatile("sti");
}

static void idt_set_entry(uint8_t entry, uint32_t base, uint16_t selector, uint8_t type) {
    idt_entries[entry].offset_lower = base & 0xFFFF;
    idt_entries[entry].offset_upper = (base >> 16) & 0xFFFF;
    idt_entries[entry].zero = 0;
    idt_entries[entry].selector = selector;
    idt_entries[entry].type = type;
}

void irq2_handler(void) {
    outb(0x20, 0x20);
}

void irq3_handler(void) {
    outb(0x20, 0x20);
}

void irq4_handler(void) {
    outb(0x20, 0x20);
}

void irq5_handler(void) {
    outb(0x20, 0x20);
}

void irq6_handler(void) {
    outb(0x20, 0x20);
}

void irq7_handler(void) {
    outb(0x20, 0x20);
}

void irq8_handler(void) {
    outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

void irq9_handler(void) {
    outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

void irq10_handler(void) {
    outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

void irq11_handler(void) {
    outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

void irq12_handler(void) {
    outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

void irq13_handler(void) {
    outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

void irq14_handler(void) {
    outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

void irq15_handler(void) {
    outb(0xA0, 0x20);
    outb(0x20, 0x20);
}
