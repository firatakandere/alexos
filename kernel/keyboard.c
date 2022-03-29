
extern void terminal_putchar(const char);

const char kbdus[128] =
{
  0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'
};

struct regs
{
  unsigned int gs, fs, es, ds;
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eas;
  unsigned int eip, cs, eflags, useresp, ss;
};

extern void irq_install_handler(int irq, void (*handler)(struct regs *r));

void keyboard_handler(struct regs *r)
{
  unsigned char scancode;
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
