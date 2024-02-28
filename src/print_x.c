#include "function.h"

int print_x(int fd, va_list list, struct flag *flag_printf)
{
    int nb;
    (void) flag_printf;

    nb = va_arg(list, int);
    return print_base(nb, "0123456789ABCDEF", fd);
}


