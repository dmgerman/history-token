multiline_comment|/*&n; * linux/arch/arm/mach-iop3xx/iop321-setup.c&n; *&n; * Author: Nicolas Pitre &lt;nico@cam.org&gt;&n; * Copyright (C) 2001 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
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
macro_line|#ifdef CONFIG_ARCH_IQ80321
r_extern
r_void
id|iq80321_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|sys_timer
id|iop321_timer
suffix:semicolon
r_extern
r_void
id|iop321_init_time
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_IQ31244
r_extern
r_void
id|iq31244_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|sys_timer
id|iop321_timer
suffix:semicolon
r_extern
r_void
id|iop321_init_time
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_static
r_void
id|__init
DECL|function|fixup_iop321
id|fixup_iop321
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
macro_line|#if defined(CONFIG_ARCH_IQ80321)
id|MACHINE_START
c_func
(paren
id|IQ80321
comma
l_string|&quot;Intel IQ80321&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Intel Corporation&quot;
)paren
id|BOOT_MEM
c_func
(paren
id|PHYS_OFFSET
comma
id|IQ80321_UART
comma
l_int|0xfe800000
)paren
id|FIXUP
c_func
(paren
id|fixup_iop321
)paren
id|MAPIO
c_func
(paren
id|iq80321_map_io
)paren
id|INITIRQ
c_func
(paren
id|iop321_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|iop331_timer
comma
id|BOOT_PARAMS
c_func
(paren
l_int|0xa0000100
)paren
id|MACHINE_END
macro_line|#elif defined(CONFIG_ARCH_IQ31244)
id|MACHINE_START
c_func
(paren
id|IQ31244
comma
l_string|&quot;Intel IQ31244&quot;
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
id|IQ31244_UART
comma
id|IQ31244_UART
)paren
id|MAPIO
c_func
(paren
id|iq31244_map_io
)paren
id|INITIRQ
c_func
(paren
id|iop321_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|iop331_timer
comma
id|BOOT_PARAMS
c_func
(paren
l_int|0xa0000100
)paren
id|MACHINE_END
macro_line|#else
macro_line|#error No machine descriptor defined for this IOP3XX implementation
macro_line|#endif
eof
