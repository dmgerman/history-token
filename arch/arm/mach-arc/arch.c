multiline_comment|/*&n; *  linux/arch/arm/mach-arc/arch.c&n; *&n; *  Copyright (C) 1998-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Architecture specific fixups.&n; */
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
r_extern
r_void
id|arc_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ARCH_ARC
id|MACHINE_START
c_func
(paren
id|ARCHIMEDES
comma
l_string|&quot;Acorn-Archimedes&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Dave Gilbert&quot;
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x0207c000
)paren
id|INITIRQ
c_func
(paren
id|arc_init_irq
)paren
id|MACHINE_END
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_A5K
id|MACHINE_START
c_func
(paren
id|A5K
comma
l_string|&quot;Acorn-A5000&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Russell King&quot;
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x0207c000
)paren
id|INITIRQ
c_func
(paren
id|arc_init_irq
)paren
id|MACHINE_END
macro_line|#endif
eof
