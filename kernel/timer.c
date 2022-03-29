#include <stddef.h>
#include "system.h"

extern void terminal_write(const char*); //@todo remove this

size_t timer_ticks = 0;

void timer_handler(regs_t* r)
{
  ++timer_ticks;

  // 100 ticks = 1 sec
  if (timer_ticks % 100 == 0)
  {
    terminal_write("One second has passed\n");
  }
}

void timer_phase(int32_t hz)
{
  int32_t divisor = 1193180 / hz;
  outportb(0x43, 0x36);
  outportb(0x40, divisor & 0xFF);
  outportb(0x40, divisor >> 8);
}

void timer_install()
{
  timer_phase(100);
  irq_install_handler(0, timer_handler);
}
