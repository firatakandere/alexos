#ifndef KERNEL_GDT_H
#define KERNEL_GDT_H

#define GDT_DATA_RO       0x00 // Read-Only
#define GDT_DATA_RDA      0x01 // Read-Only, accessed
#define GDT_DATA_RW       0x02 // Read/Write
#define GDT_DATA_RWA      0x03 // Read/Write, accessed
#define GDT_DATA_ROEXPD   0x04 // Read-Only, expand-down
#define GDT_DATA_ROEXPDA  0x05 // Read-Only, expand-down, accessed
#define GDT_DATA_RWEXPD   0x06 // Read/Write, expand-down
#define GDT_DATA_RWEXPDA  0x07 // Read/Write, expand-down, accessed
#define GDT_CODE_EO       0x08 // Execute-Only
#define GDT_CODE_EOA      0x09 // Execute-Only, accessed
#define GDT_CODE_ER       0x0A // Execute/Read
#define GDT_CODE_ERA      0x0B // Execute/Read, accessed
#define GDT_CODE_EOC      0x0C // Execute-Only, conforming
#define GDT_CODE_EOCA     0x0D // Execute-Only, confirming, accessed
#define GDT_CODE_ERC      0x0E // Execute/Read, conforming
#define GDT_CODE_ERCA     0x0F // Execute/Read, conforming, accessed

#define GDT_DESC(x)       ((x) << 0x04) // Descriptor type (0 for system, 1 for code/data)
#define GDT_PRES(x)       ((x) << 0x07) // Present
#define GDT_PRIV(x)       (((x) & 0x03) << 0x05) // Privilege level (0 - 3)

#define GDT_GRAN(x)       ((x) << 0x07) // Granularity (0 for 1B - 1MB, 1 for 4KB -4GB)
#define GDT_SIZE(x)       ((x) << 0x06) // Size (0 for 16-bit, 1 for 32-bit)
#define GDT_LONG(x)       ((x) << 0x05) // Long mode
#define GDT_RES(x)        ((x) << 0x04) // Available for system use
#define GDT_LIMIT_MASK    0x0f //  mask high 4 bits of limit

#endif // KERNEL_GDT_H
