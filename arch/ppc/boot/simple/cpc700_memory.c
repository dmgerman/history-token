multiline_comment|/*&n; * arch/ppc/boot/common/cpc700_memory.c&n; *&n; * Find memory based upon settings in the CPC700 bridge&n; *&n; * Author: Dan Cox&n; *&n; * 2001-2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;cpc700.h&quot;
r_int
r_int
DECL|function|cpc700_get_mem_size
id|cpc700_get_mem_size
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|len
comma
id|amt
suffix:semicolon
multiline_comment|/* Start at MB1EA, since MB0EA will most likely be the ending address&n;&t;   for ROM space. */
r_for
c_loop
(paren
id|len
op_assign
l_int|0
comma
id|i
op_assign
id|CPC700_MB1EA
suffix:semicolon
id|i
op_le
id|CPC700_MB4EA
suffix:semicolon
id|i
op_add_assign
l_int|4
)paren
(brace
id|amt
op_assign
id|cpc700_read_memreg
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|amt
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|len
op_assign
id|amt
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
eof
