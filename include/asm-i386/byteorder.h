macro_line|#ifndef _I386_BYTEORDER_H
DECL|macro|_I386_BYTEORDER_H
mdefine_line|#define _I386_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#ifdef __GNUC__
multiline_comment|/* For avoiding bswap on i386 */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#endif
DECL|function|___arch__swab32
r_static
id|__inline__
id|__attribute_const__
id|__u32
id|___arch__swab32
c_func
(paren
id|__u32
id|x
)paren
(brace
macro_line|#ifdef CONFIG_X86_BSWAP
id|__asm__
c_func
(paren
l_string|&quot;bswap %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
macro_line|#else
id|__asm__
c_func
(paren
l_string|&quot;xchgb %b0,%h0&bslash;n&bslash;t&quot;
multiline_comment|/* swap lower bytes&t;*/
l_string|&quot;rorl $16,%0&bslash;n&bslash;t&quot;
multiline_comment|/* swap words&t;&t;*/
l_string|&quot;xchgb %b0,%h0&quot;
multiline_comment|/* swap higher bytes&t;*/
suffix:colon
l_string|&quot;=q&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|x
suffix:semicolon
)brace
DECL|function|___arch__swab64
r_static
id|__inline__
id|__attribute_const__
id|__u64
id|___arch__swab64
c_func
(paren
id|__u64
id|val
)paren
(brace
r_union
(brace
r_struct
(brace
id|__u32
id|a
comma
id|b
suffix:semicolon
)brace
id|s
suffix:semicolon
id|__u64
id|u
suffix:semicolon
)brace
id|v
suffix:semicolon
id|v.u
op_assign
id|val
suffix:semicolon
macro_line|#ifdef CONFIG_X86_BSWAP
id|asm
c_func
(paren
l_string|&quot;bswapl %0 ; bswapl %1 ; xchgl %0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|v.s.a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|v.s.b
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|v.s.a
)paren
comma
l_string|&quot;1&quot;
(paren
id|v.s.b
)paren
)paren
suffix:semicolon
macro_line|#else
id|v.s.a
op_assign
id|___arch__swab32
c_func
(paren
id|v.s.a
)paren
suffix:semicolon
id|v.s.b
op_assign
id|___arch__swab32
c_func
(paren
id|v.s.b
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;xchgl %0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|v.s.a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|v.s.b
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|v.s.a
)paren
comma
l_string|&quot;1&quot;
(paren
id|v.s.b
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|v.u
suffix:semicolon
)brace
multiline_comment|/* Do not define swab16.  Gcc is smart enough to recognize &quot;C&quot; version and&n;   convert it into rotation or exhange.  */
DECL|macro|__arch__swab64
mdefine_line|#define __arch__swab64(x) ___arch__swab64(x)
DECL|macro|__arch__swab32
mdefine_line|#define __arch__swab32(x) ___arch__swab32(x)
DECL|macro|__BYTEORDER_HAS_U64__
mdefine_line|#define __BYTEORDER_HAS_U64__
macro_line|#endif /* __GNUC__ */
macro_line|#include &lt;linux/byteorder/little_endian.h&gt;
macro_line|#endif /* _I386_BYTEORDER_H */
eof
