multiline_comment|/*&n; *  linux/arch/arm/mach-epxa10db/arch.c&n; *&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd&n; *  Copyright (C) 2001 Altera Corporation&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
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
