multiline_comment|/* IEEE754 floating point arithmetic&n; * double precision: common utilities&n; */
multiline_comment|/*&n; * MIPS floating point support&n; * Copyright (C) 1994-2000 Algorithmics Ltd.  All rights reserved.&n; * http://www.algor.co.uk&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; */
macro_line|#include &quot;ieee754dp.h&quot;
DECL|function|ieee754dp_mul
id|ieee754dp
id|ieee754dp_mul
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
id|CLEARCX
suffix:semicolon
id|EXPLODEXDP
suffix:semicolon
id|EXPLODEYDP
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
id|IEEE754_CLASS_SNAN
)paren
suffix:colon
r_return
id|ieee754dp_nanxcpt
c_func
(paren
id|ieee754dp_bestnan
c_func
(paren
id|x
comma
id|y
)paren
comma
l_string|&quot;mul&quot;
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
id|IEEE754_CLASS_QNAN
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
r_return
id|ieee754dp_nanxcpt
c_func
(paren
id|y
comma
l_string|&quot;mul&quot;
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
id|IEEE754_CLASS_SNAN
comma
id|IEEE754_CLASS_QNAN
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
r_return
id|ieee754dp_nanxcpt
c_func
(paren
id|x
comma
l_string|&quot;mul&quot;
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
id|IEEE754_CLASS_QNAN
comma
id|IEEE754_CLASS_QNAN
)paren
suffix:colon
r_return
id|ieee754dp_bestnan
c_func
(paren
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
multiline_comment|/* Infinity handling */
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
id|IEEE754_CLASS_ZERO
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
l_string|&quot;mul&quot;
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
id|IEEE754_CLASS_DNORM
comma
id|IEEE754_CLASS_INF
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
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_INF
comma
id|IEEE754_CLASS_INF
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
r_case
id|CLPAIR
c_func
(paren
id|IEEE754_CLASS_ZERO
comma
id|IEEE754_CLASS_ZERO
)paren
suffix:colon
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
multiline_comment|/* rm = xm * ym, re = xe+ye basicly */
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
(brace
r_int
id|re
op_assign
id|xe
op_plus
id|ye
suffix:semicolon
r_int
id|rs
op_assign
id|xs
op_xor
id|ys
suffix:semicolon
r_int
r_int
r_int
id|rm
suffix:semicolon
multiline_comment|/* shunt to top of word */
id|xm
op_lshift_assign
l_int|64
op_minus
(paren
id|DP_MBITS
op_plus
l_int|1
)paren
suffix:semicolon
id|ym
op_lshift_assign
l_int|64
op_minus
(paren
id|DP_MBITS
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* multiply 32bits xm,ym to give high 32bits rm with stickness&n;&t;&t; */
multiline_comment|/* 32 * 32 =&gt; 64 */
DECL|macro|DPXMULT
mdefine_line|#define DPXMULT(x,y)&t;((unsigned long long)(x) * (unsigned long long)y)
(brace
r_int
id|lxm
op_assign
id|xm
suffix:semicolon
r_int
id|hxm
op_assign
id|xm
op_rshift
l_int|32
suffix:semicolon
r_int
id|lym
op_assign
id|ym
suffix:semicolon
r_int
id|hym
op_assign
id|ym
op_rshift
l_int|32
suffix:semicolon
r_int
r_int
r_int
id|lrm
suffix:semicolon
r_int
r_int
r_int
id|hrm
suffix:semicolon
id|lrm
op_assign
id|DPXMULT
c_func
(paren
id|lxm
comma
id|lym
)paren
suffix:semicolon
id|hrm
op_assign
id|DPXMULT
c_func
(paren
id|hxm
comma
id|hym
)paren
suffix:semicolon
(brace
r_int
r_int
r_int
id|t
op_assign
id|DPXMULT
c_func
(paren
id|lxm
comma
id|hym
)paren
suffix:semicolon
(brace
r_int
r_int
r_int
id|at
op_assign
id|lrm
op_plus
(paren
id|t
op_lshift
l_int|32
)paren
suffix:semicolon
id|hrm
op_add_assign
id|at
OL
id|lrm
suffix:semicolon
id|lrm
op_assign
id|at
suffix:semicolon
)brace
id|hrm
op_assign
id|hrm
op_plus
(paren
id|t
op_rshift
l_int|32
)paren
suffix:semicolon
)brace
(brace
r_int
r_int
r_int
id|t
op_assign
id|DPXMULT
c_func
(paren
id|hxm
comma
id|lym
)paren
suffix:semicolon
(brace
r_int
r_int
r_int
id|at
op_assign
id|lrm
op_plus
(paren
id|t
op_lshift
l_int|32
)paren
suffix:semicolon
id|hrm
op_add_assign
id|at
OL
id|lrm
suffix:semicolon
id|lrm
op_assign
id|at
suffix:semicolon
)brace
id|hrm
op_assign
id|hrm
op_plus
(paren
id|t
op_rshift
l_int|32
)paren
suffix:semicolon
)brace
id|rm
op_assign
id|hrm
op_or
(paren
id|lrm
op_ne
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * sticky shift down to normal rounding precision&n;&t;&t; */
r_if
c_cond
(paren
(paren
r_int
r_int
r_int
)paren
id|rm
OL
l_int|0
)paren
(brace
id|rm
op_assign
(paren
id|rm
op_rshift
(paren
l_int|64
op_minus
(paren
id|DP_MBITS
op_plus
l_int|1
op_plus
l_int|3
)paren
)paren
)paren
op_or
(paren
(paren
id|rm
op_lshift
(paren
id|DP_MBITS
op_plus
l_int|1
op_plus
l_int|3
)paren
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|re
op_increment
suffix:semicolon
)brace
r_else
(brace
id|rm
op_assign
(paren
id|rm
op_rshift
(paren
l_int|64
op_minus
(paren
id|DP_MBITS
op_plus
l_int|1
op_plus
l_int|3
op_plus
l_int|1
)paren
)paren
)paren
op_or
(paren
(paren
id|rm
op_lshift
(paren
id|DP_MBITS
op_plus
l_int|1
op_plus
l_int|3
op_plus
l_int|1
)paren
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
m_assert
(paren
id|rm
op_amp
(paren
id|DP_HIDDEN_BIT
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
id|DPNORMRET2
c_func
(paren
id|rs
comma
id|re
comma
id|rm
comma
l_string|&quot;mul&quot;
comma
id|x
comma
id|y
)paren
suffix:semicolon
)brace
)brace
eof
