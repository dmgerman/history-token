multiline_comment|/*&n; * linux/arch/arm/mach-h720x/h7201-eval.c&n; *&n; * Copyright (C) 2003 Thomas Gleixner &lt;tglx@linutronix.de&gt;&n; *               2003 Robert Schwebel &lt;r.schwebel@pengutronix.de&gt;&n; *               2004 Sascha Hauer    &lt;s.hauer@pengutronix.de&gt;&n; *&n; * Architecture specific stuff for Hynix GMS30C7201 development board&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &quot;common.h&quot;
id|MACHINE_START
c_func
(paren
id|H7201
comma
l_string|&quot;Hynix GMS30C7201&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Robert Schwebel, Pengutronix&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x40000000
comma
l_int|0x80000000
comma
l_int|0xf0000000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0xc0001000
)paren
id|MAPIO
c_func
(paren
id|h720x_map_io
)paren
id|INITIRQ
c_func
(paren
id|h720x_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|h7201_timer
comma
id|MACHINE_END
eof
