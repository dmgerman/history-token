multiline_comment|/*&n; *  linux/arch/m32r/mm/ioremap-nommu.c&n; *&n; *  Copyright (c) 2001, 2002  Hiroyuki Kondo&n; *&n; *  Taken from mips version.&n; *    (C) Copyright 1995 1996 Linus Torvalds&n; *    (C) Copyright 2001 Ralf Baechle&n; */
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/*&n; * Remap an arbitrary physical address space into the kernel virtual&n; * address space. Needed when the kernel wants to access high addresses&n; * directly.&n; *&n; * NOTE! We need to allow non-page-aligned mappings too: we will obviously&n; * have to convert them into an offset in a page-aligned mapping, but the&n; * caller shouldn&squot;t need to know that small detail.&n; */
DECL|macro|IS_LOW512
mdefine_line|#define IS_LOW512(addr) (!((unsigned long)(addr) &amp; ~0x1fffffffUL))
r_void
id|__iomem
op_star
DECL|function|__ioremap
id|__ioremap
c_func
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|phys_addr
suffix:semicolon
)brace
DECL|macro|IS_KSEG1
mdefine_line|#define IS_KSEG1(addr) (((unsigned long)(addr) &amp; ~0x1fffffffUL) == KSEG1)
DECL|function|iounmap
r_void
id|iounmap
c_func
(paren
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
)brace
eof
