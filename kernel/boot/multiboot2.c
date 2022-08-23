#include <multiboot2.h>

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