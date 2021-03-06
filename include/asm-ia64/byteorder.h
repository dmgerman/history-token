macro_line|#ifndef _ASM_IA64_BYTEORDER_H
DECL|macro|_ASM_IA64_BYTEORDER_H
mdefine_line|#define _ASM_IA64_BYTEORDER_H
multiline_comment|/*&n; * Modified 1998, 1999&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;, Hewlett-Packard Co.&n; */
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/intrinsics.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
r_static
id|__inline__
id|__attribute_const__
id|__u64
DECL|function|__ia64_swab64
id|__ia64_swab64
(paren
id|__u64
id|x
)paren
(brace
id|__u64
id|result
suffix:semicolon
id|result
op_assign
id|ia64_mux1
c_func
(paren
id|x
comma
id|ia64_mux1_rev
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_static
id|__inline__
id|__attribute_const__
id|__u32
DECL|function|__ia64_swab32
id|__ia64_swab32
(paren
id|__u32
id|x
)paren
(brace
r_return
id|__ia64_swab64
c_func
(paren
id|x
)paren
op_rshift
l_int|32
suffix:semicolon
)brace
r_static
id|__inline__
id|__attribute_const__
id|__u16
DECL|function|__ia64_swab16
id|__ia64_swab16
c_func
(paren
id|__u16
id|x
)paren
(brace
r_return
id|__ia64_swab64
c_func
(paren
id|x
)paren
op_rshift
l_int|48
suffix:semicolon
)brace
DECL|macro|__arch__swab64
mdefine_line|#define __arch__swab64(x) __ia64_swab64(x)
DECL|macro|__arch__swab32
mdefine_line|#define __arch__swab32(x) __ia64_swab32(x)
DECL|macro|__arch__swab16
mdefine_line|#define __arch__swab16(x) __ia64_swab16(x)
DECL|macro|__BYTEORDER_HAS_U64__
mdefine_line|#define __BYTEORDER_HAS_U64__
macro_line|#include &lt;linux/byteorder/little_endian.h&gt;
macro_line|#endif /* _ASM_IA64_BYTEORDER_H */
eof
