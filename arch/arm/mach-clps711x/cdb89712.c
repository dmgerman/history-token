multiline_comment|/*&n; *  linux/arch/arm/mach-clps711x/cdb89712.c&n; *&n; *  Copyright (C) 2000-2001 Deep Blue Solutions Ltd&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
r_extern
r_void
id|clps711x_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|clps711x_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Map the CS89712 Ethernet port.  That should be moved to the&n; * ethernet driver, perhaps.&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|cdb89712_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|ETHER_BASE
comma
id|ETHER_START
comma
id|ETHER_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
id|LAST_DESC
)brace
suffix:semicolon
r_static
r_void
id|__init
DECL|function|fixup_cdb89712
id|fixup_cdb89712
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
DECL|function|cdb89712_map_io
r_static
r_void
id|__init
id|cdb89712_map_io
c_func
(paren
r_void
)paren
(brace
id|clps711x_map_io
c_func
(paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|cdb89712_io_desc
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|CDB89712
comma
l_string|&quot;Cirrus-CDB89712&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Ray Lehtiniemi&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0xc0000000
comma
l_int|0x80000000
comma
l_int|0xff000000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0xc0000100
)paren
id|FIXUP
c_func
(paren
id|fixup_cdb89712
)paren
id|MAPIO
c_func
(paren
id|cdb89712_map_io
)paren
id|INITIRQ
c_func
(paren
id|clps711x_init_irq
)paren
id|MACHINE_END
DECL|function|cdb89712_hw_init
r_static
r_int
id|cdb89712_hw_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cdb89712_hw_init
id|__initcall
c_func
(paren
id|cdb89712_hw_init
)paren
suffix:semicolon
eof
