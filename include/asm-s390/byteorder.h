macro_line|#ifndef _S390_BYTEORDER_H
DECL|macro|_S390_BYTEORDER_H
mdefine_line|#define _S390_BYTEORDER_H
multiline_comment|/*&n; *  include/asm-s390/byteorder.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; */
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
id|x
)paren
(brace
id|__u32
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;        st    %0,0(%1)&bslash;n&quot;
l_string|&quot;        icm   %0,8,3(%1)&bslash;n&quot;
l_string|&quot;        icm   %0,4,2(%1)&bslash;n&quot;
l_string|&quot;        icm   %0,2,1(%1)&bslash;n&quot;
l_string|&quot;        ic    %0,0(%1)&quot;
suffix:colon
l_string|&quot;+&amp;d&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|temp
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|x
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
l_string|&quot;        icm   %0,8,3(%1)&bslash;n&quot;
l_string|&quot;        icm   %0,4,2(%1)&bslash;n&quot;
l_string|&quot;        icm   %0,2,1(%1)&bslash;n&quot;
l_string|&quot;        ic    %0,0(%1)&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;cc&quot;
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
l_string|&quot;        icm   0,8,3(%0)&bslash;n&quot;
l_string|&quot;        icm   0,4,2(%0)&bslash;n&quot;
l_string|&quot;        icm   0,2,1(%0)&bslash;n&quot;
l_string|&quot;        ic    0,0(%0)&bslash;n&quot;
l_string|&quot;        st    0,0(%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;0&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
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
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;        sth   %0,0(%1)&bslash;n&quot;
l_string|&quot;        icm   %0,2,1(%1)&bslash;n&quot;
l_string|&quot;        ic    %0,0(%1)&bslash;n&quot;
suffix:colon
l_string|&quot;+&amp;d&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|temp
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|x
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
l_string|&quot;        sr    %0,%0&bslash;n&quot;
l_string|&quot;        icm   %0,2,1(%1)&bslash;n&quot;
l_string|&quot;        ic    %0,0(%1)&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;cc&quot;
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
c_func
(paren
l_string|&quot;        icm   0,2,1(%0)&bslash;n&quot;
l_string|&quot;        ic    0,0(%0)&bslash;n&quot;
l_string|&quot;        sth   0,0(%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;0&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|macro|__arch__swab32
mdefine_line|#define __arch__swab32(x) ___arch__swab32(x)
DECL|macro|__arch__swab16
mdefine_line|#define __arch__swab16(x) ___arch__swab16(x)
DECL|macro|__arch__swab32p
mdefine_line|#define __arch__swab32p(x) ___arch__swab32p(x)
DECL|macro|__arch__swab16p
mdefine_line|#define __arch__swab16p(x) ___arch__swab16p(x)
DECL|macro|__arch__swab32s
mdefine_line|#define __arch__swab32s(x) ___arch__swab32s(x)
DECL|macro|__arch__swab16s
mdefine_line|#define __arch__swab16s(x) ___arch__swab16s(x)
macro_line|#if !defined(__STRICT_ANSI__) || defined(__KERNEL__)
DECL|macro|__BYTEORDER_HAS_U64__
macro_line|#  define __BYTEORDER_HAS_U64__
DECL|macro|__SWAB_64_THRU_32__
macro_line|#  define __SWAB_64_THRU_32__
macro_line|#endif
macro_line|#endif /* __GNUC__ */
macro_line|#include &lt;linux/byteorder/big_endian.h&gt;
macro_line|#endif /* _S390_BYTEORDER_H */
eof
