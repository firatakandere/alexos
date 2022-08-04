#include <stdint.h>
#include <stddef.h>
#include "phys_mmngr.h"

uint32_t _mmngr_memory_size = 0;
uint32_t _mmngr_used_blocks = 0;
uint32_t _mmngr_max_blocks = 0;
uint32_t* _mmngr_memory_map = 0;

uint32_t pmmngr_get_block_count() {
    return _mmngr_max_blocks;
}

size_t pmmngr_get_memory_size() {
    return _mmngr_memory_size;
}


uint32_t pmmngr_get_free_block_count() {
    return _mmngr_max_blocks - _mmngr_used_blocks;
}

void mmap_set(int bit) {
    _mmngr_memory_map[bit / 32] |= (1 << (bit % 32));
}

void mmap_unset(int bit) {
    _mmngr_memory_map[bit / 32] &= (1 << (bit % 32));
}

int mmap_test(int bit) {
    return _mmngr_memory_map[bit / 32] & (1 << (bit % 32));
}

int mmap_first_free() {
    for (uint32_t i = 0; i < pmmngr_get_block_count() / 32; ++i) {
        if (_mmngr_memory_map[i] != 0xffffffff)
            for (int j = 0; j < 32; ++j) {
                int bit = 1 << j;
                if (! (_mmngr_memory_map[i] & bit))
                    return i*4*8+j;
            }
    }

    return -1;
}

void pmmngr_init(size_t mem_size, physical_addr bitmap) {
    _mmngr_memory_size = mem_size;
    _mmngr_memory_map = (uint32_t*) bitmap;
    _mmngr_max_blocks = (pmmngr_get_memory_size() * 1024) / PMMNGR_BLOCK_SIZE;
    _mmngr_used_blocks = pmmngr_get_block_count();

    // all memory is in use by default
    memset (_mmngr_memory_map, 0xf, pmmngr_get_block_count() / PMMNGR_BLOCKS_PER_BYTE);
}

void pmmngr_init_region(physical_addr base, size_t size) {
    int align = base / PMMNGR_BLOCK_ALIGN;
    int blocks = size / PMMNGR_BLOCK_SIZE;

    for (; blocks > 0; --blocks) {
        mmap_unset(align++);
        --_mmngr_used_blocks;
    }

    mmap_set(0); // first block always set to insure allocs cant be 0
}

void pmmngr_deinit_region(physical_addr base, size_t size) {
    int align = base / PMMNGR_BLOCK_ALIGN;
    int blocks = size / PMMNGR_BLOCK_SIZE;

    for (; blocks > 0; --blocks) {
        mmap_set(align++);
        ++_mmngr_used_blocks;
    }
}

void* pmmngr_alloc_block() {
    if (pmmngr_get_free_block_count() <= 0)
        return 0; // @todo out of memory;

    int frame = mmap_first_free();

    if (frame == -1)
        return 0; // @todo out of memory;

    mmap_set(frame);

    physical_addr addr = frame * PMMNGR_BLOCK_SIZE;
    ++_mmngr_used_blocks;

    return (void*)addr;
}

void pmmngr_free_block (void* p) {
    physical_addr addr = (physical_addr)p;
    int frame = addr / PMMNGR_BLOCK_SIZE;

    mmap_unset (frame);
    --_mmngr_used_blocks;
}