multiline_comment|/* Software floating-point emulation.&n;   Definitions for IEEE Double Precision&n;   Copyright (C) 1997,1998,1999 Free Software Foundation, Inc.&n;   This file is part of the GNU C Library.&n;   Contributed by Richard Henderson (rth@cygnus.com),&n;&t;&t;  Jakub Jelinek (jj@ultra.linux.cz),&n;&t;&t;  David S. Miller (davem@redhat.com) and&n;&t;&t;  Peter Maydell (pmaydell@chiark.greenend.org.uk).&n;&n;   The GNU C Library is free software; you can redistribute it and/or&n;   modify it under the terms of the GNU Library General Public License as&n;   published by the Free Software Foundation; either version 2 of the&n;   License, or (at your option) any later version.&n;&n;   The GNU C Library is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;   Library General Public License for more details.&n;&n;   You should have received a copy of the GNU Library General Public&n;   License along with the GNU C Library; see the file COPYING.LIB.  If&n;   not, write to the Free Software Foundation, Inc.,&n;   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
macro_line|#ifndef    __MATH_EMU_DOUBLE_H__
DECL|macro|__MATH_EMU_DOUBLE_H__
mdefine_line|#define    __MATH_EMU_DOUBLE_H__
macro_line|#if _FP_W_TYPE_SIZE &lt; 32
macro_line|#error &quot;Here&squot;s a nickel kid.  Go buy yourself a real computer.&quot;
macro_line|#endif
macro_line|#if _FP_W_TYPE_SIZE &lt; 64
DECL|macro|_FP_FRACTBITS_D
mdefine_line|#define _FP_FRACTBITS_D&t;&t;(2 * _FP_W_TYPE_SIZE)
macro_line|#else
DECL|macro|_FP_FRACTBITS_D
mdefine_line|#define _FP_FRACTBITS_D&t;&t;_FP_W_TYPE_SIZE
macro_line|#endif
DECL|macro|_FP_FRACBITS_D
mdefine_line|#define _FP_FRACBITS_D&t;&t;53
DECL|macro|_FP_FRACXBITS_D
mdefine_line|#define _FP_FRACXBITS_D&t;&t;(_FP_FRACTBITS_D - _FP_FRACBITS_D)
DECL|macro|_FP_WFRACBITS_D
mdefine_line|#define _FP_WFRACBITS_D&t;&t;(_FP_WORKBITS + _FP_FRACBITS_D)
DECL|macro|_FP_WFRACXBITS_D
mdefine_line|#define _FP_WFRACXBITS_D&t;(_FP_FRACTBITS_D - _FP_WFRACBITS_D)
DECL|macro|_FP_EXPBITS_D
mdefine_line|#define _FP_EXPBITS_D&t;&t;11
DECL|macro|_FP_EXPBIAS_D
mdefine_line|#define _FP_EXPBIAS_D&t;&t;1023
DECL|macro|_FP_EXPMAX_D
mdefine_line|#define _FP_EXPMAX_D&t;&t;2047
DECL|macro|_FP_QNANBIT_D
mdefine_line|#define _FP_QNANBIT_D&t;&t;&bslash;&n;&t;((_FP_W_TYPE)1 &lt;&lt; (_FP_FRACBITS_D-2) % _FP_W_TYPE_SIZE)
DECL|macro|_FP_IMPLBIT_D
mdefine_line|#define _FP_IMPLBIT_D&t;&t;&bslash;&n;&t;((_FP_W_TYPE)1 &lt;&lt; (_FP_FRACBITS_D-1) % _FP_W_TYPE_SIZE)
DECL|macro|_FP_OVERFLOW_D
mdefine_line|#define _FP_OVERFLOW_D&t;&t;&bslash;&n;&t;((_FP_W_TYPE)1 &lt;&lt; _FP_WFRACBITS_D % _FP_W_TYPE_SIZE)
macro_line|#if _FP_W_TYPE_SIZE &lt; 64
DECL|union|_FP_UNION_D
r_union
id|_FP_UNION_D
(brace
DECL|member|flt
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
id|_FP_EXPBITS_D
suffix:semicolon
DECL|member|frac1
r_int
id|frac1
suffix:colon
id|_FP_FRACBITS_D
op_minus
(paren
id|_FP_IMPLBIT_D
op_ne
l_int|0
)paren
op_minus
id|_FP_W_TYPE_SIZE
suffix:semicolon
DECL|member|frac0
r_int
id|frac0
suffix:colon
id|_FP_W_TYPE_SIZE
suffix:semicolon
macro_line|#else
r_int
id|frac0
suffix:colon
id|_FP_W_TYPE_SIZE
suffix:semicolon
r_int
id|frac1
suffix:colon
id|_FP_FRACBITS_D
op_minus
(paren
id|_FP_IMPLBIT_D
op_ne
l_int|0
)paren
op_minus
id|_FP_W_TYPE_SIZE
suffix:semicolon
r_int
id|exp
suffix:colon
id|_FP_EXPBITS_D
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
DECL|macro|FP_DECL_D
mdefine_line|#define FP_DECL_D(X)&t;&t;_FP_DECL(2,X)
DECL|macro|FP_UNPACK_RAW_D
mdefine_line|#define FP_UNPACK_RAW_D(X,val)&t;_FP_UNPACK_RAW_2(D,X,val)
DECL|macro|FP_UNPACK_RAW_DP
mdefine_line|#define FP_UNPACK_RAW_DP(X,val)&t;_FP_UNPACK_RAW_2_P(D,X,val)
DECL|macro|FP_PACK_RAW_D
mdefine_line|#define FP_PACK_RAW_D(val,X)&t;_FP_PACK_RAW_2(D,val,X)
DECL|macro|FP_PACK_RAW_DP
mdefine_line|#define FP_PACK_RAW_DP(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    if (!FP_INHIBIT_RESULTS)&t;&t;&bslash;&n;      _FP_PACK_RAW_2_P(D,val,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_D
mdefine_line|#define FP_UNPACK_D(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_UNPACK_RAW_2(D,X,val);&t;&t;&bslash;&n;    _FP_UNPACK_CANONICAL(D,2,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_DP
mdefine_line|#define FP_UNPACK_DP(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_UNPACK_RAW_2_P(D,X,val);&t;&bslash;&n;    _FP_UNPACK_CANONICAL(D,2,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_D
mdefine_line|#define FP_PACK_D(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_PACK_CANONICAL(D,2,X);&t;&t;&bslash;&n;    _FP_PACK_RAW_2(D,val,X);&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_DP
mdefine_line|#define FP_PACK_DP(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_PACK_CANONICAL(D,2,X);&t;&t;&bslash;&n;    if (!FP_INHIBIT_RESULTS)&t;&t;&bslash;&n;      _FP_PACK_RAW_2_P(D,val,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_ISSIGNAN_D
mdefine_line|#define FP_ISSIGNAN_D(X)&t;&t;_FP_ISSIGNAN(D,2,X)
DECL|macro|FP_NEG_D
mdefine_line|#define FP_NEG_D(R,X)&t;&t;&t;_FP_NEG(D,2,R,X)
DECL|macro|FP_ADD_D
mdefine_line|#define FP_ADD_D(R,X,Y)&t;&t;&t;_FP_ADD(D,2,R,X,Y)
DECL|macro|FP_SUB_D
mdefine_line|#define FP_SUB_D(R,X,Y)&t;&t;&t;_FP_SUB(D,2,R,X,Y)
DECL|macro|FP_MUL_D
mdefine_line|#define FP_MUL_D(R,X,Y)&t;&t;&t;_FP_MUL(D,2,R,X,Y)
DECL|macro|FP_DIV_D
mdefine_line|#define FP_DIV_D(R,X,Y)&t;&t;&t;_FP_DIV(D,2,R,X,Y)
DECL|macro|FP_SQRT_D
mdefine_line|#define FP_SQRT_D(R,X)&t;&t;&t;_FP_SQRT(D,2,R,X)
DECL|macro|_FP_SQRT_MEAT_D
mdefine_line|#define _FP_SQRT_MEAT_D(R,S,T,X,Q)&t;_FP_SQRT_MEAT_2(R,S,T,X,Q)
DECL|macro|FP_CMP_D
mdefine_line|#define FP_CMP_D(r,X,Y,un)&t;_FP_CMP(D,2,r,X,Y,un)
DECL|macro|FP_CMP_EQ_D
mdefine_line|#define FP_CMP_EQ_D(r,X,Y)&t;_FP_CMP_EQ(D,2,r,X,Y)
DECL|macro|FP_TO_INT_D
mdefine_line|#define FP_TO_INT_D(r,X,rsz,rsg)&t;_FP_TO_INT(D,2,r,X,rsz,rsg)
DECL|macro|FP_TO_INT_ROUND_D
mdefine_line|#define FP_TO_INT_ROUND_D(r,X,rsz,rsg)&t;_FP_TO_INT_ROUND(D,2,r,X,rsz,rsg)
DECL|macro|FP_FROM_INT_D
mdefine_line|#define FP_FROM_INT_D(X,r,rs,rt)&t;_FP_FROM_INT(D,2,X,r,rs,rt)
DECL|macro|_FP_FRAC_HIGH_D
mdefine_line|#define _FP_FRAC_HIGH_D(X)&t;_FP_FRAC_HIGH_2(X)
DECL|macro|_FP_FRAC_HIGH_RAW_D
mdefine_line|#define _FP_FRAC_HIGH_RAW_D(X)&t;_FP_FRAC_HIGH_2(X)
macro_line|#else
DECL|union|_FP_UNION_D
r_union
id|_FP_UNION_D
(brace
DECL|member|flt
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
id|_FP_EXPBITS_D
suffix:semicolon
DECL|member|frac
r_int
r_int
id|frac
suffix:colon
id|_FP_FRACBITS_D
op_minus
(paren
id|_FP_IMPLBIT_D
op_ne
l_int|0
)paren
suffix:semicolon
macro_line|#else
r_int
r_int
id|frac
suffix:colon
id|_FP_FRACBITS_D
op_minus
(paren
id|_FP_IMPLBIT_D
op_ne
l_int|0
)paren
suffix:semicolon
r_int
id|exp
suffix:colon
id|_FP_EXPBITS_D
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
DECL|macro|FP_DECL_D
mdefine_line|#define FP_DECL_D(X)&t;&t;_FP_DECL(1,X)
DECL|macro|FP_UNPACK_RAW_D
mdefine_line|#define FP_UNPACK_RAW_D(X,val)&t;_FP_UNPACK_RAW_1(D,X,val)
DECL|macro|FP_UNPACK_RAW_DP
mdefine_line|#define FP_UNPACK_RAW_DP(X,val)&t;_FP_UNPACK_RAW_1_P(D,X,val)
DECL|macro|FP_PACK_RAW_D
mdefine_line|#define FP_PACK_RAW_D(val,X)&t;_FP_PACK_RAW_1(D,val,X)
DECL|macro|FP_PACK_RAW_DP
mdefine_line|#define FP_PACK_RAW_DP(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    if (!FP_INHIBIT_RESULTS)&t;&t;&bslash;&n;      _FP_PACK_RAW_1_P(D,val,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_D
mdefine_line|#define FP_UNPACK_D(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_UNPACK_RAW_1(D,X,val);&t;&t;&bslash;&n;    _FP_UNPACK_CANONICAL(D,1,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_DP
mdefine_line|#define FP_UNPACK_DP(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_UNPACK_RAW_1_P(D,X,val);&t;&bslash;&n;    _FP_UNPACK_CANONICAL(D,1,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_D
mdefine_line|#define FP_PACK_D(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_PACK_CANONICAL(D,1,X);&t;&t;&bslash;&n;    _FP_PACK_RAW_1(D,val,X);&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_DP
mdefine_line|#define FP_PACK_DP(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_PACK_CANONICAL(D,1,X);&t;&t;&bslash;&n;    if (!FP_INHIBIT_RESULTS)&t;&t;&bslash;&n;      _FP_PACK_RAW_1_P(D,val,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_ISSIGNAN_D
mdefine_line|#define FP_ISSIGNAN_D(X)&t;&t;_FP_ISSIGNAN(D,1,X)
DECL|macro|FP_NEG_D
mdefine_line|#define FP_NEG_D(R,X)&t;&t;&t;_FP_NEG(D,1,R,X)
DECL|macro|FP_ADD_D
mdefine_line|#define FP_ADD_D(R,X,Y)&t;&t;&t;_FP_ADD(D,1,R,X,Y)
DECL|macro|FP_SUB_D
mdefine_line|#define FP_SUB_D(R,X,Y)&t;&t;&t;_FP_SUB(D,1,R,X,Y)
DECL|macro|FP_MUL_D
mdefine_line|#define FP_MUL_D(R,X,Y)&t;&t;&t;_FP_MUL(D,1,R,X,Y)
DECL|macro|FP_DIV_D
mdefine_line|#define FP_DIV_D(R,X,Y)&t;&t;&t;_FP_DIV(D,1,R,X,Y)
DECL|macro|FP_SQRT_D
mdefine_line|#define FP_SQRT_D(R,X)&t;&t;&t;_FP_SQRT(D,1,R,X)
DECL|macro|_FP_SQRT_MEAT_D
mdefine_line|#define _FP_SQRT_MEAT_D(R,S,T,X,Q)&t;_FP_SQRT_MEAT_1(R,S,T,X,Q)
multiline_comment|/* The implementation of _FP_MUL_D and _FP_DIV_D should be chosen by&n;   the target machine.  */
DECL|macro|FP_CMP_D
mdefine_line|#define FP_CMP_D(r,X,Y,un)&t;_FP_CMP(D,1,r,X,Y,un)
DECL|macro|FP_CMP_EQ_D
mdefine_line|#define FP_CMP_EQ_D(r,X,Y)&t;_FP_CMP_EQ(D,1,r,X,Y)
DECL|macro|FP_TO_INT_D
mdefine_line|#define FP_TO_INT_D(r,X,rsz,rsg)&t;_FP_TO_INT(D,1,r,X,rsz,rsg)
DECL|macro|FP_TO_INT_ROUND_D
mdefine_line|#define FP_TO_INT_ROUND_D(r,X,rsz,rsg)&t;_FP_TO_INT_ROUND(D,1,r,X,rsz,rsg)
DECL|macro|FP_FROM_INT_D
mdefine_line|#define FP_FROM_INT_D(X,r,rs,rt)&t;_FP_FROM_INT(D,1,X,r,rs,rt)
DECL|macro|_FP_FRAC_HIGH_D
mdefine_line|#define _FP_FRAC_HIGH_D(X)&t;_FP_FRAC_HIGH_1(X)
DECL|macro|_FP_FRAC_HIGH_RAW_D
mdefine_line|#define _FP_FRAC_HIGH_RAW_D(X)&t;_FP_FRAC_HIGH_1(X)
macro_line|#endif /* W_TYPE_SIZE &lt; 64 */
macro_line|#endif /* __MATH_EMU_DOUBLE_H__ */
eof
