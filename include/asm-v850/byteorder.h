multiline_comment|/*&n; * include/asm-v850/byteorder.h -- Endian id and conversion ops&n; *&n; *  Copyright (C) 2001  NEC Corporation&n; *  Copyright (C) 2001  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_BYTEORDER_H__
DECL|macro|__V850_BYTEORDER_H__
mdefine_line|#define __V850_BYTEORDER_H__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __GNUC__
DECL|function|___arch__swab32
r_static
id|__inline__
id|__const__
id|__u32
id|___arch__swab32
(paren
id|__u32
id|word
)paren
(brace
id|__u32
id|res
suffix:semicolon
id|__asm__
(paren
l_string|&quot;bsw %1, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|word
)paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|___arch__swab16
r_static
id|__inline__
id|__const__
id|__u16
id|___arch__swab16
(paren
id|__u16
id|half_word
)paren
(brace
id|__u16
id|res
suffix:semicolon
id|__asm__
(paren
l_string|&quot;bsh %1, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|half_word
)paren
)paren
suffix:semicolon
r_return
id|res
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
macro_line|#endif /* __V850_BYTEORDER_H__ */
eof
