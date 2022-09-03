ENTRY(_start)

SECTIONS
{
  kernel_start = .;
  . = 0x00100000; /* 3GB + 1MB for higher-half kernel */

  .text ALIGN(4K) : AT(ADDR(.text) - 0x00000000)
  {
    *(.multiboot)
    *(.text)
  }

  .rodata ALIGN(4K) : AT(ADDR(.rodata) - 0x00000000)
  {
    *(.rodata)
  }

  .data ALIGN(4K) : AT(ADDR(.data) - 0x00000000)
  {
    *(.data)
  }

  .stack ALIGN(4K) : AT(ADDR(.stack) - 0x00000000)
  {
    *(COMMON)
    *(.stack)
  }

  kernel_size = . - kernel_start;
}
