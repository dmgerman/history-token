multiline_comment|/*&n; *  linux/arch/arm/mach-clps711x/arch-ceiva.c&n; *&n; *  Copyright (C) 2002, Rob Scott &lt;rscott@mtrob.fdns.net&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sizes.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &quot;common.h&quot;
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|ceiva_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual, physical, length, type */
multiline_comment|/* SED1355 controlled video RAM &amp; registers */
(brace
id|CEIVA_VIRT_SED1355
comma
id|CEIVA_PHYS_SED1355
comma
id|SZ_2M
comma
id|MT_DEVICE
)brace
)brace
suffix:semicolon
DECL|function|ceiva_map_io
r_static
r_void
id|__init
id|ceiva_map_io
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
id|ceiva_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|ceiva_io_desc
)paren
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|CEIVA
comma
l_string|&quot;CEIVA/Polaroid Photo MAX Digital Picture Frame&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Rob Scott&quot;
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
id|MAPIO
c_func
(paren
id|ceiva_map_io
)paren
id|INITIRQ
c_func
(paren
id|clps711x_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|clps711x_timer
comma
id|MACHINE_END
eof
