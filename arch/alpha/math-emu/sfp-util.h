macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
DECL|macro|add_ssaaaa
mdefine_line|#define add_ssaaaa(sh, sl, ah, al, bh, bl) &bslash;&n;  ((sl) = (al) + (bl), (sh) = (ah) + (bh) + ((sl) &lt; (al)))
DECL|macro|sub_ddmmss
mdefine_line|#define sub_ddmmss(sh, sl, ah, al, bh, bl) &bslash;&n;  ((sl) = (al) - (bl), (sh) = (ah) - (bh) - ((al) &lt; (bl)))
DECL|macro|umul_ppmm
mdefine_line|#define umul_ppmm(wh, wl, u, v)&t;&t;&t;&bslash;&n;  __asm__ (&quot;mulq %2,%3,%1; umulh %2,%3,%0&quot;&t;&bslash;&n;&t;   : &quot;=r&quot; ((UDItype)(wh)),&t;&t;&bslash;&n;&t;     &quot;=&amp;r&quot; ((UDItype)(wl))&t;&t;&bslash;&n;&t;   : &quot;r&quot; ((UDItype)(u)),&t;&t;&bslash;&n;&t;     &quot;r&quot; ((UDItype)(v)))
DECL|macro|udiv_qrnnd
mdefine_line|#define udiv_qrnnd(q, r, n1, n0, d)&t;&t;&t;&t;&bslash;&n;  do { unsigned long __r;&t;&t;&t;&t;&t;&bslash;&n;    (q) = __udiv_qrnnd (&amp;__r, (n1), (n0), (d));&t;&t;&t;&bslash;&n;    (r) = __r;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
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
mdefine_line|#define UDIV_NEEDS_NORMALIZATION 1  
DECL|macro|abort
mdefine_line|#define abort()&t;&t;&t;goto bad_insn
macro_line|#ifndef __LITTLE_ENDIAN
DECL|macro|__LITTLE_ENDIAN
mdefine_line|#define __LITTLE_ENDIAN -1
macro_line|#endif
DECL|macro|__BYTE_ORDER
mdefine_line|#define __BYTE_ORDER __LITTLE_ENDIAN
eof
