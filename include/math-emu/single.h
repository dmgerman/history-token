multiline_comment|/* Software floating-point emulation.&n;   Definitions for IEEE Single Precision.&n;   Copyright (C) 1997,1998,1999 Free Software Foundation, Inc.&n;   This file is part of the GNU C Library.&n;   Contributed by Richard Henderson (rth@cygnus.com),&n;&t;&t;  Jakub Jelinek (jj@ultra.linux.cz),&n;&t;&t;  David S. Miller (davem@redhat.com) and&n;&t;&t;  Peter Maydell (pmaydell@chiark.greenend.org.uk).&n;&n;   The GNU C Library is free software; you can redistribute it and/or&n;   modify it under the terms of the GNU Library General Public License as&n;   published by the Free Software Foundation; either version 2 of the&n;   License, or (at your option) any later version.&n;&n;   The GNU C Library is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;   Library General Public License for more details.&n;&n;   You should have received a copy of the GNU Library General Public&n;   License along with the GNU C Library; see the file COPYING.LIB.  If&n;   not, write to the Free Software Foundation, Inc.,&n;   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
macro_line|#ifndef    __MATH_EMU_SINGLE_H__
DECL|macro|__MATH_EMU_SINGLE_H__
mdefine_line|#define    __MATH_EMU_SINGLE_H__
macro_line|#if _FP_W_TYPE_SIZE &lt; 32
macro_line|#error &quot;Here&squot;s a nickel kid.  Go buy yourself a real computer.&quot;
macro_line|#endif
DECL|macro|_FP_FRACBITS_S
mdefine_line|#define _FP_FRACBITS_S&t;&t;24
DECL|macro|_FP_FRACXBITS_S
mdefine_line|#define _FP_FRACXBITS_S&t;&t;(_FP_W_TYPE_SIZE - _FP_FRACBITS_S)
DECL|macro|_FP_WFRACBITS_S
mdefine_line|#define _FP_WFRACBITS_S&t;&t;(_FP_WORKBITS + _FP_FRACBITS_S)
DECL|macro|_FP_WFRACXBITS_S
mdefine_line|#define _FP_WFRACXBITS_S&t;(_FP_W_TYPE_SIZE - _FP_WFRACBITS_S)
DECL|macro|_FP_EXPBITS_S
mdefine_line|#define _FP_EXPBITS_S&t;&t;8
DECL|macro|_FP_EXPBIAS_S
mdefine_line|#define _FP_EXPBIAS_S&t;&t;127
DECL|macro|_FP_EXPMAX_S
mdefine_line|#define _FP_EXPMAX_S&t;&t;255
DECL|macro|_FP_QNANBIT_S
mdefine_line|#define _FP_QNANBIT_S&t;&t;((_FP_W_TYPE)1 &lt;&lt; (_FP_FRACBITS_S-2))
DECL|macro|_FP_IMPLBIT_S
mdefine_line|#define _FP_IMPLBIT_S&t;&t;((_FP_W_TYPE)1 &lt;&lt; (_FP_FRACBITS_S-1))
DECL|macro|_FP_OVERFLOW_S
mdefine_line|#define _FP_OVERFLOW_S&t;&t;((_FP_W_TYPE)1 &lt;&lt; (_FP_WFRACBITS_S))
multiline_comment|/* The implementation of _FP_MUL_MEAT_S and _FP_DIV_MEAT_S should be&n;   chosen by the target machine.  */
DECL|union|_FP_UNION_S
r_union
id|_FP_UNION_S
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
id|_FP_EXPBITS_S
suffix:semicolon
DECL|member|frac
r_int
id|frac
suffix:colon
id|_FP_FRACBITS_S
op_minus
(paren
id|_FP_IMPLBIT_S
op_ne
l_int|0
)paren
suffix:semicolon
macro_line|#else
r_int
id|frac
suffix:colon
id|_FP_FRACBITS_S
op_minus
(paren
id|_FP_IMPLBIT_S
op_ne
l_int|0
)paren
suffix:semicolon
r_int
id|exp
suffix:colon
id|_FP_EXPBITS_S
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
DECL|macro|FP_DECL_S
mdefine_line|#define FP_DECL_S(X)&t;&t;_FP_DECL(1,X)
DECL|macro|FP_UNPACK_RAW_S
mdefine_line|#define FP_UNPACK_RAW_S(X,val)&t;_FP_UNPACK_RAW_1(S,X,val)
DECL|macro|FP_UNPACK_RAW_SP
mdefine_line|#define FP_UNPACK_RAW_SP(X,val)&t;_FP_UNPACK_RAW_1_P(S,X,val)
DECL|macro|FP_PACK_RAW_S
mdefine_line|#define FP_PACK_RAW_S(val,X)&t;_FP_PACK_RAW_1(S,val,X)
DECL|macro|FP_PACK_RAW_SP
mdefine_line|#define FP_PACK_RAW_SP(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    if (!FP_INHIBIT_RESULTS)&t;&t;&bslash;&n;      _FP_PACK_RAW_1_P(S,val,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_S
mdefine_line|#define FP_UNPACK_S(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_UNPACK_RAW_1(S,X,val);&t;&t;&bslash;&n;    _FP_UNPACK_CANONICAL(S,1,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_UNPACK_SP
mdefine_line|#define FP_UNPACK_SP(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_UNPACK_RAW_1_P(S,X,val);&t;&bslash;&n;    _FP_UNPACK_CANONICAL(S,1,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_S
mdefine_line|#define FP_PACK_S(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_PACK_CANONICAL(S,1,X);&t;&t;&bslash;&n;    _FP_PACK_RAW_1(S,val,X);&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_SP
mdefine_line|#define FP_PACK_SP(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_PACK_CANONICAL(S,1,X);&t;&t;&bslash;&n;    if (!FP_INHIBIT_RESULTS)&t;&t;&bslash;&n;      _FP_PACK_RAW_1_P(S,val,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_ISSIGNAN_S
mdefine_line|#define FP_ISSIGNAN_S(X)&t;&t;_FP_ISSIGNAN(S,1,X)
DECL|macro|FP_NEG_S
mdefine_line|#define FP_NEG_S(R,X)&t;&t;&t;_FP_NEG(S,1,R,X)
DECL|macro|FP_ADD_S
mdefine_line|#define FP_ADD_S(R,X,Y)&t;&t;&t;_FP_ADD(S,1,R,X,Y)
DECL|macro|FP_SUB_S
mdefine_line|#define FP_SUB_S(R,X,Y)&t;&t;&t;_FP_SUB(S,1,R,X,Y)
DECL|macro|FP_MUL_S
mdefine_line|#define FP_MUL_S(R,X,Y)&t;&t;&t;_FP_MUL(S,1,R,X,Y)
DECL|macro|FP_DIV_S
mdefine_line|#define FP_DIV_S(R,X,Y)&t;&t;&t;_FP_DIV(S,1,R,X,Y)
DECL|macro|FP_SQRT_S
mdefine_line|#define FP_SQRT_S(R,X)&t;&t;&t;_FP_SQRT(S,1,R,X)
DECL|macro|_FP_SQRT_MEAT_S
mdefine_line|#define _FP_SQRT_MEAT_S(R,S,T,X,Q)&t;_FP_SQRT_MEAT_1(R,S,T,X,Q)
DECL|macro|FP_CMP_S
mdefine_line|#define FP_CMP_S(r,X,Y,un)&t;_FP_CMP(S,1,r,X,Y,un)
DECL|macro|FP_CMP_EQ_S
mdefine_line|#define FP_CMP_EQ_S(r,X,Y)&t;_FP_CMP_EQ(S,1,r,X,Y)
DECL|macro|FP_TO_INT_S
mdefine_line|#define FP_TO_INT_S(r,X,rsz,rsg)&t;_FP_TO_INT(S,1,r,X,rsz,rsg)
DECL|macro|FP_TO_INT_ROUND_S
mdefine_line|#define FP_TO_INT_ROUND_S(r,X,rsz,rsg)&t;_FP_TO_INT_ROUND(S,1,r,X,rsz,rsg)
DECL|macro|FP_FROM_INT_S
mdefine_line|#define FP_FROM_INT_S(X,r,rs,rt)&t;_FP_FROM_INT(S,1,X,r,rs,rt)
DECL|macro|_FP_FRAC_HIGH_S
mdefine_line|#define _FP_FRAC_HIGH_S(X)&t;_FP_FRAC_HIGH_1(X)
DECL|macro|_FP_FRAC_HIGH_RAW_S
mdefine_line|#define _FP_FRAC_HIGH_RAW_S(X)&t;_FP_FRAC_HIGH_1(X)
macro_line|#endif /* __MATH_EMU_SINGLE_H__ */
eof
