multiline_comment|/* Never include this file directly.  Include &lt;linux/compiler.h&gt; instead.  */
multiline_comment|/* These definitions are for GCC v4.x.  */
macro_line|#include &lt;linux/compiler-gcc.h&gt;
DECL|macro|inline
mdefine_line|#define inline&t;&t;&t;inline&t;&t;__attribute__((always_inline))
DECL|macro|__inline__
mdefine_line|#define __inline__&t;&t;__inline__&t;__attribute__((always_inline))
DECL|macro|__inline
mdefine_line|#define __inline&t;&t;__inline&t;__attribute__((always_inline))
DECL|macro|__deprecated
mdefine_line|#define __deprecated&t;&t;__attribute__((deprecated))
DECL|macro|__attribute_used__
mdefine_line|#define __attribute_used__&t;__attribute__((__used__))
DECL|macro|__attribute_pure__
mdefine_line|#define __attribute_pure__&t;__attribute__((pure))
DECL|macro|__attribute_const__
mdefine_line|#define __attribute_const__&t;__attribute__((__const__))
DECL|macro|noinline
mdefine_line|#define  noinline&t;&t;__attribute__((noinline))
DECL|macro|__must_check
mdefine_line|#define __must_check &t;&t;__attribute__((warn_unused_result))
DECL|macro|__compiler_offsetof
mdefine_line|#define __compiler_offsetof(a,b) __builtin_offsetof(a,b)
eof
