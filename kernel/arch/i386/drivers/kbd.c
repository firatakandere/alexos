#include <stdio.h>

#include "kbd.h"
#include "../io.h"
#include "../interrupts/idt.h"

#define OUT_BUFFER 16

// defined under table.c
extern kb_event_t kb_event_map[0x80];

struct out_queue_struct {
    unsigned char buf[OUT_BUFFER];
    unsigned int offset:2;
    unsigned int is_available:1;
    unsigned int waiting_ack:1;
};
typedef struct out_queue_struct out_queue_t;

out_queue_t out_queue;

kb_event_t* kbd_read() {
    while((inb(0x64) & 1) == 0); // wait till scan code
    uint8_t scancode = inb(0x60);

    kb_event_t* kb_event = &kb_event_map[scancode]; // @todo check if it's there
    return kb_event;
}


void keyboard_handler(register_t* reg) {
    kb_event_t* kbd_event = kbd_read();

    if (kbd_event->input == INPUT_KEY_A) {
        printf("A IS PRESSED");
    }
}

void init_keyboard() {
    register_interrupt_handler(33, keyboard_handler);
}