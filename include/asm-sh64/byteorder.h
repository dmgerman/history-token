macro_line|#ifndef __ASM_SH64_BYTEORDER_H
DECL|macro|__ASM_SH64_BYTEORDER_H
mdefine_line|#define __ASM_SH64_BYTEORDER_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/byteorder.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; *&n; */
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
l_string|&quot;byterev&t;%0, %0&bslash;n&bslash;t&quot;
l_string|&quot;shari&t;&t;%0, 32, %0&quot;
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
l_string|&quot;byterev&t;%0, %0&bslash;n&bslash;t&quot;
l_string|&quot;shari&t;&t;%0, 48, %0&quot;
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
macro_line|#endif /* __ASM_SH64_BYTEORDER_H */
eof
