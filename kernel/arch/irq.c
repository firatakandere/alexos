#include <system.h>

#define IRQ_ROUTINE_LIMIT 16

void *irq_routines[IRQ_ROUTINE_LIMIT] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

void irq_install_handler(uint32_t irq, void (*handler)(regs_t *r))
{
  if (irq >= IRQ_ROUTINE_LIMIT)
    return; // not allowed
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

void irq_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
  if (num >= IRQ_ROUTINE_LIMIT)
    return; // not allowed

  idt_set_gate(num+32, base, sel, flags);
}

void irq_install(void)
{
  irq_remap();

#define IRQ_SET_GATE(n) irq_set_gate(n, (uint32_t)irq##n, 0x08, 0x8E);
  IRQ_SET_GATE(0);
  IRQ_SET_GATE(1);
  IRQ_SET_GATE(2);
  IRQ_SET_GATE(3);
  IRQ_SET_GATE(4);
  IRQ_SET_GATE(5);
  IRQ_SET_GATE(6);
  IRQ_SET_GATE(7);
  IRQ_SET_GATE(8);
  IRQ_SET_GATE(9);
  IRQ_SET_GATE(10);
  IRQ_SET_GATE(11);
  IRQ_SET_GATE(12);
  IRQ_SET_GATE(13);
  IRQ_SET_GATE(14);
  IRQ_SET_GATE(15);
#undef IRQ_SET_GATE
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
