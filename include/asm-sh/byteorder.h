macro_line|#ifndef __ASM_SH_BYTEORDER_H
DECL|macro|__ASM_SH_BYTEORDER_H
mdefine_line|#define __ASM_SH_BYTEORDER_H
multiline_comment|/*&n; * Copyright (C) 1999  Niibe Yutaka&n; */
macro_line|#include &lt;asm/types.h&gt;
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
l_string|&quot;swap.b&t;%0, %0&bslash;n&bslash;t&quot;
l_string|&quot;swap.w %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;swap.b %0, %0&quot;
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
l_string|&quot;swap.b %0, %0&quot;
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
DECL|function|___arch__swab64
r_static
r_inline
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
comma
id|w
suffix:semicolon
id|v.u
op_assign
id|val
suffix:semicolon
id|w.s.b
op_assign
id|___arch__swab32
c_func
(paren
id|v.s.a
)paren
suffix:semicolon
id|w.s.a
op_assign
id|___arch__swab32
c_func
(paren
id|v.s.b
)paren
suffix:semicolon
r_return
id|w.u
suffix:semicolon
)brace
DECL|macro|__arch__swab64
mdefine_line|#define __arch__swab64(x) ___arch__swab64(x)
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
macro_line|#ifdef __LITTLE_ENDIAN__
macro_line|#include &lt;linux/byteorder/little_endian.h&gt;
macro_line|#else
macro_line|#include &lt;linux/byteorder/big_endian.h&gt;
macro_line|#endif
macro_line|#endif /* __ASM_SH_BYTEORDER_H */
eof
