#ifndef _ARCH_I386_BITMAP_H
#define _ARCH_I386_BITMAP_H

#include <stdint.h>
#include <stddef.h>

void bitmap_unset(uint32_t* bitmap, int bit);
void bitmap_set(uint32_t* bitmap, int bit);
uint32_t bitmap_first_free(uint32_t* bitmap, int max_blocks);

#endif