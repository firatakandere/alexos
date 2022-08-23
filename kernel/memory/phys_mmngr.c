#include <stdint.h>
#include <phys_mmngr.h>
#include <virt_mmngr.h>

static uint8_t pmm_running;
static uintptr_t pmm_pos;

static uintptr_t *pmm_page_stack_max = (uintptr_t *) PMM_PAGE_STACK;
static uintptr_t *pmm_page_stack_ptr = (uintptr_t *) PMM_PAGE_STACK;

uintptr_t pmm_alloc_page() {
    if (pmm_running == 0) {
        pmm_pos += PAGE_SIZE;
        return pmm_pos - PAGE_SIZE;
    }

    if (pmm_page_stack_ptr == (uintptr_t *) PMM_PAGE_STACK) {
        // @todo out of memory! panic
    }

    --pmm_page_stack_ptr;

    if (pmm_page_stack_ptr <= (pmm_page_stack_max - PAGE_STACK_ENTRIES_PER_PAGE)) {
        pmm_page_stack_max -= PAGE_STACK_ENTRIES_PER_PAGE;
        uintptr_t ret = vmm_page_get((uintptr_t) pmm_page_stack_max) & PAGE_MASK;

        vmm_page_set(ret, 0);
        return ret;
    }

    return *pmm_page_stack_ptr;
}

void pmm_free_page(uintptr_t page) {
    page &= PAGE_MASK;

    if (page < pmm_pos)
        return;

    if (pmm_page_stack_ptr >= pmm_page_stack_max) {
        vmm_page_set((uintptr_t)pmm_page_stack_max, vmm_page_val(page, PAGE_PRESENT | PAGE_WRITE));
        pmm_page_stack_max = pmm_page_stack_max + PAGE_STACK_ENTRIES_PER_PAGE;
    } else {
        *pmm_page_stack_ptr++ = page;
    }

    pmm_running = 1;
}

void pmm_init(multiboot_tag_basic_meminfo_t *mboot) {
    pmm_pos = (mboot->mem_upper + PAGE_SIZE) & PAGE_MASK;
    pmm_running = 0;
}