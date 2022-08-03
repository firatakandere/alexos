#include "system.h"
#include "tty.h"
#include "multiboot2.h"

void cmain(unsigned long magic, unsigned long addr)
{
  // Initialize terminal
  terminal_cls();

  struct multiboot_tag *tag;
  unsigned size;

  if (magic != MULTIBOOT2_BOOTLOADER_MAGIC)
  {
    printf("Invalid magic number: 0x%x\n", (unsigned) magic);
    return;
  }

  if (addr & 7)
  {
    printf("Unaligned mbi: 0x%x", addr);
    return;
  }

  size = *(unsigned *) addr;
  printf("Announced mbi size 0x%x\n", size);

  for (tag = (struct multiboot_tag *) (addr + 8);
       tag->type != MULTIBOOT_TAG_TYPE_END;
       tag = (struct multiboot_tag *) ((uint8_t *) tag + ((tag->size + 7) & ~7)))
  {
    //printf("Tag 0x%x, Size 0x%x\n", tag->type, tag->size);

    switch (tag->type) {
      case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
        printf("mem_lower = %dKB, mem_upper = %dKB\n",
          ((struct multiboot_tag_basic_meminfo *) tag)->mem_lower,
          ((struct multiboot_tag_basic_meminfo *) tag)->mem_upper);
        break;
    }
  }

  tag = (struct multiboot_tag *) ((uint8_t *) tag + ((tag->size +7) & ~7));
  printf("Total mbi size 0x%x\n", (unsigned) tag - addr);

  gdt_install();
  idt_install();
  isrs_install();
  irq_install();
  timer_install();
  keyboard_install();
  __asm__ __volatile__("sti"); // enable interrupts
  printf("Hello, kernel world!\n");

  while(1) __asm__ __volatile__("hlt");
}
