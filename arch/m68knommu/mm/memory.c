multiline_comment|/*&n; *  linux/arch/m68knommu/mm/memory.c&n; *&n; *  Copyright (C) 1998  Kenneth Albanowski &lt;kjahds@kjahds.com&gt;,&n; *  Copyright (C) 1999-2002, Greg Ungerer (gerg@snapgear.com)&n; *&n; *  Based on:&n; *&n; *  linux/arch/m68k/mm/memory.c&n; *&n; *  Copyright (C) 1995  Hamish Macdonald&n; */
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
multiline_comment|/*&n; * cache_clear() semantics: Clear any cache entries for the area in question,&n; * without writing back dirty entries first. This is useful if the data will&n; * be overwritten anyway, e.g. by DMA to memory. The range is defined by a&n; * _physical_ address.&n; */
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
multiline_comment|/*&n; *&t;Define cache invalidate functions. The ColdFire 5407 is really&n; *&t;the only processor that needs to do some work here. Anything&n; *&t;that has separate data and instruction caches will be a problem.&n; */
macro_line|#ifdef CONFIG_M5407
DECL|function|cache_invalidate_lines
r_static
id|__inline__
r_void
id|cache_invalidate_lines
c_func
(paren
r_int
r_int
id|paddr
comma
r_int
id|len
)paren
(brace
r_int
r_int
id|sset
comma
id|eset
suffix:semicolon
id|sset
op_assign
(paren
id|paddr
op_amp
l_int|0x00000ff0
)paren
suffix:semicolon
id|eset
op_assign
(paren
(paren
id|paddr
op_plus
id|len
)paren
op_amp
l_int|0x0000ff0
)paren
op_plus
l_int|0x10
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;clrl&t;%%d0&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;%0,%%a0&bslash;n&bslash;t&quot;
l_string|&quot;addl&t;%%d0,%%a0&bslash;n&bslash;t&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;.word&t;0xf4e8&bslash;n&bslash;t&quot;
l_string|&quot;addl&t;#0x10,%%a0&bslash;n&bslash;t&quot;
l_string|&quot;cmpl&t;%1,%%a0&bslash;n&bslash;t&quot;
l_string|&quot;blt&t;2b&bslash;n&bslash;t&quot;
l_string|&quot;addql&t;#1,%%d0&bslash;n&bslash;t&quot;
l_string|&quot;cmpil&t;#4,%%d0&bslash;n&bslash;t&quot;
l_string|&quot;bne&t;1b&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|sset
)paren
comma
l_string|&quot;a&quot;
(paren
id|eset
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;a0&quot;
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|cache_invalidate_lines
mdefine_line|#define&t;cache_invalidate_lines(a,b)
macro_line|#endif
multiline_comment|/*&n; * cache_push() semantics: Write back any dirty cache data in the given area,&n; * and invalidate the range in the instruction cache. It needs not (but may)&n; * invalidate those entries also in the data cache. The range is defined by a&n; * _physical_ address.&n; */
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
id|cache_invalidate_lines
c_func
(paren
id|paddr
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * cache_push_v() semantics: Write back any dirty cache data in the given&n; * area, and invalidate those entries at least in the instruction cache. This&n; * is intended to be used after data has been written that can be executed as&n; * code later. The range is defined by a _user_mode_ _virtual_ address  (or,&n; * more exactly, the space is defined by the %sfc/%dfc register.)&n; */
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
id|cache_invalidate_lines
c_func
(paren
id|vaddr
comma
id|len
)paren
suffix:semicolon
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
r_extern
r_int
r_int
id|_ramstart
comma
id|_ramend
suffix:semicolon
multiline_comment|/*&n;&t; *&t;What we are really trying to do is determine if addr is&n;&t; *&t;in an allocated kernel memory region. If not then assume&n;&t; *&t;we cannot free it or otherwise de-allocate it. Ideally&n;&t; *&t;we could restrict this to really being in a ROM or flash,&n;&t; *&t;but that would need to be done on a board by board basis,&n;&t; *&t;not globally.&n;&t; */
r_if
c_cond
(paren
(paren
id|addr
OL
id|_ramstart
)paren
op_logical_or
(paren
id|addr
op_ge
id|_ramend
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Default case, not in ROM */
r_return
l_int|0
suffix:semicolon
)brace
eof
