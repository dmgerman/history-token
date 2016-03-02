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
macro_line|#ifdef CONFIG_ARCH_IQ80310
r_extern
r_void
id|iq80310_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iq80310_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
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
r_void
id|iop321_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_IQ80310
r_static
r_void
id|__init
DECL|function|fixup_iq80310
id|fixup_iq80310
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
id|system_rev
op_assign
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
l_int|0xfe830000
)paren
op_amp
l_int|0x0f
suffix:semicolon
r_if
c_cond
(paren
id|system_rev
)paren
id|system_rev
op_assign
l_int|0xF
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_IQ80321
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
id|param_struct
op_star
id|params
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
macro_line|#ifdef CONFIG_ARCH_IQ80310
id|MACHINE_START
c_func
(paren
id|IQ80310
comma
l_string|&quot;Cyclone IQ80310&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;MontaVista Software Inc.&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0xa0000000
comma
l_int|0xfe000000
comma
l_int|0xfe000000
)paren
id|FIXUP
c_func
(paren
id|fixup_iq80310
)paren
id|MAPIO
c_func
(paren
id|iq80310_map_io
)paren
id|INITIRQ
c_func
(paren
id|iq80310_init_irq
)paren
id|MACHINE_END
macro_line|#elif defined(CONFIG_ARCH_IQ80321)
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
l_string|&quot;MontaVista Software, Inc.&quot;
)paren
id|BOOT_MEM
c_func
(paren
id|PHYS_OFFSET
comma
id|IQ80321_UART1
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
id|MACHINE_END
macro_line|#else
macro_line|#error No machine descriptor defined for this IOP310 implementation
macro_line|#endif
eof
