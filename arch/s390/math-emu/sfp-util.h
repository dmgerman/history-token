macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|add_ssaaaa
mdefine_line|#define add_ssaaaa(sh, sl, ah, al, bh, bl) ({&t;&t;&bslash;&n;        unsigned int __sh = (ah);&t;&t;&t;&bslash;&n;        unsigned int __sl = (al);&t;&t;&t;&bslash;&n;        __asm__ (&quot;   alr  %1,%3&bslash;n&quot;&t;&t;&t;&bslash;&n;                 &quot;   brc  12,0f&bslash;n&quot;&t;&t;&t;&bslash;&n;                 &quot;   ahi  %0,1&bslash;n&quot;&t;&t;&t;&bslash;&n;                 &quot;0: alr  %0,%2&quot;&t;&t;&t;&bslash;&n;                 : &quot;+&amp;d&quot; (__sh), &quot;+d&quot; (__sl)&t;&t;&bslash;&n;                 : &quot;d&quot; (bh), &quot;d&quot; (bl) : &quot;cc&quot; );&t;&t;&bslash;&n;        (sh) = __sh;&t;&t;&t;&t;&t;&bslash;&n;        (sl) = __sl;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|sub_ddmmss
mdefine_line|#define sub_ddmmss(sh, sl, ah, al, bh, bl) ({&t;&t;&bslash;&n;       unsigned int __sh = (ah);&t;&t;&t;&bslash;&n;       unsigned int __sl = (al);&t;&t;&t;&bslash;&n;       __asm__ (&quot;   slr  %1,%3&bslash;n&quot;&t;&t;&t;&bslash;&n;                &quot;   brc  3,0f&bslash;n&quot;&t;&t;&t;&bslash;&n;                &quot;   ahi  %0,-1&bslash;n&quot;&t;&t;&t;&bslash;&n;                &quot;0: slr  %0,%2&quot;&t;&t;&t;&t;&bslash;&n;                : &quot;+&amp;d&quot; (__sh), &quot;+d&quot; (__sl)&t;&t;&bslash;&n;                : &quot;d&quot; (bh), &quot;d&quot; (bl) : &quot;cc&quot; );&t;&t;&bslash;&n;       (sh) = __sh;&t;&t;&t;&t;&t;&bslash;&n;       (sl) = __sl;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* a umul b = a mul b + (a&gt;=2&lt;&lt;31) ? b&lt;&lt;32:0 + (b&gt;=2&lt;&lt;31) ? a&lt;&lt;32:0 */
DECL|macro|umul_ppmm
mdefine_line|#define umul_ppmm(wh, wl, u, v) ({&t;&t;&t;&bslash;&n;        unsigned int __wh = u;&t;&t;&t;&t;&bslash;&n;        unsigned int __wl = v;&t;&t;&t;&t;&bslash;&n;        __asm__ (&quot;   ltr  1,%0&bslash;n&quot;&t;&t;&t;&bslash;&n;                 &quot;   mr   0,%1&bslash;n&quot;&t;&t;&t;&bslash;&n;                 &quot;   jnm  0f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;                 &quot;   alr  0,%1&bslash;n&quot;&t;&t;&t;&bslash;&n;                 &quot;0: ltr  %1,%1&bslash;n&quot;&t;&t;&t;&bslash;&n;                 &quot;   jnm  1f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;                 &quot;   alr  0,%0&bslash;n&quot;&t;&t;&t;&bslash;&n;                 &quot;1: lr   %0,0&bslash;n&quot;&t;&t;&t;&bslash;&n;                 &quot;   lr   %1,1&bslash;n&quot;&t;&t;&t;&bslash;&n;                 : &quot;+d&quot; (__wh), &quot;+d&quot; (__wl)&t;&t;&bslash;&n;                 : : &quot;0&quot;, &quot;1&quot;, &quot;cc&quot; );&t;&t;&t;&bslash;&n;        wh = __wh;&t;&t;&t;&t;&t;&bslash;&n;        wl = __wl;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|udiv_qrnnd
mdefine_line|#define udiv_qrnnd(q, r, n1, n0, d)&t;&t;&t;&bslash;&n;  do { unsigned long __r;&t;&t;&t;&t;&bslash;&n;    (q) = __udiv_qrnnd (&amp;__r, (n1), (n0), (d));&t;&t;&bslash;&n;    (r) = __r;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
r_extern
r_int
r_int
id|__udiv_qrnnd
(paren
r_int
r_int
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|UDIV_NEEDS_NORMALIZATION
mdefine_line|#define UDIV_NEEDS_NORMALIZATION 0
DECL|macro|abort
mdefine_line|#define abort() return 0
DECL|macro|__BYTE_ORDER
mdefine_line|#define __BYTE_ORDER __BIG_ENDIAN
eof
