multiline_comment|/* Software floating-point emulation.&n;   Basic one-word fraction declaration and manipulation.&n;   Copyright (C) 1997,1998,1999 Free Software Foundation, Inc.&n;   This file is part of the GNU C Library.&n;   Contributed by Richard Henderson (rth@cygnus.com),&n;&t;&t;  Jakub Jelinek (jj@ultra.linux.cz),&n;&t;&t;  David S. Miller (davem@redhat.com) and&n;&t;&t;  Peter Maydell (pmaydell@chiark.greenend.org.uk).&n;&n;   The GNU C Library is free software; you can redistribute it and/or&n;   modify it under the terms of the GNU Library General Public License as&n;   published by the Free Software Foundation; either version 2 of the&n;   License, or (at your option) any later version.&n;&n;   The GNU C Library is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;   Library General Public License for more details.&n;&n;   You should have received a copy of the GNU Library General Public&n;   License along with the GNU C Library; see the file COPYING.LIB.  If&n;   not, write to the Free Software Foundation, Inc.,&n;   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
macro_line|#ifndef    __MATH_EMU_OP_1_H__
DECL|macro|__MATH_EMU_OP_1_H__
mdefine_line|#define    __MATH_EMU_OP_1_H__
DECL|macro|_FP_FRAC_DECL_1
mdefine_line|#define _FP_FRAC_DECL_1(X)&t;_FP_W_TYPE X##_f
DECL|macro|_FP_FRAC_COPY_1
mdefine_line|#define _FP_FRAC_COPY_1(D,S)&t;(D##_f = S##_f)
DECL|macro|_FP_FRAC_SET_1
mdefine_line|#define _FP_FRAC_SET_1(X,I)&t;(X##_f = I)
DECL|macro|_FP_FRAC_HIGH_1
mdefine_line|#define _FP_FRAC_HIGH_1(X)&t;(X##_f)
DECL|macro|_FP_FRAC_LOW_1
mdefine_line|#define _FP_FRAC_LOW_1(X)&t;(X##_f)
DECL|macro|_FP_FRAC_WORD_1
mdefine_line|#define _FP_FRAC_WORD_1(X,w)&t;(X##_f)
DECL|macro|_FP_FRAC_ADDI_1
mdefine_line|#define _FP_FRAC_ADDI_1(X,I)&t;(X##_f += I)
DECL|macro|_FP_FRAC_SLL_1
mdefine_line|#define _FP_FRAC_SLL_1(X,N)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&bslash;&n;    if (__builtin_constant_p(N) &amp;&amp; (N) == 1)&t;&bslash;&n;      X##_f += X##_f;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&bslash;&n;      X##_f &lt;&lt;= (N);&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|_FP_FRAC_SRL_1
mdefine_line|#define _FP_FRAC_SRL_1(X,N)&t;(X##_f &gt;&gt;= N)
multiline_comment|/* Right shift with sticky-lsb.  */
DECL|macro|_FP_FRAC_SRS_1
mdefine_line|#define _FP_FRAC_SRS_1(X,N,sz)&t;__FP_FRAC_SRS_1(X##_f, N, sz)
DECL|macro|__FP_FRAC_SRS_1
mdefine_line|#define __FP_FRAC_SRS_1(X,N,sz)&t;&t;&t;&t;&t;&t;&bslash;&n;   (X = (X &gt;&gt; (N) | (__builtin_constant_p(N) &amp;&amp; (N) == 1&t;&t;&bslash;&n;&t;&t;     ? X &amp; 1 : (X &lt;&lt; (_FP_W_TYPE_SIZE - (N))) != 0)))
DECL|macro|_FP_FRAC_ADD_1
mdefine_line|#define _FP_FRAC_ADD_1(R,X,Y)&t;(R##_f = X##_f + Y##_f)
DECL|macro|_FP_FRAC_SUB_1
mdefine_line|#define _FP_FRAC_SUB_1(R,X,Y)&t;(R##_f = X##_f - Y##_f)
DECL|macro|_FP_FRAC_DEC_1
mdefine_line|#define _FP_FRAC_DEC_1(X,Y)&t;(X##_f -= Y##_f)
DECL|macro|_FP_FRAC_CLZ_1
mdefine_line|#define _FP_FRAC_CLZ_1(z, X)&t;__FP_CLZ(z, X##_f)
multiline_comment|/* Predicates */
DECL|macro|_FP_FRAC_NEGP_1
mdefine_line|#define _FP_FRAC_NEGP_1(X)&t;((_FP_WS_TYPE)X##_f &lt; 0)
DECL|macro|_FP_FRAC_ZEROP_1
mdefine_line|#define _FP_FRAC_ZEROP_1(X)&t;(X##_f == 0)
DECL|macro|_FP_FRAC_OVERP_1
mdefine_line|#define _FP_FRAC_OVERP_1(fs,X)&t;(X##_f &amp; _FP_OVERFLOW_##fs)
DECL|macro|_FP_FRAC_CLEAR_OVERP_1
mdefine_line|#define _FP_FRAC_CLEAR_OVERP_1(fs,X)&t;(X##_f &amp;= ~_FP_OVERFLOW_##fs)
DECL|macro|_FP_FRAC_EQ_1
mdefine_line|#define _FP_FRAC_EQ_1(X, Y)&t;(X##_f == Y##_f)
DECL|macro|_FP_FRAC_GE_1
mdefine_line|#define _FP_FRAC_GE_1(X, Y)&t;(X##_f &gt;= Y##_f)
DECL|macro|_FP_FRAC_GT_1
mdefine_line|#define _FP_FRAC_GT_1(X, Y)&t;(X##_f &gt; Y##_f)
DECL|macro|_FP_ZEROFRAC_1
mdefine_line|#define _FP_ZEROFRAC_1&t;&t;0
DECL|macro|_FP_MINFRAC_1
mdefine_line|#define _FP_MINFRAC_1&t;&t;1
DECL|macro|_FP_MAXFRAC_1
mdefine_line|#define _FP_MAXFRAC_1&t;&t;(~(_FP_WS_TYPE)0)
multiline_comment|/*&n; * Unpack the raw bits of a native fp value.  Do not classify or&n; * normalize the data.&n; */
DECL|macro|_FP_UNPACK_RAW_1
mdefine_line|#define _FP_UNPACK_RAW_1(fs, X, val)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_##fs _flo; _flo.flt = (val);&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_f = _flo.bits.frac;&t;&t;&t;&t;&t;&bslash;&n;    X##_e = _flo.bits.exp;&t;&t;&t;&t;&t;&bslash;&n;    X##_s = _flo.bits.sign;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|_FP_UNPACK_RAW_1_P
mdefine_line|#define _FP_UNPACK_RAW_1_P(fs, X, val)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_##fs *_flo =&t;&t;&t;&t;&bslash;&n;      (union _FP_UNION_##fs *)(val);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_f = _flo-&gt;bits.frac;&t;&t;&t;&t;&t;&bslash;&n;    X##_e = _flo-&gt;bits.exp;&t;&t;&t;&t;&t;&bslash;&n;    X##_s = _flo-&gt;bits.sign;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/*&n; * Repack the raw bits of a native fp value.&n; */
DECL|macro|_FP_PACK_RAW_1
mdefine_line|#define _FP_PACK_RAW_1(fs, val, X)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_##fs _flo;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _flo.bits.frac = X##_f;&t;&t;&t;&t;&t;&bslash;&n;    _flo.bits.exp  = X##_e;&t;&t;&t;&t;&t;&bslash;&n;    _flo.bits.sign = X##_s;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    (val) = _flo.flt;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|_FP_PACK_RAW_1_P
mdefine_line|#define _FP_PACK_RAW_1_P(fs, val, X)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_##fs *_flo =&t;&t;&t;&t;&bslash;&n;      (union _FP_UNION_##fs *)(val);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.frac = X##_f;&t;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.exp  = X##_e;&t;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.sign = X##_s;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/*&n; * Multiplication algorithms:&n; */
multiline_comment|/* Basic.  Assuming the host word size is &gt;= 2*FRACBITS, we can do the&n;   multiplication immediately.  */
DECL|macro|_FP_MUL_MEAT_1_imm
mdefine_line|#define _FP_MUL_MEAT_1_imm(wfracbits, R, X, Y)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    R##_f = X##_f * Y##_f;&t;&t;&t;&t;&t;&t;&bslash;&n;    /* Normalize since we know where the msb of the multiplicands&t;&bslash;&n;       were (bit B), we know that the msb of the of the product is&t;&bslash;&n;       at either 2B or 2B-1.  */&t;&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_SRS_1(R, wfracbits-1, 2*wfracbits);&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/* Given a 1W * 1W =&gt; 2W primitive, do the extended multiplication.  */
DECL|macro|_FP_MUL_MEAT_1_wide
mdefine_line|#define _FP_MUL_MEAT_1_wide(wfracbits, R, X, Y, doit)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_W_TYPE _Z_f0, _Z_f1;&t;&t;&t;&t;&t;&t;&bslash;&n;    doit(_Z_f1, _Z_f0, X##_f, Y##_f);&t;&t;&t;&t;&t;&bslash;&n;    /* Normalize since we know where the msb of the multiplicands&t;&bslash;&n;       were (bit B), we know that the msb of the of the product is&t;&bslash;&n;       at either 2B or 2B-1.  */&t;&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_SRS_2(_Z, wfracbits-1, 2*wfracbits);&t;&t;&t;&bslash;&n;    R##_f = _Z_f0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/* Finally, a simple widening multiply algorithm.  What fun!  */
DECL|macro|_FP_MUL_MEAT_1_hard
mdefine_line|#define _FP_MUL_MEAT_1_hard(wfracbits, R, X, Y)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_W_TYPE _xh, _xl, _yh, _yl, _z_f0, _z_f1, _a_f0, _a_f1;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    /* split the words in half */&t;&t;&t;&t;&t;&bslash;&n;    _xh = X##_f &gt;&gt; (_FP_W_TYPE_SIZE/2);&t;&t;&t;&t;&t;&bslash;&n;    _xl = X##_f &amp; (((_FP_W_TYPE)1 &lt;&lt; (_FP_W_TYPE_SIZE/2)) - 1);&t;&t;&bslash;&n;    _yh = Y##_f &gt;&gt; (_FP_W_TYPE_SIZE/2);&t;&t;&t;&t;&t;&bslash;&n;    _yl = Y##_f &amp; (((_FP_W_TYPE)1 &lt;&lt; (_FP_W_TYPE_SIZE/2)) - 1);&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    /* multiply the pieces */&t;&t;&t;&t;&t;&t;&bslash;&n;    _z_f0 = _xl * _yl;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _a_f0 = _xh * _yl;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _a_f1 = _xl * _yh;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _z_f1 = _xh * _yh;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    /* reassemble into two full words */&t;&t;&t;&t;&bslash;&n;    if ((_a_f0 += _a_f1) &lt; _a_f1)&t;&t;&t;&t;&t;&bslash;&n;      _z_f1 += (_FP_W_TYPE)1 &lt;&lt; (_FP_W_TYPE_SIZE/2);&t;&t;&t;&bslash;&n;    _a_f1 = _a_f0 &gt;&gt; (_FP_W_TYPE_SIZE/2);&t;&t;&t;&t;&bslash;&n;    _a_f0 = _a_f0 &lt;&lt; (_FP_W_TYPE_SIZE/2);&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_ADD_2(_z, _z, _a);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    /* normalize */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_SRS_2(_z, wfracbits - 1, 2*wfracbits);&t;&t;&t;&bslash;&n;    R##_f = _z_f0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/*&n; * Division algorithms:&n; */
multiline_comment|/* Basic.  Assuming the host word size is &gt;= 2*FRACBITS, we can do the&n;   division immediately.  Give this macro either _FP_DIV_HELP_imm for&n;   C primitives or _FP_DIV_HELP_ldiv for the ISO function.  Which you&n;   choose will depend on what the compiler does with divrem4.  */
DECL|macro|_FP_DIV_MEAT_1_imm
mdefine_line|#define _FP_DIV_MEAT_1_imm(fs, R, X, Y, doit)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_W_TYPE _q, _r;&t;&t;&t;&t;&t;&bslash;&n;    X##_f &lt;&lt;= (X##_f &lt; Y##_f&t;&t;&t;&t;&bslash;&n;&t;       ? R##_e--, _FP_WFRACBITS_##fs&t;&t;&bslash;&n;&t;       : _FP_WFRACBITS_##fs - 1);&t;&t;&bslash;&n;    doit(_q, _r, X##_f, Y##_f);&t;&t;&t;&t;&bslash;&n;    R##_f = _q | (_r != 0);&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/* GCC&squot;s longlong.h defines a 2W / 1W =&gt; (1W,1W) primitive udiv_qrnnd&n;   that may be useful in this situation.  This first is for a primitive&n;   that requires normalization, the second for one that does not.  Look&n;   for UDIV_NEEDS_NORMALIZATION to tell which your machine needs.  */
DECL|macro|_FP_DIV_MEAT_1_udiv_norm
mdefine_line|#define _FP_DIV_MEAT_1_udiv_norm(fs, R, X, Y)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_W_TYPE _nh, _nl, _q, _r, _y;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    /* Normalize Y -- i.e. make the most significant bit set.  */&t;&bslash;&n;    _y = Y##_f &lt;&lt; _FP_WFRACXBITS_##fs;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    /* Shift X op correspondingly high, that is, up one full word.  */&t;&bslash;&n;    if (X##_f &lt; Y##_f)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;R##_e--;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_nl = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_nh = X##_f;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_nl = X##_f &lt;&lt; (_FP_W_TYPE_SIZE - 1);&t;&t;&t;&t;&bslash;&n;&t;_nh = X##_f &gt;&gt; 1;&t;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    udiv_qrnnd(_q, _r, _nh, _nl, _y);&t;&t;&t;&t;&t;&bslash;&n;    R##_f = _q | (_r != 0);&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|_FP_DIV_MEAT_1_udiv
mdefine_line|#define _FP_DIV_MEAT_1_udiv(fs, R, X, Y)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_W_TYPE _nh, _nl, _q, _r;&t;&t;&t;&bslash;&n;    if (X##_f &lt; Y##_f)&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;R##_e--;&t;&t;&t;&t;&t;&bslash;&n;&t;_nl = X##_f &lt;&lt; _FP_WFRACBITS_##fs;&t;&t;&bslash;&n;&t;_nh = X##_f &gt;&gt; _FP_WFRACXBITS_##fs;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_nl = X##_f &lt;&lt; (_FP_WFRACBITS_##fs - 1);&t;&bslash;&n;&t;_nh = X##_f &gt;&gt; (_FP_WFRACXBITS_##fs + 1);&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    udiv_qrnnd(_q, _r, _nh, _nl, Y##_f);&t;&t;&bslash;&n;    R##_f = _q | (_r != 0);&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/*&n; * Square root algorithms:&n; * We have just one right now, maybe Newton approximation&n; * should be added for those machines where division is fast.&n; */
DECL|macro|_FP_SQRT_MEAT_1
mdefine_line|#define _FP_SQRT_MEAT_1(R, S, T, X, q)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    while (q != _FP_WORK_ROUND)&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        T##_f = S##_f + q;&t;&t;&t;&t;&bslash;&n;        if (T##_f &lt;= X##_f)&t;&t;&t;&t;&bslash;&n;          {&t;&t;&t;&t;&t;&t;&bslash;&n;            S##_f = T##_f + q;&t;&t;&t;&t;&bslash;&n;            X##_f -= T##_f;&t;&t;&t;&t;&bslash;&n;            R##_f += q;&t;&t;&t;&t;&t;&bslash;&n;          }&t;&t;&t;&t;&t;&t;&bslash;&n;        _FP_FRAC_SLL_1(X, 1);&t;&t;&t;&t;&bslash;&n;        q &gt;&gt;= 1;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (X##_f)&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (S##_f &lt; X##_f)&t;&t;&t;&t;&bslash;&n;&t;  R##_f |= _FP_WORK_ROUND;&t;&t;&t;&bslash;&n;&t;R##_f |= _FP_WORK_STICKY;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/*&n; * Assembly/disassembly for converting to/from integral types.  &n; * No shifting or overflow handled here.&n; */
DECL|macro|_FP_FRAC_ASSEMBLE_1
mdefine_line|#define _FP_FRAC_ASSEMBLE_1(r, X, rsize)&t;(r = X##_f)
DECL|macro|_FP_FRAC_DISASSEMBLE_1
mdefine_line|#define _FP_FRAC_DISASSEMBLE_1(X, r, rsize)&t;(X##_f = r)
multiline_comment|/*&n; * Convert FP values between word sizes&n; */
DECL|macro|_FP_FRAC_CONV_1_1
mdefine_line|#define _FP_FRAC_CONV_1_1(dfs, sfs, D, S)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    D##_f = S##_f;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (_FP_WFRACBITS_##sfs &gt; _FP_WFRACBITS_##dfs)&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (S##_c != FP_CLS_NAN)&t;&t;&t;&t;&t;&bslash;&n;&t;  _FP_FRAC_SRS_1(D, (_FP_WFRACBITS_##sfs-_FP_WFRACBITS_##dfs),&t;&bslash;&n;&t;&t;&t; _FP_WFRACBITS_##sfs);&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  _FP_FRAC_SRL_1(D, (_FP_WFRACBITS_##sfs-_FP_WFRACBITS_##dfs));&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      D##_f &lt;&lt;= _FP_WFRACBITS_##dfs - _FP_WFRACBITS_##sfs;&t;&t;&bslash;&n;  } while (0)
macro_line|#endif /* __MATH_EMU_OP_1_H__ */
eof
