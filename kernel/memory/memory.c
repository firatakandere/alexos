#include <memory.h>

uint32_t align_to(uint32_t n, uint32_t align) {
  if (n % align == 0) {
    return n;
  }

  return n + (align - n % align);
}

void* memset(void* bufptr, int32_t value, size_t size)
{
  uint8_t* buf = (uint8_t*) bufptr;
  for (size_t i = 0; i < size; ++i)
    buf[i] = (uint8_t) value;
  return bufptr;
}

void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size) {
    unsigned char* dst = (unsigned char*) dstptr;
    const unsigned char* src = (const unsigned char*) srcptr;
    for (size_t i = 0; i < size; ++i) {
        dst[i] = src[i];
    }
    return dstptr;
}
