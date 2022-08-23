#include <stdint.h>
#include <stddef.h>

#ifndef MEMORY_H
#define MEMORY_H

void* memset(void* bufptr, int32_t value, size_t size);
void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size);

#endif // MEMORY_H