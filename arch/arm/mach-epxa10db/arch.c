multiline_comment|/*&n; *  linux/arch/arm/mach-epxa10db/arch.c&n; *&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd&n; *  Copyright (C) 2001 Altera Corporation&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
r_extern
r_void
id|epxa10db_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|epxa10db_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|__init
DECL|function|epxa10db_fixup
id|epxa10db_fixup
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
l_int|0
suffix:semicolon
id|mi-&gt;bank
(braket
l_int|0
)braket
dot
id|size
op_assign
(paren
l_int|32
op_star
l_int|1024
op_star
l_int|1024
)paren
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
multiline_comment|/*&n;        ROOT_DEV = MKDEV(RAMDISK_MAJOR,0);&n;        setup_ramdisk( 1, 0, 0, 8192 );&n;        setup_initrd(0xc0200000, 6*1024*1024);&n;*/
)brace
id|MACHINE_START
c_func
(paren
id|CAMELOT
comma
l_string|&quot;Altera Epxa10db&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Altera Corporation&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x00000000
comma
l_int|0x7fffc000
comma
l_int|0xffffc000
)paren
id|FIXUP
c_func
(paren
id|epxa10db_fixup
)paren
id|MAPIO
c_func
(paren
id|epxa10db_map_io
)paren
id|INITIRQ
c_func
(paren
id|epxa10db_init_irq
)paren
id|MACHINE_END
eof
