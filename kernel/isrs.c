#include "system.h"


void isrs_install()
{
#define IDT_SET_GATE(n) idt_set_gate(n, (uint32_t)isr##n, 0x08, 0x8E);
  
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

extern void terminal_write(const char*); // @todo remove this

void fault_handler(regs_t* r)
{
  if (r->int_no < 32)
  {
    terminal_write(isr_exception_messages[r->int_no]);
    terminal_write("\n");
    terminal_write("System Halted!\n");
    for (;;);
  }
}
