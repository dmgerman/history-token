multiline_comment|/*&n; *  linux/include/asm-arm/arch-rpc/system.h&n; *&n; *  Copyright (C) 1996-1999 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#include &lt;asm/hardware/iomd.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|arch_idle
r_static
r_void
id|arch_idle
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start_idle
suffix:semicolon
id|start_idle
op_assign
id|jiffies
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|current-&gt;need_resched
op_logical_or
id|hlt_counter
)paren
r_goto
id|slow_out
suffix:semicolon
id|cpu_do_idle
c_func
(paren
id|IDLE_WAIT_FAST
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|start_idle
op_plus
id|HZ
op_div
l_int|50
)paren
)paren
suffix:semicolon
id|cpu_do_idle
c_func
(paren
id|IDLE_CLOCK_SLOW
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|current-&gt;need_resched
op_logical_and
op_logical_neg
id|hlt_counter
)paren
(brace
id|cpu_do_idle
c_func
(paren
id|IDLE_WAIT_SLOW
)paren
suffix:semicolon
)brace
id|cpu_do_idle
c_func
(paren
id|IDLE_CLOCK_FAST
)paren
suffix:semicolon
id|slow_out
suffix:colon
)brace
DECL|function|arch_reset
r_static
r_inline
r_void
id|arch_reset
c_func
(paren
r_char
id|mode
)paren
(brace
id|iomd_writeb
c_func
(paren
l_int|0
comma
id|IOMD_ROMCR0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Jump into the ROM&n;&t; */
id|cpu_reset
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
