#include <unistd.h>
#include <stdarg.h>
#include "stu.h"
#include "function.h"

int tc_putchar(char c)
{
   return write(1, &c, 1);
}

struct mod_table_row {
    char mod;
    int (*fptr)(va_list list);
};


int print_char(va_list list)
{
    char c;

    c = va_arg(list, int);
    return tc_putchar(c);
}

int print_int(va_list list)
{
    int d;

    d = va_arg(list, int);
    return print_base10(d);
}

int print_str(va_list list)
{
    char *s;

    s = va_arg(list, char *);
    return write(1, s, stu_strlen(s));
}

int print_perc(va_list list)
{
    (void) list;

    return write(1, "%", 1);
}

int print_x(va_list list)
{
    int nb;

    nb = va_arg(list, int);
    return print_base(nb, "0123456789ABCDEF");
}

int print_b(va_list list)
{
    int nb;

    nb = va_arg(list, int);
    return print_base(nb, "01");
}

int print_o(va_list list)
{
    int nb;

    nb = va_arg(list, int);
    return print_base(nb, "01234567");
}

/*
 * int print_x(va_list list)
 * {
 *     (void) list;
 * 
 *     return write(1, "%", 1);
 * }
 */


const struct mod_table_row MOD_TAB[] = {
    {'c', print_char},
    {'d', print_int},
    {'s', print_str},
    {'%', print_perc},
    {'o', print_o},
    {'b', print_b},
    {'x', print_x},
};

const unsigned int MOD_TAB_LEN =
    sizeof(MOD_TAB) / sizeof(struct mod_table_row);

static int detecte_function(const char *pattern, unsigned int count,
                            va_list liste)
{
    unsigned int idx;
    int size;

    idx = 0;
    size = 0;
    if (pattern[count] == '%') {
        while (idx < MOD_TAB_LEN) {
            if (MOD_TAB[idx].mod == pattern[count + 1]){
                size += MOD_TAB[idx].fptr(liste);
                idx = 8;
            }
            idx += 1;
        }
    }
    if (idx < 7)
        size += write(1, &pattern[count], 1);
    return size;
}

int stu_dprintf(const char *pattern, ...)
{
    va_list liste;
    unsigned int count;
    int size;

    va_start(liste, pattern);
    count = 0;
    size = 0;
    while (count < stu_strlen(pattern)) {
        size += detecte_function(pattern, count, liste);
        if (pattern[count] == '%')
            count += 1;
        count += 1;
    }
    va_end(liste);
    return size;
}
