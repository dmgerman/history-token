multiline_comment|/*&n; * linux/arch/arm/mach-iop3xx/arch.c&n; *&n; * Author: Nicolas Pitre &lt;nico@cam.org&gt;&n; * Copyright (C) 2001 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#ifdef CONFIG_ARCH_IQ80331
r_extern
r_void
id|iq80331_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iop331_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iop331_init_time
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_IQ80331
r_static
r_void
id|__init
DECL|function|fixup_iop331
id|fixup_iop331
c_func
(paren
r_struct
id|machine_desc
op_star
id|desc
comma
r_struct
id|tag
op_star
id|tags
comma
r_char
op_star
op_star
id|cmdline
comma
r_struct
id|meminfo
op_star
id|mi
)paren
(brace
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_ARCH_IQ80331)
id|MACHINE_START
c_func
(paren
id|IQ80331
comma
l_string|&quot;Intel IQ80331&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Intel Corp.&quot;
)paren
id|BOOT_MEM
c_func
(paren
id|PHYS_OFFSET
comma
l_int|0xfff01000
comma
l_int|0xfffff000
)paren
singleline_comment|// virtual, physical
singleline_comment|//&t;BOOT_MEM(PHYS_OFFSET, IQ80331_UART0_VIRT, IQ80331_UART0_PHYS)
id|MAPIO
c_func
(paren
id|iq80331_map_io
)paren
id|INITIRQ
c_func
(paren
id|iop331_init_irq
)paren
id|INITTIME
c_func
(paren
id|iop331_init_time
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x0100
)paren
id|MACHINE_END
macro_line|#else
macro_line|#error No machine descriptor defined for this IOP3xx implementation
macro_line|#endif
eof
