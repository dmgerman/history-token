multiline_comment|/* IEEE754 floating point arithmetic&n; * double precision: common utilities&n; */
multiline_comment|/*&n; * MIPS floating point support&n; * Copyright (C) 1994-2000 Algorithmics Ltd.  All rights reserved.&n; * http://www.algor.co.uk&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; */
macro_line|#include &quot;ieee754dp.h&quot;
DECL|function|ieee754dp_tlong
id|s64
id|ieee754dp_tlong
c_func
(paren
id|ieee754dp
id|x
)paren
(brace
id|COMPXDP
suffix:semicolon
id|CLEARCX
suffix:semicolon
id|EXPLODEXDP
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
r_case
id|IEEE754_CLASS_QNAN
suffix:colon
r_case
id|IEEE754_CLASS_INF
suffix:colon
id|SETCX
c_func
(paren
id|IEEE754_INVALID_OPERATION
)paren
suffix:semicolon
r_return
id|ieee754di_xcpt
c_func
(paren
id|ieee754di_indef
c_func
(paren
)paren
comma
l_string|&quot;dp_tlong&quot;
comma
id|x
)paren
suffix:semicolon
r_case
id|IEEE754_CLASS_ZERO
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|IEEE754_CLASS_DNORM
suffix:colon
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
op_ge
l_int|63
)paren
(brace
multiline_comment|/* look for valid corner case */
r_if
c_cond
(paren
id|xe
op_eq
l_int|63
op_logical_and
id|xs
op_logical_and
id|xm
op_eq
id|DP_HIDDEN_BIT
)paren
r_return
op_minus
l_int|0x8000000000000000LL
suffix:semicolon
multiline_comment|/* Set invalid. We will only use overflow for floating&n;&t;&t;   point overflow */
id|SETCX
c_func
(paren
id|IEEE754_INVALID_OPERATION
)paren
suffix:semicolon
r_return
id|ieee754di_xcpt
c_func
(paren
id|ieee754di_indef
c_func
(paren
)paren
comma
l_string|&quot;dp_tlong&quot;
comma
id|x
)paren
suffix:semicolon
)brace
multiline_comment|/* oh gawd */
r_if
c_cond
(paren
id|xe
OG
id|DP_MBITS
)paren
(brace
id|xm
op_lshift_assign
id|xe
op_minus
id|DP_MBITS
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|xe
OL
id|DP_MBITS
)paren
(brace
id|u64
id|residue
suffix:semicolon
r_int
id|round
suffix:semicolon
r_int
id|sticky
suffix:semicolon
r_int
id|odd
suffix:semicolon
r_if
c_cond
(paren
id|xe
OL
op_minus
l_int|1
)paren
(brace
id|residue
op_assign
id|xm
suffix:semicolon
id|round
op_assign
l_int|0
suffix:semicolon
id|sticky
op_assign
id|residue
op_ne
l_int|0
suffix:semicolon
id|xm
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Shifting a u64 64 times does not work,&n;&t;&t;&t;* so we do it in two steps. Be aware that xe&n;&t;&t;&t;* may be -1 */
id|residue
op_assign
id|xm
op_lshift
(paren
id|xe
op_plus
l_int|1
)paren
suffix:semicolon
id|residue
op_lshift_assign
l_int|63
op_minus
id|DP_MBITS
suffix:semicolon
id|round
op_assign
(paren
id|residue
op_rshift
l_int|63
)paren
op_ne
l_int|0
suffix:semicolon
id|sticky
op_assign
(paren
id|residue
op_lshift
l_int|1
)paren
op_ne
l_int|0
suffix:semicolon
id|xm
op_rshift_assign
id|DP_MBITS
op_minus
id|xe
suffix:semicolon
)brace
id|odd
op_assign
(paren
id|xm
op_amp
l_int|0x1
)paren
op_ne
l_int|0x0
suffix:semicolon
r_switch
c_cond
(paren
id|ieee754_csr.rm
)paren
(brace
r_case
id|IEEE754_RN
suffix:colon
r_if
c_cond
(paren
id|round
op_logical_and
(paren
id|sticky
op_logical_or
id|odd
)paren
)paren
id|xm
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IEEE754_RZ
suffix:colon
r_break
suffix:semicolon
r_case
id|IEEE754_RU
suffix:colon
multiline_comment|/* toward +Infinity */
r_if
c_cond
(paren
(paren
id|round
op_logical_or
id|sticky
)paren
op_logical_and
op_logical_neg
id|xs
)paren
id|xm
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IEEE754_RD
suffix:colon
multiline_comment|/* toward -Infinity */
r_if
c_cond
(paren
(paren
id|round
op_logical_or
id|sticky
)paren
op_logical_and
id|xs
)paren
id|xm
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|xm
op_rshift
l_int|63
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* This can happen after rounding */
id|SETCX
c_func
(paren
id|IEEE754_INVALID_OPERATION
)paren
suffix:semicolon
r_return
id|ieee754di_xcpt
c_func
(paren
id|ieee754di_indef
c_func
(paren
)paren
comma
l_string|&quot;dp_tlong&quot;
comma
id|x
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|round
op_logical_or
id|sticky
)paren
id|SETCX
c_func
(paren
id|IEEE754_INEXACT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xs
)paren
r_return
op_minus
id|xm
suffix:semicolon
r_else
r_return
id|xm
suffix:semicolon
)brace
DECL|function|ieee754dp_tulong
id|u64
id|ieee754dp_tulong
c_func
(paren
id|ieee754dp
id|x
)paren
(brace
id|ieee754dp
id|hb
op_assign
id|ieee754dp_1e63
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* what if x &lt; 0 ?? */
r_if
c_cond
(paren
id|ieee754dp_lt
c_func
(paren
id|x
comma
id|hb
)paren
)paren
r_return
(paren
id|u64
)paren
id|ieee754dp_tlong
c_func
(paren
id|x
)paren
suffix:semicolon
r_return
(paren
id|u64
)paren
id|ieee754dp_tlong
c_func
(paren
id|ieee754dp_sub
c_func
(paren
id|x
comma
id|hb
)paren
)paren
op_or
(paren
l_int|1ULL
op_lshift
l_int|63
)paren
suffix:semicolon
)brace
eof
