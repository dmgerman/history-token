multiline_comment|/*&n; *  linux/include/asm-arm/timex.h&n; *&n; *  Copyright (C) 1997,1998 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Architecture Specific TIME specifications&n; */
macro_line|#ifndef _ASMARM_TIMEX_H
DECL|macro|_ASMARM_TIMEX_H
mdefine_line|#define _ASMARM_TIMEX_H
multiline_comment|/*&n; * On the RiscPC, the clock ticks at 2MHz.&n; */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE         2000000
multiline_comment|/* IS THAT RIGHT ON A5000? FIXME */
DECL|typedef|cycles_t
r_typedef
r_int
r_int
id|cycles_t
suffix:semicolon
r_extern
id|cycles_t
id|cacheflush_time
suffix:semicolon
DECL|function|get_cycles
r_static
r_inline
id|cycles_t
id|get_cycles
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
