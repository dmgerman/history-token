multiline_comment|/* Software floating-point emulation.&n;   Definitions for IEEE Quad Precision.&n;   Copyright (C) 1997,1998,1999 Free Software Foundation, Inc.&n;   This file is part of the GNU C Library.&n;   Contributed by Richard Henderson (rth@cygnus.com),&n;&t;&t;  Jakub Jelinek (jj@ultra.linux.cz),&n;&t;&t;  David S. Miller (davem@redhat.com) and&n;&t;&t;  Peter Maydell (pmaydell@chiark.greenend.org.uk).&n;&n;   The GNU C Library is free software; you can redistribute it and/or&n;   modify it under the terms of the GNU Library General Public License as&n;   published by the Free Software Foundation; either version 2 of the&n;   License, or (at your option) any later version.&n;&n;   The GNU C Library is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;   Library General Public License for more details.&n;&n;   You should have received a copy of the GNU Library General Public&n;   License along with the GNU C Library; see the file COPYING.LIB.  If&n;   not, write to the Free Software Foundation, Inc.,&n;   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
macro_line|#ifndef  __MATH_EMU_QUAD_H__
DECL|macro|__MATH_EMU_QUAD_H__
mdefine_line|#define  __MATH_EMU_QUAD_H__
macro_line|#if _FP_W_TYPE_SIZE &lt; 32
macro_line|#error &quot;Here&squot;s a nickel, kid. Go buy yourself a real computer.&quot;
macro_line|#endif
macro_line|#if _FP_W_TYPE_SIZE &lt; 64
DECL|macro|_FP_FRACTBITS_Q
mdefine_line|#define _FP_FRACTBITS_Q         (4*_FP_W_TYPE_SIZE)
macro_line|#else
DECL|macro|_FP_FRACTBITS_Q
mdefine_line|#define _FP_FRACTBITS_Q&t;&t;(2*_FP_W_TYPE_SIZE)
macro_line|#endif
DECL|macro|_FP_FRACBITS_Q
mdefine_line|#define _FP_FRACBITS_Q&t;&t;113
DECL|macro|_FP_FRACXBITS_Q
mdefine_line|#define _FP_FRACXBITS_Q&t;&t;(_FP_FRACTBITS_Q - _FP_FRACBITS_Q)
DECL|macro|_FP_WFRACBITS_Q
mdefine_line|#define _FP_WFRACBITS_Q&t;&t;(_FP_WORKBITS + _FP_FRACBITS_Q)
DECL|macro|_FP_WFRACXBITS_Q
mdefine_line|#define _FP_WFRACXBITS_Q&t;(_FP_FRACTBITS_Q - _FP_WFRACBITS_Q)
DECL|macro|_FP_EXPBITS_Q
mdefine_line|#define _FP_EXPBITS_Q&t;&t;15
DECL|macro|_FP_EXPBIAS_Q
mdefine_line|#define _FP_EXPBIAS_Q&t;&t;16383
DECL|macro|_FP_EXPMAX_Q
mdefine_line|#define _FP_EXPMAX_Q&t;&t;32767
DECL|macro|_FP_QNANBIT_Q
mdefine_line|#define _FP_QNANBIT_Q&t;&t;&bslash;&n;&t;((_FP_W_TYPE)1 &lt;&lt; (_FP_FRACBITS_Q-2) % _FP_W_TYPE_SIZE)
DECL|macro|_FP_IMPLBIT_Q
mdefine_line|#define _FP_IMPLBIT_Q&t;&t;&bslash;&n;&t;((_FP_W_TYPE)1 &lt;&lt; (_FP_FRACBITS_Q-1) % _FP_W_TYPE_SIZE)
DECL|macro|_FP_OVERFLOW_Q
mdefine_line|#define _FP_OVERFLOW_Q&t;&t;&bslash;&n;&t;((_FP_W_TYPE)1 &lt;&lt; (_FP_WFRACBITS_Q % _FP_W_TYPE_SIZE))
macro_line|#if _FP_W_TYPE_SIZE &lt; 64
DECL|union|_FP_UNION_Q
r_union
id|_FP_UNION_Q
(brace
DECL|member|flt
r_int
r_float
id|flt
suffix:semicolon
r_struct
(brace
macro_line|#if __BYTE_ORDER == __BIG_ENDIAN
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
id|_FP_EXPBITS_Q
suffix:semicolon
DECL|member|frac3
r_int
r_int
id|frac3
suffix:colon
id|_FP_FRACBITS_Q
op_minus
(paren
id|_FP_IMPLBIT_Q
op_ne
l_int|0
)paren
op_minus
(paren
id|_FP_W_TYPE_SIZE
op_star
l_int|3
)paren
suffix:semicolon
DECL|member|frac2
r_int
r_int
id|frac2
suffix:colon
id|_FP_W_TYPE_SIZE
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
r_int
id|frac2
suffix:colon
id|_FP_W_TYPE_SIZE
suffix:semicolon
r_int
r_int
id|frac3
suffix:colon
id|_FP_FRACBITS_Q
op_minus
(paren
id|_FP_IMPLBIT_Q
op_ne
l_int|0
)paren
op_minus
(paren
id|_FP_W_TYPE_SIZE
op_star
l_int|3
)paren
suffix:semicolon
r_int
id|exp
suffix:colon
id|_FP_EXPBITS_Q
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
DECL|macro|FP_DECL_Q
mdefine_line|#define FP_DECL_Q(X)&t;&t;_FP_DECL(4,X)
DECL|macro|FP_UNPACK_RAW_Q
mdefine_line|#define FP_UNPACK_RAW_Q(X,val)&t;_FP_UNPACK_RAW_4(Q,X,val)
DECL|macro|FP_UNPACK_RAW_QP
mdefine_line|#define FP_UNPACK_RAW_QP(X,val)&t;_FP_UNPACK_RAW_4_P(Q,X,val)
DECL|macro|FP_PACK_RAW_Q
mdefine_line|#define FP_PACK_RAW_Q(val,X)&t;_FP_PACK_RAW_4(Q,val,X)
DECL|macro|FP_PACK_RAW_QP
mdefine_line|#define FP_PACK_RAW_QP(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    if (!FP_INHIBIT_RESULTS)&t;&t;&bslash;&n;      _FP_PACK_RAW_4_P(Q,val,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_Q
mdefine_line|#define FP_UNPACK_Q(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_UNPACK_RAW_4(Q,X,val);&t;&t;&bslash;&n;    _FP_UNPACK_CANONICAL(Q,4,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_QP
mdefine_line|#define FP_UNPACK_QP(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_UNPACK_RAW_4_P(Q,X,val);&t;&bslash;&n;    _FP_UNPACK_CANONICAL(Q,4,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_Q
mdefine_line|#define FP_PACK_Q(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_PACK_CANONICAL(Q,4,X);&t;&t;&bslash;&n;    _FP_PACK_RAW_4(Q,val,X);&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_QP
mdefine_line|#define FP_PACK_QP(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_PACK_CANONICAL(Q,4,X);&t;&t;&bslash;&n;    if (!FP_INHIBIT_RESULTS)&t;&t;&bslash;&n;      _FP_PACK_RAW_4_P(Q,val,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_ISSIGNAN_Q
mdefine_line|#define FP_ISSIGNAN_Q(X)&t;&t;_FP_ISSIGNAN(Q,4,X)
DECL|macro|FP_NEG_Q
mdefine_line|#define FP_NEG_Q(R,X)&t;&t;&t;_FP_NEG(Q,4,R,X)
DECL|macro|FP_ADD_Q
mdefine_line|#define FP_ADD_Q(R,X,Y)&t;&t;&t;_FP_ADD(Q,4,R,X,Y)
DECL|macro|FP_SUB_Q
mdefine_line|#define FP_SUB_Q(R,X,Y)&t;&t;&t;_FP_SUB(Q,4,R,X,Y)
DECL|macro|FP_MUL_Q
mdefine_line|#define FP_MUL_Q(R,X,Y)&t;&t;&t;_FP_MUL(Q,4,R,X,Y)
DECL|macro|FP_DIV_Q
mdefine_line|#define FP_DIV_Q(R,X,Y)&t;&t;&t;_FP_DIV(Q,4,R,X,Y)
DECL|macro|FP_SQRT_Q
mdefine_line|#define FP_SQRT_Q(R,X)&t;&t;&t;_FP_SQRT(Q,4,R,X)
DECL|macro|_FP_SQRT_MEAT_Q
mdefine_line|#define _FP_SQRT_MEAT_Q(R,S,T,X,Q)&t;_FP_SQRT_MEAT_4(R,S,T,X,Q)
DECL|macro|FP_CMP_Q
mdefine_line|#define FP_CMP_Q(r,X,Y,un)&t;_FP_CMP(Q,4,r,X,Y,un)
DECL|macro|FP_CMP_EQ_Q
mdefine_line|#define FP_CMP_EQ_Q(r,X,Y)&t;_FP_CMP_EQ(Q,4,r,X,Y)
DECL|macro|FP_TO_INT_Q
mdefine_line|#define FP_TO_INT_Q(r,X,rsz,rsg)&t;_FP_TO_INT(Q,4,r,X,rsz,rsg)
DECL|macro|FP_TO_INT_ROUND_Q
mdefine_line|#define FP_TO_INT_ROUND_Q(r,X,rsz,rsg)&t;_FP_TO_INT_ROUND(Q,4,r,X,rsz,rsg)
DECL|macro|FP_FROM_INT_Q
mdefine_line|#define FP_FROM_INT_Q(X,r,rs,rt)&t;_FP_FROM_INT(Q,4,X,r,rs,rt)
DECL|macro|_FP_FRAC_HIGH_Q
mdefine_line|#define _FP_FRAC_HIGH_Q(X)&t;_FP_FRAC_HIGH_4(X)
DECL|macro|_FP_FRAC_HIGH_RAW_Q
mdefine_line|#define _FP_FRAC_HIGH_RAW_Q(X)&t;_FP_FRAC_HIGH_4(X)
macro_line|#else   /* not _FP_W_TYPE_SIZE &lt; 64 */
DECL|union|_FP_UNION_Q
r_union
id|_FP_UNION_Q
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
id|_FP_EXPBITS_Q
suffix:semicolon
DECL|member|frac1
r_int
r_int
id|frac1
suffix:colon
id|_FP_FRACBITS_Q
op_minus
(paren
id|_FP_IMPLBIT_Q
op_ne
l_int|0
)paren
op_minus
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
id|_FP_FRACBITS_Q
op_minus
(paren
id|_FP_IMPLBIT_Q
op_ne
l_int|0
)paren
op_minus
id|_FP_W_TYPE_SIZE
suffix:semicolon
r_int
id|exp
suffix:colon
id|_FP_EXPBITS_Q
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
DECL|macro|FP_DECL_Q
mdefine_line|#define FP_DECL_Q(X)&t;&t;_FP_DECL(2,X)
DECL|macro|FP_UNPACK_RAW_Q
mdefine_line|#define FP_UNPACK_RAW_Q(X,val)&t;_FP_UNPACK_RAW_2(Q,X,val)
DECL|macro|FP_UNPACK_RAW_QP
mdefine_line|#define FP_UNPACK_RAW_QP(X,val)&t;_FP_UNPACK_RAW_2_P(Q,X,val)
DECL|macro|FP_PACK_RAW_Q
mdefine_line|#define FP_PACK_RAW_Q(val,X)&t;_FP_PACK_RAW_2(Q,val,X)
DECL|macro|FP_PACK_RAW_QP
mdefine_line|#define FP_PACK_RAW_QP(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    if (!FP_INHIBIT_RESULTS)&t;&t;&bslash;&n;      _FP_PACK_RAW_2_P(Q,val,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_Q
mdefine_line|#define FP_UNPACK_Q(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_UNPACK_RAW_2(Q,X,val);&t;&t;&bslash;&n;    _FP_UNPACK_CANONICAL(Q,2,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_QP
mdefine_line|#define FP_UNPACK_QP(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_UNPACK_RAW_2_P(Q,X,val);&t;&bslash;&n;    _FP_UNPACK_CANONICAL(Q,2,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_Q
mdefine_line|#define FP_PACK_Q(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_PACK_CANONICAL(Q,2,X);&t;&t;&bslash;&n;    _FP_PACK_RAW_2(Q,val,X);&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_QP
mdefine_line|#define FP_PACK_QP(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_PACK_CANONICAL(Q,2,X);&t;&t;&bslash;&n;    if (!FP_INHIBIT_RESULTS)&t;&t;&bslash;&n;      _FP_PACK_RAW_2_P(Q,val,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_ISSIGNAN_Q
mdefine_line|#define FP_ISSIGNAN_Q(X)&t;&t;_FP_ISSIGNAN(Q,2,X)
DECL|macro|FP_NEG_Q
mdefine_line|#define FP_NEG_Q(R,X)&t;&t;&t;_FP_NEG(Q,2,R,X)
DECL|macro|FP_ADD_Q
mdefine_line|#define FP_ADD_Q(R,X,Y)&t;&t;&t;_FP_ADD(Q,2,R,X,Y)
DECL|macro|FP_SUB_Q
mdefine_line|#define FP_SUB_Q(R,X,Y)&t;&t;&t;_FP_SUB(Q,2,R,X,Y)
DECL|macro|FP_MUL_Q
mdefine_line|#define FP_MUL_Q(R,X,Y)&t;&t;&t;_FP_MUL(Q,2,R,X,Y)
DECL|macro|FP_DIV_Q
mdefine_line|#define FP_DIV_Q(R,X,Y)&t;&t;&t;_FP_DIV(Q,2,R,X,Y)
DECL|macro|FP_SQRT_Q
mdefine_line|#define FP_SQRT_Q(R,X)&t;&t;&t;_FP_SQRT(Q,2,R,X)
DECL|macro|_FP_SQRT_MEAT_Q
mdefine_line|#define _FP_SQRT_MEAT_Q(R,S,T,X,Q)&t;_FP_SQRT_MEAT_2(R,S,T,X,Q)
DECL|macro|FP_CMP_Q
mdefine_line|#define FP_CMP_Q(r,X,Y,un)&t;_FP_CMP(Q,2,r,X,Y,un)
DECL|macro|FP_CMP_EQ_Q
mdefine_line|#define FP_CMP_EQ_Q(r,X,Y)&t;_FP_CMP_EQ(Q,2,r,X,Y)
DECL|macro|FP_TO_INT_Q
mdefine_line|#define FP_TO_INT_Q(r,X,rsz,rsg)&t;_FP_TO_INT(Q,2,r,X,rsz,rsg)
DECL|macro|FP_TO_INT_ROUND_Q
mdefine_line|#define FP_TO_INT_ROUND_Q(r,X,rsz,rsg)&t;_FP_TO_INT_ROUND(Q,2,r,X,rsz,rsg)
DECL|macro|FP_FROM_INT_Q
mdefine_line|#define FP_FROM_INT_Q(X,r,rs,rt)&t;_FP_FROM_INT(Q,2,X,r,rs,rt)
DECL|macro|_FP_FRAC_HIGH_Q
mdefine_line|#define _FP_FRAC_HIGH_Q(X)&t;_FP_FRAC_HIGH_2(X)
DECL|macro|_FP_FRAC_HIGH_RAW_Q
mdefine_line|#define _FP_FRAC_HIGH_RAW_Q(X)&t;_FP_FRAC_HIGH_2(X)
macro_line|#endif /* not _FP_W_TYPE_SIZE &lt; 64 */
macro_line|#endif /* __MATH_EMU_QUAD_H__ */
eof
