#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort(void) {

#if defined(__is_libk)
    // @todo add kernel panic.
    printf("Panic: abort()\n");
#else
    // @todo terminate the process similar to SIGABRT
    printf("abort()\n");
#endif

    while(1) {}
    __builtin_unreachable();
}
