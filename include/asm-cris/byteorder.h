multiline_comment|/* $Id: byteorder.h,v 1.1 2000/07/10 16:32:31 bjornw Exp $ */
macro_line|#ifndef _CRIS_BYTEORDER_H
DECL|macro|_CRIS_BYTEORDER_H
mdefine_line|#define _CRIS_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __GNUC__
multiline_comment|/* we just define these two (as we can do the swap in a single&n; * asm instruction in CRIS) and the arch-independent files will put&n; * them together into ntohl etc.&n; */
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
multiline_comment|/* defines are necessary because the other files detect the presence&n; * of a defined __arch_swab32, not an inline&n; */
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
macro_line|#endif
eof
