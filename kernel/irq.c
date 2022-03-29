extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

void *irq_routines[16] =
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned short flags);
extern void outportb(unsigned short port, unsigned char data);
void irq_install_handler(int irq, void (*handler)(struct regs *r))
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

#define IDT_SET_GATE(n) idt_set_gate(n+32, (unsigned)irq##n, 0x08, 0x8E);
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

struct regs
{
  unsigned int gs, fs, es, ds;
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
  unsigned int int_no, err_code;
  unsigned int eip, cs, eflags, useresp, ss;
};

void irq_handler(struct regs *r)
{
  void (*handler)(struct regs *r);

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
