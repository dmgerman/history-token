multiline_comment|/*  $Id: bugs.h,v 1.1 1996/12/26 13:25:20 davem Exp $&n; *  include/asm-sparc64/bugs.h:  Sparc probes for various bugs.&n; *&n; *  Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/config.h&gt;
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
DECL|function|check_bugs
r_static
r_void
id|check_bugs
c_func
(paren
r_void
)paren
(brace
macro_line|#ifndef CONFIG_SMP
id|cpu_data
c_func
(paren
l_int|0
)paren
dot
id|udelay_val
op_assign
id|loops_per_jiffy
suffix:semicolon
macro_line|#endif
)brace
eof
