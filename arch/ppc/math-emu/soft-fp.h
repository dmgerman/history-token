multiline_comment|/*&n; * BK Id: SCCS/s.soft-fp.h 1.5 05/17/01 18:14:23 cort&n; */
macro_line|#ifndef SOFT_FP_H
DECL|macro|SOFT_FP_H
mdefine_line|#define SOFT_FP_H
macro_line|#include &quot;sfp-machine.h&quot;
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
DECL|macro|_FP_ROUND_NEAREST
mdefine_line|#define _FP_ROUND_NEAREST(wc, X)&t;&t;&t;&bslash;&n;({  int __ret = 0;&t;&t;&t;&t;&t;&bslash;&n;    int __frac = _FP_FRAC_LOW_##wc(X) &amp; 15;&t;&t;&bslash;&n;    if (__frac &amp; 7) {&t;&t;&t;&t;&t;&bslash;&n;      __ret = EFLAG_INEXACT;&t;&t;&t;&t;&bslash;&n;      if ((__frac &amp; 7) != _FP_WORK_ROUND)&t;&t;&bslash;&n;        _FP_FRAC_ADDI_##wc(X, _FP_WORK_ROUND);&t;&t;&bslash;&n;      else if (__frac &amp; _FP_WORK_LSB)&t;&t;&t;&bslash;&n;        _FP_FRAC_ADDI_##wc(X, _FP_WORK_ROUND);&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __ret;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|_FP_ROUND_ZERO
mdefine_line|#define _FP_ROUND_ZERO(wc, X)&t;&t;&t;&t;&bslash;&n;({  int __ret = 0;&t;&t;&t;&t;&t;&bslash;&n;    if (_FP_FRAC_LOW_##wc(X) &amp; 7)&t;&t;&t;&bslash;&n;      __ret = EFLAG_INEXACT;&t;&t;&t;&t;&bslash;&n;    __ret;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|_FP_ROUND_PINF
mdefine_line|#define _FP_ROUND_PINF(wc, X)&t;&t;&t;&t;&bslash;&n;({  int __ret = EFLAG_INEXACT;&t;&t;&t;&t;&bslash;&n;    if (!X##_s &amp;&amp; (_FP_FRAC_LOW_##wc(X) &amp; 7))&t;&t;&bslash;&n;      _FP_FRAC_ADDI_##wc(X, _FP_WORK_LSB);&t;&t;&bslash;&n;    else __ret = 0;&t;&t;&t;&t;&t;&bslash;&n;    __ret;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|_FP_ROUND_MINF
mdefine_line|#define _FP_ROUND_MINF(wc, X)&t;&t;&t;&t;&bslash;&n;({  int __ret = EFLAG_INEXACT;&t;&t;&t;&t;&bslash;&n;    if (X##_s &amp;&amp; (_FP_FRAC_LOW_##wc(X) &amp; 7))&t;&t;&bslash;&n;      _FP_FRAC_ADDI_##wc(X, _FP_WORK_LSB);&t;&t;&bslash;&n;    else __ret = 0;&t;&t;&t;&t;&t;&bslash;&n;    __ret;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|_FP_ROUND
mdefine_line|#define _FP_ROUND(wc, X)&t;&t;&t;&bslash;&n;({&t;int __ret = 0;&t;&t;&t;&t;&bslash;&n;&t;switch (FP_ROUNDMODE)&t;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&bslash;&n;&t;  case FP_RND_NEAREST:&t;&t;&t;&bslash;&n;&t;    __ret |= _FP_ROUND_NEAREST(wc,X);&t;&bslash;&n;&t;    break;&t;&t;&t;&t;&bslash;&n;&t;  case FP_RND_ZERO:&t;&t;&t;&bslash;&n;&t;    __ret |= _FP_ROUND_ZERO(wc,X);&t;&bslash;&n;&t;    break;&t;&t;&t;&t;&bslash;&n;&t;  case FP_RND_PINF:&t;&t;&t;&bslash;&n;&t;    __ret |= _FP_ROUND_PINF(wc,X);&t;&bslash;&n;&t;    break;&t;&t;&t;&t;&bslash;&n;&t;  case FP_RND_MINF:&t;&t;&t;&bslash;&n;&t;    __ret |= _FP_ROUND_MINF(wc,X);&t;&bslash;&n;&t;    break;&t;&t;&t;&t;&bslash;&n;&t;};&t;&t;&t;&t;&t;&bslash;&n;&t;__ret;&t;&t;&t;&t;&t;&bslash;&n;})
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
macro_line|#endif
eof
