multiline_comment|/* $Id: cache-sh4.c,v 1.26 2004/02/19 12:47:24 lethal Exp $&n; *&n; *  linux/arch/sh/mm/cache-sh4.c&n; *&n; * Copyright (C) 1999, 2000, 2002  Niibe Yutaka&n; * Copyright (C) 2001, 2002, 2003, 2004  Paul Mundt&n; * Copyright (C) 2003  Richard Curnow&n; */
macro_line|#include &lt;linux/config.h&gt;
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
r_extern
r_void
id|__flush_cache_4096_all
c_func
(paren
r_int
r_int
id|start
)paren
suffix:semicolon
r_static
r_void
id|__flush_cache_4096_all_ex
c_func
(paren
r_int
r_int
id|start
)paren
suffix:semicolon
r_extern
r_void
id|__flush_dcache_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|__flush_dcache_all_ex
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|detect_cpu_and_cache_system
r_int
id|__init
id|detect_cpu_and_cache_system
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|pvr
comma
id|prr
comma
id|cvr
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_static
r_int
r_int
id|sizes
(braket
l_int|16
)braket
op_assign
(brace
(braket
l_int|1
)braket
op_assign
(paren
l_int|1
op_lshift
l_int|12
)paren
comma
(braket
l_int|2
)braket
op_assign
(paren
l_int|1
op_lshift
l_int|13
)paren
comma
(braket
l_int|4
)braket
op_assign
(paren
l_int|1
op_lshift
l_int|14
)paren
comma
(braket
l_int|8
)braket
op_assign
(paren
l_int|1
op_lshift
l_int|15
)paren
comma
(braket
l_int|9
)braket
op_assign
(paren
l_int|1
op_lshift
l_int|16
)paren
)brace
suffix:semicolon
id|pvr
op_assign
(paren
id|ctrl_inl
c_func
(paren
id|CCN_PVR
)paren
op_rshift
l_int|8
)paren
op_amp
l_int|0xffff
suffix:semicolon
id|prr
op_assign
(paren
id|ctrl_inl
c_func
(paren
id|CCN_PRR
)paren
op_rshift
l_int|4
)paren
op_amp
l_int|0xff
suffix:semicolon
id|cvr
op_assign
(paren
id|ctrl_inl
c_func
(paren
id|CCN_CVR
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Setup some sane SH-4 defaults for the icache&n;&t; */
id|cpu_data-&gt;icache.way_incr
op_assign
(paren
l_int|1
op_lshift
l_int|13
)paren
suffix:semicolon
id|cpu_data-&gt;icache.entry_shift
op_assign
l_int|5
suffix:semicolon
id|cpu_data-&gt;icache.entry_mask
op_assign
l_int|0x1fe0
suffix:semicolon
id|cpu_data-&gt;icache.sets
op_assign
l_int|256
suffix:semicolon
id|cpu_data-&gt;icache.ways
op_assign
l_int|1
suffix:semicolon
id|cpu_data-&gt;icache.linesz
op_assign
id|L1_CACHE_BYTES
suffix:semicolon
multiline_comment|/*&n;&t; * And again for the dcache ..&n;&t; */
id|cpu_data-&gt;dcache.way_incr
op_assign
(paren
l_int|1
op_lshift
l_int|14
)paren
suffix:semicolon
id|cpu_data-&gt;dcache.entry_shift
op_assign
l_int|5
suffix:semicolon
id|cpu_data-&gt;dcache.entry_mask
op_assign
l_int|0x3fe0
suffix:semicolon
id|cpu_data-&gt;dcache.sets
op_assign
l_int|512
suffix:semicolon
id|cpu_data-&gt;dcache.ways
op_assign
l_int|1
suffix:semicolon
id|cpu_data-&gt;dcache.linesz
op_assign
id|L1_CACHE_BYTES
suffix:semicolon
multiline_comment|/* Set the FPU flag, virtually all SH-4&squot;s have one */
id|cpu_data-&gt;flags
op_or_assign
id|CPU_HAS_FPU
suffix:semicolon
multiline_comment|/*&n;&t; * Probe the underlying processor version/revision and&n;&t; * adjust cpu_data setup accordingly.&n;&t; */
r_switch
c_cond
(paren
id|pvr
)paren
(brace
r_case
l_int|0x205
suffix:colon
id|cpu_data-&gt;type
op_assign
id|CPU_SH7750
suffix:semicolon
id|cpu_data-&gt;flags
op_or_assign
id|CPU_HAS_P2_FLUSH_BUG
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x206
suffix:colon
id|cpu_data-&gt;type
op_assign
id|CPU_SH7750S
suffix:semicolon
multiline_comment|/* &n;&t;&t; * FIXME: This is needed for 7750, but do we need it for the&n;&t;&t; * 7750S too? For now, assume we do.. -- PFM&n;&t;&t; */
id|cpu_data-&gt;flags
op_or_assign
id|CPU_HAS_P2_FLUSH_BUG
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1100
suffix:colon
id|cpu_data-&gt;type
op_assign
id|CPU_SH7751
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x8000
suffix:colon
id|cpu_data-&gt;type
op_assign
id|CPU_ST40RA
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x8100
suffix:colon
id|cpu_data-&gt;type
op_assign
id|CPU_ST40GX1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x700
suffix:colon
id|cpu_data-&gt;type
op_assign
id|CPU_SH4_501
suffix:semicolon
id|cpu_data-&gt;icache.ways
op_assign
l_int|2
suffix:semicolon
id|cpu_data-&gt;dcache.ways
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* No FPU on the SH4-500 series.. */
id|cpu_data-&gt;flags
op_and_assign
op_complement
id|CPU_HAS_FPU
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x600
suffix:colon
id|cpu_data-&gt;type
op_assign
id|CPU_SH4_202
suffix:semicolon
id|cpu_data-&gt;icache.ways
op_assign
l_int|2
suffix:semicolon
id|cpu_data-&gt;dcache.ways
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x500
dot
dot
dot
l_int|0x501
suffix:colon
r_switch
c_cond
(paren
id|prr
)paren
(brace
r_case
l_int|0x10
suffix:colon
id|cpu_data-&gt;type
op_assign
id|CPU_SH7750R
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x11
suffix:colon
id|cpu_data-&gt;type
op_assign
id|CPU_SH7751R
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x50
suffix:colon
id|cpu_data-&gt;type
op_assign
id|CPU_SH7760
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cpu_data-&gt;icache.ways
op_assign
l_int|2
suffix:semicolon
id|cpu_data-&gt;dcache.ways
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|cpu_data-&gt;type
op_assign
id|CPU_SH_NONE
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * On anything that&squot;s not a direct-mapped cache, look to the CVR&n;&t; * for I/D-cache specifics.&n;&t; */
r_if
c_cond
(paren
id|cpu_data-&gt;icache.ways
OG
l_int|1
)paren
(brace
id|size
op_assign
id|sizes
(braket
(paren
id|cvr
op_rshift
l_int|20
)paren
op_amp
l_int|0xf
)braket
suffix:semicolon
id|cpu_data-&gt;icache.way_incr
op_assign
id|size
op_div
id|cpu_data-&gt;icache.ways
suffix:semicolon
id|cpu_data-&gt;icache.sets
op_assign
(paren
id|size
op_rshift
l_int|6
)paren
suffix:semicolon
id|cpu_data-&gt;icache.entry_mask
op_assign
(paren
(paren
id|size
op_div
id|cpu_data-&gt;icache.ways
)paren
op_minus
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cpu_data-&gt;dcache.ways
OG
l_int|1
)paren
(brace
id|size
op_assign
id|sizes
(braket
(paren
id|cvr
op_rshift
l_int|16
)paren
op_amp
l_int|0xf
)braket
suffix:semicolon
id|cpu_data-&gt;dcache.way_incr
op_assign
id|size
op_div
id|cpu_data-&gt;dcache.ways
suffix:semicolon
id|cpu_data-&gt;dcache.sets
op_assign
(paren
id|size
op_rshift
l_int|6
)paren
suffix:semicolon
id|cpu_data-&gt;dcache.entry_mask
op_assign
(paren
(paren
id|size
op_div
id|cpu_data-&gt;dcache.ways
)paren
op_minus
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * SH-4 has virtually indexed and physically tagged cache.&n; */
DECL|variable|p3map_sem
r_struct
id|semaphore
id|p3map_sem
(braket
l_int|4
)braket
suffix:semicolon
DECL|function|p3_cache_init
r_void
id|__init
id|p3_cache_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|remap_area_pages
c_func
(paren
id|P3SEG
comma
l_int|0
comma
id|PAGE_SIZE
op_star
l_int|4
comma
id|_PAGE_CACHABLE
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;%s failed.&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|sema_init
(paren
op_amp
id|p3map_sem
(braket
l_int|0
)braket
comma
l_int|1
)paren
suffix:semicolon
id|sema_init
(paren
op_amp
id|p3map_sem
(braket
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
id|sema_init
(paren
op_amp
id|p3map_sem
(braket
l_int|2
)braket
comma
l_int|1
)paren
suffix:semicolon
id|sema_init
(paren
op_amp
id|p3map_sem
(braket
l_int|3
)braket
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back the dirty D-caches, but not invalidate them.&n; *&n; * START: Virtual Address (U0, P1, or P3)&n; * SIZE: Size of the region.&n; */
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
id|asm
r_volatile
(paren
l_string|&quot;ocbwb&t;%0&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|v
)paren
)paren
)paren
suffix:semicolon
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
id|asm
r_volatile
(paren
l_string|&quot;ocbp&t;%0&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|v
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * No write back please&n; */
DECL|function|__flush_invalidate_region
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
id|asm
r_volatile
(paren
l_string|&quot;ocbi&t;%0&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|v
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|__flush_dcache_all_ex
r_static
r_void
id|__flush_dcache_all_ex
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|addr
comma
id|end_addr
comma
id|entry_offset
suffix:semicolon
id|end_addr
op_assign
id|CACHE_OC_ADDRESS_ARRAY
op_plus
(paren
id|cpu_data-&gt;dcache.sets
op_lshift
id|cpu_data-&gt;dcache.entry_shift
)paren
op_star
id|cpu_data-&gt;dcache.ways
suffix:semicolon
id|entry_offset
op_assign
l_int|1
op_lshift
id|cpu_data-&gt;dcache.entry_shift
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|CACHE_OC_ADDRESS_ARRAY
suffix:semicolon
id|addr
OL
id|end_addr
suffix:semicolon
id|addr
op_add_assign
id|entry_offset
)paren
(brace
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|addr
)paren
suffix:semicolon
)brace
)brace
DECL|function|__flush_cache_4096_all_ex
r_static
r_void
id|__flush_cache_4096_all_ex
c_func
(paren
r_int
r_int
id|start
)paren
(brace
r_int
r_int
id|addr
comma
id|entry_offset
suffix:semicolon
r_int
id|i
suffix:semicolon
id|entry_offset
op_assign
l_int|1
op_lshift
id|cpu_data-&gt;dcache.entry_shift
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|cpu_data-&gt;dcache.ways
suffix:semicolon
id|i
op_increment
comma
id|start
op_add_assign
id|cpu_data-&gt;dcache.way_incr
)paren
(brace
r_for
c_loop
(paren
id|addr
op_assign
id|CACHE_OC_ADDRESS_ARRAY
op_plus
id|start
suffix:semicolon
id|addr
OL
id|CACHE_OC_ADDRESS_ARRAY
op_plus
l_int|4096
op_plus
id|start
suffix:semicolon
id|addr
op_add_assign
id|entry_offset
)paren
(brace
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|addr
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|flush_cache_4096_all
r_void
id|flush_cache_4096_all
c_func
(paren
r_int
r_int
id|start
)paren
(brace
r_if
c_cond
(paren
id|cpu_data-&gt;dcache.ways
op_eq
l_int|1
)paren
id|__flush_cache_4096_all
c_func
(paren
id|start
)paren
suffix:semicolon
r_else
id|__flush_cache_4096_all_ex
c_func
(paren
id|start
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back the range of D-cache, and purge the I-cache.&n; *&n; * Called from kernel/module.c:sys_init_module and routine for a.out format.&n; */
DECL|function|flush_icache_range
r_void
id|flush_icache_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back the D-cache and purge the I-cache for signal trampoline. &n; * .. which happens to be the same behavior as flush_icache_range().&n; * So, we simply flush out a line.&n; */
DECL|function|flush_cache_sigtramp
r_void
id|flush_cache_sigtramp
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|v
comma
id|index
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
id|v
op_assign
id|addr
op_amp
op_complement
(paren
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;ocbwb&t;%0&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|v
)paren
)paren
)paren
suffix:semicolon
id|index
op_assign
id|CACHE_IC_ADDRESS_ARRAY
op_or
(paren
id|v
op_amp
id|cpu_data-&gt;icache.entry_mask
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|jump_to_P2
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|cpu_data-&gt;icache.ways
suffix:semicolon
id|i
op_increment
comma
id|index
op_add_assign
id|cpu_data-&gt;icache.way_incr
)paren
(brace
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|index
)paren
suffix:semicolon
)brace
multiline_comment|/* Clear out Valid-bit */
id|back_to_P1
c_func
(paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|flush_cache_4096
r_static
r_inline
r_void
id|flush_cache_4096
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|phys
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_extern
r_void
id|__flush_cache_4096
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|phys
comma
r_int
r_int
id|exec_offset
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * SH7751, SH7751R, and ST40 have no restriction to handle cache.&n;&t; * (While SH7750 must do that at P2 area.)&n;&t; */
r_if
c_cond
(paren
(paren
id|cpu_data-&gt;flags
op_amp
id|CPU_HAS_P2_FLUSH_BUG
)paren
op_logical_or
id|start
OL
id|CACHE_OC_ADDRESS_ARRAY
)paren
(brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__flush_cache_4096
c_func
(paren
id|start
op_or
id|SH_CACHE_ASSOC
comma
id|P1SEGADDR
c_func
(paren
id|phys
)paren
comma
l_int|0x20000000
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|__flush_cache_4096
c_func
(paren
id|start
op_or
id|SH_CACHE_ASSOC
comma
id|P1SEGADDR
c_func
(paren
id|phys
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Write back &amp; invalidate the D-cache of the page.&n; * (To avoid &quot;alias&quot; issues)&n; */
DECL|function|flush_dcache_page
r_void
id|flush_dcache_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|PG_mapped
comma
op_amp
id|page-&gt;flags
)paren
)paren
(brace
r_int
r_int
id|phys
op_assign
id|PHYSADDR
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
multiline_comment|/* Loop all the D-cache */
id|flush_cache_4096
c_func
(paren
id|CACHE_OC_ADDRESS_ARRAY
comma
id|phys
)paren
suffix:semicolon
id|flush_cache_4096
c_func
(paren
id|CACHE_OC_ADDRESS_ARRAY
op_or
l_int|0x1000
comma
id|phys
)paren
suffix:semicolon
id|flush_cache_4096
c_func
(paren
id|CACHE_OC_ADDRESS_ARRAY
op_or
l_int|0x2000
comma
id|phys
)paren
suffix:semicolon
id|flush_cache_4096
c_func
(paren
id|CACHE_OC_ADDRESS_ARRAY
op_or
l_int|0x3000
comma
id|phys
)paren
suffix:semicolon
)brace
)brace
DECL|function|flush_icache_all
r_static
r_inline
r_void
id|flush_icache_all
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
comma
id|ccr
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|jump_to_P2
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Flush I-cache */
id|ccr
op_assign
id|ctrl_inl
c_func
(paren
id|CCR
)paren
suffix:semicolon
id|ccr
op_or_assign
id|CCR_CACHE_ICI
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|ccr
comma
id|CCR
)paren
suffix:semicolon
id|back_to_P1
c_func
(paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|flush_cache_all
r_void
id|flush_cache_all
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|cpu_data-&gt;dcache.ways
op_eq
l_int|1
)paren
id|__flush_dcache_all
c_func
(paren
)paren
suffix:semicolon
r_else
id|__flush_dcache_all_ex
c_func
(paren
)paren
suffix:semicolon
id|flush_icache_all
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_cache_mm
r_void
id|flush_cache_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
multiline_comment|/* Is there any good way? */
multiline_comment|/* XXX: possibly call flush_cache_range for each vm area */
multiline_comment|/* &n;&t; * FIXME: Really, the optimal solution here would be able to flush out&n;&t; * individual lines created by the specified context, but this isn&squot;t&n;&t; * feasible for a number of architectures (such as MIPS, and some&n;&t; * SPARC) .. is this possible for SuperH?&n;&t; *&n;&t; * In the meantime, we&squot;ll just flush all of the caches.. this&n;&t; * seems to be the simplest way to avoid at least a few wasted&n;&t; * cache flushes. -Lethal&n;&t; */
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|__flush_cache_page
r_static
r_void
id|__flush_cache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
r_int
id|phys
)paren
(brace
multiline_comment|/* We only need to flush D-cache when we have alias */
r_if
c_cond
(paren
(paren
id|address
op_xor
id|phys
)paren
op_amp
id|CACHE_ALIAS
)paren
(brace
multiline_comment|/* Loop 4K of the D-cache */
id|flush_cache_4096
c_func
(paren
id|CACHE_OC_ADDRESS_ARRAY
op_or
(paren
id|address
op_amp
id|CACHE_ALIAS
)paren
comma
id|phys
)paren
suffix:semicolon
multiline_comment|/* Loop another 4K of the D-cache */
id|flush_cache_4096
c_func
(paren
id|CACHE_OC_ADDRESS_ARRAY
op_or
(paren
id|phys
op_amp
id|CACHE_ALIAS
)paren
comma
id|phys
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
multiline_comment|/* Loop 4K (half) of the I-cache */
id|flush_cache_4096
c_func
(paren
id|CACHE_IC_ADDRESS_ARRAY
op_or
(paren
id|address
op_amp
l_int|0x1000
)paren
comma
id|phys
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back and invalidate D-caches.&n; *&n; * START, END: Virtual Address (U0 address)&n; *&n; * NOTE: We need to flush the _physical_ page entry.&n; * Flushing the cache lines for U0 only isn&squot;t enough.&n; * We need to flush for P1 too, which may contain aliases.&n; */
DECL|function|flush_cache_range
r_void
id|flush_cache_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_int
r_int
id|p
op_assign
id|start
op_amp
id|PAGE_MASK
suffix:semicolon
id|pgd_t
op_star
id|dir
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
id|pte_t
id|entry
suffix:semicolon
r_int
r_int
id|phys
suffix:semicolon
r_int
r_int
id|d
op_assign
l_int|0
suffix:semicolon
id|dir
op_assign
id|pgd_offset
c_func
(paren
id|vma-&gt;vm_mm
comma
id|p
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|p
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
op_logical_or
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|p
op_and_assign
op_complement
(paren
(paren
l_int|1
op_lshift
id|PMD_SHIFT
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|p
op_add_assign
(paren
l_int|1
op_lshift
id|PMD_SHIFT
)paren
suffix:semicolon
id|pmd
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|p
)paren
suffix:semicolon
r_do
(brace
id|entry
op_assign
op_star
id|pte
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pte_val
c_func
(paren
id|entry
)paren
op_amp
id|_PAGE_PRESENT
)paren
)paren
(brace
id|phys
op_assign
id|pte_val
c_func
(paren
id|entry
)paren
op_amp
id|PTE_PHYS_MASK
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_xor
id|phys
)paren
op_amp
id|CACHE_ALIAS
)paren
(brace
id|d
op_or_assign
l_int|1
op_lshift
(paren
(paren
id|p
op_amp
id|CACHE_ALIAS
)paren
op_rshift
l_int|12
)paren
suffix:semicolon
id|d
op_or_assign
l_int|1
op_lshift
(paren
(paren
id|phys
op_amp
id|CACHE_ALIAS
)paren
op_rshift
l_int|12
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d
op_eq
l_int|0x0f
)paren
r_goto
id|loop_exit
suffix:semicolon
)brace
)brace
id|pte
op_increment
suffix:semicolon
id|p
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p
OL
id|end
op_logical_and
(paren
(paren
r_int
r_int
)paren
id|pte
op_amp
op_complement
id|PAGE_MASK
)paren
)paren
suffix:semicolon
id|pmd
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p
OL
id|end
)paren
suffix:semicolon
id|loop_exit
suffix:colon
r_if
c_cond
(paren
id|d
op_amp
l_int|1
)paren
id|flush_cache_4096_all
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d
op_amp
l_int|2
)paren
id|flush_cache_4096_all
c_func
(paren
l_int|0x1000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d
op_amp
l_int|4
)paren
id|flush_cache_4096_all
c_func
(paren
l_int|0x2000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d
op_amp
l_int|8
)paren
id|flush_cache_4096_all
c_func
(paren
l_int|0x3000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
id|flush_icache_all
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back and invalidate I/D-caches for the page.&n; *&n; * ADDR: Virtual Address (U0 address)&n; */
DECL|function|flush_cache_page
r_void
id|flush_cache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
id|pte_t
id|entry
suffix:semicolon
r_int
r_int
id|phys
suffix:semicolon
id|dir
op_assign
id|pgd_offset
c_func
(paren
id|vma-&gt;vm_mm
comma
id|address
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
op_logical_or
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
r_return
suffix:semicolon
id|pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
id|entry
op_assign
op_star
id|pte
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|entry
)paren
op_amp
id|_PAGE_PRESENT
)paren
)paren
r_return
suffix:semicolon
id|phys
op_assign
id|pte_val
c_func
(paren
id|entry
)paren
op_amp
id|PTE_PHYS_MASK
suffix:semicolon
id|__flush_cache_page
c_func
(paren
id|vma
comma
id|address
comma
id|phys
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * flush_icache_user_range&n; * @vma: VMA of the process&n; * @page: page&n; * @addr: U0 address&n; * @len: length of the range (&lt; page size)&n; */
DECL|function|flush_icache_user_range
r_void
id|flush_icache_user_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|addr
comma
r_int
id|len
)paren
(brace
id|__flush_cache_page
c_func
(paren
id|vma
comma
id|addr
comma
id|PHYSADDR
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
)paren
)paren
suffix:semicolon
)brace
eof
