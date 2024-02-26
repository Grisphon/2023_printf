#ifndef FUNCTION_
#define FUNCTION_
#include <stdarg.h>
struct mod_table_row {
    char mod;
    int (*fptr)(int fd, va_list list);
};


int tc_putchar(char c, int fd);
int print_char(int fd, va_list list);
int print_int(int fd, va_list list);
int print_str(int fd, va_list list);
int print_perc(int fd, va_list list);
int print_x(int fd, va_list list);
int print_b(int fd, va_list list);
int print_o(int fd, va_list list);
int print_p(int fd, va_list list);
int print_base(long nb, char *base, int fd);
int stu_dprintf(int fd, const char *pattern, ...);


#endif
