multiline_comment|/*&n; * arch/v850/kernel/mach.c -- Defaults for some things defined by &quot;mach.h&quot;&n; *&n; *  Copyright (C) 2001  NEC Corporation&n; *  Copyright (C) 2001  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &quot;mach.h&quot;
multiline_comment|/* Called with each timer tick, if non-zero.  */
DECL|variable|mach_tick
r_void
(paren
op_star
id|mach_tick
)paren
(paren
r_void
)paren
op_assign
l_int|0
suffix:semicolon
eof
