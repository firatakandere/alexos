#include <stdint.h>

#define MULTIBOOT2_BOOTLOADER_MAGIC 0x36d76289

#define MULTIBOOT_TAG_TYPE_END               0
#define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO     4

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