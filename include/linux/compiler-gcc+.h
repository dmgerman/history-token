multiline_comment|/* Never include this file directly.  Include &lt;linux/compiler.h&gt; instead.  */
multiline_comment|/*&n; * These definitions are for Ueber-GCC: always newer than the latest&n; * version and hence sporting everything plus a kitchen-sink.&n; */
macro_line|#include &lt;linux/compiler-gcc.h&gt;
DECL|macro|inline
mdefine_line|#define inline&t;&t;&t;__inline__ __attribute__((always_inline))
DECL|macro|__inline__
mdefine_line|#define __inline__&t;&t;__inline__ __attribute__((always_inline))
DECL|macro|__inline
mdefine_line|#define __inline&t;&t;__inline__ __attribute__((always_inline))
DECL|macro|__deprecated
mdefine_line|#define __deprecated&t;&t;__attribute__((deprecated))
DECL|macro|__attribute_used__
mdefine_line|#define __attribute_used__&t;__attribute__((__used__))
DECL|macro|__attribute_pure__
mdefine_line|#define __attribute_pure__&t;__attribute__((pure))
eof
