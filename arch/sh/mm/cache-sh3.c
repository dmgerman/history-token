multiline_comment|/* $Id: cache-sh3.c,v 1.7 2003/08/28 16:16:09 lethal Exp $&n; *&n; *  linux/arch/sh/mm/cache-sh3.c&n; *&n; * Copyright (C) 1999, 2000  Niibe Yutaka&n; * Copyright (C) 2002 Paul Mundt&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
r_static
r_int
id|__init
DECL|function|detect_cpu_and_cache_system
id|detect_cpu_and_cache_system
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|addr0
comma
id|addr1
comma
id|data0
comma
id|data1
comma
id|data2
comma
id|data3
suffix:semicolon
id|jump_to_P2
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check if the entry shadows or not.&n;&t; * When shadowed, it&squot;s 128-entry system.&n;&t; * Otherwise, it&squot;s 256-entry system.&n;&t; */
id|addr0
op_assign
id|CACHE_OC_ADDRESS_ARRAY
op_plus
(paren
l_int|3
op_lshift
l_int|12
)paren
suffix:semicolon
id|addr1
op_assign
id|CACHE_OC_ADDRESS_ARRAY
op_plus
(paren
l_int|1
op_lshift
l_int|12
)paren
suffix:semicolon
multiline_comment|/* First, write back &amp; invalidate */
id|data0
op_assign
id|ctrl_inl
c_func
(paren
id|addr0
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|data0
op_amp
op_complement
(paren
id|SH_CACHE_VALID
op_or
id|SH_CACHE_UPDATED
)paren
comma
id|addr0
)paren
suffix:semicolon
id|data1
op_assign
id|ctrl_inl
c_func
(paren
id|addr1
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|data1
op_amp
op_complement
(paren
id|SH_CACHE_VALID
op_or
id|SH_CACHE_UPDATED
)paren
comma
id|addr1
)paren
suffix:semicolon
multiline_comment|/* Next, check if there&squot;s shadow or not */
id|data0
op_assign
id|ctrl_inl
c_func
(paren
id|addr0
)paren
suffix:semicolon
id|data0
op_xor_assign
id|SH_CACHE_VALID
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|data0
comma
id|addr0
)paren
suffix:semicolon
id|data1
op_assign
id|ctrl_inl
c_func
(paren
id|addr1
)paren
suffix:semicolon
id|data2
op_assign
id|data1
op_xor
id|SH_CACHE_VALID
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|data2
comma
id|addr1
)paren
suffix:semicolon
id|data3
op_assign
id|ctrl_inl
c_func
(paren
id|addr0
)paren
suffix:semicolon
multiline_comment|/* Lastly, invaliate them. */
id|ctrl_outl
c_func
(paren
id|data0
op_amp
op_complement
id|SH_CACHE_VALID
comma
id|addr0
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|data2
op_amp
op_complement
id|SH_CACHE_VALID
comma
id|addr1
)paren
suffix:semicolon
id|back_to_P1
c_func
(paren
)paren
suffix:semicolon
id|cpu_data-&gt;dcache.ways
op_assign
l_int|4
suffix:semicolon
id|cpu_data-&gt;dcache.entry_shift
op_assign
l_int|4
suffix:semicolon
id|cpu_data-&gt;dcache.linesz
op_assign
id|L1_CACHE_BYTES
suffix:semicolon
id|cpu_data-&gt;dcache.flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * 7709A/7729 has 16K cache (256-entry), while 7702 has only&n;&t; * 2K(direct) 7702 is not supported (yet)&n;&t; */
r_if
c_cond
(paren
id|data0
op_eq
id|data1
op_logical_and
id|data2
op_eq
id|data3
)paren
(brace
multiline_comment|/* Shadow */
id|cpu_data-&gt;dcache.way_shift
op_assign
l_int|11
suffix:semicolon
id|cpu_data-&gt;dcache.entry_mask
op_assign
l_int|0x7f0
suffix:semicolon
id|cpu_data-&gt;dcache.sets
op_assign
l_int|128
suffix:semicolon
id|cpu_data-&gt;type
op_assign
id|CPU_SH7708
suffix:semicolon
id|set_bit
c_func
(paren
id|CPU_HAS_MMU_PAGE_ASSOC
comma
op_amp
(paren
id|cpu_data-&gt;flags
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* 7709A or 7729  */
id|cpu_data-&gt;dcache.way_shift
op_assign
l_int|12
suffix:semicolon
id|cpu_data-&gt;dcache.entry_mask
op_assign
l_int|0xff0
suffix:semicolon
id|cpu_data-&gt;dcache.sets
op_assign
l_int|256
suffix:semicolon
id|cpu_data-&gt;type
op_assign
id|CPU_SH7729
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * SH-3 doesn&squot;t have separate caches&n;&t; */
id|cpu_data-&gt;dcache.flags
op_or_assign
id|SH_CACHE_COMBINED
suffix:semicolon
id|cpu_data-&gt;icache
op_assign
id|cpu_data-&gt;dcache
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back the dirty D-caches, but not invalidate them.&n; *&n; * Is this really worth it, or should we just alias this routine&n; * to __flush_purge_region too?&n; *&n; * START: Virtual Address (U0, P1, or P3)&n; * SIZE: Size of the region.&n; */
DECL|function|__flush_wback_region
r_void
id|__flush_wback_region
c_func
(paren
r_void
op_star
id|start
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|v
comma
id|j
suffix:semicolon
r_int
r_int
id|begin
comma
id|end
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|begin
op_assign
(paren
r_int
r_int
)paren
id|start
op_amp
op_complement
(paren
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_assign
(paren
(paren
r_int
r_int
)paren
id|start
op_plus
id|size
op_plus
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|v
op_assign
id|begin
suffix:semicolon
id|v
OL
id|end
suffix:semicolon
id|v
op_add_assign
id|L1_CACHE_BYTES
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cpu_data-&gt;dcache.ways
suffix:semicolon
id|j
op_increment
)paren
(brace
r_int
r_int
id|data
comma
id|addr
comma
id|p
suffix:semicolon
id|p
op_assign
id|__pa
c_func
(paren
id|v
)paren
suffix:semicolon
id|addr
op_assign
id|CACHE_OC_ADDRESS_ARRAY
op_or
(paren
id|j
op_lshift
id|cpu_data-&gt;dcache.way_shift
)paren
op_or
(paren
id|v
op_amp
id|cpu_data-&gt;dcache.entry_mask
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|data
op_assign
id|ctrl_inl
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|data
op_amp
id|CACHE_PHYSADDR_MASK
)paren
op_eq
(paren
id|p
op_amp
id|CACHE_PHYSADDR_MASK
)paren
)paren
(brace
id|data
op_and_assign
op_complement
id|SH_CACHE_UPDATED
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|data
comma
id|addr
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Write back the dirty D-caches and invalidate them.&n; *&n; * START: Virtual Address (U0, P1, or P3)&n; * SIZE: Size of the region.&n; */
DECL|function|__flush_purge_region
r_void
id|__flush_purge_region
c_func
(paren
r_void
op_star
id|start
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|v
suffix:semicolon
r_int
r_int
id|begin
comma
id|end
suffix:semicolon
id|begin
op_assign
(paren
r_int
r_int
)paren
id|start
op_amp
op_complement
(paren
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_assign
(paren
(paren
r_int
r_int
)paren
id|start
op_plus
id|size
op_plus
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|v
op_assign
id|begin
suffix:semicolon
id|v
OL
id|end
suffix:semicolon
id|v
op_add_assign
id|L1_CACHE_BYTES
)paren
(brace
r_int
r_int
id|data
comma
id|addr
suffix:semicolon
id|data
op_assign
(paren
id|v
op_amp
l_int|0xfffffc00
)paren
suffix:semicolon
multiline_comment|/* _Virtual_ address, ~U, ~V */
id|addr
op_assign
id|CACHE_OC_ADDRESS_ARRAY
op_or
(paren
id|v
op_amp
id|cpu_data-&gt;dcache.entry_mask
)paren
op_or
id|SH_CACHE_ASSOC
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|data
comma
id|addr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * No write back please&n; *&n; * Except I don&squot;t think there&squot;s any way to avoid the writeback. So we&n; * just alias it to __flush_purge_region(). dwmw2.&n; */
r_void
id|__flush_invalidate_region
c_func
(paren
r_void
op_star
id|start
comma
r_int
id|size
)paren
id|__attribute__
c_func
(paren
(paren
id|alias
c_func
(paren
l_string|&quot;__flush_purge_region&quot;
)paren
)paren
)paren
suffix:semicolon
eof
