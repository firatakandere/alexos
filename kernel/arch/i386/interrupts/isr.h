#ifndef _ARCH_I386_ISR_H
#define _ARCH_I386_ISR_H

#include <stdint.h>

struct register_struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};
typedef struct register_struct register_t;

void isr_handler(register_t*);
typedef void (*isr_t)(register_t*);

#endif