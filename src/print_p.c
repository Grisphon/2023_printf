#include "function.h"
#include <unistd.h>

int print_p(int fd, va_list list, struct flag *flag_printf)
{
    long pointeur;
    (void) flag_printf;

    pointeur = (long) va_arg(list, void *);
    if (pointeur == 0)
        return write(fd, "(null)", 6);
    write(fd, "0x", 2);
    return print_base(pointeur, "0123456789abcdef", fd) + 2;
}

