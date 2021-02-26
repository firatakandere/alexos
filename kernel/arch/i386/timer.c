#include <stdio.h>
#include <stddef.h>

#include <kernel/timer.h>

#include "io.h"
#include "interrupts/idt.h"

uint32_t tick = 0;

void timer_handler(register_t* reg) {
    ++tick;
}

void init_timer(size_t frequency) {
    uint32_t divisor = 1193180 / (uint32_t) frequency;

    outb(0x43, 0x36);

    uint8_t low_b  = (uint8_t) (divisor & 0xFF);
    uint8_t high_b = (uint8_t) ((divisor >> 8) & 0xFF);

    outb(0x40, low_b);
    outb(0x40, high_b);

    register_interrupt_handler(32, timer_handler);
}