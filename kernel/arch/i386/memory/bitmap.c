#include "bitmap.h"

void bitmap_unset(uint32_t* bitmap, int bit) {
    bitmap[bit / 32] &= ~(1 << (bit % 32));
}

void bitmap_set(uint32_t* bitmap, int bit) {
    bitmap[bit / 32] |= (1 << (bit % 32));
}

uint32_t bitmap_first_free(uint32_t* bitmap, int max_blocks) {
    for (size_t i = 0; i < max_blocks / 32; ++i) {
        if (bitmap[i] != 0xFFFFFFFF) {
            for (size_t j = 0; j < 32; ++j) {
                if (!(bitmap[i] & (1 << j)))
                    return i * 32 + j;
            }
        }
    }

    return -1;
}