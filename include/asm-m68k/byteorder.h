macro_line|#ifndef _M68K_BYTEORDER_H
DECL|macro|_M68K_BYTEORDER_H
mdefine_line|#define _M68K_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __GNUC__
DECL|function|___arch__swab32
r_static
id|__inline__
id|__const__
id|__u32
id|___arch__swab32
c_func
(paren
id|__u32
id|val
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;rolw #8,%0; swap %0; rolw #8,%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|macro|__arch__swab32
mdefine_line|#define __arch__swab32(x) ___arch__swab32(x)
macro_line|#endif
macro_line|#if defined(__GNUC__) &amp;&amp; !defined(__STRICT_ANSI__) || defined(__KERNEL__)
DECL|macro|__BYTEORDER_HAS_U64__
macro_line|#  define __BYTEORDER_HAS_U64__
DECL|macro|__SWAB_64_THRU_32__
macro_line|#  define __SWAB_64_THRU_32__
macro_line|#endif
macro_line|#include &lt;linux/byteorder/big_endian.h&gt;
macro_line|#endif /* _M68K_BYTEORDER_H */
eof
