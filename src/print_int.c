#include "function.h"

int print_int(int fd, va_list list)
{
    int d;

    d = va_arg(list, int);
    return print_base(d, "0123456789", fd);
}
