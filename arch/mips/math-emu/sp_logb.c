multiline_comment|/* IEEE754 floating point arithmetic&n; * single precision&n; */
multiline_comment|/*&n; * MIPS floating point support&n; * Copyright (C) 1994-2000 Algorithmics Ltd.&n; * http://www.algor.co.uk&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; */
macro_line|#include &quot;ieee754sp.h&quot;
DECL|function|ieee754sp_logb
id|ieee754sp
id|ieee754sp_logb
c_func
(paren
id|ieee754sp
id|x
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
r_return
id|ieee754sp_nanxcpt
c_func
(paren
id|x
comma
l_string|&quot;logb&quot;
comma
id|x
)paren
suffix:semicolon
r_case
id|IEEE754_CLASS_QNAN
suffix:colon
r_return
id|x
suffix:semicolon
r_case
id|IEEE754_CLASS_INF
suffix:colon
r_return
id|ieee754sp_inf
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|IEEE754_CLASS_ZERO
suffix:colon
r_return
id|ieee754sp_inf
c_func
(paren
l_int|1
)paren
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
r_return
id|ieee754sp_fint
c_func
(paren
id|xe
)paren
suffix:semicolon
)brace
eof
