multiline_comment|/* Symbol versioning nastiness.  */
DECL|macro|__SYMBOL_VERSION
mdefine_line|#define __SYMBOL_VERSION(x)       __ver_ ## x
DECL|macro|__VERSIONED_SYMBOL2
mdefine_line|#define __VERSIONED_SYMBOL2(x,v)  x ## _R ## v
DECL|macro|__VERSIONED_SYMBOL1
mdefine_line|#define __VERSIONED_SYMBOL1(x,v)  __VERSIONED_SYMBOL2(x,v)
DECL|macro|__VERSIONED_SYMBOL
mdefine_line|#define __VERSIONED_SYMBOL(x)     __VERSIONED_SYMBOL1(x,__SYMBOL_VERSION(x))
macro_line|#ifndef _set_ver
DECL|macro|_set_ver
mdefine_line|#define _set_ver(x)&t;&t;  __VERSIONED_SYMBOL(x)
macro_line|#endif
eof
