multiline_comment|/* More subroutines needed by GCC output code on some machines.  */
multiline_comment|/* Compile this one with gcc.  */
multiline_comment|/* Copyright (C) 1989, 92-98, 1999 Free Software Foundation, Inc.&n;&n;This file is part of GNU CC.&n;&n;GNU CC is free software; you can redistribute it and/or modify&n;it under the terms of the GNU General Public License as published by&n;the Free Software Foundation; either version 2, or (at your option)&n;any later version.&n;&n;GNU CC is distributed in the hope that it will be useful,&n;but WITHOUT ANY WARRANTY; without even the implied warranty of&n;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;GNU General Public License for more details.&n;&n;You should have received a copy of the GNU General Public License&n;along with GNU CC; see the file COPYING.  If not, write to&n;the Free Software Foundation, 59 Temple Place - Suite 330,&n;Boston, MA 02111-1307, USA.  */
multiline_comment|/* As a special exception, if you link this library with other files,&n;   some of which are compiled with GCC, to produce an executable,&n;   this library does not by itself cause the resulting executable&n;   to be covered by the GNU General Public License.&n;   This exception does not however invalidate any other reasons why&n;   the executable file might be covered by the GNU General Public License.&n; */
multiline_comment|/* support functions required by the kernel. based on code from gcc-2.95.3 */
multiline_comment|/* I Molton&t;29/07/01 */
macro_line|#include &quot;gcclib.h&quot;
id|DItype
DECL|function|__ashldi3
id|__ashldi3
(paren
id|DItype
id|u
comma
id|word_type
id|b
)paren
(brace
id|DIunion
id|w
suffix:semicolon
id|word_type
id|bm
suffix:semicolon
id|DIunion
id|uu
suffix:semicolon
r_if
c_cond
(paren
id|b
op_eq
l_int|0
)paren
r_return
id|u
suffix:semicolon
id|uu.ll
op_assign
id|u
suffix:semicolon
id|bm
op_assign
(paren
r_sizeof
(paren
id|SItype
)paren
op_star
id|BITS_PER_UNIT
)paren
op_minus
id|b
suffix:semicolon
r_if
c_cond
(paren
id|bm
op_le
l_int|0
)paren
(brace
id|w.s.low
op_assign
l_int|0
suffix:semicolon
id|w.s.high
op_assign
(paren
id|USItype
)paren
id|uu.s.low
op_lshift
op_minus
id|bm
suffix:semicolon
)brace
r_else
(brace
id|USItype
id|carries
op_assign
(paren
id|USItype
)paren
id|uu.s.low
op_rshift
id|bm
suffix:semicolon
id|w.s.low
op_assign
(paren
id|USItype
)paren
id|uu.s.low
op_lshift
id|b
suffix:semicolon
id|w.s.high
op_assign
(paren
(paren
id|USItype
)paren
id|uu.s.high
op_lshift
id|b
)paren
op_or
id|carries
suffix:semicolon
)brace
r_return
id|w.ll
suffix:semicolon
)brace
eof
