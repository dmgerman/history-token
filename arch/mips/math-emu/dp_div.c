multiline_comment|/* IEEE754 floating point arithmetic&n; * double precision: common utilities&n; */
multiline_comment|/*&n; * MIPS floating point support&n; * Copyright (C) 1994-2000 Algorithmics Ltd.&n; * http://www.algor.co.uk&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; */
macro_line|#include &quot;ieee754dp.h&quot;
DECL|function|ieee754dp_div
id|ieee754dp
id|ieee754dp_div
c_func
(paren
id|ieee754dp
id|x
comma
id|ieee754dp
id|y
)paren
(brace
id|COMPXDP
suffix:semicolon
id|COMPYDP
suffix:semicolon
id|EXPLODEXDP
suffix:semicolon
id|EXPLODEYDP
suffix:semicolon
id|CLEARCX
suffix:semicolon
id|FLUSHXDP
suffix:semicolon
id|FLUSHYDP
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
id|ieee754dp_nanxcpt
c_func
(paren
id|ieee754dp_indef
c_func
(paren
)paren
comma
l_string|&quot;div&quot;
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
id|SETCX
c_func
(paren
id|IEEE754_INVALID_OPERATION
)paren
suffix:semicolon
r_return
id|ieee754dp_xcpt
c_func
(paren
id|ieee754dp_indef
c_func
(paren
)paren
comma
l_string|&quot;div&quot;
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
id|IEEE754_CLASS_NORM
comma
id|IEEE754_CLASS_INF
)paren
suffix:colon
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
r_return
id|ieee754dp_zero
c_func
(paren
id|xs
op_xor
id|ys
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
id|ieee754dp_inf
c_func
(paren
id|xs
op_xor
id|ys
)paren
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
id|SETCX
c_func
(paren
id|IEEE754_INVALID_OPERATION
)paren
suffix:semicolon
r_return
id|ieee754dp_xcpt
c_func
(paren
id|ieee754dp_indef
c_func
(paren
)paren
comma
l_string|&quot;div&quot;
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
id|SETCX
c_func
(paren
id|IEEE754_ZERO_DIVIDE
)paren
suffix:semicolon
r_return
id|ieee754dp_xcpt
c_func
(paren
id|ieee754dp_inf
c_func
(paren
id|xs
op_xor
id|ys
)paren
comma
l_string|&quot;div&quot;
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
r_return
id|ieee754dp_zero
c_func
(paren
id|xs
op_eq
id|ys
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
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
id|DPDNORMX
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
id|DPDNORMY
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
id|DPDNORMX
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
m_assert
(paren
id|xm
op_amp
id|DP_HIDDEN_BIT
)paren
suffix:semicolon
m_assert
(paren
id|ym
op_amp
id|DP_HIDDEN_BIT
)paren
suffix:semicolon
multiline_comment|/* provide rounding space */
id|xm
op_lshift_assign
l_int|3
suffix:semicolon
id|ym
op_lshift_assign
l_int|3
suffix:semicolon
(brace
multiline_comment|/* now the dirty work */
id|u64
id|rm
op_assign
l_int|0
suffix:semicolon
r_int
id|re
op_assign
id|xe
op_minus
id|ye
suffix:semicolon
id|u64
id|bm
suffix:semicolon
r_for
c_loop
(paren
id|bm
op_assign
id|DP_MBIT
c_func
(paren
id|DP_MBITS
op_plus
l_int|2
)paren
suffix:semicolon
id|bm
suffix:semicolon
id|bm
op_rshift_assign
l_int|1
)paren
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
op_sub_assign
id|ym
suffix:semicolon
id|rm
op_or_assign
id|bm
suffix:semicolon
r_if
c_cond
(paren
id|xm
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|xm
op_lshift_assign
l_int|1
suffix:semicolon
)brace
id|rm
op_lshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|xm
)paren
id|rm
op_or_assign
l_int|1
suffix:semicolon
multiline_comment|/* have remainder, set sticky */
m_assert
(paren
id|rm
)paren
suffix:semicolon
multiline_comment|/* normalise rm to rounding precision ?&n;&t;&t; */
r_while
c_loop
(paren
(paren
id|rm
op_rshift
(paren
id|DP_MBITS
op_plus
l_int|3
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|rm
op_lshift_assign
l_int|1
suffix:semicolon
id|re
op_decrement
suffix:semicolon
)brace
id|DPNORMRET2
c_func
(paren
id|xs
op_eq
id|ys
ques
c_cond
l_int|0
suffix:colon
l_int|1
comma
id|re
comma
id|rm
comma
l_string|&quot;div&quot;
comma
id|x
comma
id|y
)paren
suffix:semicolon
)brace
)brace
eof
