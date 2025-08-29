#ifndef KEYWORDS_H
#define KEYWORDS_H

struct keyword      { int id; const char *name; UT_hash_handle hh; };
struct type_void    { int id; const char *name; UT_hash_handle hh; };
struct type_char    { int id; const char *name; UT_hash_handle hh; };
struct type_schar   { int id; const char *name; UT_hash_handle hh; };
struct type_uchar   { int id; const char *name; UT_hash_handle hh; };
struct type_short   { int id; const char *name; UT_hash_handle hh; };
struct type_ushort  { int id; const char *name; UT_hash_handle hh; };
struct type_int     { int id; const char *name; UT_hash_handle hh; };
struct type_uint    { int id; const char *name; UT_hash_handle hh; };
struct type_long    { int id; const char *name; UT_hash_handle hh; };
struct type_ulong   { int id; const char *name; UT_hash_handle hh; };
struct type_llong   { int id; const char *name; UT_hash_handle hh; };
struct type_ullong  { int id; const char *name; UT_hash_handle hh; };
struct type_float   { int id; const char *name; UT_hash_handle hh; };
struct type_double  { int id; const char *name; UT_hash_handle hh; };
struct type_ldouble { int id; const char *name; UT_hash_handle hh; };
struct kw_if        { int id; const char *name; UT_hash_handle hh; };
struct kw_else      { int id; const char *name; UT_hash_handle hh; };
struct kw_switch    { int id; const char *name; UT_hash_handle hh; };
struct kw_case      { int id; const char *name; UT_hash_handle hh; };
struct kw_default   { int id; const char *name; UT_hash_handle hh; };
struct kw_for       { int id; const char *name; UT_hash_handle hh; };
struct kw_while     { int id; const char *name; UT_hash_handle hh; };
struct kw_do        { int id; const char *name; UT_hash_handle hh; };
struct kw_goto      { int id; const char *name; UT_hash_handle hh; };
struct kw_continue  { int id; const char *name; UT_hash_handle hh; };
struct kw_break     { int id; const char *name; UT_hash_handle hh; };
struct kw_return    { int id; const char *name; UT_hash_handle hh; };

extern void *kw_table;

void init_keywords();

#endif
