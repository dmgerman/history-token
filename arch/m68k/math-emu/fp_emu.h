multiline_comment|/*&n; * fp_emu.h&n; *&n; * Copyright Roman Zippel, 1997.  All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, and the entire permission notice in its entirety,&n; *    including the disclaimer of warranties.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice, this list of conditions and the following disclaimer in the&n; *    documentation and/or other materials provided with the distribution.&n; * 3. The name of the author may not be used to endorse or promote&n; *    products derived from this software without specific prior&n; *    written permission.&n; *&n; * ALTERNATIVELY, this product may be distributed under the terms of&n; * the GNU Public License, in which case the provisions of the GPL are&n; * required INSTEAD OF the above restrictions.  (This clause is&n; * necessary due to a potential bad interaction between the GPL and&n; * the restrictions contained in a BSD-style copyright.)&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES&n; * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,&n; * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES&n; * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n; * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)&n; * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED&n; * OF THE POSSIBILITY OF SUCH DAMAGE.&n; */
macro_line|#ifndef _FP_EMU_H
DECL|macro|_FP_EMU_H
mdefine_line|#define _FP_EMU_H
macro_line|#include &quot;../kernel/m68k_defs.h&quot;
macro_line|#include &lt;asm/math-emu.h&gt;
macro_line|#ifndef __ASSEMBLY__
DECL|macro|IS_INF
mdefine_line|#define IS_INF(a) ((a)-&gt;exp == 0x7fff)
DECL|macro|IS_ZERO
mdefine_line|#define IS_ZERO(a) ((a)-&gt;mant.m64 == 0)
DECL|macro|fp_set_sr
mdefine_line|#define fp_set_sr(bit) ({&t;&t;&t;&t;&t;&bslash;&n;&t;FPDATA-&gt;fpsr |= 1 &lt;&lt; (bit);&t;&t;&t;&t;&bslash;&n;})
DECL|macro|fp_set_quotient
mdefine_line|#define fp_set_quotient(quotient) ({&t;&t;&t;&t;&bslash;&n;&t;FPDATA-&gt;fpsr &amp;= 0xff00ffff;&t;&t;&t;&t;&bslash;&n;&t;FPDATA-&gt;fpsr |= ((quotient) &amp; 0xff) &lt;&lt; 16;&t;&t;&bslash;&n;})
multiline_comment|/* linkage for several useful functions */
multiline_comment|/* Normalize the extended struct, return 0 for a NaN */
DECL|macro|fp_normalize_ext
mdefine_line|#define fp_normalize_ext(fpreg) ({&t;&t;&t;&t;&bslash;&n;&t;register struct fp_ext *reg asm (&quot;a0&quot;) = fpreg;&t;&t;&bslash;&n;&t;register int res asm (&quot;d0&quot;);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;jsr fp_conv_ext2ext&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=d&quot; (res) : &quot;a&quot; (reg)&t;&t;&bslash;&n;&t;&t;&t;: &quot;a1&quot;, &quot;d1&quot;, &quot;d2&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|fp_copy_ext
mdefine_line|#define fp_copy_ext(dest, src) ({&t;&t;&t;&t;&bslash;&n;&t;*dest = *src;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|fp_monadic_check
mdefine_line|#define fp_monadic_check(dest, src) ({&t;&t;&t;&t;&bslash;&n;&t;fp_copy_ext(dest, src);&t;&t;&t;&t;&t;&bslash;&n;&t;if (!fp_normalize_ext(dest))&t;&t;&t;&t;&bslash;&n;&t;&t;return dest;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|fp_dyadic_check
mdefine_line|#define fp_dyadic_check(dest, src) ({&t;&t;&t;&t;&bslash;&n;&t;if (!fp_normalize_ext(dest))&t;&t;&t;&t;&bslash;&n;&t;&t;return dest;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!fp_normalize_ext(src)) {&t;&t;&t;&t;&bslash;&n;&t;&t;fp_copy_ext(dest, src);&t;&t;&t;&t;&bslash;&n;&t;&t;return dest;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
r_extern
r_const
r_struct
id|fp_ext
id|fp_QNaN
suffix:semicolon
r_extern
r_const
r_struct
id|fp_ext
id|fp_Inf
suffix:semicolon
DECL|macro|fp_set_nan
mdefine_line|#define fp_set_nan(dest) ({&t;&t;&t;&t;&t;&bslash;&n;&t;fp_set_sr(FPSR_EXC_OPERR);&t;&t;&t;&t;&bslash;&n;&t;*dest = fp_QNaN;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* TODO check rounding mode? */
DECL|macro|fp_set_ovrflw
mdefine_line|#define fp_set_ovrflw(dest) ({&t;&t;&t;&t;&t;&bslash;&n;&t;fp_set_sr(FPSR_EXC_OVFL);&t;&t;&t;&t;&bslash;&n;&t;dest-&gt;exp = 0x7fff;&t;&t;&t;&t;&t;&bslash;&n;&t;dest-&gt;mant.m64 = 0;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|fp_conv_ext2long
mdefine_line|#define fp_conv_ext2long(src) ({&t;&t;&t;&t;&bslash;&n;&t;register struct fp_ext *__src asm (&quot;a0&quot;) = src;&t;&t;&bslash;&n;&t;register int __res asm (&quot;d0&quot;);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;jsr fp_conv_ext2long&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=d&quot; (__res) : &quot;a&quot; (__src)&t;&t;&bslash;&n;&t;&t;&t;: &quot;a1&quot;, &quot;d1&quot;, &quot;d2&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#else /* __ASSEMBLY__ */
multiline_comment|/*&n; * set, reset or clear a bit in the fp status register&n; */
dot
id|macro
id|fp_set_sr
id|bit
id|bset
macro_line|#(&bslash;bit&amp;7),(FPD_FPSR+3-(&bslash;bit/8),FPDATA)
dot
id|endm
dot
id|macro
id|fp_clr_sr
id|bit
id|bclr
macro_line|#(&bslash;bit&amp;7),(FPD_FPSR+3-(&bslash;bit/8),FPDATA)
dot
id|endm
dot
id|macro
id|fp_tst_sr
id|bit
id|btst
macro_line|#(&bslash;bit&amp;7),(FPD_FPSR+3-(&bslash;bit/8),FPDATA)
dot
id|endm
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _FP_EMU_H */
eof
