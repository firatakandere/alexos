#include <stddef.h>

struct regs
{
  unsigned int gs, fs, es, ds;
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
  unsigned int int_no, err_code;
  unsigned int eip, cs, eflags, useresp, ss;
};

extern void terminal_write(const char*);
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));

int timer_ticks = 0;

void timer_handler(struct regs *r)
{
  ++timer_ticks;

  // 100 ticks = 1 sec
  if (timer_ticks % 100 == 0)
  {
    terminal_write("One second has passed\n");
  }
}

extern void outportb(unsigned short port, unsigned char data);

void timer_phase(int hz)
{
  int divisor = 1193180 / hz;
  outportb(0x43, 0x36);
  outportb(0x40, divisor & 0xFF);
  outportb(0x40, divisor >> 8);
}

void timer_install()
{
  timer_phase(100);
  irq_install_handler(0, timer_handler);
}
