#include <stdlib.h>
#include "function.h"

struct flag *flag_create()
{
    struct flag *flag_printf;

    flag_printf = malloc(sizeof(struct flag));
    flag_printf->is_sign = 0;
    flag_printf->mod_size = 0;
    return flag_printf;
}
