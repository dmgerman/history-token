multiline_comment|/*&n; *  linux/arch/arm/mach-clps711x/mm.c&n; *&n; *  Extra MM routines for the EDB7211 board&n; *&n; *  Copyright (C) 2000, 2001 Blue Mug, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/sizes.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
r_extern
r_void
id|clps711x_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * The on-chip registers are given a size of 1MB so that a section can&n; * be used to map them; this saves a page table.  This is the place to&n; * add mappings for ROM, expansion memory, PCMCIA, etc.  (if static&n; * mappings are chosen for those areas).&n; *&n; * Here is a physical memory map (to be fleshed out later):&n; *&n; * Physical Address  Size  Description&n; * ----------------- ----- ---------------------------------&n; * c0000000-c001ffff 128KB reserved for video RAM [1]&n; * c0020000-c0023fff  16KB parameters (see Documentation/arm/Setup)&n; * c0024000-c0027fff  16KB swapper_pg_dir (task 0 page directory)&n; * c0028000-...            kernel image (TEXTADDR)&n; *&n; * [1] Unused pages should be given back to the VM; they are not yet.&n; *     The parameter block should also be released (not sure if this&n; *     happens).&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|edb7211_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual, physical, length, domain, r, w, c, b */
multiline_comment|/* memory-mapped extra keyboard row and CS8900A Ethernet chip */
(brace
id|EP7211_VIRT_EXTKBD
comma
id|EP7211_PHYS_EXTKBD
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
(brace
id|EP7211_VIRT_CS8900A
comma
id|EP7211_PHYS_CS8900A
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
multiline_comment|/* flash banks */
(brace
id|EP7211_VIRT_FLASH1
comma
id|EP7211_PHYS_FLASH1
comma
id|SZ_8M
comma
id|DOMAIN_KERNEL
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
(brace
id|EP7211_VIRT_FLASH2
comma
id|EP7211_PHYS_FLASH2
comma
id|SZ_8M
comma
id|DOMAIN_KERNEL
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
DECL|function|edb7211_map_io
r_void
id|__init
id|edb7211_map_io
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
id|edb7211_io_desc
)paren
suffix:semicolon
)brace
eof
