ENTRY(_start)

SECTIONS
{
  kernel_start = .;
  . = 1M;

  .text BLOCK(4K) : ALIGN(4K)
  {
    *(.multiboot)
    *(.text)
  }

  .rodata BLOCK(4K) : ALIGN(4K)
  {
    *(.rodata)
  }

  .data BLOCK(4K) : ALIGN(4K)
  {
    *(.data)
  }

  .stack BLOCK(4K) : ALIGN(4K)
  {
    *(COMMON)
    *(.stack)
  }

  kernel_size = . - kernel_start;
}
