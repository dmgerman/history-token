multiline_comment|/* IEEE754 floating point arithmetic&n; * single precision&n; */
multiline_comment|/*&n; * MIPS floating point support&n; * Copyright (C) 1994-2000 Algorithmics Ltd.  All rights reserved.&n; * http://www.algor.co.uk&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; */
macro_line|#include &quot;ieee754sp.h&quot;
DECL|function|ieee754sp_sub
id|ieee754sp
id|ieee754sp_sub
c_func
(paren
id|ieee754sp
id|x
comma
id|ieee754sp
id|y
)paren
(brace
id|COMPXSP
suffix:semicolon
id|COMPYSP
suffix:semicolon
id|EXPLODEXSP
suffix:semicolon
id|EXPLODEYSP
suffix:semicolon
id|CLEARCX
suffix:semicolon
id|FLUSHXSP
suffix:semicolon
id|FLUSHYSP
suffix:semicolon
r_switch
c_cond
(paren
id|CLPAIR
c_func
(paren
id|xc
comma
id|yc
)paren
)paren
(brace
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_SNAN
comma
id|IEEE754_CLASS_QNAN
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_QNAN
comma
id|IEEE754_CLASS_SNAN
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_SNAN
comma
id|IEEE754_CLASS_SNAN
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_ZERO
comma
id|IEEE754_CLASS_SNAN
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_NORM
comma
id|IEEE754_CLASS_SNAN
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_DNORM
comma
id|IEEE754_CLASS_SNAN
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_INF
comma
id|IEEE754_CLASS_SNAN
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_SNAN
comma
id|IEEE754_CLASS_ZERO
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_SNAN
comma
id|IEEE754_CLASS_NORM
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_SNAN
comma
id|IEEE754_CLASS_DNORM
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_SNAN
comma
id|IEEE754_CLASS_INF
)paren
suffix:colon
id|SETCX
c_func
(paren
id|IEEE754_INVALID_OPERATION
)paren
suffix:semicolon
r_return
id|ieee754sp_nanxcpt
c_func
(paren
id|ieee754sp_indef
c_func
(paren
)paren
comma
l_string|&quot;sub&quot;
comma
id|x
comma
id|y
)paren
suffix:semicolon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_ZERO
comma
id|IEEE754_CLASS_QNAN
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_NORM
comma
id|IEEE754_CLASS_QNAN
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_DNORM
comma
id|IEEE754_CLASS_QNAN
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_INF
comma
id|IEEE754_CLASS_QNAN
)paren
suffix:colon
r_return
id|y
suffix:semicolon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_QNAN
comma
id|IEEE754_CLASS_QNAN
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_QNAN
comma
id|IEEE754_CLASS_ZERO
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_QNAN
comma
id|IEEE754_CLASS_NORM
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_QNAN
comma
id|IEEE754_CLASS_DNORM
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_QNAN
comma
id|IEEE754_CLASS_INF
)paren
suffix:colon
r_return
id|x
suffix:semicolon
multiline_comment|/* Infinity handling&n;&t;&t; */
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_INF
comma
id|IEEE754_CLASS_INF
)paren
suffix:colon
r_if
c_cond
(paren
id|xs
op_ne
id|ys
)paren
r_return
id|x
suffix:semicolon
id|SETCX
c_func
(paren
id|IEEE754_INVALID_OPERATION
)paren
suffix:semicolon
r_return
id|ieee754sp_xcpt
c_func
(paren
id|ieee754sp_indef
c_func
(paren
)paren
comma
l_string|&quot;sub&quot;
comma
id|x
comma
id|y
)paren
suffix:semicolon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_ZERO
comma
id|IEEE754_CLASS_INF
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_DNORM
comma
id|IEEE754_CLASS_INF
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_NORM
comma
id|IEEE754_CLASS_INF
)paren
suffix:colon
r_return
id|ieee754sp_inf
c_func
(paren
id|ys
op_xor
l_int|1
)paren
suffix:semicolon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_INF
comma
id|IEEE754_CLASS_ZERO
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_INF
comma
id|IEEE754_CLASS_NORM
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_INF
comma
id|IEEE754_CLASS_DNORM
)paren
suffix:colon
r_return
id|x
suffix:semicolon
multiline_comment|/* Zero handling&n;&t;&t; */
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_ZERO
comma
id|IEEE754_CLASS_ZERO
)paren
suffix:colon
r_if
c_cond
(paren
id|xs
op_ne
id|ys
)paren
r_return
id|x
suffix:semicolon
r_else
r_return
id|ieee754sp_zero
c_func
(paren
id|ieee754_csr.rm
op_eq
id|IEEE754_RD
)paren
suffix:semicolon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_NORM
comma
id|IEEE754_CLASS_ZERO
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_DNORM
comma
id|IEEE754_CLASS_ZERO
)paren
suffix:colon
r_return
id|x
suffix:semicolon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_ZERO
comma
id|IEEE754_CLASS_NORM
)paren
suffix:colon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_ZERO
comma
id|IEEE754_CLASS_DNORM
)paren
suffix:colon
multiline_comment|/* quick fix up */
id|DPSIGN
c_func
(paren
id|y
)paren
op_xor_assign
l_int|1
suffix:semicolon
r_return
id|y
suffix:semicolon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_DNORM
comma
id|IEEE754_CLASS_DNORM
)paren
suffix:colon
id|SPDNORMX
suffix:semicolon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_NORM
comma
id|IEEE754_CLASS_DNORM
)paren
suffix:colon
id|SPDNORMY
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_DNORM
comma
id|IEEE754_CLASS_NORM
)paren
suffix:colon
id|SPDNORMX
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_NORM
comma
id|IEEE754_CLASS_NORM
)paren
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* flip sign of y and handle as add */
id|ys
op_xor_assign
l_int|1
suffix:semicolon
m_assert
(paren
id|xm
op_amp
id|SP_HIDDEN_BIT
)paren
suffix:semicolon
m_assert
(paren
id|ym
op_amp
id|SP_HIDDEN_BIT
)paren
suffix:semicolon
multiline_comment|/* provide guard,round and stick bit space */
id|xm
op_lshift_assign
l_int|3
suffix:semicolon
id|ym
op_lshift_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|xe
OG
id|ye
)paren
(brace
multiline_comment|/* have to shift y fraction right to align&n;&t;&t; */
r_int
id|s
op_assign
id|xe
op_minus
id|ye
suffix:semicolon
id|SPXSRSYn
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ye
OG
id|xe
)paren
(brace
multiline_comment|/* have to shift x fraction right to align&n;&t;&t; */
r_int
id|s
op_assign
id|ye
op_minus
id|xe
suffix:semicolon
id|SPXSRSXn
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
m_assert
(paren
id|xe
op_eq
id|ye
)paren
suffix:semicolon
m_assert
(paren
id|xe
op_le
id|SP_EMAX
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xs
op_eq
id|ys
)paren
(brace
multiline_comment|/* generate 28 bit result of adding two 27 bit numbers&n;&t;&t; */
id|xm
op_assign
id|xm
op_plus
id|ym
suffix:semicolon
id|xe
op_assign
id|xe
suffix:semicolon
id|xs
op_assign
id|xs
suffix:semicolon
r_if
c_cond
(paren
id|xm
op_rshift
(paren
id|SP_MBITS
op_plus
l_int|1
op_plus
l_int|3
)paren
)paren
(brace
multiline_comment|/* carry out */
id|SPXSRSX1
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* shift preserving sticky */
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|xm
op_ge
id|ym
)paren
(brace
id|xm
op_assign
id|xm
op_minus
id|ym
suffix:semicolon
id|xe
op_assign
id|xe
suffix:semicolon
id|xs
op_assign
id|xs
suffix:semicolon
)brace
r_else
(brace
id|xm
op_assign
id|ym
op_minus
id|xm
suffix:semicolon
id|xe
op_assign
id|xe
suffix:semicolon
id|xs
op_assign
id|ys
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xm
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ieee754_csr.rm
op_eq
id|IEEE754_RD
)paren
r_return
id|ieee754sp_zero
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* round negative inf. =&gt; sign = -1 */
r_else
r_return
id|ieee754sp_zero
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* other round modes   =&gt; sign = 1 */
)brace
multiline_comment|/* normalize to rounding precision&n;&t;&t; */
r_while
c_loop
(paren
(paren
id|xm
op_rshift
(paren
id|SP_MBITS
op_plus
l_int|3
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|xm
op_lshift_assign
l_int|1
suffix:semicolon
id|xe
op_decrement
suffix:semicolon
)brace
)brace
id|SPNORMRET2
c_func
(paren
id|xs
comma
id|xe
comma
id|xm
comma
l_string|&quot;sub&quot;
comma
id|x
comma
id|y
)paren
suffix:semicolon
)brace
eof
