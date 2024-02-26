#include "function.h"
#include <unistd.h>
#include "stu.h"
int print_str(int fd, va_list list)
{
    char *s;

    s = va_arg(list, char *);
    return write(fd, s, stu_strlen(s));
}
