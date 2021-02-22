#ifndef _ARCH_I386_INPUT_H
#define _ARCH_I386_INPUT_H

#include <stdint.h>

enum {
    KEY_RELEASED = 0,
    KEY_PRESSED = 1
};

enum {
    INPUT_KEY_A = 0x0004,
    INPUT_KEY_B,
    INPUT_KEY_C,
    INPUT_KEY_D,
    INPUT_KEY_E,
    INPUT_KEY_F,
    INPUT_KEY_G,
    INPUT_KEY_H,
    INPUT_KEY_I,
    INPUT_KEY_J,
    INPUT_KEY_K,
    INPUT_KEY_L,
    INPUT_KEY_M,
    INPUT_KEY_N,
    INPUT_KEY_O,
    INPUT_KEY_P,
    INPUT_KEY_Q,
    INPUT_KEY_R,
    INPUT_KEY_S,
    INPUT_KEY_T,
    INPUT_KEY_U,
    INPUT_KEY_W,
    INPUT_KEY_X,
    INPUT_KEY_Y,
    INPUT_KEY_Z,
    INPUT_KEY_1,
    INPUT_KEY_2,
    INPUT_KEY_3,
    INPUT_KEY_4,
    INPUT_KEY_5,
    INPUT_KEY_6,
    INPUT_KEY_7,
    INPUT_KEY_8,
    INPUT_KEY_9,
    INPUT_KEY_0,

    INPUT_KEY_ESCAPE,
    INPUT_KEY_DASH,
    INPUT_KEY_EQUAL,
    INPUT_KEY_BACKSPACE,
    INPUT_KEY_TAB,
    INPUT_KEY_LEFT_BRACKET,
    INPUT_KEY_RIGHT_BRACKET,
    INPUT_KEY_ENTER,
    INPUT_KEY_LEFT_CONTROL
    
};

struct kb_event_struct {
    uint8_t key_event;
    uint16_t input; 
};
typedef struct kb_event_struct kb_event_t;

#endif