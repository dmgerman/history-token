multiline_comment|/* Never include this file directly.  Include &lt;linux/compiler.h&gt; instead.  */
multiline_comment|/* These definitions are for GCC v3.x.  */
macro_line|#include &lt;linux/compiler-gcc.h&gt;
macro_line|#if __GNUC_MINOR__ &gt;= 1
DECL|macro|inline
macro_line|# define inline&t;&t;inline&t;&t;__attribute__((always_inline))
DECL|macro|__inline__
macro_line|# define __inline__&t;__inline__&t;__attribute__((always_inline))
DECL|macro|__inline
macro_line|# define __inline&t;__inline&t;__attribute__((always_inline))
macro_line|#endif
macro_line|#if __GNUC_MINOR__ &gt; 0
DECL|macro|__deprecated
macro_line|# define __deprecated&t;__attribute__((deprecated))
macro_line|#endif
macro_line|#if __GNUC_MINOR__ &gt;= 3
DECL|macro|__attribute_used__
macro_line|# define __attribute_used__&t;__attribute__((__used__))
macro_line|#else
DECL|macro|__attribute_used__
macro_line|# define __attribute_used__&t;__attribute__((__unused__))
macro_line|#endif
DECL|macro|__attribute_pure__
mdefine_line|#define __attribute_pure__&t;__attribute__((pure))
DECL|macro|__attribute_const__
mdefine_line|#define __attribute_const__&t;__attribute__((__const__))
macro_line|#if __GNUC_MINOR__ &gt;= 1
DECL|macro|noinline
mdefine_line|#define  noinline __attribute__((noinline))
macro_line|#endif
macro_line|#if __GNUC_MINOR__ &gt;= 4
DECL|macro|__must_check
mdefine_line|#define __must_check __attribute__((warn_unused_result))
macro_line|#endif
macro_line|#if __GNUC_MINOR__ &gt;= 5
DECL|macro|__compiler_offsetof
mdefine_line|#define __compiler_offsetof(a,b) __builtin_offsetof(a,b)
macro_line|#endif
eof
