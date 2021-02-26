#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/timer.h>
#include <kernel/keyboard.h>

#include <kernel/multiboot.h>
#include <kernel/memory.h>

void check_multiboot(multiboot_info_t* mb_info, uint32_t magic) {
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("Not booted from multiboot bootloader!\n");
        // @todo panic
    }

    if (mb_info == NULL) {
        printf("Multiboot information is empty.\n");
        // @todo panic
    }

    if (!(mb_info->flags & MULTIBOOT_INFO_MEMORY)) {
        printf("Memory is not mapped in multiboot\n");
        // @todo panic
    }
}

void kernel_main(multiboot_info_t* mb_info, uint32_t magic) {
    init_gdt();
    init_idt();
    init_timer(50);
    init_keyboard();
    terminal_initialize();

    check_multiboot(mb_info, magic);

    extern uint32_t _kernel_size;

    printf("Kernel size: %d \n", &_kernel_size);


    uint32_t memory_size = 1024 + mb_info->mem_lower + mb_info->mem_upper;
    printf("Estimated memory size is %d KB \n", memory_size);

    //init_memory_manager(memory_size, 0x100000 + kernel_size * 512);
    extern size_t _kernel_end;
    pmm_init((uint32_t) &_kernel_end, memory_size);


    printf("Physical Memory Map:\n");

    multiboot_memory_map_t* entry = mb_info->mmap_addr;
    while (entry < mb_info->mmap_addr + mb_info->mmap_length) {
        printf("addr_high = 0x%x, addr_low = 0x%x, length_high = 0x%x, length_low = 0x%x, type = 0x%x\n",
        entry->addr_high, entry->addr_low, entry->length_high, entry->length_low, entry->type
        );

        entry = (multiboot_memory_map_t*) ((uint32_t) entry + entry->size + sizeof(entry->size));
    }

    pmm_deinit_kernel();

    printf("Hello, kernel world %d", 2);

    // prevent premature
    for(;;) {
        asm("hlt");
    }
}
