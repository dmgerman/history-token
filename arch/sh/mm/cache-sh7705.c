multiline_comment|/*&n; * arch/sh/mm/cache-sh7705.c&n; *&n; * Copyright (C) 1999, 2000  Niibe Yutaka&n; * Copyright (C) 2004  Alex Song&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; */
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
multiline_comment|/* The 32KB cache on the SH7705 suffers from the same synonym problem&n; * as SH4 CPUs */
DECL|macro|__pte_offset
mdefine_line|#define __pte_offset(address) &bslash;&n;&t;&t;((address &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset
mdefine_line|#define pte_offset(dir, address) ((pte_t *) pmd_page_kernel(*(dir)) + &bslash;&n;&t;&t;__pte_offset(address))
DECL|function|cache_wback_all
r_static
r_inline
r_void
id|cache_wback_all
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ways
comma
id|waysize
comma
id|addrstart
suffix:semicolon
id|ways
op_assign
id|cpu_data-&gt;dcache.ways
suffix:semicolon
id|waysize
op_assign
id|cpu_data-&gt;dcache.sets
suffix:semicolon
id|waysize
op_lshift_assign
id|cpu_data-&gt;dcache.entry_shift
suffix:semicolon
id|addrstart
op_assign
id|CACHE_OC_ADDRESS_ARRAY
suffix:semicolon
r_do
(brace
r_int
r_int
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|addrstart
suffix:semicolon
id|addr
OL
id|addrstart
op_plus
id|waysize
suffix:semicolon
id|addr
op_add_assign
id|cpu_data-&gt;dcache.linesz
)paren
(brace
r_int
r_int
id|data
suffix:semicolon
r_int
id|v
op_assign
id|SH_CACHE_UPDATED
op_or
id|SH_CACHE_VALID
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
id|v
)paren
op_eq
id|v
)paren
id|ctrl_outl
c_func
(paren
id|data
op_amp
op_complement
id|v
comma
id|addr
)paren
suffix:semicolon
)brace
id|addrstart
op_add_assign
id|cpu_data-&gt;dcache.way_incr
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|ways
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
id|__flush_wback_region
c_func
(paren
(paren
r_void
op_star
)paren
id|start
comma
id|end
op_minus
id|start
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Writeback&amp;Invalidate the D-cache of the page&n; */
DECL|function|__flush_dcache_page
r_static
r_void
id|__flush_dcache_page
c_func
(paren
r_int
r_int
id|phys
)paren
(brace
r_int
r_int
id|ways
comma
id|waysize
comma
id|addrstart
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|phys
op_or_assign
id|SH_CACHE_VALID
suffix:semicolon
multiline_comment|/*&n;&t; * Here, phys is the physical address of the page. We check all the&n;&t; * tags in the cache for those with the same page number as this page&n;&t; * (by masking off the lowest 2 bits of the 19-bit tag; these bits are&n;&t; * derived from the offset within in the 4k page). Matching valid&n;&t; * entries are invalidated.&n;&t; *&n;&t; * Since 2 bits of the cache index are derived from the virtual page&n;&t; * number, knowing this would reduce the number of cache entries to be&n;&t; * searched by a factor of 4. However this function exists to deal with&n;&t; * potential cache aliasing, therefore the optimisation is probably not&n;&t; * possible.&n;&t; */
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
id|ways
op_assign
id|cpu_data-&gt;dcache.ways
suffix:semicolon
id|waysize
op_assign
id|cpu_data-&gt;dcache.sets
suffix:semicolon
id|waysize
op_lshift_assign
id|cpu_data-&gt;dcache.entry_shift
suffix:semicolon
id|addrstart
op_assign
id|CACHE_OC_ADDRESS_ARRAY
suffix:semicolon
r_do
(brace
r_int
r_int
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|addrstart
suffix:semicolon
id|addr
OL
id|addrstart
op_plus
id|waysize
suffix:semicolon
id|addr
op_add_assign
id|cpu_data-&gt;dcache.linesz
)paren
(brace
r_int
r_int
id|data
suffix:semicolon
id|data
op_assign
id|ctrl_inl
c_func
(paren
id|addr
)paren
op_amp
(paren
l_int|0x1ffffC00
op_or
id|SH_CACHE_VALID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
id|phys
)paren
(brace
id|data
op_and_assign
op_complement
(paren
id|SH_CACHE_VALID
op_or
id|SH_CACHE_UPDATED
)paren
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
id|addrstart
op_add_assign
id|cpu_data-&gt;dcache.way_incr
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|ways
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
id|__flush_dcache_page
c_func
(paren
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
DECL|function|flush_cache_all
r_void
id|flush_cache_all
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
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
id|cache_wback_all
c_func
(paren
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
id|flush_cache_all
c_func
(paren
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
multiline_comment|/*&n;&t; * We could call flush_cache_page for the pages of these range,&n;&t; * but it&squot;s not efficient (scan the caches all the time...).&n;&t; *&n;&t; * We can&squot;t use A-bit magic, as there&squot;s the case we don&squot;t have&n;&t; * valid entry on TLB.&n;&t; */
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back and invalidate I/D-caches for the page.&n; *&n; * ADDRESS: Virtual Address (U0 address)&n; */
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
comma
r_int
r_int
id|pfn
)paren
(brace
id|__flush_dcache_page
c_func
(paren
id|pfn
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called when a page-cache page is about to be mapped into a&n; * user process&squot; address space.  It offers an opportunity for a&n; * port to ensure d-cache/i-cache coherency if necessary.&n; *&n; * Not entirely sure why this is necessary on SH3 with 32K cache but&n; * without it we get occasional &quot;Memory fault&quot; when loading a program.&n; */
DECL|function|flush_icache_page
r_void
id|flush_icache_page
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
)paren
(brace
id|__flush_purge_region
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
comma
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
eof
