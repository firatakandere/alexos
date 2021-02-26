#include <stdio.h>
#include <kernel/tty.h>
#include "isr.h"

void isr_handler(register_t *reg) {
    terminal_writestring("received interrupt: ");
    if (reg->int_no < 32) {
        printf("EXCEPTION");
        for(;;);
    }
}