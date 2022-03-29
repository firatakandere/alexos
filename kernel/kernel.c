#include "system.h"

/* VGA STUFF */
#define COLUMNS   80
#define LINES     24
#define ATTR      7
#define VIDEO     0xB8000

static int x_pos;
static int y_pos;
static volatile uint8_t* v_mem;

void terminal_write(const char *data);
void terminal_cls(void);

void cmain()
{
  terminal_cls();
  gdt_install();
  idt_install();
  isrs_install();
  irq_install();
  timer_install();
  keyboard_install();
  __asm__ __volatile__("sti"); // enable interrupts
  terminal_write("Hello, kernel world!\n");
  
  while(1) __asm__ __volatile__("hlt");
}

void terminal_cls(void)
{
  v_mem = (uint8_t*) VIDEO;

  for (int i = 0; i < COLUMNS * LINES * 2; ++i)
    *(v_mem + i) = 0;
  
  x_pos = 0;
  y_pos = 0;
}

void terminal_putchar(char c)
{
  if (c == '\n' || c == '\r')
  {
newline:
    x_pos = 0;
    ++y_pos;
    if (y_pos >= LINES)
      y_pos = 0;
    return;
  }

  *(v_mem + (x_pos + y_pos * COLUMNS) * 2) = c & 0xFF;
  *(v_mem + (x_pos + y_pos * COLUMNS) * 2 + 1) = ATTR;

  ++x_pos;
  if (x_pos >= COLUMNS)
    goto newline;
}

void terminal_write(const char* data)
{
  int c;
  while ((c = *data++) != 0)
  {
    terminal_putchar(c);
  }
}
