multiline_comment|/* $Id: byteorder.h,v 1.8 1997/12/18 02:44:14 ecd Exp $ */
macro_line|#ifndef _SPARC64_BYTEORDER_H
DECL|macro|_SPARC64_BYTEORDER_H
mdefine_line|#define _SPARC64_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#ifdef __GNUC__
DECL|function|___arch__swab16p
r_static
id|__inline__
id|__u16
id|___arch__swab16p
c_func
(paren
id|__u16
op_star
id|addr
)paren
(brace
id|__u16
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;lduha [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PL
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|___arch__swab32p
r_static
id|__inline__
id|__u32
id|___arch__swab32p
c_func
(paren
id|__u32
op_star
id|addr
)paren
(brace
id|__u32
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;lduwa [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PL
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|___arch__swab64p
r_static
id|__inline__
id|__u64
id|___arch__swab64p
c_func
(paren
id|__u64
op_star
id|addr
)paren
(brace
id|__u64
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;ldxa [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PL
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|macro|__arch__swab16p
mdefine_line|#define __arch__swab16p(x) ___arch__swab16p(x)
DECL|macro|__arch__swab32p
mdefine_line|#define __arch__swab32p(x) ___arch__swab32p(x)
DECL|macro|__arch__swab64p
mdefine_line|#define __arch__swab64p(x) ___arch__swab64p(x)
DECL|macro|__BYTEORDER_HAS_U64__
mdefine_line|#define __BYTEORDER_HAS_U64__
macro_line|#endif /* __GNUC__ */
macro_line|#include &lt;linux/byteorder/big_endian.h&gt;
macro_line|#endif /* _SPARC64_BYTEORDER_H */
eof
