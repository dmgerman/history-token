multiline_comment|/* Machine-dependent software floating-point definitions.&n;   S/390 kernel version.&n;   Copyright (C) 1997,1998,1999 Free Software Foundation, Inc.&n;   This file is part of the GNU C Library.&n;   Contributed by Richard Henderson (rth@cygnus.com),&n;&t;&t;  Jakub Jelinek (jj@ultra.linux.cz),&n;&t;&t;  David S. Miller (davem@redhat.com) and&n;&t;&t;  Peter Maydell (pmaydell@chiark.greenend.org.uk).&n;&n;   The GNU C Library is free software; you can redistribute it and/or&n;   modify it under the terms of the GNU Library General Public License as&n;   published by the Free Software Foundation; either version 2 of the&n;   License, or (at your option) any later version.&n;&n;   The GNU C Library is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;   Library General Public License for more details.&n;&n;   You should have received a copy of the GNU Library General Public&n;   License along with the GNU C Library; see the file COPYING.LIB.  If&n;   not, write to the Free Software Foundation, Inc.,&n;   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
multiline_comment|/*&n; * If one NaN is signaling and the other is not,&n; * we choose that one, otherwise we choose X.&n; */
DECL|macro|_FP_CHOOSENAN
mdefine_line|#define _FP_CHOOSENAN(fs, wc, R, X, Y, OP)                      &bslash;&n;  do {                                                          &bslash;&n;    if ((_FP_FRAC_HIGH_RAW_##fs(X) &amp; _FP_QNANBIT_##fs)          &bslash;&n;        &amp;&amp; !(_FP_FRAC_HIGH_RAW_##fs(Y) &amp; _FP_QNANBIT_##fs))     &bslash;&n;      {                                                         &bslash;&n;        R##_s = Y##_s;                                          &bslash;&n;        _FP_FRAC_COPY_##wc(R,Y);                                &bslash;&n;      }                                                         &bslash;&n;    else                                                        &bslash;&n;      {                                                         &bslash;&n;        R##_s = X##_s;                                          &bslash;&n;        _FP_FRAC_COPY_##wc(R,X);                                &bslash;&n;      }                                                         &bslash;&n;    R##_c = FP_CLS_NAN;                                         &bslash;&n;  } while (0)
multiline_comment|/* Some assembly to speed things up. */
DECL|macro|__FP_FRAC_ADD_3
mdefine_line|#define __FP_FRAC_ADD_3(r2,r1,r0,x2,x1,x0,y2,y1,y0) ({&t;&t;&bslash;&n;&t;unsigned int __r2 = (x2) + (y2);&t;&t;&t;&bslash;&n;&t;unsigned int __r1 = (x1);&t;&t;&t;&t;&bslash;&n;&t;unsigned int __r0 = (x0);&t;&t;&t;&t;&bslash;&n;&t;__asm__ (&quot;   alr %2,%3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;   brc 12,0f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;   lhi 0,1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;   alr %1,0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;   brc 12,0f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;   alr %0,0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;0:&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; : &quot;+&amp;d&quot; (__r2), &quot;+&amp;d&quot; (__r1), &quot;+&amp;d&quot; (__r0)&t;&bslash;&n;&t;&t; : &quot;d&quot; (y0), &quot;i&quot; (1) : &quot;cc&quot;, &quot;0&quot; );&t;&t;&bslash;&n;&t;__asm__ (&quot;   alr %1,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;   brc 12,0f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;   ahi %0,1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;0:&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; : &quot;+&amp;d&quot; (__r2), &quot;+&amp;d&quot; (__r1)&t;&t;&t;&bslash;&n;&t;&t; : &quot;d&quot; (y1) : &quot;cc&quot; );&t;&t;&t;&t;&bslash;&n;&t;(r2) = __r2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(r1) = __r1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(r0) = __r0;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__FP_FRAC_SUB_3
mdefine_line|#define __FP_FRAC_SUB_3(r2,r1,r0,x2,x1,x0,y2,y1,y0) ({&t;&t;&bslash;&n;&t;unsigned int __r2 = (x2) - (y2);&t;&t;&t;&bslash;&n;&t;unsigned int __r1 = (x1);&t;&t;&t;&t;&bslash;&n;&t;unsigned int __r0 = (x0);&t;&t;&t;&t;&bslash;&n;&t;__asm__ (&quot;   slr %2,%3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;   brc 3,0f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;   lhi 0,1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;   slr %1,0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;   brc 3,0f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;   slr %0,0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;0:&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; : &quot;+&amp;d&quot; (__r2), &quot;+&amp;d&quot; (__r1), &quot;+&amp;d&quot; (__r0)&t;&bslash;&n;&t;&t; : &quot;d&quot; (y0) : &quot;cc&quot;, &quot;0&quot; );&t;&t;&t;&bslash;&n;&t;__asm__ (&quot;   slr %1,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;   brc 3,0f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;   ahi %0,-1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;0:&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; : &quot;+&amp;d&quot; (__r2), &quot;+&amp;d&quot; (__r1)&t;&t;&t;&bslash;&n;&t;&t; : &quot;d&quot; (y1) : &quot;cc&quot; );&t;&t;&t;&t;&bslash;&n;&t;(r2) = __r2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(r1) = __r1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(r0) = __r0;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__FP_FRAC_DEC_3
mdefine_line|#define __FP_FRAC_DEC_3(x2,x1,x0,y2,y1,y0) __FP_FRAC_SUB_3(x2,x1,x0,x2,x1,x0,y2,y1,y0)
multiline_comment|/* Obtain the current rounding mode. */
DECL|macro|FP_ROUNDMODE
mdefine_line|#define FP_ROUNDMODE&t;mode
multiline_comment|/* Exception flags. */
DECL|macro|FP_EX_INVALID
mdefine_line|#define FP_EX_INVALID&t;&t;0x800000
DECL|macro|FP_EX_DIVZERO
mdefine_line|#define FP_EX_DIVZERO&t;&t;0x400000
DECL|macro|FP_EX_OVERFLOW
mdefine_line|#define FP_EX_OVERFLOW&t;&t;0x200000
DECL|macro|FP_EX_UNDERFLOW
mdefine_line|#define FP_EX_UNDERFLOW&t;&t;0x100000
DECL|macro|FP_EX_INEXACT
mdefine_line|#define FP_EX_INEXACT&t;&t;0x080000
multiline_comment|/* We write the results always */
DECL|macro|FP_INHIBIT_RESULTS
mdefine_line|#define FP_INHIBIT_RESULTS 0
macro_line|#endif
eof
