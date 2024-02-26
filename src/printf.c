#include <unistd.h>
#include <stdarg.h>
#include "stu.h"
#include "function.h"

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

static int detect_mod(int fd, const char *pattern, unsigned int count,
                            va_list list)
{
    unsigned int idx;
    int size;
    int mod_found;

    mod_found = 0;
    idx = 0;
    size = 0;
    if (pattern[count] == '%') {
        while (idx < MOD_TAB_LEN) {
            if (MOD_TAB[idx].mod == pattern[count + 1]){
                size += MOD_TAB[idx].fptr(fd, list);
                mod_found = 1;
            }
            idx += 1;
        }
    }
    if (mod_found == 0)
        size += write(fd, &pattern[count], 1);
    return size;
}

int stu_dprintf(int fd, const char *pattern, ...)
{
    va_list list;
    unsigned int count;
    int size;

    va_start(list, pattern);
    count = 0;
    size = 0;
    while (count < stu_strlen(pattern)) {
        size += detect_mod(fd, pattern, count, list);
        if (pattern[count] == '%')
            count += 1;
        count += 1;
    }
    va_end(list);
    return size;
}
