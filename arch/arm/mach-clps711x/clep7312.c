multiline_comment|/*&n; *  linux/arch/arm/mach-clps711x/clep7312.c&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &quot;common.h&quot;
r_static
r_void
id|__init
DECL|function|fixup_clep7312
id|fixup_clep7312
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
id|mi-&gt;nr_banks
op_assign
l_int|1
suffix:semicolon
id|mi-&gt;bank
(braket
l_int|0
)braket
dot
id|start
op_assign
l_int|0xc0000000
suffix:semicolon
id|mi-&gt;bank
(braket
l_int|0
)braket
dot
id|size
op_assign
l_int|0x01000000
suffix:semicolon
id|mi-&gt;bank
(braket
l_int|0
)braket
dot
id|node
op_assign
l_int|0
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|CLEP7212
comma
l_string|&quot;Cirrus Logic 7212/7312&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Nobody&quot;
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
id|fixup_clep7312
)paren
id|MAPIO
c_func
(paren
id|clps711x_map_io
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
