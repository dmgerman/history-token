multiline_comment|/*&n; *  linux/arch/arm/mach-epxa10db/time.c&n; *&n; *  Copyright (C) 2000 Deep Blue Solutions&n; *  Copyright (C) 2001 Altera Corporation&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
r_extern
r_int
(paren
op_star
id|set_rtc
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|function|epxa10db_set_rtc
r_static
r_int
id|epxa10db_set_rtc
c_func
(paren
r_void
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|epxa10db_rtc_init
r_static
r_int
id|epxa10db_rtc_init
c_func
(paren
r_void
)paren
(brace
id|set_rtc
op_assign
id|epxa10db_set_rtc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|epxa10db_rtc_init
id|__initcall
c_func
(paren
id|epxa10db_rtc_init
)paren
suffix:semicolon
eof
