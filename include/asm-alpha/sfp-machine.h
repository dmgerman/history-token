multiline_comment|/* Machine-dependent software floating-point definitions.&n;   Alpha kernel version.&n;   Copyright (C) 1997,1998,1999 Free Software Foundation, Inc.&n;   This file is part of the GNU C Library.&n;   Contributed by Richard Henderson (rth@cygnus.com),&n;&t;&t;  Jakub Jelinek (jakub@redhat.com) and&n;&t;&t;  David S. Miller (davem@redhat.com).&n;&n;   The GNU C Library is free software; you can redistribute it and/or&n;   modify it under the terms of the GNU Library General Public License as&n;   published by the Free Software Foundation; either version 2 of the&n;   License, or (at your option) any later version.&n;&n;   The GNU C Library is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;   Library General Public License for more details.&n;&n;   You should have received a copy of the GNU Library General Public&n;   License along with the GNU C Library; see the file COPYING.LIB.  If&n;   not, write to the Free Software Foundation, Inc.,&n;   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
macro_line|#ifndef _SFP_MACHINE_H
DECL|macro|_SFP_MACHINE_H
mdefine_line|#define _SFP_MACHINE_H
DECL|macro|_FP_W_TYPE_SIZE
mdefine_line|#define _FP_W_TYPE_SIZE&t;&t;64
DECL|macro|_FP_W_TYPE
mdefine_line|#define _FP_W_TYPE&t;&t;unsigned long
DECL|macro|_FP_WS_TYPE
mdefine_line|#define _FP_WS_TYPE&t;&t;signed long
DECL|macro|_FP_I_TYPE
mdefine_line|#define _FP_I_TYPE&t;&t;long
DECL|macro|_FP_MUL_MEAT_S
mdefine_line|#define _FP_MUL_MEAT_S(R,X,Y)&t;&t;&t;&t;&t;&bslash;&n;  _FP_MUL_MEAT_1_imm(_FP_WFRACBITS_S,R,X,Y)
DECL|macro|_FP_MUL_MEAT_D
mdefine_line|#define _FP_MUL_MEAT_D(R,X,Y)&t;&t;&t;&t;&t;&bslash;&n;  _FP_MUL_MEAT_1_wide(_FP_WFRACBITS_D,R,X,Y,umul_ppmm)
DECL|macro|_FP_MUL_MEAT_Q
mdefine_line|#define _FP_MUL_MEAT_Q(R,X,Y)&t;&t;&t;&t;&t;&bslash;&n;  _FP_MUL_MEAT_2_wide(_FP_WFRACBITS_Q,R,X,Y,umul_ppmm)
DECL|macro|_FP_DIV_MEAT_S
mdefine_line|#define _FP_DIV_MEAT_S(R,X,Y)&t;_FP_DIV_MEAT_1_imm(S,R,X,Y,_FP_DIV_HELP_imm)
DECL|macro|_FP_DIV_MEAT_D
mdefine_line|#define _FP_DIV_MEAT_D(R,X,Y)&t;_FP_DIV_MEAT_1_udiv(D,R,X,Y)
DECL|macro|_FP_DIV_MEAT_Q
mdefine_line|#define _FP_DIV_MEAT_Q(R,X,Y)&t;_FP_DIV_MEAT_2_udiv(Q,R,X,Y)
DECL|macro|_FP_NANFRAC_S
mdefine_line|#define _FP_NANFRAC_S&t;&t;_FP_QNANBIT_S
DECL|macro|_FP_NANFRAC_D
mdefine_line|#define _FP_NANFRAC_D&t;&t;_FP_QNANBIT_D
DECL|macro|_FP_NANFRAC_Q
mdefine_line|#define _FP_NANFRAC_Q&t;&t;_FP_QNANBIT_Q
DECL|macro|_FP_NANSIGN_S
mdefine_line|#define _FP_NANSIGN_S&t;&t;1
DECL|macro|_FP_NANSIGN_D
mdefine_line|#define _FP_NANSIGN_D&t;&t;1
DECL|macro|_FP_NANSIGN_Q
mdefine_line|#define _FP_NANSIGN_Q&t;&t;1
DECL|macro|_FP_KEEPNANFRACP
mdefine_line|#define _FP_KEEPNANFRACP 1
multiline_comment|/* Alpha Architecture Handbook, 4.7.10.4 sais that&n; * we should prefer any type of NaN in Fb, then Fa.&n; */
DECL|macro|_FP_CHOOSENAN
mdefine_line|#define _FP_CHOOSENAN(fs, wc, R, X, Y, OP)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    R##_s = Y##_s;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_COPY_##wc(R,X);&t;&t;&t;&t;&t;&bslash;&n;    R##_c = FP_CLS_NAN;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/* Obtain the current rounding mode. */
DECL|macro|FP_ROUNDMODE
mdefine_line|#define FP_ROUNDMODE&t;mode
DECL|macro|FP_RND_NEAREST
mdefine_line|#define FP_RND_NEAREST&t;(FPCR_DYN_NORMAL &gt;&gt; FPCR_DYN_SHIFT)
DECL|macro|FP_RND_ZERO
mdefine_line|#define FP_RND_ZERO&t;(FPCR_DYN_CHOPPED &gt;&gt; FPCR_DYN_SHIFT)
DECL|macro|FP_RND_PINF
mdefine_line|#define FP_RND_PINF&t;(FPCR_DYN_PLUS &gt;&gt; FPCR_DYN_SHIFT)
DECL|macro|FP_RND_MINF
mdefine_line|#define FP_RND_MINF&t;(FPCR_DYN_MINUS &gt;&gt; FPCR_DYN_SHIFT)
multiline_comment|/* Exception flags. */
DECL|macro|FP_EX_INVALID
mdefine_line|#define FP_EX_INVALID&t;&t;IEEE_TRAP_ENABLE_INV
DECL|macro|FP_EX_OVERFLOW
mdefine_line|#define FP_EX_OVERFLOW&t;&t;IEEE_TRAP_ENABLE_OVF
DECL|macro|FP_EX_UNDERFLOW
mdefine_line|#define FP_EX_UNDERFLOW&t;&t;IEEE_TRAP_ENABLE_UNF
DECL|macro|FP_EX_DIVZERO
mdefine_line|#define FP_EX_DIVZERO&t;&t;IEEE_TRAP_ENABLE_DZE
DECL|macro|FP_EX_INEXACT
mdefine_line|#define FP_EX_INEXACT&t;&t;IEEE_TRAP_ENABLE_INE
DECL|macro|FP_EX_DENORM
mdefine_line|#define FP_EX_DENORM&t;&t;IEEE_TRAP_ENABLE_DNO
DECL|macro|FP_DENORM_ZERO
mdefine_line|#define FP_DENORM_ZERO&t;&t;(swcr &amp; IEEE_MAP_DMZ)
multiline_comment|/* We write the results always */
DECL|macro|FP_INHIBIT_RESULTS
mdefine_line|#define FP_INHIBIT_RESULTS 0
macro_line|#endif
eof
