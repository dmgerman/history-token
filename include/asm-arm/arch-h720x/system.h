multiline_comment|/*&n; * linux/arch/arm/mach-h720x/system.h&n; *&n; * Copyright (C) 2001-2002 Jungjun Kim, Hynix Semiconductor Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; * linux/include/asm-arm/arch-h720x/system.h&n; *&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
macro_line|#include &lt;asm/hardware.h&gt;
DECL|function|arch_idle
r_static
r_void
id|arch_idle
c_func
(paren
r_void
)paren
(brace
id|CPU_REG
(paren
id|PMU_BASE
comma
id|PMU_MODE
)paren
op_assign
id|PMU_MODE_IDLE
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;r0, r0&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;r0, r0&quot;
)paren
suffix:semicolon
)brace
DECL|function|arch_reset
r_static
id|__inline__
r_void
id|arch_reset
c_func
(paren
r_char
id|mode
)paren
(brace
id|CPU_REG
(paren
id|PMU_BASE
comma
id|PMU_STAT
)paren
op_or_assign
id|PMU_WARMRESET
suffix:semicolon
)brace
macro_line|#endif
eof
