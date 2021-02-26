#ifndef _KERNEL_MEMORY_H
#define _KERNEL_MEMORY_H

void pmm_init(uint32_t pmmap_addr, size_t size);
void pmm_deinit_kernel(void);

#endif