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


Test(stu_print, mod_char, .init = redirect_all_std) {
    cr_assert(eq(stu_dprintf(1, "%c\n", 't'), 2));
    cr_assert_stdout_eq_str("t\n");
}

Test(stu_print, mod_str, .init = redirect_all_std) {
    cr_assert(eq(stu_dprintf(1, "%s\n", "je suis un test"), 16));
    cr_assert_stdout_eq_str("je suis un test\n");
}


Test(stu_print, mod_str_dec, .init = redirect_all_std) {
    cr_assert(eq(i32, stu_dprintf(1, "Pomme %d %s !\n", 3, "zdeh"), 15));
    cr_assert_stdout_eq_str("Pomme 3 zdeh !\n");
}

Test(stu_print, no_mod, .init = redirect_all_std) {
    cr_assert(eq(i32, stu_dprintf(1, "Je % heu ?\n"), 10));
    cr_assert_stdout_eq_str("Je  heu ?\n");
}

Test(stu_print, mod_ptr) {
    char *ptr = "i will survive";
    char *ref;
    int refsize;

    ref = malloc(sizeof(char) * 20);
    refsize = snprintf(ref, 19, "%p\n", ptr);
    cr_log_warn("%p\n", ptr);
    cr_assert(eq(i32, stu_dprintf(1, "%p\n", ptr), refsize));
    free(ref);
}

Test(stu_print, mod_ptr_null) {
    char *ptr = NULL;

    cr_assert(eq(i32, stu_dprintf(1, "%p\n", ptr), 7));
}

Test(stu_print, mod_dec, .init = redirect_all_std) {
    cr_assert(eq(stu_dprintf(1, "%d\n", 100), 4));
    cr_assert_stdout_eq_str("100\n");
}

Test(stu_print, mod_dec_signed, .init = redirect_all_std) {
    cr_assert(eq(i32, stu_dprintf(1, "%+d\n", 100), 5));
    cr_assert_stdout_eq_str("+100\n");
}

Test(stu_print, mod_str_signed, .init = redirect_all_std) {
    cr_assert(eq(stu_dprintf(1, "%+s\n", "just do it"), 11));
    cr_assert_stdout_eq_str("just do it\n");
}

Test(stu_print, mod_bin, .init = redirect_all_std) {
    cr_assert(eq(stu_dprintf(1, "%b\n", 12), 5));
    cr_assert_stdout_eq_str("1100\n");
}

Test(stu_print, mod_oct, .init = redirect_all_std) {
    cr_assert(eq(stu_dprintf(1, "%o\n", 12), 3));
    cr_assert_stdout_eq_str("14\n");
}

Test(stu_print, mod_hex, .init = redirect_all_std) {
    cr_assert(eq(stu_dprintf(1, "%x\n", 31), 3));
    cr_assert_stdout_eq_str("1F\n");
}
