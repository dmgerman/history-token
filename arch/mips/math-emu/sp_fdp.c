multiline_comment|/* IEEE754 floating point arithmetic&n; * single precision&n; */
multiline_comment|/*&n; * MIPS floating point support&n; * Copyright (C) 1994-2000 Algorithmics Ltd.&n; * http://www.algor.co.uk&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; */
macro_line|#include &quot;ieee754sp.h&quot;
DECL|function|ieee754sp_fdp
id|ieee754sp
id|ieee754sp_fdp
c_func
(paren
id|ieee754dp
id|x
)paren
(brace
id|COMPXDP
suffix:semicolon
id|ieee754sp
id|nan
suffix:semicolon
id|EXPLODEXDP
suffix:semicolon
id|CLEARCX
suffix:semicolon
id|FLUSHXDP
suffix:semicolon
r_switch
c_cond
(paren
id|xc
)paren
(brace
r_case
id|IEEE754_CLASS_SNAN
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
l_string|&quot;fdp&quot;
)paren
suffix:semicolon
r_case
id|IEEE754_CLASS_QNAN
suffix:colon
id|nan
op_assign
id|buildsp
c_func
(paren
id|xs
comma
id|SP_EMAX
op_plus
l_int|1
op_plus
id|SP_EBIAS
comma
(paren
id|u32
)paren
(paren
id|xm
op_rshift
(paren
id|DP_MBITS
op_minus
id|SP_MBITS
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ieee754sp_isnan
c_func
(paren
id|nan
)paren
)paren
id|nan
op_assign
id|ieee754sp_indef
c_func
(paren
)paren
suffix:semicolon
r_return
id|ieee754sp_nanxcpt
c_func
(paren
id|nan
comma
l_string|&quot;fdp&quot;
comma
id|x
)paren
suffix:semicolon
r_case
id|IEEE754_CLASS_INF
suffix:colon
r_return
id|ieee754sp_inf
c_func
(paren
id|xs
)paren
suffix:semicolon
r_case
id|IEEE754_CLASS_ZERO
suffix:colon
r_return
id|ieee754sp_zero
c_func
(paren
id|xs
)paren
suffix:semicolon
r_case
id|IEEE754_CLASS_DNORM
suffix:colon
multiline_comment|/* can&squot;t possibly be sp representable */
id|SETCX
c_func
(paren
id|IEEE754_UNDERFLOW
)paren
suffix:semicolon
id|SETCX
c_func
(paren
id|IEEE754_INEXACT
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ieee754_csr.rm
op_eq
id|IEEE754_RU
op_logical_and
op_logical_neg
id|xs
)paren
op_logical_or
(paren
id|ieee754_csr.rm
op_eq
id|IEEE754_RD
op_logical_and
id|xs
)paren
)paren
r_return
id|ieee754sp_xcpt
c_func
(paren
id|ieee754sp_mind
c_func
(paren
id|xs
)paren
comma
l_string|&quot;fdp&quot;
comma
id|x
)paren
suffix:semicolon
r_return
id|ieee754sp_xcpt
c_func
(paren
id|ieee754sp_zero
c_func
(paren
id|xs
)paren
comma
l_string|&quot;fdp&quot;
comma
id|x
)paren
suffix:semicolon
r_case
id|IEEE754_CLASS_NORM
suffix:colon
r_break
suffix:semicolon
)brace
(brace
id|u32
id|rm
suffix:semicolon
multiline_comment|/* convert from DP_MBITS to SP_MBITS+3 with sticky right shift&n;&t;&t; */
id|rm
op_assign
(paren
id|xm
op_rshift
(paren
id|DP_MBITS
op_minus
(paren
id|SP_MBITS
op_plus
l_int|3
)paren
)paren
)paren
op_or
(paren
(paren
id|xm
op_lshift
(paren
l_int|64
op_minus
(paren
id|DP_MBITS
op_minus
(paren
id|SP_MBITS
op_plus
l_int|3
)paren
)paren
)paren
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|SPNORMRET1
c_func
(paren
id|xs
comma
id|xe
comma
id|rm
comma
l_string|&quot;fdp&quot;
comma
id|x
)paren
suffix:semicolon
)brace
)brace
eof
