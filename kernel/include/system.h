#ifndef KERNEL_SYSTEM_H
#define KERNEL_SYSTEM_H

#include <stdint.h>

typedef struct regs
{
  uint32_t gs, fs, es, ds;
  uint32_t edi, esi, ebp, esp, ebx, eds, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags, useresp, ss;
} regs_t;

void outportb(uint16_t port, uint8_t data); // defined in io.S
uint8_t inportb(uint16_t port);

void gdt_flush(void); // defined in start.S
void gdt_install(void);

void idt_load(void); // defined in start.S
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void idt_install(void);

/* defined in start.S */
void irq0(void);
void irq1(void);
void irq2(void);
void irq3(void);
void irq4(void);
void irq5(void);
void irq6(void);
void irq7(void);
void irq8(void);
void irq9(void);
void irq10(void);
void irq11(void);
void irq12(void);
void irq13(void);
void irq14(void);
void irq15(void);

void irq_install_handler(uint32_t irq, void (*handler)(regs_t *r));
void irq_install(void);

/* defined in start.S */
void isr0(void);
void isr1(void);
void isr2(void);
void isr3(void);
void isr4(void);
void isr5(void);
void isr6(void);
void isr7(void);
void isr8(void);
void isr9(void);
void isr10(void);
void isr11(void);
void isr12(void);
void isr13(void);
void isr14(void);
void isr15(void);
void isr16(void);
void isr17(void);
void isr18(void);
void isr19(void);
void isr20(void);
void isr21(void);
void isr22(void);
void isr23(void);
void isr24(void);
void isr25(void);
void isr26(void);
void isr27(void);
void isr28(void);
void isr29(void);
void isr30(void);
void isr30(void);
void isr31(void);

void isrs_install(void);
void timer_install(void);
void keyboard_install(void);

void set_page_directory(uint32_t* pt);
void enable_paging(void);
#endif
