ENTRY(_start)

SECTIONS
{
    . = 1M;

    _kernel_start = .;

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

    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

    . = ALIGN(4K);
    _kernel_end = .; end = .; _end = .; __end = .; 
    _kernel_size = _kernel_end - _kernel_start;
}
