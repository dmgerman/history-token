multiline_comment|/* Software floating-point emulation.&n;   Definitions for IEEE Extended Precision.&n;   Copyright (C) 1999 Free Software Foundation, Inc.&n;   This file is part of the GNU C Library.&n;   Contributed by Jakub Jelinek (jj@ultra.linux.cz).&n;&n;   The GNU C Library is free software; you can redistribute it and/or&n;   modify it under the terms of the GNU Library General Public License as&n;   published by the Free Software Foundation; either version 2 of the&n;   License, or (at your option) any later version.&n;&n;   The GNU C Library is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;   Library General Public License for more details.&n;&n;   You should have received a copy of the GNU Library General Public&n;   License along with the GNU C Library; see the file COPYING.LIB.  If&n;   not, write to the Free Software Foundation, Inc.,&n;   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
macro_line|#ifndef    __MATH_EMU_EXTENDED_H__
DECL|macro|__MATH_EMU_EXTENDED_H__
mdefine_line|#define    __MATH_EMU_EXTENDED_H__
macro_line|#if _FP_W_TYPE_SIZE &lt; 32
macro_line|#error &quot;Here&squot;s a nickel, kid. Go buy yourself a real computer.&quot;
macro_line|#endif
macro_line|#if _FP_W_TYPE_SIZE &lt; 64
DECL|macro|_FP_FRACTBITS_E
mdefine_line|#define _FP_FRACTBITS_E         (4*_FP_W_TYPE_SIZE)
macro_line|#else
DECL|macro|_FP_FRACTBITS_E
mdefine_line|#define _FP_FRACTBITS_E&t;&t;(2*_FP_W_TYPE_SIZE)
macro_line|#endif
DECL|macro|_FP_FRACBITS_E
mdefine_line|#define _FP_FRACBITS_E&t;&t;64
DECL|macro|_FP_FRACXBITS_E
mdefine_line|#define _FP_FRACXBITS_E&t;&t;(_FP_FRACTBITS_E - _FP_FRACBITS_E)
DECL|macro|_FP_WFRACBITS_E
mdefine_line|#define _FP_WFRACBITS_E&t;&t;(_FP_WORKBITS + _FP_FRACBITS_E)
DECL|macro|_FP_WFRACXBITS_E
mdefine_line|#define _FP_WFRACXBITS_E&t;(_FP_FRACTBITS_E - _FP_WFRACBITS_E)
DECL|macro|_FP_EXPBITS_E
mdefine_line|#define _FP_EXPBITS_E&t;&t;15
DECL|macro|_FP_EXPBIAS_E
mdefine_line|#define _FP_EXPBIAS_E&t;&t;16383
DECL|macro|_FP_EXPMAX_E
mdefine_line|#define _FP_EXPMAX_E&t;&t;32767
DECL|macro|_FP_QNANBIT_E
mdefine_line|#define _FP_QNANBIT_E&t;&t;&bslash;&n;&t;((_FP_W_TYPE)1 &lt;&lt; (_FP_FRACBITS_E-2) % _FP_W_TYPE_SIZE)
DECL|macro|_FP_IMPLBIT_E
mdefine_line|#define _FP_IMPLBIT_E&t;&t;&bslash;&n;&t;((_FP_W_TYPE)1 &lt;&lt; (_FP_FRACBITS_E-1) % _FP_W_TYPE_SIZE)
DECL|macro|_FP_OVERFLOW_E
mdefine_line|#define _FP_OVERFLOW_E&t;&t;&bslash;&n;&t;((_FP_W_TYPE)1 &lt;&lt; (_FP_WFRACBITS_E % _FP_W_TYPE_SIZE))
macro_line|#if _FP_W_TYPE_SIZE &lt; 64
DECL|union|_FP_UNION_E
r_union
id|_FP_UNION_E
(brace
DECL|member|flt
r_int
r_float
id|flt
suffix:semicolon
r_struct
(brace
macro_line|#if __BYTE_ORDER == __BIG_ENDIAN
DECL|member|pad1
r_int
r_int
id|pad1
suffix:colon
id|_FP_W_TYPE_SIZE
suffix:semicolon
DECL|member|pad2
r_int
r_int
id|pad2
suffix:colon
(paren
id|_FP_W_TYPE_SIZE
op_minus
l_int|1
op_minus
id|_FP_EXPBITS_E
)paren
suffix:semicolon
DECL|member|sign
r_int
r_int
id|sign
suffix:colon
l_int|1
suffix:semicolon
DECL|member|exp
r_int
r_int
id|exp
suffix:colon
id|_FP_EXPBITS_E
suffix:semicolon
DECL|member|frac1
r_int
r_int
id|frac1
suffix:colon
id|_FP_W_TYPE_SIZE
suffix:semicolon
DECL|member|frac0
r_int
r_int
id|frac0
suffix:colon
id|_FP_W_TYPE_SIZE
suffix:semicolon
macro_line|#else
r_int
r_int
id|frac0
suffix:colon
id|_FP_W_TYPE_SIZE
suffix:semicolon
r_int
r_int
id|frac1
suffix:colon
id|_FP_W_TYPE_SIZE
suffix:semicolon
r_int
id|exp
suffix:colon
id|_FP_EXPBITS_E
suffix:semicolon
r_int
id|sign
suffix:colon
l_int|1
suffix:semicolon
macro_line|#endif /* not bigendian */
DECL|member|bits
)brace
id|bits
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FP_DECL_E
mdefine_line|#define FP_DECL_E(X)&t;&t;_FP_DECL(4,X)
DECL|macro|FP_UNPACK_RAW_E
mdefine_line|#define FP_UNPACK_RAW_E(X, val)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_E _flo; _flo.flt = (val);&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_f[2] = 0; X##_f[3] = 0;&t;&t;&t;&t;&bslash;&n;    X##_f[0] = _flo.bits.frac0;&t;&t;&t;&t;&bslash;&n;    X##_f[1] = _flo.bits.frac1;&t;&t;&t;&t;&bslash;&n;    X##_e  = _flo.bits.exp;&t;&t;&t;&t;&bslash;&n;    X##_s  = _flo.bits.sign;&t;&t;&t;&t;&bslash;&n;    if (!X##_e &amp;&amp; (X##_f[1] || X##_f[0])&t;&t;&bslash;&n;        &amp;&amp; !(X##_f[1] &amp; _FP_IMPLBIT_E))&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        X##_e++;&t;&t;&t;&t;&t;&bslash;&n;        FP_SET_EXCEPTION(FP_EX_DENORM);&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_RAW_EP
mdefine_line|#define FP_UNPACK_RAW_EP(X, val)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_E *_flo =&t;&t;&t;&t;&bslash;&n;    (union _FP_UNION_E *)(val);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_f[2] = 0; X##_f[3] = 0;&t;&t;&t;&t;&bslash;&n;    X##_f[0] = _flo-&gt;bits.frac0;&t;&t;&t;&bslash;&n;    X##_f[1] = _flo-&gt;bits.frac1;&t;&t;&t;&bslash;&n;    X##_e  = _flo-&gt;bits.exp;&t;&t;&t;&t;&bslash;&n;    X##_s  = _flo-&gt;bits.sign;&t;&t;&t;&t;&bslash;&n;    if (!X##_e &amp;&amp; (X##_f[1] || X##_f[0])&t;&t;&bslash;&n;        &amp;&amp; !(X##_f[1] &amp; _FP_IMPLBIT_E))&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        X##_e++;&t;&t;&t;&t;&t;&bslash;&n;        FP_SET_EXCEPTION(FP_EX_DENORM);&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_RAW_E
mdefine_line|#define FP_PACK_RAW_E(val, X)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_E _flo;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (X##_e) X##_f[1] |= _FP_IMPLBIT_E;&t;&t;&bslash;&n;    else X##_f[1] &amp;= ~(_FP_IMPLBIT_E);&t;&t;&t;&bslash;&n;    _flo.bits.frac0 = X##_f[0];&t;&t;&t;&t;&bslash;&n;    _flo.bits.frac1 = X##_f[1];&t;&t;&t;&t;&bslash;&n;    _flo.bits.exp   = X##_e;&t;&t;&t;&t;&bslash;&n;    _flo.bits.sign  = X##_s;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    (val) = _flo.flt;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_RAW_EP
mdefine_line|#define FP_PACK_RAW_EP(val, X)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (!FP_INHIBIT_RESULTS)&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;union _FP_UNION_E *_flo =&t;&t;&t;&bslash;&n;&t;  (union _FP_UNION_E *)(val);&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (X##_e) X##_f[1] |= _FP_IMPLBIT_E;&t;&t;&bslash;&n;&t;else X##_f[1] &amp;= ~(_FP_IMPLBIT_E);&t;&t;&bslash;&n;&t;_flo-&gt;bits.frac0 = X##_f[0];&t;&t;&t;&bslash;&n;&t;_flo-&gt;bits.frac1 = X##_f[1];&t;&t;&t;&bslash;&n;&t;_flo-&gt;bits.exp   = X##_e;&t;&t;&t;&bslash;&n;&t;_flo-&gt;bits.sign  = X##_s;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_E
mdefine_line|#define FP_UNPACK_E(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    FP_UNPACK_RAW_E(X,val);&t;&t;&bslash;&n;    _FP_UNPACK_CANONICAL(E,4,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_EP
mdefine_line|#define FP_UNPACK_EP(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    FP_UNPACK_RAW_2_P(X,val);&t;&t;&bslash;&n;    _FP_UNPACK_CANONICAL(E,4,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_E
mdefine_line|#define FP_PACK_E(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_PACK_CANONICAL(E,4,X);&t;&t;&bslash;&n;    FP_PACK_RAW_E(val,X);&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_EP
mdefine_line|#define FP_PACK_EP(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_PACK_CANONICAL(E,4,X);&t;&t;&bslash;&n;    FP_PACK_RAW_EP(val,X);&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_ISSIGNAN_E
mdefine_line|#define FP_ISSIGNAN_E(X)&t;_FP_ISSIGNAN(E,4,X)
DECL|macro|FP_NEG_E
mdefine_line|#define FP_NEG_E(R,X)&t;&t;_FP_NEG(E,4,R,X)
DECL|macro|FP_ADD_E
mdefine_line|#define FP_ADD_E(R,X,Y)&t;&t;_FP_ADD(E,4,R,X,Y)
DECL|macro|FP_SUB_E
mdefine_line|#define FP_SUB_E(R,X,Y)&t;&t;_FP_SUB(E,4,R,X,Y)
DECL|macro|FP_MUL_E
mdefine_line|#define FP_MUL_E(R,X,Y)&t;&t;_FP_MUL(E,4,R,X,Y)
DECL|macro|FP_DIV_E
mdefine_line|#define FP_DIV_E(R,X,Y)&t;&t;_FP_DIV(E,4,R,X,Y)
DECL|macro|FP_SQRT_E
mdefine_line|#define FP_SQRT_E(R,X)&t;&t;_FP_SQRT(E,4,R,X)
multiline_comment|/*&n; * Square root algorithms:&n; * We have just one right now, maybe Newton approximation&n; * should be added for those machines where division is fast.&n; * This has special _E version because standard _4 square&n; * root would not work (it has to start normally with the&n; * second word and not the first), but as we have to do it&n; * anyway, we optimize it by doing most of the calculations&n; * in two UWtype registers instead of four.&n; */
DECL|macro|_FP_SQRT_MEAT_E
mdefine_line|#define _FP_SQRT_MEAT_E(R, S, T, X, q)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    q = (_FP_W_TYPE)1 &lt;&lt; (_FP_W_TYPE_SIZE - 1);&t;&t;&bslash;&n;    _FP_FRAC_SRL_4(X, (_FP_WORKBITS));&t;&t;&t;&bslash;&n;    while (q)&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;T##_f[1] = S##_f[1] + q;&t;&t;&t;&bslash;&n;&t;if (T##_f[1] &lt;= X##_f[1])&t;&t;&t;&bslash;&n;&t;  {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    S##_f[1] = T##_f[1] + q;&t;&t;&t;&bslash;&n;&t;    X##_f[1] -= T##_f[1];&t;&t;&t;&bslash;&n;&t;    R##_f[1] += q;&t;&t;&t;&t;&bslash;&n;&t;  }&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_FP_FRAC_SLL_2(X, 1);&t;&t;&t;&t;&bslash;&n;&t;q &gt;&gt;= 1;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    q = (_FP_W_TYPE)1 &lt;&lt; (_FP_W_TYPE_SIZE - 1);&t;&t;&bslash;&n;    while (q)&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;T##_f[0] = S##_f[0] + q;&t;&t;&t;&bslash;&n;&t;T##_f[1] = S##_f[1];&t;&t;&t;&t;&bslash;&n;&t;if (T##_f[1] &lt; X##_f[1] || &t;&t;&t;&bslash;&n;&t;    (T##_f[1] == X##_f[1] &amp;&amp;&t;&t;&t;&bslash;&n;&t;     T##_f[0] &lt;= X##_f[0]))&t;&t;&t;&bslash;&n;&t;  {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    S##_f[0] = T##_f[0] + q;&t;&t;&t;&bslash;&n;&t;    S##_f[1] += (T##_f[0] &gt; S##_f[0]);&t;&t;&bslash;&n;&t;    _FP_FRAC_DEC_2(X, T);&t;&t;&t;&bslash;&n;&t;    R##_f[0] += q;&t;&t;&t;&t;&bslash;&n;&t;  }&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_FP_FRAC_SLL_2(X, 1);&t;&t;&t;&t;&bslash;&n;&t;q &gt;&gt;= 1;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_SLL_4(R, (_FP_WORKBITS));&t;&t;&t;&bslash;&n;    if (X##_f[0] | X##_f[1])&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (S##_f[1] &lt; X##_f[1] || &t;&t;&t;&bslash;&n;&t;    (S##_f[1] == X##_f[1] &amp;&amp;&t;&t;&t;&bslash;&n;&t;     S##_f[0] &lt; X##_f[0]))&t;&t;&t;&bslash;&n;&t;  R##_f[0] |= _FP_WORK_ROUND;&t;&t;&t;&bslash;&n;&t;R##_f[0] |= _FP_WORK_STICKY;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_CMP_E
mdefine_line|#define FP_CMP_E(r,X,Y,un)&t;_FP_CMP(E,4,r,X,Y,un)
DECL|macro|FP_CMP_EQ_E
mdefine_line|#define FP_CMP_EQ_E(r,X,Y)&t;_FP_CMP_EQ(E,4,r,X,Y)
DECL|macro|FP_TO_INT_E
mdefine_line|#define FP_TO_INT_E(r,X,rsz,rsg)&t;_FP_TO_INT(E,4,r,X,rsz,rsg)
DECL|macro|FP_TO_INT_ROUND_E
mdefine_line|#define FP_TO_INT_ROUND_E(r,X,rsz,rsg)&t;_FP_TO_INT_ROUND(E,4,r,X,rsz,rsg)
DECL|macro|FP_FROM_INT_E
mdefine_line|#define FP_FROM_INT_E(X,r,rs,rt)&t;_FP_FROM_INT(E,4,X,r,rs,rt)
DECL|macro|_FP_FRAC_HIGH_E
mdefine_line|#define _FP_FRAC_HIGH_E(X)&t;(X##_f[2])
DECL|macro|_FP_FRAC_HIGH_RAW_E
mdefine_line|#define _FP_FRAC_HIGH_RAW_E(X)&t;(X##_f[1])
macro_line|#else   /* not _FP_W_TYPE_SIZE &lt; 64 */
DECL|union|_FP_UNION_E
r_union
id|_FP_UNION_E
(brace
DECL|member|flt
r_int
r_float
id|flt
multiline_comment|/* __attribute__((mode(TF))) */
suffix:semicolon
r_struct
(brace
macro_line|#if __BYTE_ORDER == __BIG_ENDIAN
DECL|member|pad
r_int
r_int
id|pad
suffix:colon
(paren
id|_FP_W_TYPE_SIZE
op_minus
l_int|1
op_minus
id|_FP_EXPBITS_E
)paren
suffix:semicolon
DECL|member|sign
r_int
id|sign
suffix:colon
l_int|1
suffix:semicolon
DECL|member|exp
r_int
id|exp
suffix:colon
id|_FP_EXPBITS_E
suffix:semicolon
DECL|member|frac
r_int
r_int
id|frac
suffix:colon
id|_FP_W_TYPE_SIZE
suffix:semicolon
macro_line|#else
r_int
r_int
id|frac
suffix:colon
id|_FP_W_TYPE_SIZE
suffix:semicolon
r_int
id|exp
suffix:colon
id|_FP_EXPBITS_E
suffix:semicolon
r_int
id|sign
suffix:colon
l_int|1
suffix:semicolon
macro_line|#endif
DECL|member|bits
)brace
id|bits
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FP_DECL_E
mdefine_line|#define FP_DECL_E(X)&t;&t;_FP_DECL(2,X)
DECL|macro|FP_UNPACK_RAW_E
mdefine_line|#define FP_UNPACK_RAW_E(X, val)&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_E _flo; _flo.flt = (val);&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_f0 = _flo.bits.frac;&t;&t;&t;&t;&t;&bslash;&n;    X##_f1 = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_e = _flo.bits.exp;&t;&t;&t;&t;&t;&bslash;&n;    X##_s = _flo.bits.sign;&t;&t;&t;&t;&t;&bslash;&n;    if (!X##_e &amp;&amp; X##_f0 &amp;&amp; !(X##_f0 &amp; _FP_IMPLBIT_E))&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        X##_e++;&t;&t;&t;&t;&t;&t;&bslash;&n;        FP_SET_EXCEPTION(FP_EX_DENORM);&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_RAW_EP
mdefine_line|#define FP_UNPACK_RAW_EP(X, val)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_E *_flo =&t;&t;&t;&t;&t;&bslash;&n;      (union _FP_UNION_E *)(val);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_f0 = _flo-&gt;bits.frac;&t;&t;&t;&t;&t;&bslash;&n;    X##_f1 = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_e = _flo-&gt;bits.exp;&t;&t;&t;&t;&t;&bslash;&n;    X##_s = _flo-&gt;bits.sign;&t;&t;&t;&t;&t;&bslash;&n;    if (!X##_e &amp;&amp; X##_f0 &amp;&amp; !(X##_f0 &amp; _FP_IMPLBIT_E))&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        X##_e++;&t;&t;&t;&t;&t;&t;&bslash;&n;        FP_SET_EXCEPTION(FP_EX_DENORM);&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_RAW_E
mdefine_line|#define FP_PACK_RAW_E(val, X)&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_E _flo;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (X##_e) X##_f0 |= _FP_IMPLBIT_E;&t;&t;&t;&t;&bslash;&n;    else X##_f0 &amp;= ~(_FP_IMPLBIT_E);&t;&t;&t;&t;&bslash;&n;    _flo.bits.frac = X##_f0;&t;&t;&t;&t;&t;&bslash;&n;    _flo.bits.exp  = X##_e;&t;&t;&t;&t;&t;&bslash;&n;    _flo.bits.sign = X##_s;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    (val) = _flo.flt;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_RAW_EP
mdefine_line|#define FP_PACK_RAW_EP(fs, val, X)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (!FP_INHIBIT_RESULTS)&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;union _FP_UNION_E *_flo =&t;&t;&t;&t;&bslash;&n;&t;  (union _FP_UNION_E *)(val);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (X##_e) X##_f0 |= _FP_IMPLBIT_E;&t;&t;&t;&bslash;&n;&t;else X##_f0 &amp;= ~(_FP_IMPLBIT_E);&t;&t;&t;&bslash;&n;&t;_flo-&gt;bits.frac = X##_f0;&t;&t;&t;&t;&bslash;&n;&t;_flo-&gt;bits.exp  = X##_e;&t;&t;&t;&t;&bslash;&n;&t;_flo-&gt;bits.sign = X##_s;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_E
mdefine_line|#define FP_UNPACK_E(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    FP_UNPACK_RAW_E(X,val);&t;&t;&bslash;&n;    _FP_UNPACK_CANONICAL(E,2,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_EP
mdefine_line|#define FP_UNPACK_EP(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    FP_UNPACK_RAW_EP(X,val);&t;&t;&bslash;&n;    _FP_UNPACK_CANONICAL(E,2,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_E
mdefine_line|#define FP_PACK_E(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_PACK_CANONICAL(E,2,X);&t;&t;&bslash;&n;    FP_PACK_RAW_E(val,X);&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_EP
mdefine_line|#define FP_PACK_EP(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_PACK_CANONICAL(E,2,X);&t;&t;&bslash;&n;    FP_PACK_RAW_EP(val,X);&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_ISSIGNAN_E
mdefine_line|#define FP_ISSIGNAN_E(X)&t;_FP_ISSIGNAN(E,2,X)
DECL|macro|FP_NEG_E
mdefine_line|#define FP_NEG_E(R,X)&t;&t;_FP_NEG(E,2,R,X)
DECL|macro|FP_ADD_E
mdefine_line|#define FP_ADD_E(R,X,Y)&t;&t;_FP_ADD(E,2,R,X,Y)
DECL|macro|FP_SUB_E
mdefine_line|#define FP_SUB_E(R,X,Y)&t;&t;_FP_SUB(E,2,R,X,Y)
DECL|macro|FP_MUL_E
mdefine_line|#define FP_MUL_E(R,X,Y)&t;&t;_FP_MUL(E,2,R,X,Y)
DECL|macro|FP_DIV_E
mdefine_line|#define FP_DIV_E(R,X,Y)&t;&t;_FP_DIV(E,2,R,X,Y)
DECL|macro|FP_SQRT_E
mdefine_line|#define FP_SQRT_E(R,X)&t;&t;_FP_SQRT(E,2,R,X)
multiline_comment|/*&n; * Square root algorithms:&n; * We have just one right now, maybe Newton approximation&n; * should be added for those machines where division is fast.&n; * We optimize it by doing most of the calculations&n; * in one UWtype registers instead of two, although we don&squot;t&n; * have to.&n; */
DECL|macro|_FP_SQRT_MEAT_E
mdefine_line|#define _FP_SQRT_MEAT_E(R, S, T, X, q)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    q = (_FP_W_TYPE)1 &lt;&lt; (_FP_W_TYPE_SIZE - 1);&t;&t;&bslash;&n;    _FP_FRAC_SRL_2(X, (_FP_WORKBITS));&t;&t;&t;&bslash;&n;    while (q)&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        T##_f0 = S##_f0 + q;&t;&t;&t;&t;&bslash;&n;        if (T##_f0 &lt;= X##_f0)&t;&t;&t;&t;&bslash;&n;          {&t;&t;&t;&t;&t;&t;&bslash;&n;            S##_f0 = T##_f0 + q;&t;&t;&t;&bslash;&n;            X##_f0 -= T##_f0;&t;&t;&t;&t;&bslash;&n;            R##_f0 += q;&t;&t;&t;&t;&bslash;&n;          }&t;&t;&t;&t;&t;&t;&bslash;&n;        _FP_FRAC_SLL_1(X, 1);&t;&t;&t;&t;&bslash;&n;        q &gt;&gt;= 1;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_SLL_2(R, (_FP_WORKBITS));&t;&t;&t;&bslash;&n;    if (X##_f0)&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (S##_f0 &lt; X##_f0)&t;&t;&t;&t;&bslash;&n;&t;  R##_f0 |= _FP_WORK_ROUND;&t;&t;&t;&bslash;&n;&t;R##_f0 |= _FP_WORK_STICKY;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_CMP_E
mdefine_line|#define FP_CMP_E(r,X,Y,un)&t;_FP_CMP(E,2,r,X,Y,un)
DECL|macro|FP_CMP_EQ_E
mdefine_line|#define FP_CMP_EQ_E(r,X,Y)&t;_FP_CMP_EQ(E,2,r,X,Y)
DECL|macro|FP_TO_INT_E
mdefine_line|#define FP_TO_INT_E(r,X,rsz,rsg)&t;_FP_TO_INT(E,2,r,X,rsz,rsg)
DECL|macro|FP_TO_INT_ROUND_E
mdefine_line|#define FP_TO_INT_ROUND_E(r,X,rsz,rsg)&t;_FP_TO_INT_ROUND(E,2,r,X,rsz,rsg)
DECL|macro|FP_FROM_INT_E
mdefine_line|#define FP_FROM_INT_E(X,r,rs,rt)&t;_FP_FROM_INT(E,2,X,r,rs,rt)
DECL|macro|_FP_FRAC_HIGH_E
mdefine_line|#define _FP_FRAC_HIGH_E(X)&t;(X##_f1)
DECL|macro|_FP_FRAC_HIGH_RAW_E
mdefine_line|#define _FP_FRAC_HIGH_RAW_E(X)&t;(X##_f0)
macro_line|#endif /* not _FP_W_TYPE_SIZE &lt; 64 */
macro_line|#endif /* __MATH_EMU_EXTENDED_H__ */
eof
