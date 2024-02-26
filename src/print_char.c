#include "function.h"
#include <unistd.h>
#include <stdarg.h>

int tc_putchar(char c, int fd)
{
   return write(fd, &c, 1);
}

int print_char(int fd, va_list list)
{
    char c;

    c = va_arg(list, int);
    return tc_putchar(c, fd);
}
