multiline_comment|/*&n; *  linux/arch/arm/mach-versatile/versatile_ab.c&n; *&n; *  Copyright (C) 2004 ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware/amba.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &quot;core.h&quot;
id|MACHINE_START
c_func
(paren
id|VERSATILE_AB
comma
l_string|&quot;ARM-Versatile AB&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;ARM Ltd/Deep Blue Solutions Ltd&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x00000000
comma
l_int|0x101f1000
comma
l_int|0xf11f1000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x00000100
)paren
id|MAPIO
c_func
(paren
id|versatile_map_io
)paren
id|INITIRQ
c_func
(paren
id|versatile_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|versatile_timer
comma
id|INIT_MACHINE
c_func
(paren
id|versatile_init
)paren
id|MACHINE_END
eof
