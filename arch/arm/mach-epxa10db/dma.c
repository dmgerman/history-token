multiline_comment|/*&n; *  linux/arch/arm/mach-epxa10db/dma.c&n; *&n; *  Copyright (C) 1999 ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach/dma.h&gt;
DECL|function|arch_dma_init
r_void
id|__init
id|arch_dma_init
c_func
(paren
id|dma_t
op_star
id|dma
)paren
(brace
)brace
eof
