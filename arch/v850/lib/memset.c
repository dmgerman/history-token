multiline_comment|/*&n; * arch/v850/lib/memset.c -- Memory initialization&n; *&n; *  Copyright (C) 2001,02,04  NEC Corporation&n; *  Copyright (C) 2001,02,04  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
DECL|function|memset
r_void
op_star
id|memset
(paren
r_void
op_star
id|dst
comma
r_int
id|val
comma
id|__kernel_size_t
id|count
)paren
(brace
r_if
c_cond
(paren
id|count
)paren
(brace
r_register
r_int
id|loop
suffix:semicolon
r_register
r_void
op_star
id|ptr
id|asm
(paren
l_string|&quot;ep&quot;
)paren
op_assign
id|dst
suffix:semicolon
multiline_comment|/* replicate VAL into a long.  */
id|val
op_and_assign
l_int|0xff
suffix:semicolon
id|val
op_or_assign
id|val
op_lshift
l_int|8
suffix:semicolon
id|val
op_or_assign
id|val
op_lshift
l_int|16
suffix:semicolon
multiline_comment|/* copy initial unaligned bytes.  */
r_if
c_cond
(paren
(paren
r_int
)paren
id|ptr
op_amp
l_int|1
)paren
(brace
op_star
(paren
r_char
op_star
)paren
id|ptr
op_assign
id|val
suffix:semicolon
id|ptr
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|ptr
op_plus
l_int|1
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
l_int|2
op_logical_and
(paren
(paren
r_int
)paren
id|ptr
op_amp
l_int|2
)paren
)paren
(brace
op_star
(paren
r_int
op_star
)paren
id|ptr
op_assign
id|val
suffix:semicolon
id|ptr
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_int
op_star
)paren
id|ptr
op_plus
l_int|1
)paren
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/* 32-byte copying loop.  */
r_for
c_loop
(paren
id|loop
op_assign
id|count
op_div
l_int|32
suffix:semicolon
id|loop
suffix:semicolon
id|loop
op_decrement
)paren
(brace
id|asm
(paren
l_string|&quot;sst.w %0, 0[ep]; sst.w %0, 4[ep];&quot;
l_string|&quot;sst.w %0, 8[ep]; sst.w %0, 12[ep];&quot;
l_string|&quot;sst.w %0, 16[ep]; sst.w %0, 20[ep];&quot;
l_string|&quot;sst.w %0, 24[ep]; sst.w %0, 28[ep]&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|ptr
op_add_assign
l_int|32
suffix:semicolon
)brace
id|count
op_mod_assign
l_int|32
suffix:semicolon
multiline_comment|/* long copying loop.  */
r_for
c_loop
(paren
id|loop
op_assign
id|count
op_div
l_int|4
suffix:semicolon
id|loop
suffix:semicolon
id|loop
op_decrement
)paren
(brace
op_star
(paren
r_int
op_star
)paren
id|ptr
op_assign
id|val
suffix:semicolon
id|ptr
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_int
op_star
)paren
id|ptr
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|count
op_mod_assign
l_int|4
suffix:semicolon
multiline_comment|/* finish up with any trailing bytes.  */
r_if
c_cond
(paren
id|count
op_amp
l_int|2
)paren
(brace
op_star
(paren
r_int
op_star
)paren
id|ptr
op_assign
id|val
suffix:semicolon
id|ptr
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_int
op_star
)paren
id|ptr
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_amp
l_int|1
)paren
(brace
op_star
(paren
r_char
op_star
)paren
id|ptr
op_assign
id|val
suffix:semicolon
)brace
)brace
r_return
id|dst
suffix:semicolon
)brace
eof
