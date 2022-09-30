#include <multiboot2.h>
#include <stddef.h>

char* get_memory_type(uint32_t type) {
    switch (type)
    {
    case MULTIBOOT_MEMORY_AVAILABLE:
        return "AVAILABLE";
    case MULTIBOOT_MEMORY_RESERVED:
        return "RESERVED";
    case MULTIBOOT_MEMORY_ACPI_RECLAIMABLE:
        return "ACPI RECLAIMABLE";
    case MULTIBOOT_MEMORY_NVS:
        return "NVS";
    case MULTIBOOT_MEMORY_BADRAM:
        return "BADRAM";
    default:
        return "UNKNOWN";
    }
}

multiboot_tag_t* multiboot_find_tag(unsigned long addr, uint32_t tag_type) {
    multiboot_tag_t* tag;
    for (tag = (multiboot_tag_t*) (addr + 8); tag->type != MULTIBOOT_TAG_TYPE_END; tag = (multiboot_tag_t*) ((uint8_t*) tag + align_to(tag->size, 8))) {
        if (tag->type == tag_type) {
            return tag;
        }
    }

    return NULL;
}
