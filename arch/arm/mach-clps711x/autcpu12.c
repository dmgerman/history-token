multiline_comment|/*&n; *  linux/arch/arm/mach-clps711x/autcpu12.c&n; *&n; * (c) 2001 Thomas Gleixner, autronix automation &lt;gleixner@autronix.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/sizes.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/arch/autcpu12.h&gt;
r_extern
r_void
id|clps711x_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|clps711x_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * The on-chip registers are given a size of 1MB so that a section can&n; * be used to map them; this saves a page table.  This is the place to&n; * add mappings for ROM, expansion memory, PCMCIA, etc.  (if static&n; * mappings are chosen for those areas).&n; *&n;*/
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|autcpu12_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual, physical, length, domain, r, w, c, b */
multiline_comment|/* memory-mapped extra io and CS8900A Ethernet chip */
multiline_comment|/* ethernet chip */
(brace
id|AUTCPU12_VIRT_CS8900A
comma
id|AUTCPU12_PHYS_CS8900A
comma
id|SZ_1M
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
DECL|function|autcpu12_map_io
r_void
id|__init
id|autcpu12_map_io
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
id|autcpu12_io_desc
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|AUTCPU12
comma
l_string|&quot;autronix autcpu12&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Thomas Gleixner&quot;
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
l_int|0xc0020000
)paren
id|MAPIO
c_func
(paren
id|autcpu12_map_io
)paren
id|INITIRQ
c_func
(paren
id|clps711x_init_irq
)paren
id|MACHINE_END
eof
