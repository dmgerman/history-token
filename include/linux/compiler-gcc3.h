multiline_comment|/* Never include this file directly.  Include &lt;linux/compiler.h&gt; instead.  */
multiline_comment|/* These definitions are for GCC v3.x.  */
macro_line|#include &lt;linux/compiler-gcc.h&gt;
macro_line|#if __GNUC_MINOR__ &gt;= 1
DECL|macro|inline
macro_line|# define inline&t;&t;__inline__ __attribute__((always_inline))
DECL|macro|__inline__
macro_line|# define __inline__&t;__inline__ __attribute__((always_inline))
DECL|macro|__inline
macro_line|# define __inline&t;__inline__ __attribute__((always_inline))
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
eof
