multiline_comment|/* Software floating-point emulation.&n;   Copyright (C) 1997,1998,1999 Free Software Foundation, Inc.&n;   This file is part of the GNU C Library.&n;   Contributed by Richard Henderson (rth@cygnus.com),&n;&t;&t;  Jakub Jelinek (jj@ultra.linux.cz),&n;&t;&t;  David S. Miller (davem@redhat.com) and&n;&t;&t;  Peter Maydell (pmaydell@chiark.greenend.org.uk).&n;&n;   The GNU C Library is free software; you can redistribute it and/or&n;   modify it under the terms of the GNU Library General Public License as&n;   published by the Free Software Foundation; either version 2 of the&n;   License, or (at your option) any later version.&n;&n;   The GNU C Library is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;   Library General Public License for more details.&n;&n;   You should have received a copy of the GNU Library General Public&n;   License along with the GNU C Library; see the file COPYING.LIB.  If&n;   not, write to the Free Software Foundation, Inc.,&n;   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
macro_line|#ifndef __MATH_EMU_SOFT_FP_H__
DECL|macro|__MATH_EMU_SOFT_FP_H__
mdefine_line|#define __MATH_EMU_SOFT_FP_H__
macro_line|#include &lt;asm/sfp-machine.h&gt;
multiline_comment|/* Allow sfp-machine to have its own byte order definitions. */
macro_line|#ifndef __BYTE_ORDER
macro_line|#include &lt;endian.h&gt;
macro_line|#endif
DECL|macro|_FP_WORKBITS
mdefine_line|#define _FP_WORKBITS&t;&t;3
DECL|macro|_FP_WORK_LSB
mdefine_line|#define _FP_WORK_LSB&t;&t;((_FP_W_TYPE)1 &lt;&lt; 3)
DECL|macro|_FP_WORK_ROUND
mdefine_line|#define _FP_WORK_ROUND&t;&t;((_FP_W_TYPE)1 &lt;&lt; 2)
DECL|macro|_FP_WORK_GUARD
mdefine_line|#define _FP_WORK_GUARD&t;&t;((_FP_W_TYPE)1 &lt;&lt; 1)
DECL|macro|_FP_WORK_STICKY
mdefine_line|#define _FP_WORK_STICKY&t;&t;((_FP_W_TYPE)1 &lt;&lt; 0)
macro_line|#ifndef FP_RND_NEAREST
DECL|macro|FP_RND_NEAREST
macro_line|# define FP_RND_NEAREST&t;&t;0
DECL|macro|FP_RND_ZERO
macro_line|# define FP_RND_ZERO&t;&t;1
DECL|macro|FP_RND_PINF
macro_line|# define FP_RND_PINF&t;&t;2
DECL|macro|FP_RND_MINF
macro_line|# define FP_RND_MINF&t;&t;3
macro_line|#ifndef FP_ROUNDMODE
DECL|macro|FP_ROUNDMODE
macro_line|# define FP_ROUNDMODE&t;&t;FP_RND_NEAREST
macro_line|#endif
macro_line|#endif
multiline_comment|/* By default don&squot;t care about exceptions. */
macro_line|#ifndef FP_EX_INVALID
DECL|macro|FP_EX_INVALID
mdefine_line|#define FP_EX_INVALID&t;&t;0
macro_line|#endif
macro_line|#ifndef FP_EX_OVERFLOW
DECL|macro|FP_EX_OVERFLOW
mdefine_line|#define FP_EX_OVERFLOW&t;&t;0
macro_line|#endif
macro_line|#ifndef FP_EX_UNDERFLOW
DECL|macro|FP_EX_UNDERFLOW
mdefine_line|#define FP_EX_UNDERFLOW&t;&t;
macro_line|#endif
macro_line|#ifndef FP_EX_DIVZERO
DECL|macro|FP_EX_DIVZERO
mdefine_line|#define FP_EX_DIVZERO&t;&t;0
macro_line|#endif
macro_line|#ifndef FP_EX_INEXACT
DECL|macro|FP_EX_INEXACT
mdefine_line|#define FP_EX_INEXACT&t;&t;0
macro_line|#endif
macro_line|#ifndef FP_EX_DENORM
DECL|macro|FP_EX_DENORM
mdefine_line|#define FP_EX_DENORM&t;&t;0
macro_line|#endif
macro_line|#ifdef _FP_DECL_EX
DECL|macro|FP_DECL_EX
mdefine_line|#define FP_DECL_EX&t;&t;&t;&t;&t;&bslash;&n;  int _fex = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;  _FP_DECL_EX
macro_line|#else
DECL|macro|FP_DECL_EX
mdefine_line|#define FP_DECL_EX int _fex = 0
macro_line|#endif
macro_line|#ifndef FP_INIT_ROUNDMODE
DECL|macro|FP_INIT_ROUNDMODE
mdefine_line|#define FP_INIT_ROUNDMODE do {} while (0)
macro_line|#endif
macro_line|#ifndef FP_HANDLE_EXCEPTIONS
DECL|macro|FP_HANDLE_EXCEPTIONS
mdefine_line|#define FP_HANDLE_EXCEPTIONS do {} while (0)
macro_line|#endif
multiline_comment|/* By default we never flush denormal input operands to signed zero. */
macro_line|#ifndef FP_DENORM_ZERO
DECL|macro|FP_DENORM_ZERO
mdefine_line|#define FP_DENORM_ZERO 0
macro_line|#endif
macro_line|#ifndef FP_INHIBIT_RESULTS
multiline_comment|/* By default we write the results always.&n; * sfp-machine may override this and e.g.&n; * check if some exceptions are unmasked&n; * and inhibit it in such a case.&n; */
DECL|macro|FP_INHIBIT_RESULTS
mdefine_line|#define FP_INHIBIT_RESULTS 0
macro_line|#endif
DECL|macro|FP_SET_EXCEPTION
mdefine_line|#define FP_SET_EXCEPTION(ex)&t;&t;&t;&t;&bslash;&n;  _fex |= (ex)
DECL|macro|FP_UNSET_EXCEPTION
mdefine_line|#define FP_UNSET_EXCEPTION(ex)&t;&t;&t;&t;&bslash;&n;  _fex &amp;= ~(ex)
DECL|macro|FP_CLEAR_EXCEPTIONS
mdefine_line|#define FP_CLEAR_EXCEPTIONS&t;&t;&t;&t;&bslash;&n;  _fex = 0
DECL|macro|_FP_ROUND_NEAREST
mdefine_line|#define _FP_ROUND_NEAREST(wc, X)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if ((_FP_FRAC_LOW_##wc(X) &amp; 15) != _FP_WORK_ROUND)&t;&bslash;&n;      _FP_FRAC_ADDI_##wc(X, _FP_WORK_ROUND);&t;&t;&bslash;&n;} while (0)
DECL|macro|_FP_ROUND_ZERO
mdefine_line|#define _FP_ROUND_ZERO(wc, X)&t;&t;0
DECL|macro|_FP_ROUND_PINF
mdefine_line|#define _FP_ROUND_PINF(wc, X)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (!X##_s &amp;&amp; (_FP_FRAC_LOW_##wc(X) &amp; 7))&t;&t;&bslash;&n;      _FP_FRAC_ADDI_##wc(X, _FP_WORK_LSB);&t;&t;&bslash;&n;} while (0)
DECL|macro|_FP_ROUND_MINF
mdefine_line|#define _FP_ROUND_MINF(wc, X)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (X##_s &amp;&amp; (_FP_FRAC_LOW_##wc(X) &amp; 7))&t;&t;&bslash;&n;      _FP_FRAC_ADDI_##wc(X, _FP_WORK_LSB);&t;&t;&bslash;&n;} while (0)
DECL|macro|_FP_ROUND
mdefine_line|#define _FP_ROUND(wc, X)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (_FP_FRAC_LOW_##wc(X) &amp; 7)&t;&t;&bslash;&n;&t;  FP_SET_EXCEPTION(FP_EX_INEXACT);&t;&bslash;&n;&t;switch (FP_ROUNDMODE)&t;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&bslash;&n;&t;  case FP_RND_NEAREST:&t;&t;&t;&bslash;&n;&t;    _FP_ROUND_NEAREST(wc,X);&t;&t;&bslash;&n;&t;    break;&t;&t;&t;&t;&bslash;&n;&t;  case FP_RND_ZERO:&t;&t;&t;&bslash;&n;&t;    _FP_ROUND_ZERO(wc,X);&t;&t;&bslash;&n;&t;    break;&t;&t;&t;&t;&bslash;&n;&t;  case FP_RND_PINF:&t;&t;&t;&bslash;&n;&t;    _FP_ROUND_PINF(wc,X);&t;&t;&bslash;&n;&t;    break;&t;&t;&t;&t;&bslash;&n;&t;  case FP_RND_MINF:&t;&t;&t;&bslash;&n;&t;    _FP_ROUND_MINF(wc,X);&t;&t;&bslash;&n;&t;    break;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|FP_CLS_NORMAL
mdefine_line|#define FP_CLS_NORMAL&t;&t;0
DECL|macro|FP_CLS_ZERO
mdefine_line|#define FP_CLS_ZERO&t;&t;1
DECL|macro|FP_CLS_INF
mdefine_line|#define FP_CLS_INF&t;&t;2
DECL|macro|FP_CLS_NAN
mdefine_line|#define FP_CLS_NAN&t;&t;3
DECL|macro|_FP_CLS_COMBINE
mdefine_line|#define _FP_CLS_COMBINE(x,y)&t;(((x) &lt;&lt; 2) | (y))
macro_line|#include &quot;op-1.h&quot;
macro_line|#include &quot;op-2.h&quot;
macro_line|#include &quot;op-4.h&quot;
macro_line|#include &quot;op-8.h&quot;
macro_line|#include &quot;op-common.h&quot;
multiline_comment|/* Sigh.  Silly things longlong.h needs.  */
DECL|macro|UWtype
mdefine_line|#define UWtype&t;&t;_FP_W_TYPE
DECL|macro|W_TYPE_SIZE
mdefine_line|#define W_TYPE_SIZE&t;_FP_W_TYPE_SIZE
DECL|typedef|SItype
r_typedef
r_int
id|SItype
id|__attribute__
c_func
(paren
(paren
id|mode
c_func
(paren
id|SI
)paren
)paren
)paren
suffix:semicolon
DECL|typedef|DItype
r_typedef
r_int
id|DItype
id|__attribute__
c_func
(paren
(paren
id|mode
c_func
(paren
id|DI
)paren
)paren
)paren
suffix:semicolon
DECL|typedef|USItype
r_typedef
r_int
r_int
id|USItype
id|__attribute__
c_func
(paren
(paren
id|mode
c_func
(paren
id|SI
)paren
)paren
)paren
suffix:semicolon
DECL|typedef|UDItype
r_typedef
r_int
r_int
id|UDItype
id|__attribute__
c_func
(paren
(paren
id|mode
c_func
(paren
id|DI
)paren
)paren
)paren
suffix:semicolon
macro_line|#if _FP_W_TYPE_SIZE == 32
DECL|typedef|UHWtype
r_typedef
r_int
r_int
id|UHWtype
id|__attribute__
c_func
(paren
(paren
id|mode
c_func
(paren
id|HI
)paren
)paren
)paren
suffix:semicolon
macro_line|#elif _FP_W_TYPE_SIZE == 64
DECL|typedef|UHWtype
r_typedef
id|USItype
id|UHWtype
suffix:semicolon
macro_line|#endif
macro_line|#ifndef umul_ppmm
macro_line|#include &lt;stdlib/longlong.h&gt;
macro_line|#endif
macro_line|#endif /* __MATH_EMU_SOFT_FP_H__ */
eof
