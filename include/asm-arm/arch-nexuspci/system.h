multiline_comment|/*&n; * linux/include/asm-arm/arch-nexuspci/system.h&n; *&n; * Copyright (c) 1996, 97, 98, 99, 2000 FutureTV Labs Ltd.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
DECL|function|arch_idle
r_static
r_void
id|arch_idle
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|hlt_counter
)paren
id|cpu_do_idle
c_func
(paren
id|IDLE_WAIT_SLOW
)paren
suffix:semicolon
)brace
DECL|macro|arch_reset
mdefine_line|#define arch_reset(mode)&t;do { } while (0)
macro_line|#endif
eof
