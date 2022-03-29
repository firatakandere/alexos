#include "system.h"

void *irq_routines[16] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

void irq_install_handler(uint32_t irq, void (*handler)(regs_t *r))
{
  irq_routines[irq] = handler;
}

void irq_remap(void)
{
  outportb(0x20, 0x11);
  outportb(0xA0, 0x11);
  outportb(0x21, 0x20);
  outportb(0xA1, 0x28);
  outportb(0x21, 0x04);
  outportb(0xA1, 0x02);
  outportb(0x21, 0x01);
  outportb(0xA1, 0x01);
  outportb(0x21, 0x0);
  outportb(0xA1, 0x0);
}

void irq_install(void)
{
  irq_remap();

#define IDT_SET_GATE(n) idt_set_gate(n+32, (uint32_t)irq##n, 0x08, 0x8E);
  IDT_SET_GATE(0);
  IDT_SET_GATE(1);
  IDT_SET_GATE(2);
  IDT_SET_GATE(3);
  IDT_SET_GATE(4);
  IDT_SET_GATE(5);
  IDT_SET_GATE(6);
  IDT_SET_GATE(7);
  IDT_SET_GATE(8);
  IDT_SET_GATE(9);
  IDT_SET_GATE(10);
  IDT_SET_GATE(11);
  IDT_SET_GATE(12);
  IDT_SET_GATE(13);
  IDT_SET_GATE(14);
  IDT_SET_GATE(15);
#undef IDT_SET_GATE
}

void irq_handler(regs_t* r)
{
  void (*handler)(regs_t* r);

  handler = irq_routines[r->int_no - 32];
  if (handler)
  {
    handler(r);
  }

  if (r->int_no >= 40)
  {
    outportb(0xA0, 0x20);
  }

  outportb(0x20, 0x20);
}
