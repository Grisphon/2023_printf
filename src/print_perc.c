#include <unistd.h>
#include "function.h"

int print_perc(int fd, va_list list)
{
    (void) list;

    return write(fd, "%", 1);
}
