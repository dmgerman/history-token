multiline_comment|/* IEEE754 floating point arithmetic&n; * single precision&n; */
multiline_comment|/*&n; * MIPS floating point support&n; * Copyright (C) 1994-2000 Algorithmics Ltd.&n; * http://www.algor.co.uk&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; */
macro_line|#include &quot;ieee754sp.h&quot;
multiline_comment|/* close to ieeep754sp_logb&n;*/
DECL|function|ieee754sp_frexp
id|ieee754sp
id|ieee754sp_frexp
c_func
(paren
id|ieee754sp
id|x
comma
r_int
op_star
id|eptr
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
id|eptr
op_assign
l_int|0
suffix:semicolon
r_return
id|x
suffix:semicolon
r_case
id|IEEE754_CLASS_DNORM
suffix:colon
id|SPDNORMX
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IEEE754_CLASS_NORM
suffix:colon
r_break
suffix:semicolon
)brace
op_star
id|eptr
op_assign
id|xe
op_plus
l_int|1
suffix:semicolon
r_return
id|buildsp
c_func
(paren
id|xs
comma
op_minus
l_int|1
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
