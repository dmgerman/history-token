multiline_comment|/* Machine-dependent software floating-point definitions.  PPC version.&n;   Copyright (C) 1997 Free Software Foundation, Inc.&n;   This file is part of the GNU C Library.&n;&n;   The GNU C Library is free software; you can redistribute it and/or&n;   modify it under the terms of the GNU Library General Public License as&n;   published by the Free Software Foundation; either version 2 of the&n;   License, or (at your option) any later version.&n;&n;   The GNU C Library is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;   Library General Public License for more details.&n;&n;   You should have received a copy of the GNU Library General Public&n;   License along with the GNU C Library; see the file COPYING.LIB.  If&n;   not, write to the Free Software Foundation, Inc.,&n;   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  &n;&n;   Actually, this is a PPC (32bit) version, written based on the&n;   i386, sparc, and sparc64 versions, by me, &n;   Peter Maydell (pmaydell@chiark.greenend.org.uk).&n;   Comments are by and large also mine, although they may be inaccurate.&n;&n;   In picking out asm fragments I&squot;ve gone with the lowest common&n;   denominator, which also happens to be the hardware I have :-&gt;&n;   That is, a SPARC without hardware multiply and divide.&n; */
multiline_comment|/* basic word size definitions */
DECL|macro|_FP_W_TYPE_SIZE
mdefine_line|#define _FP_W_TYPE_SIZE&t;&t;32
DECL|macro|_FP_W_TYPE
mdefine_line|#define _FP_W_TYPE&t;&t;unsigned long
DECL|macro|_FP_WS_TYPE
mdefine_line|#define _FP_WS_TYPE&t;&t;signed long
DECL|macro|_FP_I_TYPE
mdefine_line|#define _FP_I_TYPE&t;&t;long
DECL|macro|__ll_B
mdefine_line|#define __ll_B&t;&t;&t;((UWtype) 1 &lt;&lt; (W_TYPE_SIZE / 2))
DECL|macro|__ll_lowpart
mdefine_line|#define __ll_lowpart(t)&t;&t;((UWtype) (t) &amp; (__ll_B - 1))
DECL|macro|__ll_highpart
mdefine_line|#define __ll_highpart(t)&t;((UWtype) (t) &gt;&gt; (W_TYPE_SIZE / 2))
multiline_comment|/* You can optionally code some things like addition in asm. For&n; * example, i386 defines __FP_FRAC_ADD_2 as asm. If you don&squot;t&n; * then you get a fragment of C code [if you change an #ifdef 0&n; * in op-2.h] or a call to add_ssaaaa (see below).&n; * Good places to look for asm fragments to use are gcc and glibc.&n; * gcc&squot;s longlong.h is useful.&n; */
multiline_comment|/* We need to know how to multiply and divide. If the host word size&n; * is &gt;= 2*fracbits you can use FP_MUL_MEAT_n_imm(t,R,X,Y) which&n; * codes the multiply with whatever gcc does to &squot;a * b&squot;.&n; * _FP_MUL_MEAT_n_wide(t,R,X,Y,f) is used when you have an asm &n; * function that can multiply two 1W values and get a 2W result. &n; * Otherwise you&squot;re stuck with _FP_MUL_MEAT_n_hard(t,R,X,Y) which&n; * does bitshifting to avoid overflow.&n; * For division there is FP_DIV_MEAT_n_imm(t,R,X,Y,f) for word size&n; * &gt;= 2*fracbits, where f is either _FP_DIV_HELP_imm or &n; * _FP_DIV_HELP_ldiv (see op-1.h).&n; * _FP_DIV_MEAT_udiv() is if you have asm to do 2W/1W =&gt; (1W, 1W).&n; * [GCC and glibc have longlong.h which has the asm macro udiv_qrnnd&n; * to do this.]&n; * In general, &squot;n&squot; is the number of words required to hold the type,&n; * and &squot;t&squot; is either S, D or Q for single/double/quad.&n; *           -- PMM&n; */
multiline_comment|/* Example: SPARC64:&n; * #define _FP_MUL_MEAT_S(R,X,Y)&t;_FP_MUL_MEAT_1_imm(S,R,X,Y)&n; * #define _FP_MUL_MEAT_D(R,X,Y)&t;_FP_MUL_MEAT_1_wide(D,R,X,Y,umul_ppmm)&n; * #define _FP_MUL_MEAT_Q(R,X,Y)&t;_FP_MUL_MEAT_2_wide(Q,R,X,Y,umul_ppmm)&n; *&n; * #define _FP_DIV_MEAT_S(R,X,Y)&t;_FP_DIV_MEAT_1_imm(S,R,X,Y,_FP_DIV_HELP_imm)&n; * #define _FP_DIV_MEAT_D(R,X,Y)&t;_FP_DIV_MEAT_1_udiv(D,R,X,Y)&n; * #define _FP_DIV_MEAT_Q(R,X,Y)&t;_FP_DIV_MEAT_2_udiv_64(Q,R,X,Y)&n; *&n; * Example: i386:&n; * #define _FP_MUL_MEAT_S(R,X,Y)   _FP_MUL_MEAT_1_wide(S,R,X,Y,_i386_mul_32_64)&n; * #define _FP_MUL_MEAT_D(R,X,Y)   _FP_MUL_MEAT_2_wide(D,R,X,Y,_i386_mul_32_64)&n; *&n; * #define _FP_DIV_MEAT_S(R,X,Y)   _FP_DIV_MEAT_1_udiv(S,R,X,Y,_i386_div_64_32)&n; * #define _FP_DIV_MEAT_D(R,X,Y)   _FP_DIV_MEAT_2_udiv_64(D,R,X,Y)&n; */
DECL|macro|_FP_MUL_MEAT_S
mdefine_line|#define _FP_MUL_MEAT_S(R,X,Y)   _FP_MUL_MEAT_1_wide(S,R,X,Y,umul_ppmm)
DECL|macro|_FP_MUL_MEAT_D
mdefine_line|#define _FP_MUL_MEAT_D(R,X,Y)   _FP_MUL_MEAT_2_wide(D,R,X,Y,umul_ppmm)
DECL|macro|_FP_DIV_MEAT_S
mdefine_line|#define _FP_DIV_MEAT_S(R,X,Y)   _FP_DIV_MEAT_1_udiv(S,R,X,Y)
DECL|macro|_FP_DIV_MEAT_D
mdefine_line|#define _FP_DIV_MEAT_D(R,X,Y)   _FP_DIV_MEAT_2_udiv_64(D,R,X,Y)
multiline_comment|/* These macros define what NaN looks like. They&squot;re supposed to expand to &n; * a comma-separated set of 32bit unsigned ints that encode NaN.&n; */
DECL|macro|_FP_NANFRAC_S
mdefine_line|#define _FP_NANFRAC_S&t;&t;_FP_QNANBIT_S
DECL|macro|_FP_NANFRAC_D
mdefine_line|#define _FP_NANFRAC_D&t;&t;_FP_QNANBIT_D, 0
DECL|macro|_FP_NANFRAC_Q
mdefine_line|#define _FP_NANFRAC_Q           _FP_QNANBIT_Q, 0, 0, 0
DECL|macro|_FP_KEEPNANFRACP
mdefine_line|#define _FP_KEEPNANFRACP 1
multiline_comment|/* This macro appears to be called when both X and Y are NaNs, and &n; * has to choose one and copy it to R. i386 goes for the larger of the&n; * two, sparc64 just picks Y. I don&squot;t understand this at all so I&squot;ll&n; * go with sparc64 because it&squot;s shorter :-&gt;   -- PMM &n; */
DECL|macro|_FP_CHOOSENAN
mdefine_line|#define _FP_CHOOSENAN(fs, wc, R, X, Y)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    R##_s = Y##_s;&t;&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_COPY_##wc(R,Y);&t;&t;&t;&t;&bslash;&n;    R##_c = FP_CLS_NAN;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
r_extern
r_void
id|fp_unpack_d
c_func
(paren
r_int
op_star
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
comma
r_int
op_star
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|fp_pack_d
c_func
(paren
r_void
op_star
comma
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|fp_pack_ds
c_func
(paren
r_void
op_star
comma
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|__FP_UNPACK_RAW_1
mdefine_line|#define __FP_UNPACK_RAW_1(fs, X, val)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_##fs *_flo =&t;&t;&t;&bslash;&n;    &t;(union _FP_UNION_##fs *)val;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_f = _flo-&gt;bits.frac;&t;&t;&t;&t;&bslash;&n;    X##_e = _flo-&gt;bits.exp;&t;&t;&t;&t;&bslash;&n;    X##_s = _flo-&gt;bits.sign;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|__FP_UNPACK_RAW_2
mdefine_line|#define __FP_UNPACK_RAW_2(fs, X, val)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_##fs *_flo =&t;&t;&t;&bslash;&n;    &t;(union _FP_UNION_##fs *)val;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_f0 = _flo-&gt;bits.frac0;&t;&t;&t;&t;&bslash;&n;    X##_f1 = _flo-&gt;bits.frac1;&t;&t;&t;&t;&bslash;&n;    X##_e  = _flo-&gt;bits.exp;&t;&t;&t;&t;&bslash;&n;    X##_s  = _flo-&gt;bits.sign;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|__FP_UNPACK_S
mdefine_line|#define __FP_UNPACK_S(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    __FP_UNPACK_RAW_1(S,X,val);&t;&t;&bslash;&n;    _FP_UNPACK_CANONICAL(S,1,X);&t;&bslash;&n;  } while (0)
DECL|macro|__FP_UNPACK_D
mdefine_line|#define __FP_UNPACK_D(X,val)&t;&t;&bslash;&n;&t;fp_unpack_d(&amp;X##_s, &amp;X##_f1, &amp;X##_f0, &amp;X##_e, &amp;X##_c, val)
DECL|macro|__FP_PACK_RAW_1
mdefine_line|#define __FP_PACK_RAW_1(fs, val, X)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_##fs *_flo =&t;&t;&t;&bslash;&n;    &t;(union _FP_UNION_##fs *)val;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.frac = X##_f;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.exp  = X##_e;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.sign = X##_s;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|__FP_PACK_RAW_2
mdefine_line|#define __FP_PACK_RAW_2(fs, val, X)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_##fs *_flo =&t;&t;&t;&bslash;&n;    &t;(union _FP_UNION_##fs *)val;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.frac0 = X##_f0;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.frac1 = X##_f1;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.exp   = X##_e;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.sign  = X##_s;&t;&t;&t;&t;&bslash;&n;  } while (0)
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
DECL|macro|__FPU_FPSCR
mdefine_line|#define __FPU_FPSCR&t;(current-&gt;thread.fpscr)
multiline_comment|/* We only actually write to the destination register&n; * if exceptions signalled (if any) will not trap.&n; */
DECL|macro|__FPU_ENABLED_EXC
mdefine_line|#define __FPU_ENABLED_EXC &bslash;&n;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(__FPU_FPSCR &gt;&gt; 3) &amp; 0x1f;&t;&bslash;&n;})
DECL|macro|__FPU_TRAP_P
mdefine_line|#define __FPU_TRAP_P(bits) &bslash;&n;&t;((__FPU_ENABLED_EXC &amp; (bits)) != 0)
DECL|macro|__FP_PACK_S
mdefine_line|#define __FP_PACK_S(val,X)&t;&t;&t;&bslash;&n;({  int __exc = _FP_PACK_CANONICAL(S,1,X);&t;&bslash;&n;    if(!__exc || !__FPU_TRAP_P(__exc))&t;&t;&bslash;&n;        __FP_PACK_RAW_1(S,val,X);&t;&t;&bslash;&n;    __exc;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__FP_PACK_D
mdefine_line|#define __FP_PACK_D(val,X)&t;&t;&t;&bslash;&n;&t;fp_pack_d(val, X##_s, X##_f1, X##_f0, X##_e, X##_c)
DECL|macro|__FP_PACK_DS
mdefine_line|#define __FP_PACK_DS(val,X)&t;&t;&t;&bslash;&n;&t;fp_pack_ds(val, X##_s, X##_f1, X##_f0, X##_e, X##_c)
multiline_comment|/* Obtain the current rounding mode. */
DECL|macro|FP_ROUNDMODE
mdefine_line|#define FP_ROUNDMODE&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&bslash;&n;&t;__FPU_FPSCR &amp; 0x3;&t;&t;&bslash;&n;})
multiline_comment|/* the asm fragments go here: all these are taken from glibc-2.0.5&squot;s&n; * stdlib/longlong.h&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/* add_ssaaaa is used in op-2.h and should be equivalent to&n; * #define add_ssaaaa(sh,sl,ah,al,bh,bl) (sh = ah+bh+ (( sl = al+bl) &lt; al))&n; * add_ssaaaa(high_sum, low_sum, high_addend_1, low_addend_1,&n; * high_addend_2, low_addend_2) adds two UWtype integers, composed by&n; * HIGH_ADDEND_1 and LOW_ADDEND_1, and HIGH_ADDEND_2 and LOW_ADDEND_2&n; * respectively.  The result is placed in HIGH_SUM and LOW_SUM.  Overflow&n; * (i.e. carry out) is not stored anywhere, and is lost.&n; */
DECL|macro|add_ssaaaa
mdefine_line|#define add_ssaaaa(sh, sl, ah, al, bh, bl)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (__builtin_constant_p (bh) &amp;&amp; (bh) == 0)&t;&t;&t;&t;&bslash;&n;      __asm__ (&quot;{a%I4|add%I4c} %1,%3,%4&bslash;n&bslash;t{aze|addze} %0,%2&quot;&t;&t;&bslash;&n;&t;     : &quot;=r&quot; ((USItype)(sh)),&t;&t;&t;&t;&t;&bslash;&n;&t;       &quot;=&amp;r&quot; ((USItype)(sl))&t;&t;&t;&t;&t;&bslash;&n;&t;     : &quot;%r&quot; ((USItype)(ah)),&t;&t;&t;&t;&t;&bslash;&n;&t;       &quot;%r&quot; ((USItype)(al)),&t;&t;&t;&t;&t;&bslash;&n;&t;       &quot;rI&quot; ((USItype)(bl)));&t;&t;&t;&t;&t;&bslash;&n;    else if (__builtin_constant_p (bh) &amp;&amp; (bh) ==~(USItype) 0)&t;&t;&bslash;&n;      __asm__ (&quot;{a%I4|add%I4c} %1,%3,%4&bslash;n&bslash;t{ame|addme} %0,%2&quot;&t;&t;&bslash;&n;&t;     : &quot;=r&quot; ((USItype)(sh)),&t;&t;&t;&t;&t;&bslash;&n;&t;       &quot;=&amp;r&quot; ((USItype)(sl))&t;&t;&t;&t;&t;&bslash;&n;&t;     : &quot;%r&quot; ((USItype)(ah)),&t;&t;&t;&t;&t;&bslash;&n;&t;       &quot;%r&quot; ((USItype)(al)),&t;&t;&t;&t;&t;&bslash;&n;&t;       &quot;rI&quot; ((USItype)(bl)));&t;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      __asm__ (&quot;{a%I5|add%I5c} %1,%4,%5&bslash;n&bslash;t{ae|adde} %0,%2,%3&quot;&t;&t;&bslash;&n;&t;     : &quot;=r&quot; ((USItype)(sh)),&t;&t;&t;&t;&t;&bslash;&n;&t;       &quot;=&amp;r&quot; ((USItype)(sl))&t;&t;&t;&t;&t;&bslash;&n;&t;     : &quot;%r&quot; ((USItype)(ah)),&t;&t;&t;&t;&t;&bslash;&n;&t;       &quot;r&quot; ((USItype)(bh)),&t;&t;&t;&t;&t;&bslash;&n;&t;       &quot;%r&quot; ((USItype)(al)),&t;&t;&t;&t;&t;&bslash;&n;&t;       &quot;rI&quot; ((USItype)(bl)));&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/* sub_ddmmss is used in op-2.h and udivmodti4.c and should be equivalent to&n; * #define sub_ddmmss(sh, sl, ah, al, bh, bl) (sh = ah-bh - ((sl = al-bl) &gt; al))&n; * sub_ddmmss(high_difference, low_difference, high_minuend, low_minuend,&n; * high_subtrahend, low_subtrahend) subtracts two two-word UWtype integers,&n; * composed by HIGH_MINUEND_1 and LOW_MINUEND_1, and HIGH_SUBTRAHEND_2 and&n; * LOW_SUBTRAHEND_2 respectively.  The result is placed in HIGH_DIFFERENCE&n; * and LOW_DIFFERENCE.  Overflow (i.e. carry out) is not stored anywhere,&n; * and is lost.&n; */
DECL|macro|sub_ddmmss
mdefine_line|#define sub_ddmmss(sh, sl, ah, al, bh, bl)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (__builtin_constant_p (ah) &amp;&amp; (ah) == 0)&t;&t;&t;&t;&bslash;&n;      __asm__ (&quot;{sf%I3|subf%I3c} %1,%4,%3&bslash;n&bslash;t{sfze|subfze} %0,%2&quot;&t;&bslash;&n;&t;       : &quot;=r&quot; ((USItype)(sh)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;=&amp;r&quot; ((USItype)(sl))&t;&t;&t;&t;&t;&bslash;&n;&t;       : &quot;r&quot; ((USItype)(bh)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;rI&quot; ((USItype)(al)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;r&quot; ((USItype)(bl)));&t;&t;&t;&t;&t;&bslash;&n;    else if (__builtin_constant_p (ah) &amp;&amp; (ah) ==~(USItype) 0)&t;&t;&bslash;&n;      __asm__ (&quot;{sf%I3|subf%I3c} %1,%4,%3&bslash;n&bslash;t{sfme|subfme} %0,%2&quot;&t;&bslash;&n;&t;       : &quot;=r&quot; ((USItype)(sh)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;=&amp;r&quot; ((USItype)(sl))&t;&t;&t;&t;&t;&bslash;&n;&t;       : &quot;r&quot; ((USItype)(bh)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;rI&quot; ((USItype)(al)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;r&quot; ((USItype)(bl)));&t;&t;&t;&t;&t;&bslash;&n;    else if (__builtin_constant_p (bh) &amp;&amp; (bh) == 0)&t;&t;&t;&bslash;&n;      __asm__ (&quot;{sf%I3|subf%I3c} %1,%4,%3&bslash;n&bslash;t{ame|addme} %0,%2&quot;&t;&t;&bslash;&n;&t;       : &quot;=r&quot; ((USItype)(sh)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;=&amp;r&quot; ((USItype)(sl))&t;&t;&t;&t;&t;&bslash;&n;&t;       : &quot;r&quot; ((USItype)(ah)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;rI&quot; ((USItype)(al)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;r&quot; ((USItype)(bl)));&t;&t;&t;&t;&t;&bslash;&n;    else if (__builtin_constant_p (bh) &amp;&amp; (bh) ==~(USItype) 0)&t;&t;&bslash;&n;      __asm__ (&quot;{sf%I3|subf%I3c} %1,%4,%3&bslash;n&bslash;t{aze|addze} %0,%2&quot;&t;&t;&bslash;&n;&t;       : &quot;=r&quot; ((USItype)(sh)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;=&amp;r&quot; ((USItype)(sl))&t;&t;&t;&t;&t;&bslash;&n;&t;       : &quot;r&quot; ((USItype)(ah)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;rI&quot; ((USItype)(al)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;r&quot; ((USItype)(bl)));&t;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      __asm__ (&quot;{sf%I4|subf%I4c} %1,%5,%4&bslash;n&bslash;t{sfe|subfe} %0,%3,%2&quot;&t;&bslash;&n;&t;       : &quot;=r&quot; ((USItype)(sh)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;=&amp;r&quot; ((USItype)(sl))&t;&t;&t;&t;&t;&bslash;&n;&t;       : &quot;r&quot; ((USItype)(ah)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;r&quot; ((USItype)(bh)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;rI&quot; ((USItype)(al)),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;r&quot; ((USItype)(bl)));&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/* asm fragments for mul and div */
multiline_comment|/* umul_ppmm(high_prod, low_prod, multipler, multiplicand) multiplies two&n; * UWtype integers MULTIPLER and MULTIPLICAND, and generates a two UWtype&n; * word product in HIGH_PROD and LOW_PROD.&n; */
DECL|macro|umul_ppmm
mdefine_line|#define umul_ppmm(ph, pl, m0, m1)&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    USItype __m0 = (m0), __m1 = (m1);&t;&t;&t;&t;&t;&bslash;&n;    __asm__ (&quot;mulhwu %0,%1,%2&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     : &quot;=r&quot; ((USItype)(ph))&t;&t;&t;&t;&t;&bslash;&n;&t;     : &quot;%r&quot; (__m0),&t;&t;&t;&t;&t;&t;&bslash;&n;               &quot;r&quot; (__m1));&t;&t;&t;&t;&t;&t;&bslash;&n;    (pl) = __m0 * __m1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/* udiv_qrnnd(quotient, remainder, high_numerator, low_numerator,&n; * denominator) divides a UDWtype, composed by the UWtype integers&n; * HIGH_NUMERATOR and LOW_NUMERATOR, by DENOMINATOR and places the quotient&n; * in QUOTIENT and the remainder in REMAINDER.  HIGH_NUMERATOR must be less&n; * than DENOMINATOR for correct operation.  If, in addition, the most&n; * significant bit of DENOMINATOR must be 1, then the pre-processor symbol&n; * UDIV_NEEDS_NORMALIZATION is defined to 1.&n; */
DECL|macro|udiv_qrnnd
mdefine_line|#define udiv_qrnnd(q, r, n1, n0, d)&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    UWtype __d1, __d0, __q1, __q0, __r1, __r0, __m;&t;&t;&t;&bslash;&n;    __d1 = __ll_highpart (d);&t;&t;&t;&t;&t;&t;&bslash;&n;    __d0 = __ll_lowpart (d);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __r1 = (n1) % __d1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __q1 = (n1) / __d1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __m = (UWtype) __q1 * __d0;&t;&t;&t;&t;&t;&t;&bslash;&n;    __r1 = __r1 * __ll_B | __ll_highpart (n0);&t;&t;&t;&t;&bslash;&n;    if (__r1 &lt; __m)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__q1--, __r1 += (d);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__r1 &gt;= (d)) /* we didn&squot;t get carry when adding to __r1 */&t;&bslash;&n;&t;  if (__r1 &lt; __m)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    __q1--, __r1 += (d);&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __r1 -= __m;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __r0 = __r1 % __d1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __q0 = __r1 / __d1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __m = (UWtype) __q0 * __d0;&t;&t;&t;&t;&t;&t;&bslash;&n;    __r0 = __r0 * __ll_B | __ll_lowpart (n0);&t;&t;&t;&t;&bslash;&n;    if (__r0 &lt; __m)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__q0--, __r0 += (d);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__r0 &gt;= (d))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  if (__r0 &lt; __m)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    __q0--, __r0 += (d);&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __r0 -= __m;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    (q) = (UWtype) __q1 * __ll_B | __q0;&t;&t;&t;&t;&bslash;&n;    (r) = __r0;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|UDIV_NEEDS_NORMALIZATION
mdefine_line|#define UDIV_NEEDS_NORMALIZATION 1
DECL|macro|abort
mdefine_line|#define abort()&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return 0
macro_line|#ifdef __BIG_ENDIAN
DECL|macro|__BYTE_ORDER
mdefine_line|#define __BYTE_ORDER __BIG_ENDIAN
macro_line|#else
DECL|macro|__BYTE_ORDER
mdefine_line|#define __BYTE_ORDER __LITTLE_ENDIAN
macro_line|#endif
multiline_comment|/* Exception flags. */
DECL|macro|EFLAG_INVALID
mdefine_line|#define EFLAG_INVALID&t;&t;(1 &lt;&lt; (31 - 2))
DECL|macro|EFLAG_OVERFLOW
mdefine_line|#define EFLAG_OVERFLOW&t;&t;(1 &lt;&lt; (31 - 3))
DECL|macro|EFLAG_UNDERFLOW
mdefine_line|#define EFLAG_UNDERFLOW&t;&t;(1 &lt;&lt; (31 - 4))
DECL|macro|EFLAG_DIVZERO
mdefine_line|#define EFLAG_DIVZERO&t;&t;(1 &lt;&lt; (31 - 5))
DECL|macro|EFLAG_INEXACT
mdefine_line|#define EFLAG_INEXACT&t;&t;(1 &lt;&lt; (31 - 6))
DECL|macro|EFLAG_VXSNAN
mdefine_line|#define EFLAG_VXSNAN&t;&t;(1 &lt;&lt; (31 - 7))
DECL|macro|EFLAG_VXISI
mdefine_line|#define EFLAG_VXISI&t;&t;(1 &lt;&lt; (31 - 8))
DECL|macro|EFLAG_VXIDI
mdefine_line|#define EFLAG_VXIDI&t;&t;(1 &lt;&lt; (31 - 9))
DECL|macro|EFLAG_VXZDZ
mdefine_line|#define EFLAG_VXZDZ&t;&t;(1 &lt;&lt; (31 - 10))
DECL|macro|EFLAG_VXIMZ
mdefine_line|#define EFLAG_VXIMZ&t;&t;(1 &lt;&lt; (31 - 11))
DECL|macro|EFLAG_VXVC
mdefine_line|#define EFLAG_VXVC&t;&t;(1 &lt;&lt; (31 - 12))
DECL|macro|EFLAG_VXSOFT
mdefine_line|#define EFLAG_VXSOFT&t;&t;(1 &lt;&lt; (31 - 21))
DECL|macro|EFLAG_VXSQRT
mdefine_line|#define EFLAG_VXSQRT&t;&t;(1 &lt;&lt; (31 - 22))
DECL|macro|EFLAG_VXCVI
mdefine_line|#define EFLAG_VXCVI&t;&t;(1 &lt;&lt; (31 - 23))
eof
