macro_line|#ifndef _S390_BYTEORDER_H
DECL|macro|_S390_BYTEORDER_H
mdefine_line|#define _S390_BYTEORDER_H
multiline_comment|/*&n; *  include/asm-s390/byteorder.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; */
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
id|__u64
id|result
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   lrvg %0,%1&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|___arch__swab64p
r_static
id|__inline__
id|__const__
id|__u64
id|___arch__swab64p
c_func
(paren
id|__u64
op_star
id|x
)paren
(brace
id|__u64
id|result
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   lrvg %0,%1&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|x
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|___arch__swab64s
r_static
id|__inline__
r_void
id|___arch__swab64s
c_func
(paren
id|__u64
op_star
id|x
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;   lrvg 0,%0&bslash;n&quot;
l_string|&quot;   stg  0,%0&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|x
)paren
suffix:colon
suffix:colon
l_string|&quot;0&quot;
)paren
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
id|__u32
id|result
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   lrv  %0,%1&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|___arch__swab32p
r_static
id|__inline__
id|__const__
id|__u32
id|___arch__swab32p
c_func
(paren
id|__u32
op_star
id|x
)paren
(brace
id|__u32
id|result
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   lrv  %0,%1&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|x
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|___arch__swab32s
r_static
id|__inline__
r_void
id|___arch__swab32s
c_func
(paren
id|__u32
op_star
id|x
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;   lrv  0,%0&bslash;n&quot;
l_string|&quot;   st   0,%0&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|x
)paren
suffix:colon
suffix:colon
l_string|&quot;0&quot;
)paren
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
id|__u16
id|result
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   lrvh %0,%1&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|___arch__swab16p
r_static
id|__inline__
id|__const__
id|__u16
id|___arch__swab16p
c_func
(paren
id|__u16
op_star
id|x
)paren
(brace
id|__u16
id|result
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   lrvh %0,%1&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|x
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|___arch__swab16s
r_static
id|__inline__
r_void
id|___arch__swab16s
c_func
(paren
id|__u16
op_star
id|x
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;   lrvh 0,%0&bslash;n&quot;
l_string|&quot;   sth  0,%0&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|x
)paren
suffix:colon
suffix:colon
l_string|&quot;0&quot;
)paren
suffix:semicolon
)brace
DECL|macro|__arch__swab64
mdefine_line|#define __arch__swab64(x) ___arch__swab64(x)
DECL|macro|__arch__swab32
mdefine_line|#define __arch__swab32(x) ___arch__swab32(x)
DECL|macro|__arch__swab16
mdefine_line|#define __arch__swab16(x) ___arch__swab16(x)
DECL|macro|__arch__swab64p
mdefine_line|#define __arch__swab64p(x) ___arch__swab64p(x)
DECL|macro|__arch__swab32p
mdefine_line|#define __arch__swab32p(x) ___arch__swab32p(x)
DECL|macro|__arch__swab16p
mdefine_line|#define __arch__swab16p(x) ___arch__swab16p(x)
DECL|macro|__arch__swab64s
mdefine_line|#define __arch__swab64s(x) ___arch__swab64s(x)
DECL|macro|__arch__swab32s
mdefine_line|#define __arch__swab32s(x) ___arch__swab32s(x)
DECL|macro|__arch__swab16s
mdefine_line|#define __arch__swab16s(x) ___arch__swab16s(x)
DECL|macro|__BYTEORDER_HAS_U64__
mdefine_line|#define __BYTEORDER_HAS_U64__
macro_line|#endif /* __GNUC__ */
macro_line|#include &lt;linux/byteorder/big_endian.h&gt;
macro_line|#endif /* _S390_BYTEORDER_H */
eof
