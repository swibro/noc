#include "uthash.h"
#include "keywords.h"

struct type_void    type_void    = { 1,  "void" };
struct type_char    type_char    = { 2,  "char" };
struct type_schar   type_schar   = { 3,  "signed char" };
struct type_uchar   type_uchar   = { 4,  "unsigned char" };
struct type_short   type_short   = { 5,  "short" };
struct type_ushort  type_ushort  = { 6,  "unsigned short" };
struct type_int     type_int     = { 7,  "int" };
struct type_uint    type_uint    = { 8,  "unsigned int" };
struct type_long    type_long    = { 9,  "long" };
struct type_ulong   type_ulong   = { 10, "unsigned long" };
struct type_llong   type_llong   = { 11, "long long" };
struct type_ullong  type_ullong  = { 12, "unsigned long long" };
struct type_float   type_float   = { 13, "float" };
struct type_double  type_double  = { 14, "double" };
struct type_ldouble type_ldouble = { 15, "long double" };
struct kw_if        kw_if        = { 16,  "if" };
struct kw_else      kw_else      = { 17,  "else" };
struct kw_switch    kw_switch    = { 18,  "switch" };
struct kw_case      kw_case      = { 19,  "case" };
struct kw_default   kw_default   = { 20,  "default" };
struct kw_for       kw_for       = { 21,  "for" };
struct kw_while     kw_while     = { 22,  "while" };
struct kw_do        kw_do        = { 23,  "do" };
struct kw_goto      kw_goto      = { 24,  "goto" };
struct kw_continue  kw_continue  = { 25, "continue" };
struct kw_break     kw_break     = { 26, "break" };
struct kw_return    kw_return    = { 27, "return" };



void *kw_table = NULL;

void init_keywords() {
    HASH_ADD_KEYPTR(hh, kw_table, type_void.name,    strlen(type_void.name),    &type_void);
    HASH_ADD_KEYPTR(hh, kw_table, type_char.name,    strlen(type_char.name),    &type_char);
    HASH_ADD_KEYPTR(hh, kw_table, type_schar.name,   strlen(type_schar.name),   &type_schar);
    HASH_ADD_KEYPTR(hh, kw_table, type_uchar.name,   strlen(type_uchar.name),   &type_uchar);
    HASH_ADD_KEYPTR(hh, kw_table, type_short.name,   strlen(type_short.name),   &type_short);
    HASH_ADD_KEYPTR(hh, kw_table, type_ushort.name,  strlen(type_ushort.name),  &type_ushort);
    HASH_ADD_KEYPTR(hh, kw_table, type_int.name,     strlen(type_int.name),     &type_int);
    HASH_ADD_KEYPTR(hh, kw_table, type_uint.name,    strlen(type_uint.name),    &type_uint);
    HASH_ADD_KEYPTR(hh, kw_table, type_long.name,    strlen(type_long.name),    &type_long);
    HASH_ADD_KEYPTR(hh, kw_table, type_ulong.name,   strlen(type_ulong.name),   &type_ulong);
    HASH_ADD_KEYPTR(hh, kw_table, type_llong.name,   strlen(type_llong.name),   &type_llong);
    HASH_ADD_KEYPTR(hh, kw_table, type_ullong.name,  strlen(type_ullong.name),  &type_ullong);
    HASH_ADD_KEYPTR(hh, kw_table, type_float.name,   strlen(type_float.name),   &type_float);
    HASH_ADD_KEYPTR(hh, kw_table, type_double.name,  strlen(type_double.name),  &type_double);
    HASH_ADD_KEYPTR(hh, kw_table, type_ldouble.name, strlen(type_ldouble.name), &type_ldouble);
    HASH_ADD_KEYPTR(hh, kw_table, kw_if.name,        strlen(kw_if.name),        &kw_if);
    HASH_ADD_KEYPTR(hh, kw_table, kw_else.name,      strlen(kw_else.name),      &kw_else);
    HASH_ADD_KEYPTR(hh, kw_table, kw_switch.name,    strlen(kw_switch.name),    &kw_switch);
    HASH_ADD_KEYPTR(hh, kw_table, kw_case.name,      strlen(kw_case.name),      &kw_case);
    HASH_ADD_KEYPTR(hh, kw_table, kw_default.name,   strlen(kw_default.name),   &kw_default);
    HASH_ADD_KEYPTR(hh, kw_table, kw_for.name,       strlen(kw_for.name),       &kw_for);
    HASH_ADD_KEYPTR(hh, kw_table, kw_while.name,     strlen(kw_while.name),     &kw_while);
    HASH_ADD_KEYPTR(hh, kw_table, kw_do.name,        strlen(kw_do.name),        &kw_do);
    HASH_ADD_KEYPTR(hh, kw_table, kw_goto.name,      strlen(kw_goto.name),      &kw_goto);
    HASH_ADD_KEYPTR(hh, kw_table, kw_continue.name,  strlen(kw_continue.name),  &kw_continue);
    HASH_ADD_KEYPTR(hh, kw_table, kw_break.name,     strlen(kw_break.name),     &kw_break);
    HASH_ADD_KEYPTR(hh, kw_table, kw_return.name,    strlen(kw_return.name),    &kw_return);
}

