multiline_comment|/*&n; * Linux/PA-RISC Project (http://www.parisc-linux.org/)&n; *&n; * Floating-point emulation code&n; *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) &lt;bame@debian.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; * BEGIN_DESC&n; *&n; *  File:&n; *&t;@(#)&t;pa/fp/denormal.c&t;&t;$ Revision: $&n; *&n; *  Purpose:&n; *&t;&lt;&lt;please update with a synopsis of the functionality provided by this file&gt;&gt;&n; *&n; *  External Interfaces:&n; *&t;&lt;&lt;the following list was autogenerated, please review&gt;&gt;&n; *&t;dbl_denormalize(dbl_opndp1,dbl_opndp2,inexactflag,rmode)&n; *&t;sgl_denormalize(sgl_opnd,inexactflag,rmode)&n; *&n; *  Internal Interfaces:&n; *&t;&lt;&lt;please update&gt;&gt;&n; *&n; *  Theory:&n; *&t;&lt;&lt;please update with a overview of the operation of this file&gt;&gt;&n; *&n; * END_DESC&n;*/
macro_line|#include &quot;float.h&quot;
macro_line|#include &quot;sgl_float.h&quot;
macro_line|#include &quot;dbl_float.h&quot;
macro_line|#include &quot;hppa.h&quot;
macro_line|#include &lt;linux/kernel.h&gt;
multiline_comment|/* #include &lt;machine/sys/mdep_private.h&gt; */
DECL|macro|Fpustatus_register
macro_line|#undef Fpustatus_register
DECL|macro|Fpustatus_register
mdefine_line|#define Fpustatus_register Fpu_register[0]
r_void
DECL|function|sgl_denormalize
id|sgl_denormalize
c_func
(paren
r_int
r_int
op_star
id|sgl_opnd
comma
id|boolean
op_star
id|inexactflag
comma
r_int
id|rmode
)paren
(brace
r_int
r_int
id|opnd
suffix:semicolon
r_int
id|sign
comma
id|exponent
suffix:semicolon
id|boolean
id|guardbit
op_assign
id|FALSE
comma
id|stickybit
comma
id|inexact
suffix:semicolon
id|opnd
op_assign
op_star
id|sgl_opnd
suffix:semicolon
id|stickybit
op_assign
op_star
id|inexactflag
suffix:semicolon
id|exponent
op_assign
id|Sgl_exponent
c_func
(paren
id|opnd
)paren
op_minus
id|SGL_WRAP
suffix:semicolon
id|sign
op_assign
id|Sgl_sign
c_func
(paren
id|opnd
)paren
suffix:semicolon
id|Sgl_denormalize
c_func
(paren
id|opnd
comma
id|exponent
comma
id|guardbit
comma
id|stickybit
comma
id|inexact
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inexact
)paren
(brace
r_switch
c_cond
(paren
id|rmode
)paren
(brace
r_case
id|ROUNDPLUS
suffix:colon
r_if
c_cond
(paren
id|sign
op_eq
l_int|0
)paren
(brace
id|Sgl_increment
c_func
(paren
id|opnd
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ROUNDMINUS
suffix:colon
r_if
c_cond
(paren
id|sign
op_ne
l_int|0
)paren
(brace
id|Sgl_increment
c_func
(paren
id|opnd
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ROUNDNEAREST
suffix:colon
r_if
c_cond
(paren
id|guardbit
op_logical_and
(paren
id|stickybit
op_logical_or
id|Sgl_isone_lowmantissa
c_func
(paren
id|opnd
)paren
)paren
)paren
(brace
id|Sgl_increment
c_func
(paren
id|opnd
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
id|Sgl_set_sign
c_func
(paren
id|opnd
comma
id|sign
)paren
suffix:semicolon
op_star
id|sgl_opnd
op_assign
id|opnd
suffix:semicolon
op_star
id|inexactflag
op_assign
id|inexact
suffix:semicolon
r_return
suffix:semicolon
)brace
r_void
DECL|function|dbl_denormalize
id|dbl_denormalize
c_func
(paren
r_int
r_int
op_star
id|dbl_opndp1
comma
r_int
r_int
op_star
id|dbl_opndp2
comma
id|boolean
op_star
id|inexactflag
comma
r_int
id|rmode
)paren
(brace
r_int
r_int
id|opndp1
comma
id|opndp2
suffix:semicolon
r_int
id|sign
comma
id|exponent
suffix:semicolon
id|boolean
id|guardbit
op_assign
id|FALSE
comma
id|stickybit
comma
id|inexact
suffix:semicolon
id|opndp1
op_assign
op_star
id|dbl_opndp1
suffix:semicolon
id|opndp2
op_assign
op_star
id|dbl_opndp2
suffix:semicolon
id|stickybit
op_assign
op_star
id|inexactflag
suffix:semicolon
id|exponent
op_assign
id|Dbl_exponent
c_func
(paren
id|opndp1
)paren
op_minus
id|DBL_WRAP
suffix:semicolon
id|sign
op_assign
id|Dbl_sign
c_func
(paren
id|opndp1
)paren
suffix:semicolon
id|Dbl_denormalize
c_func
(paren
id|opndp1
comma
id|opndp2
comma
id|exponent
comma
id|guardbit
comma
id|stickybit
comma
id|inexact
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inexact
)paren
(brace
r_switch
c_cond
(paren
id|rmode
)paren
(brace
r_case
id|ROUNDPLUS
suffix:colon
r_if
c_cond
(paren
id|sign
op_eq
l_int|0
)paren
(brace
id|Dbl_increment
c_func
(paren
id|opndp1
comma
id|opndp2
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ROUNDMINUS
suffix:colon
r_if
c_cond
(paren
id|sign
op_ne
l_int|0
)paren
(brace
id|Dbl_increment
c_func
(paren
id|opndp1
comma
id|opndp2
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ROUNDNEAREST
suffix:colon
r_if
c_cond
(paren
id|guardbit
op_logical_and
(paren
id|stickybit
op_logical_or
id|Dbl_isone_lowmantissap2
c_func
(paren
id|opndp2
)paren
)paren
)paren
(brace
id|Dbl_increment
c_func
(paren
id|opndp1
comma
id|opndp2
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
id|Dbl_set_sign
c_func
(paren
id|opndp1
comma
id|sign
)paren
suffix:semicolon
op_star
id|dbl_opndp1
op_assign
id|opndp1
suffix:semicolon
op_star
id|dbl_opndp2
op_assign
id|opndp2
suffix:semicolon
op_star
id|inexactflag
op_assign
id|inexact
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
