multiline_comment|/* IEEE754 floating point arithmetic&n; * single precision&n; */
multiline_comment|/*&n; * MIPS floating point support&n; * Copyright (C) 1994-2000 Algorithmics Ltd.&n; * http://www.algor.co.uk&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; */
macro_line|#include &quot;ieee754sp.h&quot;
multiline_comment|/* modf function is always exact for a finite number&n;*/
DECL|function|ieee754sp_modf
id|ieee754sp
id|ieee754sp_modf
c_func
(paren
id|ieee754sp
id|x
comma
id|ieee754sp
op_star
id|ip
)paren
(brace
id|COMPXSP
suffix:semicolon
id|CLEARCX
suffix:semicolon
id|EXPLODEXSP
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
r_case
id|IEEE754_CLASS_QNAN
suffix:colon
r_case
id|IEEE754_CLASS_INF
suffix:colon
r_case
id|IEEE754_CLASS_ZERO
suffix:colon
op_star
id|ip
op_assign
id|x
suffix:semicolon
r_return
id|x
suffix:semicolon
r_case
id|IEEE754_CLASS_DNORM
suffix:colon
multiline_comment|/* far to small */
op_star
id|ip
op_assign
id|ieee754sp_zero
c_func
(paren
id|xs
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
r_case
id|IEEE754_CLASS_NORM
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xe
OL
l_int|0
)paren
(brace
op_star
id|ip
op_assign
id|ieee754sp_zero
c_func
(paren
id|xs
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xe
op_ge
id|SP_MBITS
)paren
(brace
op_star
id|ip
op_assign
id|x
suffix:semicolon
r_return
id|ieee754sp_zero
c_func
(paren
id|xs
)paren
suffix:semicolon
)brace
multiline_comment|/* generate ipart mantissa by clearing bottom bits&n;&t; */
op_star
id|ip
op_assign
id|buildsp
c_func
(paren
id|xs
comma
id|xe
op_plus
id|SP_EBIAS
comma
(paren
(paren
id|xm
op_rshift
(paren
id|SP_MBITS
op_minus
id|xe
)paren
)paren
op_lshift
(paren
id|SP_MBITS
op_minus
id|xe
)paren
)paren
op_amp
op_complement
id|SP_HIDDEN_BIT
)paren
suffix:semicolon
multiline_comment|/* generate fpart mantissa by clearing top bits&n;&t; * and normalizing (must be able to normalize)&n;&t; */
id|xm
op_assign
(paren
id|xm
op_lshift
(paren
l_int|32
op_minus
(paren
id|SP_MBITS
op_minus
id|xe
)paren
)paren
)paren
op_rshift
(paren
l_int|32
op_minus
(paren
id|SP_MBITS
op_minus
id|xe
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xm
op_eq
l_int|0
)paren
r_return
id|ieee754sp_zero
c_func
(paren
id|xs
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|xm
op_rshift
id|SP_MBITS
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
r_return
id|buildsp
c_func
(paren
id|xs
comma
id|xe
op_plus
id|SP_EBIAS
comma
id|xm
op_amp
op_complement
id|SP_HIDDEN_BIT
)paren
suffix:semicolon
)brace
eof
