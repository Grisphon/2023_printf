#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "stu.h"
#include "function.h"

//%c pour les caractères individuels ;
//%s pour les chaînes de caractères ;
//%d pour les entiers à afficher en base 10 ;
//%p pour les pointeurs à afficher en base 16 ;
//%b pour les entiers à afficher en binaire ;
//%o pour les entiers à afficher en base 8 ;


static void redirect_all_std(void)
{
    cr_redirect_stdout();
}


Test(stu_print, c, .init = redirect_all_std) {
    cr_assert(eq(stu_dprintf("%c\n", 't'), 2));
    cr_assert_stdout_eq_str("t\n");
}

Test(stu_print, s, .init = redirect_all_std) {
    cr_assert(eq(stu_dprintf("%s\n", "je suis un test"), 16));
    cr_assert_stdout_eq_str("je suis un test\n");
}

/*
 * Test(stu_print, p, .init = redirect_all_std) {
 *     char *ptr = "i will survive";
 * 
 *     cr_assert(eq(stu_dprintf("%p\n", ptr), ?????));
 *     cr_assert_stdout_eq_str("?????\n");
 * }
 */

Test(stu_print, d, .init = redirect_all_std) {
    cr_assert(eq(stu_dprintf("%d\n", 100), 4));
    cr_assert_stdout_eq_str("100\n");
}

Test(stu_print, b, .init = redirect_all_std) {
    cr_assert(eq(stu_dprintf("%b\n", 12), 5));
    cr_assert_stdout_eq_str("1100\n");
}

Test(stu_print, o, .init = redirect_all_std) {
    cr_assert(eq(stu_dprintf("%o\n", 12), 3));
    cr_assert_stdout_eq_str("14\n");
}

Test(stu_print, x, .init = redirect_all_std) {
    cr_assert(eq(stu_dprintf("%x\n", 31), 3));
    cr_assert_stdout_eq_str("1F\n");
}
