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
        uint32_t mem_lower = ((struct multiboot_tag_basic_meminfo *) tag)->mem_lower;
        uint32_t mem_upper = ((struct multiboot_tag_basic_meminfo *) tag)->mem_upper;
        printf("mem_lower = %dKB, mem_upper = %dKB\n", mem_lower, mem_upper);
        break;
      case MULTIBOOT_TAG_TYPE_MMAP:
        multiboot_memory_map_t *mmap;
        printf("Physical Memory Map:\n");

        for (mmap = ((struct multiboot_tag_mmap *) tag)->entries;
            (uint8_t *) mmap < (uint8_t *) tag + tag->size;
            mmap = (multiboot_memory_map_t *) ((unsigned long) mmap + ((struct multiboot_tag_mmap *) tag)->entry_size))
            printf("base addr = 0x%x%x, length = 0x%x%x (%s)\n",
              (unsigned) (mmap->addr >> 32),
              (unsigned) (mmap->addr & 0xffffffff),
              (unsigned) (mmap->len >> 32),
              (unsigned) (mmap->len & 0xffffffff),
              get_memory_type((unsigned) mmap->type));
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
