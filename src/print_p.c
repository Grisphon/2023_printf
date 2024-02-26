#include "function.h"
#include <unistd.h>

int print_p(int fd, va_list list)
{
    long pointeur;

    pointeur = (long) va_arg(list, void *);
    write(fd, "0x", 2);
    return print_base(pointeur, "0123456789abcdef", fd) + 2;
}
