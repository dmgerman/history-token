multiline_comment|/*&n; * include/asm-v850/delay.h -- Delay routines, using a pre-computed&n; * &t;&quot;loops_per_second&quot; value&n; *&n; *  Copyright (C) 2001,03  NEC Corporation&n; *  Copyright (C) 2001,03  Miles Bader &lt;miles@gnu.org&gt;&n; *  Copyright (C) 1994 Hamish Macdonald&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; */
macro_line|#ifndef __V850_DELAY_H__
DECL|macro|__V850_DELAY_H__
mdefine_line|#define __V850_DELAY_H__
macro_line|#include &lt;asm/param.h&gt;
DECL|function|__delay
r_extern
id|__inline__
r_void
id|__delay
c_func
(paren
r_int
r_int
id|loops
)paren
(brace
r_if
c_cond
(paren
id|loops
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;1: add -1, %0; bnz 1b&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|loops
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|loops
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Use only for very small delays ( &lt; 1 msec).  Should probably use a&n; * lookup table, really, as the multiplications take much too long with&n; * short delays.  This is a &quot;reasonable&quot; implementation, though (and the&n; * first constant multiplications gets optimized away if the delay is&n; * a constant)  &n; */
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
DECL|function|udelay
r_extern
id|__inline__
r_void
id|udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
(brace
r_register
r_int
r_int
id|full_loops
comma
id|part_loops
suffix:semicolon
id|full_loops
op_assign
(paren
(paren
id|usecs
op_star
id|HZ
)paren
op_div
l_int|1000000
)paren
op_star
id|loops_per_jiffy
suffix:semicolon
id|usecs
op_mod_assign
(paren
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
id|part_loops
op_assign
(paren
id|usecs
op_star
id|HZ
op_star
id|loops_per_jiffy
)paren
op_div
l_int|1000000
suffix:semicolon
id|__delay
c_func
(paren
id|full_loops
op_plus
id|part_loops
)paren
suffix:semicolon
)brace
macro_line|#endif /* __V850_DELAY_H__ */
eof
