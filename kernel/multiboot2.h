#include <stdint.h>

#define MULTIBOOT2_BOOTLOADER_MAGIC 0x36d76289

#define MULTIBOOT_TAG_TYPE_END               0
#define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO     4
#define MULTIBOOT_TAG_TYPE_MMAP              6

struct multiboot_tag
{
    uint32_t type;
    uint32_t size;
};

struct multiboot_tag_basic_meminfo
{
    uint32_t type;
    uint32_t size;
    uint32_t mem_lower;
    uint32_t mem_upper;
};

struct multiboot_mmap_entry
{
  uint64_t addr;
  uint64_t len;
#define MULTIBOOT_MEMORY_AVAILABLE              1
#define MULTIBOOT_MEMORY_RESERVED               2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE       3
#define MULTIBOOT_MEMORY_NVS                    4
#define MULTIBOOT_MEMORY_BADRAM                 5
  uint32_t type;
  uint32_t zero;
};

typedef struct multiboot_mmap_entry multiboot_memory_map_t;

struct multiboot_tag_mmap
{
  uint32_t type;
  uint32_t size;
  uint32_t entry_size;
  uint32_t entry_version;
  struct multiboot_mmap_entry entries[0];  
};


// custom utils

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