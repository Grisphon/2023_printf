#include <unistd.h>
#include "stu.h"

static void tc_putchar(char c)
{
    write(1, &c, 1);
}

static int get_digit(int nb, int index, int len_base)
{
    int result;

    if (nb < 0)
        nb = nb * -1;
    while (index > 0) {
        nb = nb / len_base;
        index = index - 1;
    }
    result = nb % len_base;
    return result;
}

static int nb_len(int nb, int len_base)
{
    int len;

    len = 0;
    if (nb == 0)
        return 1;
    if (nb < 0)
        nb = nb * -1;
    while (nb > 0) {
        nb = nb / len_base;
        len = len + 1;
    }
    return len;
}

int print_base(int nb, char *base)
{
    int len;
    int count;
    int len_base;

    len_base = stu_strlen(base);
    len = nb_len(nb, len_base);
    count = 0;
    if (nb < 0) {
        count = count + 1;
        tc_putchar('-');
    }
    while (len > 0) {
        tc_putchar(base[get_digit(nb, len - 1, len_base)]);
        len = len - 1;
        count = count + 1;
    }
    return count;
}

