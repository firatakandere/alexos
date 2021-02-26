#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static bool print(const char* data, size_t length) {
    const unsigned char* bytes = (const unsigned char*) data;
    for (size_t i = 0; i < length; ++i)
        if (putchar(bytes[i]) == EOF)
            return false;
    return true;
}

// @todo deprecate with itoa
static inline void dec_to_str(char *buffer, int num) {
    static char digits[] = "0123456789";
    char buffer_int[10], *ptr;

    // Put end of line
    ptr = buffer_int + 9;
    *ptr = '\0';

    do {
        *(--ptr) = digits[num % 10];
        num /= 10;
    } while (num > 0);

    strcpy(buffer, ptr);
}

// @todo deprecate with itoa
static inline void hex_to_str(char *buffer, int num) {
    static char digits[] = "0123456789ABCDEF";
    char buffer_int[9], *ptr;

    // Put end of line
    ptr = buffer_int + 8;
    *ptr = '\0';

    do {
        *(--ptr) = digits[num % 16];
        num /= 16;
    } while (num > 0);

    strcpy(buffer, ptr);
}

int printf(const char* restrict format, ...) {
    va_list parameters;
    va_start(parameters, format);

    int written = 0;

    while (*format != '\0') {
        size_t maxrem = INT_MAX - written;

        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%') {
                ++format;
            }

            size_t amount = 1;

            while (format[amount] && format[amount] != '%')
                ++amount;

            if (maxrem < amount) {
                // @todo EOVERFLOW
                return -1;
            }

            if (!print(format, amount))
                return -1;

            format += amount;
            written += amount;
            continue;
        }

        const char* format_begun_at = format++;

        if (*format == 'c') {
            ++format;
            char c = (char) va_arg(parameters, int);

            if (!maxrem) {
                // @todo EOVERFLOW
                return -1;
            }

            if (!print(&c, sizeof(c)))
                    return -1;

            ++written;
        }
        else if (*format == 's') {
            ++format;
            const char* str = va_arg(parameters, const char*);
            size_t len = strlen(str);
            if (maxrem < len) {
                // @todo EOVERFLOW;
                return -1;
            }

            if (!print(str,len))
                return -1;
            written += len;
        }
        else if (*format == 'd') {
            ++format;
            const int dec = va_arg(parameters, int);
            char buffer[10]; // @todo hardcoded for 32bit
            dec_to_str(buffer, dec);
            size_t len = strlen(buffer);
            if (maxrem < len) {
                // @todo EOVERFLOW;
                return -1;
            }

            if (!print(buffer,len))
                return -1;
            written += len;
        }
        else if (*format == 'x') {
            ++format;
            const int dec = va_arg(parameters, int);
            char buffer[9];
            hex_to_str(buffer, dec);
            size_t len = strlen(buffer);
            if (maxrem < len) {
                return -1;
            }

            if (!print(buffer, len))
                return -1;
            
            written += len;
        }
        else {
            format = format_begun_at;
            size_t len = strlen(format);
            if (maxrem < len) {
                // @todo EOVERFLOW
                return -1;
            }
            if (!print(format, len))
                return -1;

            written += len;
            format += len;
        }
    }

    va_end(parameters);
    return written;
}