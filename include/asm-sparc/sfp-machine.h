multiline_comment|/* Machine-dependent software floating-point definitions.&n;   Sparc userland (_Q_*) version.&n;   Copyright (C) 1997,1998,1999 Free Software Foundation, Inc.&n;   This file is part of the GNU C Library.&n;   Contributed by Richard Henderson (rth@cygnus.com),&n;&t;&t;  Jakub Jelinek (jj@ultra.linux.cz),&n;&t;&t;  David S. Miller (davem@redhat.com) and&n;&t;&t;  Peter Maydell (pmaydell@chiark.greenend.org.uk).&n;&n;   The GNU C Library is free software; you can redistribute it and/or&n;   modify it under the terms of the GNU Library General Public License as&n;   published by the Free Software Foundation; either version 2 of the&n;   License, or (at your option) any later version.&n;&n;   The GNU C Library is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;   Library General Public License for more details.&n;&n;   You should have received a copy of the GNU Library General Public&n;   License along with the GNU C Library; see the file COPYING.LIB.  If&n;   not, write to the Free Software Foundation, Inc.,&n;   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
macro_line|#ifndef _SFP_MACHINE_H
DECL|macro|_SFP_MACHINE_H
mdefine_line|#define _SFP_MACHINE_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|_FP_W_TYPE_SIZE
mdefine_line|#define _FP_W_TYPE_SIZE&t;&t;32
DECL|macro|_FP_W_TYPE
mdefine_line|#define _FP_W_TYPE&t;&t;unsigned long
DECL|macro|_FP_WS_TYPE
mdefine_line|#define _FP_WS_TYPE&t;&t;signed long
DECL|macro|_FP_I_TYPE
mdefine_line|#define _FP_I_TYPE&t;&t;long
DECL|macro|_FP_MUL_MEAT_S
mdefine_line|#define _FP_MUL_MEAT_S(R,X,Y)&t;&t;&t;&t;&t;&bslash;&n;  _FP_MUL_MEAT_1_wide(_FP_WFRACBITS_S,R,X,Y,umul_ppmm)
DECL|macro|_FP_MUL_MEAT_D
mdefine_line|#define _FP_MUL_MEAT_D(R,X,Y)&t;&t;&t;&t;&t;&bslash;&n;  _FP_MUL_MEAT_2_wide(_FP_WFRACBITS_D,R,X,Y,umul_ppmm)
DECL|macro|_FP_MUL_MEAT_Q
mdefine_line|#define _FP_MUL_MEAT_Q(R,X,Y)&t;&t;&t;&t;&t;&bslash;&n;  _FP_MUL_MEAT_4_wide(_FP_WFRACBITS_Q,R,X,Y,umul_ppmm)
DECL|macro|_FP_DIV_MEAT_S
mdefine_line|#define _FP_DIV_MEAT_S(R,X,Y)&t;_FP_DIV_MEAT_1_udiv(S,R,X,Y)
DECL|macro|_FP_DIV_MEAT_D
mdefine_line|#define _FP_DIV_MEAT_D(R,X,Y)&t;_FP_DIV_MEAT_2_udiv(D,R,X,Y)
DECL|macro|_FP_DIV_MEAT_Q
mdefine_line|#define _FP_DIV_MEAT_Q(R,X,Y)&t;_FP_DIV_MEAT_4_udiv(Q,R,X,Y)
DECL|macro|_FP_NANFRAC_S
mdefine_line|#define _FP_NANFRAC_S&t;&t;((_FP_QNANBIT_S &lt;&lt; 1) - 1)
DECL|macro|_FP_NANFRAC_D
mdefine_line|#define _FP_NANFRAC_D&t;&t;((_FP_QNANBIT_D &lt;&lt; 1) - 1), -1
DECL|macro|_FP_NANFRAC_Q
mdefine_line|#define _FP_NANFRAC_Q&t;&t;((_FP_QNANBIT_Q &lt;&lt; 1) - 1), -1, -1, -1
DECL|macro|_FP_NANSIGN_S
mdefine_line|#define _FP_NANSIGN_S&t;&t;0
DECL|macro|_FP_NANSIGN_D
mdefine_line|#define _FP_NANSIGN_D&t;&t;0
DECL|macro|_FP_NANSIGN_Q
mdefine_line|#define _FP_NANSIGN_Q&t;&t;0
DECL|macro|_FP_KEEPNANFRACP
mdefine_line|#define _FP_KEEPNANFRACP 1
multiline_comment|/* If one NaN is signaling and the other is not,&n; * we choose that one, otherwise we choose X.&n; */
multiline_comment|/* For _Qp_* and _Q_*, this should prefer X, for&n; * CPU instruction emulation this should prefer Y.&n; * (see SPAMv9 B.2.2 section).&n; */
DECL|macro|_FP_CHOOSENAN
mdefine_line|#define _FP_CHOOSENAN(fs, wc, R, X, Y, OP)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if ((_FP_FRAC_HIGH_RAW_##fs(Y) &amp; _FP_QNANBIT_##fs)&t;&t;&bslash;&n;&t;&amp;&amp; !(_FP_FRAC_HIGH_RAW_##fs(X) &amp; _FP_QNANBIT_##fs))&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;R##_s = X##_s;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_FP_FRAC_COPY_##wc(R,X);&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;R##_s = Y##_s;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_FP_FRAC_COPY_##wc(R,Y);&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    R##_c = FP_CLS_NAN;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/* Some assembly to speed things up. */
DECL|macro|__FP_FRAC_ADD_3
mdefine_line|#define __FP_FRAC_ADD_3(r2,r1,r0,x2,x1,x0,y2,y1,y0)&t;&t;&t;&bslash;&n;  __asm__ (&quot;addcc %r7,%8,%2
id|addxcc
op_mod
id|r5
comma
op_mod
l_int|6
comma
op_mod
l_int|1
id|addx
op_mod
id|r3
comma
op_mod
l_int|4
comma
op_mod
l_int|0
l_string|&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_assign
id|r
l_string|&quot; ((USItype)(r2)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((USItype)(r1)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((USItype)(r0))&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_mod
id|rJ
l_string|&quot; ((USItype)(x2)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype)(y2)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_mod
id|rJ
l_string|&quot; ((USItype)(x1)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype)(y1)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_mod
id|rJ
l_string|&quot; ((USItype)(x0)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype)(y0))&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
id|cc
"&quot;"
)paren
DECL|macro|__FP_FRAC_SUB_3
mdefine_line|#define __FP_FRAC_SUB_3(r2,r1,r0,x2,x1,x0,y2,y1,y0)&t;&t;&t;&bslash;&n;  __asm__ (&quot;subcc %r7,%8,%2
id|subxcc
op_mod
id|r5
comma
op_mod
l_int|6
comma
op_mod
l_int|1
id|subx
op_mod
id|r3
comma
op_mod
l_int|4
comma
op_mod
l_int|0
l_string|&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_assign
id|r
l_string|&quot; ((USItype)(r2)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((USItype)(r1)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((USItype)(r0))&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_mod
id|rJ
l_string|&quot; ((USItype)(x2)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype)(y2)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_mod
id|rJ
l_string|&quot; ((USItype)(x1)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype)(y1)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_mod
id|rJ
l_string|&quot; ((USItype)(x0)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype)(y0))&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
id|cc
"&quot;"
)paren
DECL|macro|__FP_FRAC_ADD_4
mdefine_line|#define __FP_FRAC_ADD_4(r3,r2,r1,r0,x3,x2,x1,x0,y3,y2,y1,y0)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    /* We need to fool gcc,  as we need to pass more than 10&t;&t;&bslash;&n;       input/outputs.  */&t;&t;&t;&t;&t;&t;&bslash;&n;    register USItype _t1 __asm__ (&quot;g1&quot;), _t2 __asm__ (&quot;g2&quot;);&t;&t;&bslash;&n;    __asm__ __volatile__ (&quot;
id|addcc
op_mod
id|r8
comma
op_mod
l_int|9
comma
op_mod
l_int|1
id|addxcc
op_mod
id|r6
comma
op_mod
l_int|7
comma
op_mod
l_int|0
id|addxcc
op_mod
id|r4
comma
op_mod
l_int|5
comma
op_mod
op_mod
id|g2
id|addx
op_mod
id|r2
comma
op_mod
l_int|3
comma
op_mod
op_mod
id|g1
l_string|&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_assign
op_amp
id|r
l_string|&quot; ((USItype)(r1)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((USItype)(r0))&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_mod
id|rJ
l_string|&quot; ((USItype)(x3)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype)(y3)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_mod
id|rJ
l_string|&quot; ((USItype)(x2)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype)(y2)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_mod
id|rJ
l_string|&quot; ((USItype)(x1)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype)(y1)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_mod
id|rJ
l_string|&quot; ((USItype)(x0)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype)(y0))&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
id|cc
l_string|&quot;, &quot;
id|g1
l_string|&quot;, &quot;
id|g2
l_string|&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;    __asm__ __volatile__ (&quot;&quot; : &quot;
op_assign
id|r
l_string|&quot; (_t1), &quot;
op_assign
id|r
"&quot;"
(paren
id|_t2
)paren
)paren
suffix:semicolon
"&bslash;"
id|r3
op_assign
id|_t1
suffix:semicolon
id|r2
op_assign
id|_t2
suffix:semicolon
"&bslash;"
)brace
r_while
c_loop
(paren
l_int|0
)paren
DECL|macro|__FP_FRAC_SUB_4
mdefine_line|#define __FP_FRAC_SUB_4(r3,r2,r1,r0,x3,x2,x1,x0,y3,y2,y1,y0)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    /* We need to fool gcc,  as we need to pass more than 10&t;&t;&bslash;&n;       input/outputs.  */&t;&t;&t;&t;&t;&t;&bslash;&n;    register USItype _t1 __asm__ (&quot;g1&quot;), _t2 __asm__ (&quot;g2&quot;);&t;&t;&bslash;&n;    __asm__ __volatile__ (&quot;
id|subcc
op_mod
id|r8
comma
op_mod
l_int|9
comma
op_mod
l_int|1
id|subxcc
op_mod
id|r6
comma
op_mod
l_int|7
comma
op_mod
l_int|0
id|subxcc
op_mod
id|r4
comma
op_mod
l_int|5
comma
op_mod
op_mod
id|g2
id|subx
op_mod
id|r2
comma
op_mod
l_int|3
comma
op_mod
op_mod
id|g1
l_string|&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_assign
op_amp
id|r
l_string|&quot; ((USItype)(r1)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((USItype)(r0))&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_mod
id|rJ
l_string|&quot; ((USItype)(x3)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype)(y3)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_mod
id|rJ
l_string|&quot; ((USItype)(x2)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype)(y2)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_mod
id|rJ
l_string|&quot; ((USItype)(x1)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype)(y1)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_mod
id|rJ
l_string|&quot; ((USItype)(x0)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype)(y0))&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
id|cc
l_string|&quot;, &quot;
id|g1
l_string|&quot;, &quot;
id|g2
l_string|&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;    __asm__ __volatile__ (&quot;&quot; : &quot;
op_assign
id|r
l_string|&quot; (_t1), &quot;
op_assign
id|r
"&quot;"
(paren
id|_t2
)paren
)paren
suffix:semicolon
"&bslash;"
id|r3
op_assign
id|_t1
suffix:semicolon
id|r2
op_assign
id|_t2
suffix:semicolon
"&bslash;"
)brace
r_while
c_loop
(paren
l_int|0
)paren
DECL|macro|__FP_FRAC_DEC_3
mdefine_line|#define __FP_FRAC_DEC_3(x2,x1,x0,y2,y1,y0) __FP_FRAC_SUB_3(x2,x1,x0,x2,x1,x0,y2,y1,y0)
DECL|macro|__FP_FRAC_DEC_4
mdefine_line|#define __FP_FRAC_DEC_4(x3,x2,x1,x0,y3,y2,y1,y0) __FP_FRAC_SUB_4(x3,x2,x1,x0,x3,x2,x1,x0,y3,y2,y1,y0)
DECL|macro|__FP_FRAC_ADDI_4
mdefine_line|#define __FP_FRAC_ADDI_4(x3,x2,x1,x0,i)&t;&t;&t;&t;&t;&bslash;&n;  __asm__ (&quot;addcc %3,%4,%3
id|addxcc
op_mod
l_int|2
comma
op_mod
op_mod
id|g0
comma
op_mod
l_int|2
id|addxcc
op_mod
l_int|1
comma
op_mod
op_mod
id|g0
comma
op_mod
l_int|1
id|addx
op_mod
l_int|0
comma
op_mod
op_mod
id|g0
comma
op_mod
l_int|0
l_string|&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_assign
op_amp
id|r
l_string|&quot; ((USItype)(x3)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((USItype)(x2)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((USItype)(x1)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((USItype)(x0))&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
id|rI
l_string|&quot; ((USItype)(i)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
l_int|0
l_string|&quot; ((USItype)(x3)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
l_int|1
l_string|&quot; ((USItype)(x2)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
l_int|2
l_string|&quot; ((USItype)(x1)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
l_int|3
l_string|&quot; ((USItype)(x0))&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
id|cc
"&quot;"
)paren
macro_line|#ifndef CONFIG_SMP
r_extern
r_struct
id|task_struct
op_star
id|last_task_used_math
suffix:semicolon
macro_line|#endif
multiline_comment|/* Obtain the current rounding mode. */
macro_line|#ifndef FP_ROUNDMODE
macro_line|#ifdef CONFIG_SMP
DECL|macro|FP_ROUNDMODE
mdefine_line|#define FP_ROUNDMODE&t;((current-&gt;thread.fsr &gt;&gt; 30) &amp; 0x3)
macro_line|#else
DECL|macro|FP_ROUNDMODE
mdefine_line|#define FP_ROUNDMODE&t;((last_task_used_math-&gt;thread.fsr &gt;&gt; 30) &amp; 0x3)
macro_line|#endif
macro_line|#endif
multiline_comment|/* Exception flags. */
DECL|macro|FP_EX_INVALID
mdefine_line|#define FP_EX_INVALID&t;&t;(1 &lt;&lt; 4)
DECL|macro|FP_EX_OVERFLOW
mdefine_line|#define FP_EX_OVERFLOW&t;&t;(1 &lt;&lt; 3)
DECL|macro|FP_EX_UNDERFLOW
mdefine_line|#define FP_EX_UNDERFLOW&t;&t;(1 &lt;&lt; 2)
DECL|macro|FP_EX_DIVZERO
mdefine_line|#define FP_EX_DIVZERO&t;&t;(1 &lt;&lt; 1)
DECL|macro|FP_EX_INEXACT
mdefine_line|#define FP_EX_INEXACT&t;&t;(1 &lt;&lt; 0)
DECL|macro|FP_HANDLE_EXCEPTIONS
mdefine_line|#define FP_HANDLE_EXCEPTIONS return _fex
macro_line|#ifdef CONFIG_SMP
DECL|macro|FP_INHIBIT_RESULTS
mdefine_line|#define FP_INHIBIT_RESULTS ((current-&gt;thread.fsr &gt;&gt; 23) &amp; _fex)
macro_line|#else
DECL|macro|FP_INHIBIT_RESULTS
mdefine_line|#define FP_INHIBIT_RESULTS ((last_task_used_math-&gt;thread.fsr &gt;&gt; 23) &amp; _fex)
macro_line|#endif
macro_line|#endif
eof
