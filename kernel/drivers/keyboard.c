#include <system.h>

extern void terminal_putchar(const char);

const char kbdus[128] =
{
  0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'
};


void keyboard_handler(regs_t* r)
{
  uint8_t scancode;
  scancode = inportb(0x60);

  if (scancode & 0x80)
  {
    // key release, idc
  }
  else
  {
    terminal_putchar(kbdus[scancode]);
  }
}

void keyboard_install()
{
  irq_install_handler(1, keyboard_handler);
}
