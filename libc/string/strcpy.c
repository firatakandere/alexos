#include <string.h>

char* strcpy(char* restrict dest, char* restrict src) {
    char c;
    char *p = dest;

    while ((c = *src++)) {
        *p++ = c;
    }

    *p = '\0';
    return dest;
}