macro_line|#ifndef _CRIS_ARCH_BYTEORDER_H
DECL|macro|_CRIS_ARCH_BYTEORDER_H
mdefine_line|#define _CRIS_ARCH_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
multiline_comment|/* we just define these two (as we can do the swap in a single&n; * asm instruction in CRIS) and the arch-independent files will put&n; * them together into ntohl etc.&n; */
DECL|function|___arch__swab32
r_extern
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
id|__asm__
(paren
l_string|&quot;swapwb %0&quot;
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
DECL|function|___arch__swab16
r_extern
id|__inline__
id|__attribute_const__
id|__u16
id|___arch__swab16
c_func
(paren
id|__u16
id|x
)paren
(brace
id|__asm__
(paren
l_string|&quot;swapb %0&quot;
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
macro_line|#endif
eof
