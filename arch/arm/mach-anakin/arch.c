multiline_comment|/*&n; *  linux/arch/arm/mach-anakin/arch.c&n; *&n; *  Copyright (C) 2001 Aleph One Ltd. for Acunia N.V.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   09-Apr-2001 W/TTC&t;Created&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
r_extern
r_void
id|anakin_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|genarch_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|ANAKIN
comma
l_string|&quot;Anakin&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Wookey/Tak-Shing Chan&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x20000000
comma
l_int|0x40000000
comma
l_int|0xe0000000
)paren
id|VIDEO
c_func
(paren
l_int|0x80000000
comma
l_int|0x8002db40
)paren
id|MAPIO
c_func
(paren
id|anakin_map_io
)paren
id|INITIRQ
c_func
(paren
id|genarch_init_irq
)paren
id|MACHINE_END
eof
