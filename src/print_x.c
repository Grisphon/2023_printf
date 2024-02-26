#include "function.h"

int print_x(int fd, va_list list)
{
    int nb;

    nb = va_arg(list, int);
    return print_base(nb, "0123456789ABCDEF", fd);
}
