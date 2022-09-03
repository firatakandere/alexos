#include <system.h>
#include <tty.h>
#include <page_table.h>
#include <multiboot2.h>

void cmain(unsigned long magic, unsigned long addr)
{
  // Initialize terminal
  terminal_cls();

  struct multiboot_tag *tag;
  unsigned size;
  extern unsigned long kernel_size;

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
  printf("Kernel size: 0x%x\n", &kernel_size);
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
          mmap = (multiboot_memory_map_t *) ((unsigned long) mmap + ((struct multiboot_tag_mmap *) tag)->entry_size)) {
            
          printf("base addr = 0x%x%x, length = 0x%x%x (%s)\n",
            (unsigned) (mmap->addr >> 32),
            (unsigned) (mmap->addr & 0xffffffff),
            (unsigned) (mmap->len >> 32),
            (unsigned) (mmap->len & 0xffffffff),
            get_memory_type((unsigned) mmap->type));

          if ((unsigned) mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
          }
        }
        break;
    }
  }

  tag = (struct multiboot_tag *) ((uint8_t *) tag + ((tag->size +7) & ~7));
  printf("Total mbi size 0x%x\n", (unsigned) tag - addr);

  gdt_install();
  idt_install();
  isrs_install();
  irq_install();

  printf("Initializing...\n");
  page_directory_t pd = initialize_page_directory();
  printf("Initialized page directory.\n");
  printf("Address of page directory: 0x%x\n", pd);

  page_table_t pt = get_page_table(pd, 0);
  printf("Address of the first page table: 0x%x\n", (uint32_t) pt);

  printf("First 5 page table entries: \n");
  for (int i = 0; i < 5; ++i) {
    printf("0x%x\n", pt[i]);
  }

  printf("Setting page directory...\n");
  set_page_directory(pd);
  printf("Set page directory.\n");

  printf("Enabling paging...\n");
  enable_paging();
  printf("Paging enabled.\n");


  timer_install();
  keyboard_install();
  __asm__ __volatile__("sti"); // enable interrupts
  printf("Hello, kernel world!\n");

  while(1) __asm__ __volatile__("hlt");
}
