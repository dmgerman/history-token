multiline_comment|/*&n; *  linux/arch/arm/mach-adifcc/arch.c&n; *&n; *  Copyright (C) 2001 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
r_extern
r_void
id|adifcc_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|adifcc_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ARCH_ADI_EVB
id|MACHINE_START
c_func
(paren
id|ADI_EVB
comma
l_string|&quot;ADI 80200FCC Evaluation Board&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;MontaVista Software Inc.&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0xc0000000
comma
l_int|0x00400000
comma
l_int|0xff400000
)paren
id|MAPIO
c_func
(paren
id|adifcc_map_io
)paren
id|INITIRQ
c_func
(paren
id|adifcc_init_irq
)paren
id|MACHINE_END
macro_line|#endif
eof
