#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <kernel/memory.h>

#include "manager.h"
#include "bitmap.h"

#define PM_MANAGER_BLOCKS_PER_BYTE 32
#define PM_MANAGER_BLOCK_SIZE 4096
#define PM_MANAGER_BLOCK_ALIGN PM_MANAGER_BLOCK_SIZE

#define KB_TO_BLOCK(x) (((x) * 1024) / PM_MANAGER_BLOCK_SIZE)

#define IS_ALIGNED(addr, align) !((addr) & ~((align) - 1))
#define ALIGN(addr, align) (((addr) & ~((align) - 1)) + (align))

static uint32_t mem_size = 0;
static uint32_t used_blocks = 0;
static uint32_t max_blocks = 0;
static uint32_t pmmap_size = 0;

uint32_t* pmmap;

void pmm_init(uint32_t pmmap_addr, size_t size) {
    mem_size = size;
    max_blocks = KB_TO_BLOCK(mem_size);
    used_blocks = max_blocks;
    pmmap = (uint32_t *) pmmap_addr;

    pmmap_size = max_blocks / PM_MANAGER_BLOCKS_PER_BYTE;
    if (max_blocks % PM_MANAGER_BLOCKS_PER_BYTE) {
        ++pmmap_size;
    }

    memset(pmmap, 0xFF, pmmap_size);
}

void pmm_init_region(uint32_t base, size_t size) {
    size_t blocks = size / PM_MANAGER_BLOCK_SIZE;
    uint32_t align = base / PM_MANAGER_BLOCK_SIZE;

    for (size_t i = 0; i < blocks; ++i) {
        bitmap_unset(pmmap, align++);
        --used_blocks;
    }

    bitmap_set(pmmap, 0);
}

void pmm_deinit_region(uint32_t base, size_t size) {
    size_t blocks = size / PM_MANAGER_BLOCK_SIZE;
    size_t align = base / PM_MANAGER_BLOCK_SIZE;

    for (size_t i = 0; i < blocks; ++i) {
        bitmap_set(pmmap, align++);
        ++used_blocks;
    }
}

void pmm_deinit_kernel(void) {
    extern uint8_t *_kernel_start;
    extern uint8_t *_kernel_end;

    size_t kernel_size = (size_t) &_kernel_end - (size_t) &_kernel_start;

    uint32_t pmmap_size_aligned = pmmap_size;
    if (!IS_ALIGNED(pmmap_size_aligned, PM_MANAGER_BLOCK_SIZE)) {
        pmmap_size_aligned = ALIGN(pmmap_size_aligned, PM_MANAGER_BLOCK_SIZE);
    }

    pmm_deinit_region((uint32_t) &_kernel_start, kernel_size);
    pmm_deinit_region((uint32_t) &_kernel_end, pmmap_size_aligned);
}

void* pmm_alloc_block(void) {
    if (used_blocks - max_blocks <= 0)
        return NULL;

    int p_index = bitmap_first_free(pmmap, max_blocks);

    if (p_index == -1)
        return NULL;

    bitmap_set(pmmap, p_index);
    ++used_blocks;

    return (void*) (PM_MANAGER_BLOCK_SIZE * p_index);
}

void pmm_free_block(void *block) {
    if (block == NULL)
        return;

    uint32_t block_addr = (uint32_t) block;

    int index = block_addr / PM_MANAGER_BLOCK_SIZE;
    bitmap_unset(pmmap, index);

    --used_blocks;
}