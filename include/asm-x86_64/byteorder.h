macro_line|#ifndef _X86_64_BYTEORDER_H
DECL|macro|_X86_64_BYTEORDER_H
mdefine_line|#define _X86_64_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __GNUC__
DECL|function|___arch__swab64
r_static
id|__inline__
id|__const__
id|__u64
id|___arch__swab64
c_func
(paren
id|__u64
id|x
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;bswapq %0&quot;
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
r_return
id|x
suffix:semicolon
)brace
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
id|__asm__
c_func
(paren
l_string|&quot;bswapl %0&quot;
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
r_return
id|x
suffix:semicolon
)brace
multiline_comment|/* Do not define swab16.  Gcc is smart enought to recognize &quot;C&quot; version and&n;   convert it into rotation or exhange.  */
DECL|macro|__arch__swab32
mdefine_line|#define __arch__swab32(x) ___arch__swab32(x)
DECL|macro|__arch__swab64
mdefine_line|#define __arch__swab64(x) ___arch__swab64(x)
macro_line|#endif /* __GNUC__ */
DECL|macro|__BYTEORDER_HAS_U64__
mdefine_line|#define __BYTEORDER_HAS_U64__
macro_line|#include &lt;linux/byteorder/little_endian.h&gt;
macro_line|#endif /* _X86_64_BYTEORDER_H */
eof
