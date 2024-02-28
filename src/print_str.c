#include "function.h"
#include <unistd.h>
#include "stu.h"

int print_str(int fd, va_list list, struct flag *flag_printf)
{
    char *s;
    (void) flag_printf;

    s = va_arg(list, char *);
    return write(fd, s, stu_strlen(s));
}

