multiline_comment|/*&n; *  linux/arch/arm/mach-clps711x/mm.c&n; *&n; *  Generic MM setup for the CLPS711x-based machines.&n; *&n; *  Copyright (C) 2001 Deep Blue Solutions Ltd&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/hardware/clps7111.h&gt;
macro_line|#if 0 
singleline_comment|//def CONFIG_DISCONTIGMEM
multiline_comment|/*&n; * The assumption of maximum 4 discontiguous memory banks is present&n; * in several places in the ARM kernel, including the parameter block&n; * (this affects boot loaders, too).  Banks do not necessarily&n; * correspond 1:1 with NUMA nodes, although they usually will,&n; * especially if they are widely discontiguous.&n; *&n; *  - note that the parameter block is depreciated for new implementations&n; *  - also note that discontig_node_data is actually used&n; *    -- rmk &n; */
r_static
id|bootmem_data_t
id|node_bootmem_data
(braket
l_int|4
)braket
suffix:semicolon
id|pg_data_t
id|clps711x_node_data
(braket
l_int|4
)braket
op_assign
(brace
(brace
id|bdata
suffix:colon
op_amp
id|node_bootmem_data
(braket
l_int|0
)braket
)brace
comma
(brace
id|bdata
suffix:colon
op_amp
id|node_bootmem_data
(braket
l_int|1
)braket
)brace
comma
(brace
id|bdata
suffix:colon
op_amp
id|node_bootmem_data
(braket
l_int|2
)braket
)brace
comma
(brace
id|bdata
suffix:colon
op_amp
id|node_bootmem_data
(braket
l_int|3
)braket
)brace
comma
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * This maps the generic CLPS711x registers&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|clps711x_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|CLPS7111_VIRT_BASE
comma
id|CLPS7111_PHYS_BASE
comma
l_int|1048576
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
)brace
comma
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|clps711x_map_io
r_void
id|__init
id|clps711x_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|clps711x_io_desc
)paren
suffix:semicolon
)brace
eof
