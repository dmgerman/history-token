multiline_comment|/* IEEE754 floating point arithmetic&n; * double precision: common utilities&n; */
multiline_comment|/*&n; * MIPS floating point support&n; * Copyright (C) 1994-2000 Algorithmics Ltd.  All rights reserved.&n; * http://www.algor.co.uk&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; */
macro_line|#include &quot;ieee754dp.h&quot;
DECL|function|ieee754dp_cmp
r_int
id|ieee754dp_cmp
c_func
(paren
id|ieee754dp
id|x
comma
id|ieee754dp
id|y
comma
r_int
id|cmp
comma
r_int
id|sig
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
id|FLUSHXDP
suffix:semicolon
id|FLUSHYDP
suffix:semicolon
id|CLEARCX
suffix:semicolon
multiline_comment|/* Even clear inexact flag here */
r_if
c_cond
(paren
id|ieee754dp_isnan
c_func
(paren
id|x
)paren
op_logical_or
id|ieee754dp_isnan
c_func
(paren
id|y
)paren
)paren
(brace
r_if
c_cond
(paren
id|sig
op_logical_or
id|xc
op_eq
id|IEEE754_CLASS_SNAN
op_logical_or
id|yc
op_eq
id|IEEE754_CLASS_SNAN
)paren
id|SETCX
c_func
(paren
id|IEEE754_INVALID_OPERATION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
op_amp
id|IEEE754_CUN
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|cmp
op_amp
(paren
id|IEEE754_CLT
op_or
id|IEEE754_CGT
)paren
)paren
(brace
r_if
c_cond
(paren
id|sig
op_logical_and
id|SETANDTESTCX
c_func
(paren
id|IEEE754_INVALID_OPERATION
)paren
)paren
r_return
id|ieee754si_xcpt
c_func
(paren
l_int|0
comma
l_string|&quot;fcmpf&quot;
comma
id|x
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|s64
id|vx
op_assign
id|x.bits
suffix:semicolon
id|s64
id|vy
op_assign
id|y.bits
suffix:semicolon
r_if
c_cond
(paren
id|vx
OL
l_int|0
)paren
id|vx
op_assign
op_minus
id|vx
op_xor
id|DP_SIGN_BIT
suffix:semicolon
r_if
c_cond
(paren
id|vy
OL
l_int|0
)paren
id|vy
op_assign
op_minus
id|vy
op_xor
id|DP_SIGN_BIT
suffix:semicolon
r_if
c_cond
(paren
id|vx
OL
id|vy
)paren
r_return
(paren
id|cmp
op_amp
id|IEEE754_CLT
)paren
op_ne
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|vx
op_eq
id|vy
)paren
r_return
(paren
id|cmp
op_amp
id|IEEE754_CEQ
)paren
op_ne
l_int|0
suffix:semicolon
r_else
r_return
(paren
id|cmp
op_amp
id|IEEE754_CGT
)paren
op_ne
l_int|0
suffix:semicolon
)brace
)brace
eof
