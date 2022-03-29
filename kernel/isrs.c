extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

void isrs_install()
{
#define IDT_SET_GATE(n) idt_set_gate(n, (unsigned)isr##n, 0x08, 0x8E);
  
  //idt_set_gate(0, (unsigned)isr0, 0x08, 0x8E);
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
  IDT_SET_GATE(16);
  IDT_SET_GATE(17);
  IDT_SET_GATE(18);
  IDT_SET_GATE(19);
  IDT_SET_GATE(20);
  IDT_SET_GATE(21);
  IDT_SET_GATE(22);
  IDT_SET_GATE(23);
  IDT_SET_GATE(24);
  IDT_SET_GATE(25);
  IDT_SET_GATE(26);
  IDT_SET_GATE(27);
  IDT_SET_GATE(28);
  IDT_SET_GATE(29);
  IDT_SET_GATE(30);
  IDT_SET_GATE(31);
  
#undef IDT_SET_GATE
}

char *isr_exception_messages[] =
{
  "Division by zero exception",
  "Debug exception",
  "Non-maskable interrupt exception",
  "Breakpoint exception",
  "Into detected overflow exception",
  "Out of bounds exception",
  "Invalid opcode exception",
  "No coprocessor exception",
  "Double fault exception",
  "Coprocessor segment overrun exception",
  "Bad TSS exception",
  "Segment not present exception",
  "Stack fault exception",
  "General protection fault exception",
  "Page fault exception",
  "Unknown interrupt exception",
  "Coprocessor fault exception",
  "Alignment check exception",
  "Machine check exception",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved"
};

struct regs
{
  unsigned int gs, fs, es,ds;
  unsigned int edi, esi, ebp, esp, ebx, eds, ecx, eax;
  unsigned int int_no, err_code;
  unsigned int eip, cs, eflags, useresp, ss;
};

extern void terminal_write(const char*); // @todo remove this

char* itoa(int value, char* str, int base)
{
  char *rc;
  char *ptr;
  char *low;

  if (base < 2 || base > 36)
  {
    *str = '\0';
    return str;
  }

  rc = ptr = str;
  if (value < 0 && base == 10) 
  {
    *ptr++ = '-';
  }

  low = ptr;
  do
  {
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
    value /= base;
  } while (value);

  *ptr-- = '\0';
  while (low < ptr)
  {
    char tmp = *low;
    *low++ = *ptr;
    *ptr-- = tmp;
  }

  return rc;
}

void fault_handler(struct regs *r)
{
  if (r->int_no < 32)
  {
    terminal_write(isr_exception_messages[r->int_no]);
    terminal_write("\n");
    terminal_write("Error code: ");
    char buff[30];
    terminal_write(itoa(r->err_code, buff, 10));
    terminal_write("\n");
    terminal_write("System Halted!\n");
    for (;;);
  }
}
