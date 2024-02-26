#include <unistd.h>
#include <stdarg.h>
#include "stu.h"
#include "function.h"

int tc_putchar(char c, int fd)
{
   return write(fd, &c, 1);
}

struct mod_table_row {
    char mod;
    int (*fptr)(int fd, va_list list);
};


int print_char(int fd, va_list list)
{
    char c;

    c = va_arg(list, int);
    return tc_putchar(c, fd);
}

int print_int(int fd, va_list list)
{
    int d;

    d = va_arg(list, int);
    return print_base(d, "0123456789", fd);
}

int print_str(int fd, va_list list)
{
    char *s;

    s = va_arg(list, char *);
    return write(fd, s, stu_strlen(s));
}

int print_perc(int fd, va_list list)
{
    (void) list;

    return write(fd, "%", 1);
}

int print_x(int fd, va_list list)
{
    int nb;

    nb = va_arg(list, int);
    return print_base(nb, "0123456789ABCDEF", fd);
}

int print_b(int fd, va_list list)
{
    int nb;

    nb = va_arg(list, int);
    return print_base(nb, "01", fd);
}

int print_o(int fd, va_list list)
{
    int nb;

    nb = va_arg(list, int);
    return print_base(nb, "01234567", fd);
}

int print_p(int fd, va_list list)
{
    long pointeur;

    pointeur = (long) va_arg(list, void *);
    write(fd, "0x", 2);
    return print_base(pointeur, "0123456789abcdef", fd);
}


const struct mod_table_row MOD_TAB[] = {
    {'c', print_char},
    {'d', print_int},
    {'s', print_str},
    {'%', print_perc},
    {'o', print_o},
    {'b', print_b},
    {'x', print_x},
    {'p', print_p},
};

const unsigned int MOD_TAB_LEN =
    sizeof(MOD_TAB) / sizeof(struct mod_table_row);

static int detecte_function(int fd, const char *pattern, unsigned int count,
                            va_list liste)
{
    unsigned int idx;
    int size;

    idx = 0;
    size = 0;
    if (pattern[count] == '%') {
        while (idx < MOD_TAB_LEN) {
            if (MOD_TAB[idx].mod == pattern[count + 1]){
                size += MOD_TAB[idx].fptr(fd, liste);
                idx = 8;
            }
            idx += 1;
        }
    }
    if (idx < 7)
        size += write(fd, &pattern[count], 1);
    return size;
}

int stu_dprintf(int fd, const char *pattern, ...)
{
    va_list liste;
    unsigned int count;
    int size;

    va_start(liste, pattern);
    count = 0;
    size = 0;
    while (count < stu_strlen(pattern)) {
        size += detecte_function(fd, pattern, count, liste);
        if (pattern[count] == '%')
            count += 1;
        count += 1;
    }
    va_end(liste);
    return size;
}
