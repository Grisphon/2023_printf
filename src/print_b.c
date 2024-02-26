#include "function.h"

int print_b(int fd, va_list list)
{
    int nb;

    nb = va_arg(list, int);
    return print_base(nb, "01", fd);
}
