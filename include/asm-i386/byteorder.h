macro_line|#ifndef _I386_BYTEORDER_H
DECL|macro|_I386_BYTEORDER_H
mdefine_line|#define _I386_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __GNUC__
multiline_comment|/* For avoiding bswap on i386 */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#endif
DECL|function|___arch__swab32
r_static
id|__inline__
id|__const__
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
DECL|function|___arch__swab16
r_static
id|__inline__
id|__const__
id|__u16
id|___arch__swab16
c_func
(paren
id|__u16
id|x
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;xchgb %b0,%h0&quot;
multiline_comment|/* swap bytes&t;&t;*/
"&bslash;"
suffix:colon
l_string|&quot;=q&quot;
(paren
id|x
)paren
"&bslash;"
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
"&bslash;"
r_return
id|x
suffix:semicolon
)brace
DECL|macro|__arch__swab32
mdefine_line|#define __arch__swab32(x) ___arch__swab32(x)
DECL|macro|__arch__swab16
mdefine_line|#define __arch__swab16(x) ___arch__swab16(x)
macro_line|#if !defined(__STRICT_ANSI__) || defined(__KERNEL__)
DECL|macro|__BYTEORDER_HAS_U64__
macro_line|#  define __BYTEORDER_HAS_U64__
DECL|macro|__SWAB_64_THRU_32__
macro_line|#  define __SWAB_64_THRU_32__
macro_line|#endif
macro_line|#endif /* __GNUC__ */
macro_line|#include &lt;linux/byteorder/little_endian.h&gt;
macro_line|#endif /* _I386_BYTEORDER_H */
eof
