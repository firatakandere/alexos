#include <stdarg.h>

/* VGA STUFF */
#define COLUMNS   80
#define LINES     24
#define ATTR      7
#define VIDEO     0xB8000

static int x_pos;
static int y_pos;
static volatile uint8_t* v_mem;

void terminal_cls(void)
{
  v_mem = (uint8_t*) VIDEO;

  for (int i = 0; i < COLUMNS * LINES * 2; ++i)
    *(v_mem + i) = 0;
  
  x_pos = 0;
  y_pos = 0;
}

void terminal_putchar(char c)
{
  if (c == '\n' || c == '\r')
  {
newline:
    x_pos = 0;
    ++y_pos;
    if (y_pos >= LINES)
      y_pos = 0;
    return;
  }

  *(v_mem + (x_pos + y_pos * COLUMNS) * 2) = c & 0xFF;
  *(v_mem + (x_pos + y_pos * COLUMNS) * 2 + 1) = ATTR;

  ++x_pos;
  if (x_pos >= COLUMNS)
    goto newline;
}

void terminal_write(const char* data)
{
  int c;
  while ((c = *data++) != 0)
  {
    terminal_putchar(c);
  }
}

//-----------------------------------------------------
// Minimal printf implementation for debugging purposes
//-----------------------------------------------------

int normalize(double *val) {
    int exponent = 0;
    double value = *val;

    while (value >= 1.0) {
        value /= 10.0;
        ++exponent;
    }

    while (value < 0.1) {
        value *= 10.0;
        --exponent;
    }
    *val = value;
    return exponent;
}

void ftoa_fixed(char *buffer, double value) {
    int exponent = 0;
    int places = 0;
    const int width = 4;

    if (value == 0.0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    if (value < 0.0) {
        *buffer++ = '-';
        value *= -1;
    }

    exponent = normalize(&value);

    while (exponent > 0) { 
        int digit = value * 10;
        *buffer++ = digit + '0';
        value = value * 10 - digit;
        ++places;
        --exponent;
    }

    if (places == 0)
        *buffer++ = '0';

    *buffer++ = '.';

    while (exponent < 0 && places < width) {
        *buffer++ = '0';
        --exponent;
        ++places;
    }

    while (places < width) {
        int digit = value * 10.0;
        *buffer++ = digit + '0';
        value = value * 10.0 - digit;
        ++places;
    }
    *buffer = '\0';
}

int itoa(int value, char  *sp, int radix) {
    char tmp[16];
    char *tp = tmp;
    int i;
    unsigned v;

    int sign = (radix == 10 && value < 0);
    if (sign) {
        v = -value;
    } else {
        v = (unsigned) value;
    }

    while (v || tp == tmp) {
        i = v % radix;
        v /= radix;
        if (i < 10) {
            *tp++ = i + '0';
        } else {
            *tp++ = i + 'a' - 10;
        }
    }

    int len = tp - tmp;

    if (sign) {
        *sp++ = '-';
        len++;
    }

    while (tp > tmp)
        *sp++ = *--tp;

    return len;
}

unsigned int strlen(const char *s) {
    unsigned int count = 0;
    while (*s++ != '\0'){
        ++count;
    }

    return count;
}

int vprintf(char const *format, va_list arg) {
    int int_temp;
    char char_temp;
    char *string_temp;
    double double_temp;

    char ch;
    int length = 0;

    char buffer[512];

    while (ch = *format++) {
        if (ch == '%') {
            switch (ch = *format++) {
                case '%':
                    terminal_putchar('%');
                    ++length;
                    break;
                case 'c':
                    char_temp = va_arg(arg, int);
                    terminal_putchar(char_temp);
                    ++length;
                    break;
                case 's':
                    string_temp = va_arg(arg, char*);
                    terminal_write(string_temp);
                    length += strlen(string_temp);
                    break;
                case 'd':
                    int_temp = va_arg(arg, int);
                    itoa(int_temp, buffer, 10);
                    terminal_write(buffer);
                    length += strlen(buffer);
                    break;
                case 'x':
                    int_temp = va_arg(arg, int);
                    itoa(int_temp, buffer, 16);
                    terminal_write(buffer);
                    length += strlen(buffer);
                    break;
                case 'f':
                    double_temp = va_arg(arg, double);
                    ftoa_fixed(buffer, double_temp);
                    terminal_write(buffer);
                    length += strlen(buffer);
                    break;
            }
        } else {
            terminal_putchar(ch);
            ++length;
        }
    }

    return length;
}

int printf(char const *format, ...) {
    va_list arg;
    int length;

    va_start(arg, format);
    length = vprintf(format, arg);
    va_end(arg);
    return length;
}