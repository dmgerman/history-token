multiline_comment|/*&n; *  linux/arch/h8300/mm/memory.c&n; *&n; *  Copyright (C) 2002  Yoshinori Sato &lt;ysato@users.sourceforge.jp&gt;,&n; *&n; *  Based on:&n; *&n; *  linux/arch/m68knommu/mm/memory.c&n; *&n; *  Copyright (C) 1998  Kenneth Albanowski &lt;kjahds@kjahds.com&gt;,&n; *  Copyright (C) 1999-2002, Greg Ungerer (gerg@snapgear.com)&n; *&n; *  Based on:&n; *&n; *  linux/arch/m68k/mm/memory.c&n; *&n; *  Copyright (C) 1995  Hamish Macdonald&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|cache_clear
r_void
id|cache_clear
(paren
r_int
r_int
id|paddr
comma
r_int
id|len
)paren
(brace
)brace
DECL|function|cache_push
r_void
id|cache_push
(paren
r_int
r_int
id|paddr
comma
r_int
id|len
)paren
(brace
)brace
DECL|function|cache_push_v
r_void
id|cache_push_v
(paren
r_int
r_int
id|vaddr
comma
r_int
id|len
)paren
(brace
)brace
multiline_comment|/* Map some physical address range into the kernel address space. The&n; * code is copied and adapted from map_chunk().&n; */
DECL|function|kernel_map
r_int
r_int
id|kernel_map
c_func
(paren
r_int
r_int
id|paddr
comma
r_int
r_int
id|size
comma
r_int
id|nocacheflag
comma
r_int
r_int
op_star
id|memavailp
)paren
(brace
r_return
id|paddr
suffix:semicolon
)brace
macro_line|#ifdef MAGIC_ROM_PTR
DECL|function|is_in_rom
r_int
id|is_in_rom
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
multiline_comment|/* Anything not in operational RAM is returned as in rom! */
r_if
c_cond
(paren
id|addr
OL
id|_ramstart
op_logical_or
id|addr
op_ge
id|_ramend
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
