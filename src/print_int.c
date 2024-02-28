#include <stdio.h>
#include "function.h"
#include <unistd.h>

int print_int(int fd, va_list list, struct flag *flag_printf)
{
    int d;

    d = va_arg(list, int);
    if (flag_printf->is_sign == 1 && d > 0)
        return write(1, "+", 1) + print_base(d, "0123456789", fd);
    return print_base(d, "0123456789", fd);
}
