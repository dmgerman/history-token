macro_line|#ifndef _PARISC_BYTEORDER_H
DECL|macro|_PARISC_BYTEORDER_H
mdefine_line|#define _PARISC_BYTEORDER_H
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
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;shd %0, %0, 16, %1&bslash;n&bslash;t&quot;
multiline_comment|/* shift abcdabcd -&gt; cdab */
l_string|&quot;dep %1, 15, 8, %1&bslash;n&bslash;t&quot;
multiline_comment|/* deposit cdab -&gt; cbab */
l_string|&quot;shd %0, %1, 8, %0&quot;
multiline_comment|/* shift abcdcbab -&gt; dcba */
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|temp
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
macro_line|#if BITS_PER_LONG &gt; 32
multiline_comment|/*&n;** From &quot;PA-RISC 2.0 Architecture&quot;, HP Professional Books.&n;** See Appendix I page 8 , &quot;Endian Byte Swapping&quot;.&n;**&n;** Pretty cool algorithm: (* == zero&squot;d bits)&n;**      PERMH   01234567 -&gt; 67452301 into %0&n;**      HSHL    67452301 -&gt; 7*5*3*1* into %1&n;**      HSHR    67452301 -&gt; *6*4*2*0 into %0&n;**      OR      %0 | %1  -&gt; 76543210 into %0 (all done!)&n;*/
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
id|temp
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;permh 3210, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;hshl %0, 8, %1&bslash;n&bslash;t&quot;
l_string|&quot;hshr u, %0, 8, %0&bslash;n&bslash;t&quot;
l_string|&quot;or %1, %0, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|temp
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
DECL|macro|__arch__swab64
mdefine_line|#define __arch__swab64(x) ___arch__swab64(x)
macro_line|#else
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
id|__u32
id|t1
op_assign
(paren
id|__u32
)paren
id|x
suffix:semicolon
id|__u32
id|t2
op_assign
(paren
id|__u32
)paren
(paren
(paren
id|x
)paren
op_rshift
l_int|32
)paren
suffix:semicolon
id|___arch__swab32
c_func
(paren
id|t1
)paren
suffix:semicolon
id|___arch__swab32
c_func
(paren
id|t2
)paren
suffix:semicolon
r_return
(paren
(paren
(paren
id|__u64
)paren
id|t1
op_lshift
l_int|32
)paren
op_plus
(paren
(paren
id|__u64
)paren
id|t2
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
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
l_string|&quot;dep %0, 15, 8, %0&bslash;n&bslash;t&quot;
multiline_comment|/* deposit 00ab -&gt; 0bab */
l_string|&quot;shd %r0, %0, 8, %0&quot;
multiline_comment|/* shift 000000ab -&gt; 00ba */
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
macro_line|#endif /* __GNUC__ */
macro_line|#include &lt;linux/byteorder/big_endian.h&gt;
macro_line|#endif /* _PARISC_BYTEORDER_H */
eof
