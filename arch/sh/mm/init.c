multiline_comment|/* $Id: init.c,v 1.11 2003/05/27 16:21:23 lethal Exp $&n; *&n; *  linux/arch/sh/mm/init.c&n; *&n; *  Copyright (C) 1999  Niibe Yutaka&n; *  Copyright (C) 2002  Paul Mundt&n; *&n; *  Based on linux/arch/i386/mm/init.c:&n; *   Copyright (C) 1995  Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|mmu_gather
comma
id|mmu_gathers
)paren
suffix:semicolon
DECL|variable|swapper_pg_dir
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
multiline_comment|/*&n; * Cache of MMU context last used.&n; */
DECL|variable|mmu_context_cache
r_int
r_int
id|mmu_context_cache
op_assign
id|NO_CONTEXT
suffix:semicolon
macro_line|#ifdef CONFIG_MMU
multiline_comment|/* It&squot;d be good if these lines were in the standard header file. */
DECL|macro|START_PFN
mdefine_line|#define START_PFN&t;(NODE_DATA(0)-&gt;bdata-&gt;node_boot_start &gt;&gt; PAGE_SHIFT)
DECL|macro|MAX_LOW_PFN
mdefine_line|#define MAX_LOW_PFN&t;(NODE_DATA(0)-&gt;bdata-&gt;node_low_pfn)
macro_line|#endif
macro_line|#ifdef CONFIG_DISCONTIGMEM
DECL|variable|discontig_page_data
id|pg_data_t
id|discontig_page_data
(braket
id|NR_NODES
)braket
suffix:semicolon
DECL|variable|discontig_node_bdata
id|bootmem_data_t
id|discontig_node_bdata
(braket
id|NR_NODES
)braket
suffix:semicolon
macro_line|#endif
DECL|function|show_mem
r_void
id|show_mem
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|total
op_assign
l_int|0
comma
id|reserved
op_assign
l_int|0
suffix:semicolon
r_int
id|shared
op_assign
l_int|0
comma
id|cached
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Mem-info:&bslash;n&quot;
)paren
suffix:semicolon
id|show_free_areas
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Free swap:       %6dkB&bslash;n&quot;
comma
id|nr_swap_pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
id|i
op_assign
id|max_mapnr
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
(brace
id|total
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|mem_map
op_plus
id|i
)paren
)paren
id|reserved
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|mem_map
op_plus
id|i
)paren
)paren
id|cached
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|page_count
c_func
(paren
id|mem_map
op_plus
id|i
)paren
)paren
id|shared
op_add_assign
id|page_count
c_func
(paren
id|mem_map
op_plus
id|i
)paren
op_minus
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%d pages of RAM&bslash;n&quot;
comma
id|total
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d reserved pages&bslash;n&quot;
comma
id|reserved
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages shared&bslash;n&quot;
comma
id|shared
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages swap cached&bslash;n&quot;
comma
id|cached
)paren
suffix:semicolon
)brace
multiline_comment|/* References to section boundaries */
r_extern
r_char
id|_text
comma
id|_etext
comma
id|_edata
comma
id|__bss_start
comma
id|_end
suffix:semicolon
r_extern
r_char
id|__init_begin
comma
id|__init_end
suffix:semicolon
multiline_comment|/*&n; * paging_init() sets up the page tables&n; *&n; * This routines also unmaps the page at virtual kernel address 0, so&n; * that we can trap those pesky NULL-reference errors in the kernel.&n; */
DECL|function|paging_init
r_void
id|__init
id|paging_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|zones_size
(braket
id|MAX_NR_ZONES
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*&n;&t; * Setup some defaults for the zone sizes.. these should be safe&n;&t; * regardless of distcontiguous memory or MMU settings.&n;&t; */
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
l_int|0
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|zones_size
(braket
id|ZONE_NORMAL
)braket
op_assign
id|__MEMORY_SIZE
op_rshift
id|PAGE_SHIFT
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
id|zones_size
(braket
id|ZONE_HIGHMEM
)braket
op_assign
l_int|0
op_rshift
id|PAGE_SHIFT
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MMU
multiline_comment|/*&n;&t; * If we have an MMU, and want to be using it .. we need to adjust&n;&t; * the zone sizes accordingly, in addition to turning it on.&n;&t; */
(brace
r_int
r_int
id|max_dma
comma
id|low
comma
id|start_pfn
suffix:semicolon
id|pgd_t
op_star
id|pg_dir
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* We don&squot;t need kernel mapping as hardware support that. */
id|pg_dir
op_assign
id|swapper_pg_dir
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
id|PTRS_PER_PGD
suffix:semicolon
id|i
op_increment
)paren
id|pgd_val
c_func
(paren
id|pg_dir
(braket
id|i
)braket
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Turn on the MMU */
id|enable_mmu
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Fixup the zone sizes */
id|start_pfn
op_assign
id|START_PFN
suffix:semicolon
id|max_dma
op_assign
id|virt_to_phys
c_func
(paren
(paren
r_char
op_star
)paren
id|MAX_DMA_ADDRESS
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|low
op_assign
id|MAX_LOW_PFN
suffix:semicolon
r_if
c_cond
(paren
id|low
OL
id|max_dma
)paren
(brace
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|low
op_minus
id|start_pfn
suffix:semicolon
)brace
r_else
(brace
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|max_dma
op_minus
id|start_pfn
suffix:semicolon
id|zones_size
(braket
id|ZONE_NORMAL
)braket
op_assign
id|low
op_minus
id|max_dma
suffix:semicolon
)brace
)brace
macro_line|#elif defined(CONFIG_CPU_SH3) || defined(CONFIG_CPU_SH4)
multiline_comment|/*&n;&t; * If we don&squot;t have CONFIG_MMU set and the processor in question&n;&t; * still has an MMU, care needs to be taken to make sure it doesn&squot;t&n;&t; * stay on.. Since the boot loader could have potentially already&n;&t; * turned it on, and we clearly don&squot;t want it, we simply turn it off.&n;&t; *&n;&t; * We don&squot;t need to do anything special for the zone sizes, since the&n;&t; * default values that were already configured up above should be&n;&t; * satisfactory.&n;&t; */
id|disable_mmu
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|free_area_init_node
c_func
(paren
l_int|0
comma
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
l_int|0
comma
id|zones_size
comma
id|__MEMORY_START
op_rshift
id|PAGE_SHIFT
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* XXX: MRB-remove - this doesn&squot;t seem sane, should this be done somewhere else ?*/
id|mem_map
op_assign
id|NODE_DATA
c_func
(paren
l_int|0
)paren
op_member_access_from_pointer
id|node_mem_map
suffix:semicolon
macro_line|#ifdef CONFIG_DISCONTIGMEM
multiline_comment|/*&n;&t; * And for discontig, do some more fixups on the zone sizes..&n;&t; */
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|__MEMORY_SIZE_2ND
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|zones_size
(braket
id|ZONE_NORMAL
)braket
op_assign
l_int|0
suffix:semicolon
id|free_area_init_node
c_func
(paren
l_int|1
comma
id|NODE_DATA
c_func
(paren
l_int|1
)paren
comma
l_int|0
comma
id|zones_size
comma
id|__MEMORY_START_2ND
op_rshift
id|PAGE_SHIFT
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|mem_init
r_void
id|__init
id|mem_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
r_int
id|empty_zero_page
(braket
l_int|1024
)braket
suffix:semicolon
r_int
id|codesize
comma
id|reservedpages
comma
id|datasize
comma
id|initsize
suffix:semicolon
r_int
id|tmp
suffix:semicolon
macro_line|#ifdef CONFIG_MMU
id|high_memory
op_assign
(paren
r_void
op_star
)paren
id|__va
c_func
(paren
id|MAX_LOW_PFN
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#else
r_extern
r_int
r_int
id|memory_end
suffix:semicolon
id|high_memory
op_assign
(paren
r_void
op_star
)paren
(paren
id|memory_end
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
macro_line|#endif
id|max_mapnr
op_assign
id|num_physpages
op_assign
id|MAP_NR
c_func
(paren
id|high_memory
)paren
suffix:semicolon
multiline_comment|/* clear the zero-page */
id|memset
c_func
(paren
id|empty_zero_page
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|__flush_wback_region
c_func
(paren
id|empty_zero_page
comma
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/* this will put all low memory onto the freelists */
id|totalram_pages
op_add_assign
id|free_all_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DISCONTIGMEM
id|totalram_pages
op_add_assign
id|free_all_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
macro_line|#endif
id|reservedpages
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|num_physpages
suffix:semicolon
id|tmp
op_increment
)paren
multiline_comment|/*&n;&t;&t; * Only count reserved RAM pages&n;&t;&t; */
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|mem_map
op_plus
id|tmp
)paren
)paren
id|reservedpages
op_increment
suffix:semicolon
id|codesize
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_etext
op_minus
(paren
r_int
r_int
)paren
op_amp
id|_text
suffix:semicolon
id|datasize
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_edata
op_minus
(paren
r_int
r_int
)paren
op_amp
id|_etext
suffix:semicolon
id|initsize
op_assign
(paren
r_int
r_int
)paren
op_amp
id|__init_end
op_minus
(paren
r_int
r_int
)paren
op_amp
id|__init_begin
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Memory: %luk/%luk available (%dk kernel code, %dk reserved, %dk data, %dk init)&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|nr_free_pages
c_func
(paren
)paren
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|max_mapnr
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|codesize
op_rshift
l_int|10
comma
id|reservedpages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|datasize
op_rshift
l_int|10
comma
id|initsize
op_rshift
l_int|10
)paren
suffix:semicolon
id|p3_cache_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|free_initmem
r_void
id|free_initmem
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|__init_begin
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|addr
OL
(paren
r_int
r_int
)paren
(paren
op_amp
id|__init_end
)paren
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|virt_to_page
c_func
(paren
id|addr
)paren
comma
l_int|1
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|addr
)paren
suffix:semicolon
id|totalram_pages
op_increment
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;Freeing unused kernel memory: %dk freed&bslash;n&quot;
comma
(paren
op_amp
id|__init_end
op_minus
op_amp
id|__init_begin
)paren
op_rshift
l_int|10
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
DECL|function|free_initrd_mem
r_void
id|free_initrd_mem
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
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|start
suffix:semicolon
id|p
OL
id|end
suffix:semicolon
id|p
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|virt_to_page
c_func
(paren
id|p
)paren
comma
l_int|1
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|p
)paren
suffix:semicolon
id|totalram_pages
op_increment
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;Freeing initrd memory: %ldk freed&bslash;n&quot;
comma
(paren
id|end
op_minus
id|start
)paren
op_rshift
l_int|10
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Generic first-level cache init&n; */
DECL|function|sh_cache_init
r_void
id|__init
id|sh_cache_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
id|detect_cpu_and_cache_system
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|ccr
comma
id|flags
op_assign
l_int|0
suffix:semicolon
id|detect_cpu_and_cache_system
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_data-&gt;type
op_eq
id|CPU_SH_NONE
)paren
id|panic
c_func
(paren
l_string|&quot;Unknown CPU&quot;
)paren
suffix:semicolon
id|jump_to_P2
c_func
(paren
)paren
suffix:semicolon
id|ccr
op_assign
id|ctrl_inl
c_func
(paren
id|CCR
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the cache is already enabled .. flush it.&n;&t; */
r_if
c_cond
(paren
id|ccr
op_amp
id|CCR_CACHE_ENABLE
)paren
(brace
r_int
r_int
id|entries
comma
id|i
comma
id|j
suffix:semicolon
id|entries
op_assign
id|cpu_data-&gt;dcache.sets
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the OC is already in RAM mode, we only have&n;&t;&t; * half of the entries to flush..&n;&t;&t; */
r_if
c_cond
(paren
id|ccr
op_amp
id|CCR_CACHE_ORA
)paren
id|entries
op_rshift_assign
l_int|1
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
id|entries
suffix:semicolon
id|i
op_increment
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
id|i
op_lshift
id|cpu_data-&gt;dcache.entry_shift
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
(paren
id|SH_CACHE_UPDATED
op_or
id|SH_CACHE_VALID
)paren
)paren
op_eq
(paren
id|SH_CACHE_UPDATED
op_or
id|SH_CACHE_VALID
)paren
)paren
id|ctrl_outl
c_func
(paren
id|data
op_amp
op_complement
id|SH_CACHE_UPDATED
comma
id|addr
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* &n;&t; * Default CCR values .. enable the caches&n;&t; * and flush them immediately..&n;&t; */
id|flags
op_or_assign
id|CCR_CACHE_ENABLE
op_or
id|CCR_CACHE_INVALIDATE
op_or
(paren
id|ccr
op_amp
id|CCR_CACHE_EMODE
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SH_WRITETHROUGH
multiline_comment|/* Turn on Write-through caching */
id|flags
op_or_assign
id|CCR_CACHE_WT
suffix:semicolon
macro_line|#else
multiline_comment|/* .. or default to Write-back */
id|flags
op_or_assign
id|CCR_CACHE_CB
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SH_OCRAM
multiline_comment|/* Turn on OCRAM -- halve the OC */
id|flags
op_or_assign
id|CCR_CACHE_ORA
suffix:semicolon
id|cpu_data-&gt;dcache.sets
op_rshift_assign
l_int|1
suffix:semicolon
macro_line|#endif
id|ctrl_outl
c_func
(paren
id|flags
comma
id|CCR
)paren
suffix:semicolon
id|back_to_P1
c_func
(paren
)paren
suffix:semicolon
)brace
eof
