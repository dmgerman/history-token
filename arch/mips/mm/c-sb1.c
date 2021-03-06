multiline_comment|/*&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copyright (C) 1997, 2001 Ralf Baechle (ralf@gnu.org)&n; * Copyright (C) 2000, 2001, 2002, 2003 Broadcom Corporation&n; * Copyright (C) 2004  Maciej W. Rozycki&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/asm.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cacheops.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_void
id|sb1_dma_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* These are probed at ld_mmu time */
DECL|variable|icache_size
r_static
r_int
r_int
id|icache_size
suffix:semicolon
DECL|variable|dcache_size
r_static
r_int
r_int
id|dcache_size
suffix:semicolon
DECL|variable|icache_line_size
r_static
r_int
r_int
id|icache_line_size
suffix:semicolon
DECL|variable|dcache_line_size
r_static
r_int
r_int
id|dcache_line_size
suffix:semicolon
DECL|variable|icache_index_mask
r_static
r_int
r_int
id|icache_index_mask
suffix:semicolon
DECL|variable|dcache_index_mask
r_static
r_int
r_int
id|dcache_index_mask
suffix:semicolon
DECL|variable|icache_assoc
r_static
r_int
r_int
id|icache_assoc
suffix:semicolon
DECL|variable|dcache_assoc
r_static
r_int
r_int
id|dcache_assoc
suffix:semicolon
DECL|variable|icache_sets
r_static
r_int
r_int
id|icache_sets
suffix:semicolon
DECL|variable|dcache_sets
r_static
r_int
r_int
id|dcache_sets
suffix:semicolon
DECL|variable|icache_range_cutoff
r_static
r_int
r_int
id|icache_range_cutoff
suffix:semicolon
DECL|variable|dcache_range_cutoff
r_static
r_int
r_int
id|dcache_range_cutoff
suffix:semicolon
multiline_comment|/*&n; * The dcache is fully coherent to the system, with one&n; * big caveat:  the instruction stream.  In other words,&n; * if we miss in the icache, and have dirty data in the&n; * L1 dcache, then we&squot;ll go out to memory (or the L2) and&n; * get the not-as-recent data.&n; *&n; * So the only time we have to flush the dcache is when&n; * we&squot;re flushing the icache.  Since the L2 is fully&n; * coherent to everything, including I/O, we never have&n; * to flush it&n; */
DECL|macro|cache_set_op
mdefine_line|#define cache_set_op(op, addr)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.set&t;noreorder&t;&t;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.set&t;mips64&bslash;n&bslash;t&t;&t;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;cache&t;%0, (0&lt;&lt;13)(%1)&t;&t;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;cache&t;%0, (1&lt;&lt;13)(%1)&t;&t;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;cache&t;%0, (2&lt;&lt;13)(%1)&t;&t;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;cache&t;%0, (3&lt;&lt;13)(%1)&t;&t;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.set&t;mips0&t;&t;&t;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.set&t;reorder&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;i&quot; (op), &quot;r&quot; (addr))
DECL|macro|sync
mdefine_line|#define sync()&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.set&t;mips64&bslash;n&bslash;t&t;&t;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;sync&t;&t;&t;&t;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.set&t;mips0&quot;)
DECL|macro|mispredict
mdefine_line|#define mispredict()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;bnezl  $0, 1f&t;&t;&bslash;n&quot; /* Force mispredict */&t;&bslash;&n;&t;&quot;1:&t;&t;&t;&t;&bslash;n&quot;);
multiline_comment|/*&n; * Writeback and invalidate the entire dcache&n; */
DECL|function|__sb1_writeback_inv_dcache_all
r_static
r_inline
r_void
id|__sb1_writeback_inv_dcache_all
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|addr
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|addr
OL
id|dcache_line_size
op_star
id|dcache_sets
)paren
(brace
id|cache_set_op
c_func
(paren
id|Index_Writeback_Inv_D
comma
id|addr
)paren
suffix:semicolon
id|addr
op_add_assign
id|dcache_line_size
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Writeback and invalidate a range of the dcache.  The addresses are&n; * virtual, and since we&squot;re using index ops and bit 12 is part of both&n; * the virtual frame and physical index, we have to clear both sets&n; * (bit 12 set and cleared).&n; */
DECL|function|__sb1_writeback_inv_dcache_range
r_static
r_inline
r_void
id|__sb1_writeback_inv_dcache_range
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
r_int
r_int
id|index
suffix:semicolon
id|start
op_and_assign
op_complement
(paren
id|dcache_line_size
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_assign
(paren
id|end
op_plus
id|dcache_line_size
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|dcache_line_size
op_minus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
op_ne
id|end
)paren
(brace
id|index
op_assign
id|start
op_amp
id|dcache_index_mask
suffix:semicolon
id|cache_set_op
c_func
(paren
id|Index_Writeback_Inv_D
comma
id|index
)paren
suffix:semicolon
id|cache_set_op
c_func
(paren
id|Index_Writeback_Inv_D
comma
id|index
op_xor
(paren
l_int|1
op_lshift
l_int|12
)paren
)paren
suffix:semicolon
id|start
op_add_assign
id|dcache_line_size
suffix:semicolon
)brace
id|sync
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Writeback and invalidate a range of the dcache.  With physical&n; * addresseses, we don&squot;t have to worry about possible bit 12 aliasing.&n; * XXXKW is it worth turning on KX and using hit ops with xkphys?&n; */
DECL|function|__sb1_writeback_inv_dcache_phys_range
r_static
r_inline
r_void
id|__sb1_writeback_inv_dcache_phys_range
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
id|start
op_and_assign
op_complement
(paren
id|dcache_line_size
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_assign
(paren
id|end
op_plus
id|dcache_line_size
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|dcache_line_size
op_minus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
op_ne
id|end
)paren
(brace
id|cache_set_op
c_func
(paren
id|Index_Writeback_Inv_D
comma
id|start
op_amp
id|dcache_index_mask
)paren
suffix:semicolon
id|start
op_add_assign
id|dcache_line_size
suffix:semicolon
)brace
id|sync
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Invalidate the entire icache&n; */
DECL|function|__sb1_flush_icache_all
r_static
r_inline
r_void
id|__sb1_flush_icache_all
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|addr
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|addr
OL
id|icache_line_size
op_star
id|icache_sets
)paren
(brace
id|cache_set_op
c_func
(paren
id|Index_Invalidate_I
comma
id|addr
)paren
suffix:semicolon
id|addr
op_add_assign
id|icache_line_size
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Flush the icache for a given physical page.  Need to writeback the&n; * dcache first, then invalidate the icache.  If the page isn&squot;t&n; * executable, nothing is required.&n; */
DECL|function|local_sb1_flush_cache_page
r_static
r_void
id|local_sb1_flush_cache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|pfn
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
id|__sb1_writeback_inv_dcache_range
c_func
(paren
id|addr
comma
id|addr
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Bumping the ASID is probably cheaper than the flush ...&n;&t; */
r_if
c_cond
(paren
id|cpu_context
c_func
(paren
id|cpu
comma
id|vma-&gt;vm_mm
)paren
op_ne
l_int|0
)paren
id|drop_mmu_context
c_func
(paren
id|vma-&gt;vm_mm
comma
id|cpu
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|struct|flush_cache_page_args
r_struct
id|flush_cache_page_args
(brace
DECL|member|vma
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|pfn
r_int
r_int
id|pfn
suffix:semicolon
)brace
suffix:semicolon
DECL|function|sb1_flush_cache_page_ipi
r_static
r_void
id|sb1_flush_cache_page_ipi
c_func
(paren
r_void
op_star
id|info
)paren
(brace
r_struct
id|flush_cache_page_args
op_star
id|args
op_assign
id|info
suffix:semicolon
id|local_sb1_flush_cache_page
c_func
(paren
id|args-&gt;vma
comma
id|args-&gt;addr
comma
id|args-&gt;pfn
)paren
suffix:semicolon
)brace
multiline_comment|/* Dirty dcache could be on another CPU, so do the IPIs */
DECL|function|sb1_flush_cache_page
r_static
r_void
id|sb1_flush_cache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|pfn
)paren
(brace
r_struct
id|flush_cache_page_args
id|args
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
)paren
r_return
suffix:semicolon
id|addr
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|args.vma
op_assign
id|vma
suffix:semicolon
id|args.addr
op_assign
id|addr
suffix:semicolon
id|args.pfn
op_assign
id|pfn
suffix:semicolon
id|on_each_cpu
c_func
(paren
id|sb1_flush_cache_page_ipi
comma
(paren
r_void
op_star
)paren
op_amp
id|args
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#else
r_void
id|sb1_flush_cache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|pfn
)paren
id|__attribute__
c_func
(paren
(paren
id|alias
c_func
(paren
l_string|&quot;local_sb1_flush_cache_page&quot;
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Invalidate a range of the icache.  The addresses are virtual, and&n; * the cache is virtually indexed and tagged.  However, we don&squot;t&n; * necessarily have the right ASID context, so use index ops instead&n; * of hit ops.&n; */
DECL|function|__sb1_flush_icache_range
r_static
r_inline
r_void
id|__sb1_flush_icache_range
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
id|start
op_and_assign
op_complement
(paren
id|icache_line_size
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_assign
(paren
id|end
op_plus
id|icache_line_size
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|icache_line_size
op_minus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
op_ne
id|end
)paren
(brace
id|cache_set_op
c_func
(paren
id|Index_Invalidate_I
comma
id|start
op_amp
id|icache_index_mask
)paren
suffix:semicolon
id|start
op_add_assign
id|icache_line_size
suffix:semicolon
)brace
id|mispredict
c_func
(paren
)paren
suffix:semicolon
id|sync
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Invalidate all caches on this CPU&n; */
DECL|function|local_sb1___flush_cache_all
r_static
r_void
id|local_sb1___flush_cache_all
c_func
(paren
r_void
)paren
(brace
id|__sb1_writeback_inv_dcache_all
c_func
(paren
)paren
suffix:semicolon
id|__sb1_flush_icache_all
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
r_void
id|sb1___flush_cache_all_ipi
c_func
(paren
r_void
op_star
id|ignored
)paren
id|__attribute__
c_func
(paren
(paren
id|alias
c_func
(paren
l_string|&quot;local_sb1___flush_cache_all&quot;
)paren
)paren
)paren
suffix:semicolon
DECL|function|sb1___flush_cache_all
r_static
r_void
id|sb1___flush_cache_all
c_func
(paren
r_void
)paren
(brace
id|on_each_cpu
c_func
(paren
id|sb1___flush_cache_all_ipi
comma
l_int|0
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#else
r_void
id|sb1___flush_cache_all
c_func
(paren
r_void
)paren
id|__attribute__
c_func
(paren
(paren
id|alias
c_func
(paren
l_string|&quot;local_sb1___flush_cache_all&quot;
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * When flushing a range in the icache, we have to first writeback&n; * the dcache for the same range, so new ifetches will see any&n; * data that was dirty in the dcache.&n; *&n; * The start/end arguments are Kseg addresses (possibly mapped Kseg).&n; */
DECL|function|local_sb1_flush_icache_range
r_static
r_void
id|local_sb1_flush_icache_range
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
multiline_comment|/* Just wb-inv the whole dcache if the range is big enough */
r_if
c_cond
(paren
(paren
id|end
op_minus
id|start
)paren
OG
id|dcache_range_cutoff
)paren
id|__sb1_writeback_inv_dcache_all
c_func
(paren
)paren
suffix:semicolon
r_else
id|__sb1_writeback_inv_dcache_range
c_func
(paren
id|start
comma
id|end
)paren
suffix:semicolon
multiline_comment|/* Just flush the whole icache if the range is big enough */
r_if
c_cond
(paren
(paren
id|end
op_minus
id|start
)paren
OG
id|icache_range_cutoff
)paren
id|__sb1_flush_icache_all
c_func
(paren
)paren
suffix:semicolon
r_else
id|__sb1_flush_icache_range
c_func
(paren
id|start
comma
id|end
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|struct|flush_icache_range_args
r_struct
id|flush_icache_range_args
(brace
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
)brace
suffix:semicolon
DECL|function|sb1_flush_icache_range_ipi
r_static
r_void
id|sb1_flush_icache_range_ipi
c_func
(paren
r_void
op_star
id|info
)paren
(brace
r_struct
id|flush_icache_range_args
op_star
id|args
op_assign
id|info
suffix:semicolon
id|local_sb1_flush_icache_range
c_func
(paren
id|args-&gt;start
comma
id|args-&gt;end
)paren
suffix:semicolon
)brace
DECL|function|sb1_flush_icache_range
r_void
id|sb1_flush_icache_range
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
r_struct
id|flush_icache_range_args
id|args
suffix:semicolon
id|args.start
op_assign
id|start
suffix:semicolon
id|args.end
op_assign
id|end
suffix:semicolon
id|on_each_cpu
c_func
(paren
id|sb1_flush_icache_range_ipi
comma
op_amp
id|args
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#else
r_void
id|sb1_flush_icache_range
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
id|__attribute__
c_func
(paren
(paren
id|alias
c_func
(paren
l_string|&quot;local_sb1_flush_icache_range&quot;
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Flush the icache for a given physical page.  Need to writeback the&n; * dcache first, then invalidate the icache.  If the page isn&squot;t&n; * executable, nothing is required.&n; */
DECL|function|local_sb1_flush_icache_page
r_static
r_void
id|local_sb1_flush_icache_page
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
r_int
r_int
id|start
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
multiline_comment|/* Need to writeback any dirty data for that page, we have the PA */
id|start
op_assign
(paren
r_int
r_int
)paren
(paren
id|page
op_minus
id|mem_map
)paren
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|__sb1_writeback_inv_dcache_phys_range
c_func
(paren
id|start
comma
id|start
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If there&squot;s a context, bump the ASID (cheaper than a flush,&n;&t; * since we don&squot;t know VAs!)&n;&t; */
r_if
c_cond
(paren
id|cpu_context
c_func
(paren
id|cpu
comma
id|vma-&gt;vm_mm
)paren
op_ne
l_int|0
)paren
(brace
id|drop_mmu_context
c_func
(paren
id|vma-&gt;vm_mm
comma
id|cpu
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_SMP
DECL|struct|flush_icache_page_args
r_struct
id|flush_icache_page_args
(brace
DECL|member|vma
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
DECL|member|page
r_struct
id|page
op_star
id|page
suffix:semicolon
)brace
suffix:semicolon
DECL|function|sb1_flush_icache_page_ipi
r_static
r_void
id|sb1_flush_icache_page_ipi
c_func
(paren
r_void
op_star
id|info
)paren
(brace
r_struct
id|flush_icache_page_args
op_star
id|args
op_assign
id|info
suffix:semicolon
id|local_sb1_flush_icache_page
c_func
(paren
id|args-&gt;vma
comma
id|args-&gt;page
)paren
suffix:semicolon
)brace
multiline_comment|/* Dirty dcache could be on another CPU, so do the IPIs */
DECL|function|sb1_flush_icache_page
r_static
r_void
id|sb1_flush_icache_page
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
r_struct
id|flush_icache_page_args
id|args
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
)paren
r_return
suffix:semicolon
id|args.vma
op_assign
id|vma
suffix:semicolon
id|args.page
op_assign
id|page
suffix:semicolon
id|on_each_cpu
c_func
(paren
id|sb1_flush_icache_page_ipi
comma
(paren
r_void
op_star
)paren
op_amp
id|args
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#else
r_void
id|sb1_flush_icache_page
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
id|__attribute__
c_func
(paren
(paren
id|alias
c_func
(paren
l_string|&quot;local_sb1_flush_icache_page&quot;
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * A signal trampoline must fit into a single cacheline.&n; */
DECL|function|local_sb1_flush_cache_sigtramp
r_static
r_void
id|local_sb1_flush_cache_sigtramp
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|cache_set_op
c_func
(paren
id|Index_Writeback_Inv_D
comma
id|addr
op_amp
id|dcache_index_mask
)paren
suffix:semicolon
id|cache_set_op
c_func
(paren
id|Index_Writeback_Inv_D
comma
(paren
id|addr
op_xor
(paren
l_int|1
op_lshift
l_int|12
)paren
)paren
op_amp
id|dcache_index_mask
)paren
suffix:semicolon
id|cache_set_op
c_func
(paren
id|Index_Invalidate_I
comma
id|addr
op_amp
id|icache_index_mask
)paren
suffix:semicolon
id|mispredict
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|function|sb1_flush_cache_sigtramp_ipi
r_static
r_void
id|sb1_flush_cache_sigtramp_ipi
c_func
(paren
r_void
op_star
id|info
)paren
(brace
r_int
r_int
id|iaddr
op_assign
(paren
r_int
r_int
)paren
id|info
suffix:semicolon
id|local_sb1_flush_cache_sigtramp
c_func
(paren
id|iaddr
)paren
suffix:semicolon
)brace
DECL|function|sb1_flush_cache_sigtramp
r_static
r_void
id|sb1_flush_cache_sigtramp
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|on_each_cpu
c_func
(paren
id|sb1_flush_cache_sigtramp_ipi
comma
(paren
r_void
op_star
)paren
id|addr
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#else
r_void
id|sb1_flush_cache_sigtramp
c_func
(paren
r_int
r_int
id|addr
)paren
id|__attribute__
c_func
(paren
(paren
id|alias
c_func
(paren
l_string|&quot;local_sb1_flush_cache_sigtramp&quot;
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Anything that just flushes dcache state can be ignored, as we&squot;re always&n; * coherent in dcache space.  This is just a dummy function that all the&n; * nop&squot;ed routines point to&n; */
DECL|function|sb1_nop
r_static
r_void
id|sb1_nop
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/*&n; *  Cache set values (from the mips64 spec)&n; * 0 - 64&n; * 1 - 128&n; * 2 - 256&n; * 3 - 512&n; * 4 - 1024&n; * 5 - 2048&n; * 6 - 4096&n; * 7 - Reserved&n; */
DECL|function|decode_cache_sets
r_static
r_int
r_int
id|decode_cache_sets
c_func
(paren
r_int
r_int
id|config_field
)paren
(brace
r_if
c_cond
(paren
id|config_field
op_eq
l_int|7
)paren
(brace
multiline_comment|/* JDCXXX - Find a graceful way to abort. */
r_return
l_int|0
suffix:semicolon
)brace
r_return
(paren
l_int|1
op_lshift
(paren
id|config_field
op_plus
l_int|6
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Cache line size values (from the mips64 spec)&n; * 0 - No cache present.&n; * 1 - 4 bytes&n; * 2 - 8 bytes&n; * 3 - 16 bytes&n; * 4 - 32 bytes&n; * 5 - 64 bytes&n; * 6 - 128 bytes&n; * 7 - Reserved&n; */
DECL|function|decode_cache_line_size
r_static
r_int
r_int
id|decode_cache_line_size
c_func
(paren
r_int
r_int
id|config_field
)paren
(brace
r_if
c_cond
(paren
id|config_field
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|config_field
op_eq
l_int|7
)paren
(brace
multiline_comment|/* JDCXXX - Find a graceful way to abort. */
r_return
l_int|0
suffix:semicolon
)brace
r_return
(paren
l_int|1
op_lshift
(paren
id|config_field
op_plus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Relevant bits of the config1 register format (from the MIPS32/MIPS64 specs)&n; *&n; * 24:22 Icache sets per way&n; * 21:19 Icache line size&n; * 18:16 Icache Associativity&n; * 15:13 Dcache sets per way&n; * 12:10 Dcache line size&n; * 9:7   Dcache Associativity&n; */
DECL|variable|way_string
r_static
r_char
op_star
id|way_string
(braket
)braket
op_assign
(brace
l_string|&quot;direct mapped&quot;
comma
l_string|&quot;2-way&quot;
comma
l_string|&quot;3-way&quot;
comma
l_string|&quot;4-way&quot;
comma
l_string|&quot;5-way&quot;
comma
l_string|&quot;6-way&quot;
comma
l_string|&quot;7-way&quot;
comma
l_string|&quot;8-way&quot;
comma
)brace
suffix:semicolon
DECL|function|probe_cache_sizes
r_static
id|__init
r_void
id|probe_cache_sizes
c_func
(paren
r_void
)paren
(brace
id|u32
id|config1
suffix:semicolon
id|config1
op_assign
id|read_c0_config1
c_func
(paren
)paren
suffix:semicolon
id|icache_line_size
op_assign
id|decode_cache_line_size
c_func
(paren
(paren
id|config1
op_rshift
l_int|19
)paren
op_amp
l_int|0x7
)paren
suffix:semicolon
id|dcache_line_size
op_assign
id|decode_cache_line_size
c_func
(paren
(paren
id|config1
op_rshift
l_int|10
)paren
op_amp
l_int|0x7
)paren
suffix:semicolon
id|icache_sets
op_assign
id|decode_cache_sets
c_func
(paren
(paren
id|config1
op_rshift
l_int|22
)paren
op_amp
l_int|0x7
)paren
suffix:semicolon
id|dcache_sets
op_assign
id|decode_cache_sets
c_func
(paren
(paren
id|config1
op_rshift
l_int|13
)paren
op_amp
l_int|0x7
)paren
suffix:semicolon
id|icache_assoc
op_assign
(paren
(paren
id|config1
op_rshift
l_int|16
)paren
op_amp
l_int|0x7
)paren
op_plus
l_int|1
suffix:semicolon
id|dcache_assoc
op_assign
(paren
(paren
id|config1
op_rshift
l_int|7
)paren
op_amp
l_int|0x7
)paren
op_plus
l_int|1
suffix:semicolon
id|icache_size
op_assign
id|icache_line_size
op_star
id|icache_sets
op_star
id|icache_assoc
suffix:semicolon
id|dcache_size
op_assign
id|dcache_line_size
op_star
id|dcache_sets
op_star
id|dcache_assoc
suffix:semicolon
multiline_comment|/* Need to remove non-index bits for index ops */
id|icache_index_mask
op_assign
(paren
id|icache_sets
op_minus
l_int|1
)paren
op_star
id|icache_line_size
suffix:semicolon
id|dcache_index_mask
op_assign
(paren
id|dcache_sets
op_minus
l_int|1
)paren
op_star
id|dcache_line_size
suffix:semicolon
multiline_comment|/*&n;&t; * These are for choosing range (index ops) versus all.&n;&t; * icache flushes all ways for each set, so drop icache_assoc.&n;&t; * dcache flushes all ways and each setting of bit 12 for each&n;&t; * index, so drop dcache_assoc and halve the dcache_sets.&n;&t; */
id|icache_range_cutoff
op_assign
id|icache_sets
op_star
id|icache_line_size
suffix:semicolon
id|dcache_range_cutoff
op_assign
(paren
id|dcache_sets
op_div
l_int|2
)paren
op_star
id|icache_line_size
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Primary instruction cache %ldkB, %s, linesize %d bytes.&bslash;n&quot;
comma
id|icache_size
op_rshift
l_int|10
comma
id|way_string
(braket
id|icache_assoc
op_minus
l_int|1
)braket
comma
id|icache_line_size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Primary data cache %ldkB, %s, linesize %d bytes.&bslash;n&quot;
comma
id|dcache_size
op_rshift
l_int|10
comma
id|way_string
(braket
id|dcache_assoc
op_minus
l_int|1
)braket
comma
id|dcache_line_size
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called from loadmmu.c.  We have to set up all the&n; * memory management function pointers, as well as initialize&n; * the caches and tlbs&n; */
DECL|function|ld_mmu_sb1
r_void
id|ld_mmu_sb1
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
id|except_vec2_sb1
suffix:semicolon
r_extern
r_char
id|handle_vec2_sb1
suffix:semicolon
multiline_comment|/* Special cache error handler for SB1 */
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|CAC_BASE
op_plus
l_int|0x100
)paren
comma
op_amp
id|except_vec2_sb1
comma
l_int|0x80
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|UNCAC_BASE
op_plus
l_int|0x100
)paren
comma
op_amp
id|except_vec2_sb1
comma
l_int|0x80
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|CKSEG1ADDR
c_func
(paren
op_amp
id|handle_vec2_sb1
)paren
comma
op_amp
id|handle_vec2_sb1
comma
l_int|0x80
)paren
suffix:semicolon
id|probe_cache_sizes
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SIBYTE_DMA_PAGEOPS
id|sb1_dma_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * None of these are needed for the SB1 - the Dcache is&n;&t; * physically indexed and tagged, so no virtual aliasing can&n;&t; * occur&n;&t; */
id|flush_cache_range
op_assign
(paren
r_void
op_star
)paren
id|sb1_nop
suffix:semicolon
id|flush_cache_mm
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
r_struct
id|mm_struct
op_star
)paren
)paren
id|sb1_nop
suffix:semicolon
id|flush_cache_all
op_assign
id|sb1_nop
suffix:semicolon
multiline_comment|/* These routines are for Icache coherence with the Dcache */
id|flush_icache_range
op_assign
id|sb1_flush_icache_range
suffix:semicolon
id|flush_icache_page
op_assign
id|sb1_flush_icache_page
suffix:semicolon
id|flush_icache_all
op_assign
id|__sb1_flush_icache_all
suffix:semicolon
multiline_comment|/* local only */
multiline_comment|/* This implies an Icache flush too, so can&squot;t be nop&squot;ed */
id|flush_cache_page
op_assign
id|sb1_flush_cache_page
suffix:semicolon
id|flush_cache_sigtramp
op_assign
id|sb1_flush_cache_sigtramp
suffix:semicolon
id|flush_data_cache_page
op_assign
(paren
r_void
op_star
)paren
id|sb1_nop
suffix:semicolon
multiline_comment|/* Full flush */
id|__flush_cache_all
op_assign
id|sb1___flush_cache_all
suffix:semicolon
id|change_c0_config
c_func
(paren
id|CONF_CM_CMASK
comma
id|CONF_CM_DEFAULT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is the only way to force the update of K0 to complete&n;&t; * before subsequent instruction fetch.&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&t;push&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;noat&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;noreorder&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;mips3&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;&quot;
id|STR
c_func
(paren
id|PTR_LA
)paren
l_string|&quot;&t;$1, 1f&t;&t;&bslash;n&quot;
l_string|&quot;&t;&quot;
id|STR
c_func
(paren
id|MTC0
)paren
l_string|&quot;&t;$1, $14&t;&t;&bslash;n&quot;
l_string|&quot;&t;eret&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;1:&t;.set&t;pop&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
)brace
eof
