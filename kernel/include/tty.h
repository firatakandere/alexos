#ifndef TTY_H
#define TTY_H

#include <stdarg.h>

/* VGA STUFF */
#define COLUMNS   80
#define LINES     24
#define ATTR      7
#define VIDEO     0x000B8000

int printf(char const *format, ...);
void terminal_cls(void);

#endif // TTY_H