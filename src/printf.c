#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
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
                      va_list list, struct flag *printf_flag)
{
    unsigned int idx;
    int size;
    int pathing;
    int mod_found;

    pathing = 1;
    mod_found = 0;
    size = 0;
    if (pattern[count] == '%') {
        while (mod_found == 0 && pattern[count + pathing] != '\0') {
            idx = 0;
            while (idx < MOD_TAB_LEN) {
                if (MOD_TAB[idx].mod == pattern[count + pathing]) {
                    size = MOD_TAB[idx].fptr(fd, list, printf_flag);
                    mod_found = 1;
                    printf_flag->mod_size = pathing;
                } else if ('+' == pattern[count + pathing])
                    printf_flag->is_sign = 1;
                idx += 1;
            }
            pathing += 1;
        }
    } else
        size += write(fd, &pattern[count], 1);
    return size;
}

int stu_dprintf(int fd, const char *pattern, ...)
{
    va_list list;
    unsigned int count;
    int size;
    struct flag *flag_printf;

    flag_printf = flag_create();
    va_start(list, pattern);
    count = 0;
    size = 0;
    while (count < stu_strlen(pattern)) {
        size += detect_mod(fd, pattern, count, list, flag_printf);
        count += 1 + flag_printf->mod_size;
        flag_printf->mod_size = 0;
        flag_printf->is_sign = 0;
    }
    va_end(list);
    free(flag_printf);
    return size;
}
