#include <stdio.h>
#include <kernel/tty.h>
#include "isr.h"

void isr_handler(struct regs *r) {
    terminal_writestring("received interrupt: ");
    if (r->int_no < 32) {
        printf("EXCEPTION");
        for(;;);
    }
}