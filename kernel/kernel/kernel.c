#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/timer.h>

void kernel_main(void) {
    init_gdt();
    init_idt();
    init_timer(50);
    terminal_initialize();

    printf("Hello, kernel world \n");
    printf("Hello, kernel world 2 \n");


    // prevent premature
    for(;;) {
        asm("hlt");
    }
}
