multiline_comment|/*&n; *  linux/arch/m32r/mm/init.c&n; *&n; *  Copyright (c) 2001, 2002  Hitoshi Yamamoto&n; *&n; *  Some code taken from sh version.&n; *    Copyright (C) 1999  Niibe Yutaka&n; *    Based on linux/arch/i386/mm/init.c:&n; *      Copyright (C) 1995  Linus Torvalds&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/nodemask.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
multiline_comment|/* References to section boundaries */
r_extern
r_char
id|_text
comma
id|_etext
comma
id|_edata
suffix:semicolon
r_extern
r_char
id|__init_begin
comma
id|__init_end
suffix:semicolon
DECL|variable|swapper_pg_dir
id|pgd_t
id|swapper_pg_dir
(braket
l_int|1024
)braket
suffix:semicolon
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|mmu_gather
comma
id|mmu_gathers
)paren
suffix:semicolon
DECL|function|show_mem
r_void
id|show_mem
c_func
(paren
r_void
)paren
(brace
r_int
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
r_int
id|highmem
op_assign
l_int|0
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|pg_data_t
op_star
id|pgdat
suffix:semicolon
r_int
r_int
id|i
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
l_string|&quot;Free swap:       %6ldkB&bslash;n&quot;
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
id|for_each_pgdat
c_func
(paren
id|pgdat
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pgdat-&gt;node_spanned_pages
suffix:semicolon
op_increment
id|i
)paren
(brace
id|page
op_assign
id|pgdat-&gt;node_mem_map
op_plus
id|i
suffix:semicolon
id|total
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
id|highmem
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|page
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
id|page
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
id|page
)paren
)paren
id|shared
op_add_assign
id|page_count
c_func
(paren
id|page
)paren
op_minus
l_int|1
suffix:semicolon
)brace
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
l_string|&quot;%d pages of HIGHMEM&bslash;n&quot;
comma
id|highmem
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
multiline_comment|/*&n; * Cache of MMU context last used.&n; */
macro_line|#ifndef CONFIG_SMP
DECL|variable|mmu_context_cache_dat
r_int
r_int
id|mmu_context_cache_dat
suffix:semicolon
macro_line|#else
DECL|variable|mmu_context_cache_dat
r_int
r_int
id|mmu_context_cache_dat
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#endif
DECL|variable|hole_pages
r_static
r_int
r_int
id|hole_pages
suffix:semicolon
multiline_comment|/*&n; * function prototype&n; */
r_void
id|__init
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|__init
id|mem_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|free_initmem
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_void
id|free_initrd_mem
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* It&squot;d be good if these lines were in the standard header file. */
DECL|macro|START_PFN
mdefine_line|#define START_PFN(nid)&t;&bslash;&n;&t;(NODE_DATA(nid)-&gt;bdata-&gt;node_boot_start &gt;&gt; PAGE_SHIFT)
DECL|macro|MAX_LOW_PFN
mdefine_line|#define MAX_LOW_PFN(nid)&t;(NODE_DATA(nid)-&gt;bdata-&gt;node_low_pfn)
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|function|zone_sizes_init
r_int
r_int
id|__init
id|zone_sizes_init
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
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
r_int
id|max_dma
suffix:semicolon
r_int
r_int
id|low
suffix:semicolon
r_int
r_int
id|start_pfn
suffix:semicolon
macro_line|#ifdef CONFIG_MMU
id|start_pfn
op_assign
id|START_PFN
c_func
(paren
l_int|0
)paren
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
c_func
(paren
l_int|0
)paren
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
id|zones_size
(braket
id|ZONE_NORMAL
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_else
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
macro_line|#else
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
id|start_pfn
op_assign
id|__MEMORY_START
op_rshift
id|PAGE_SHIFT
suffix:semicolon
macro_line|#endif /* CONFIG_MMU */
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
id|zones_size
comma
id|start_pfn
comma
l_int|0
)paren
suffix:semicolon
id|mem_map
op_assign
id|contig_page_data.node_mem_map
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else&t;/* CONFIG_DISCONTIGMEM */
r_extern
r_int
r_int
id|zone_sizes_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_DISCONTIGMEM */
multiline_comment|/*======================================================================*&n; * paging_init() : sets up the page tables&n; *======================================================================*/
DECL|function|paging_init
r_void
id|__init
id|paging_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_MMU
r_int
id|i
suffix:semicolon
id|pgd_t
op_star
id|pg_dir
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
id|USER_PTRS_PER_PGD
op_star
l_int|2
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
macro_line|#endif /* CONFIG_MMU */
id|hole_pages
op_assign
id|zone_sizes_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|reservedpages_count
r_int
id|__init
id|reservedpages_count
c_func
(paren
r_void
)paren
(brace
r_int
id|reservedpages
comma
id|nid
comma
id|i
suffix:semicolon
id|reservedpages
op_assign
l_int|0
suffix:semicolon
id|for_each_online_node
c_func
(paren
id|nid
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_LOW_PFN
c_func
(paren
id|nid
)paren
op_minus
id|START_PFN
c_func
(paren
id|nid
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|node_mem_map
op_plus
id|i
)paren
)paren
id|reservedpages
op_increment
suffix:semicolon
r_return
id|reservedpages
suffix:semicolon
)brace
multiline_comment|/*======================================================================*&n; * mem_init() :&n; * orig : arch/sh/mm/init.c&n; *======================================================================*/
DECL|function|mem_init
r_void
id|__init
id|mem_init
c_func
(paren
r_void
)paren
(brace
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
id|nid
suffix:semicolon
macro_line|#ifndef CONFIG_MMU
r_extern
r_int
r_int
id|memory_end
suffix:semicolon
macro_line|#endif
id|num_physpages
op_assign
l_int|0
suffix:semicolon
id|for_each_online_node
c_func
(paren
id|nid
)paren
id|num_physpages
op_add_assign
id|MAX_LOW_PFN
c_func
(paren
id|nid
)paren
op_minus
id|START_PFN
c_func
(paren
id|nid
)paren
op_plus
l_int|1
suffix:semicolon
id|num_physpages
op_sub_assign
id|hole_pages
suffix:semicolon
macro_line|#ifndef CONFIG_DISCONTIGMEM
id|max_mapnr
op_assign
id|num_physpages
suffix:semicolon
macro_line|#endif&t;/* CONFIG_DISCONTIGMEM */
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
id|PFN_PHYS
c_func
(paren
id|MAX_LOW_PFN
c_func
(paren
l_int|0
)paren
)paren
)paren
suffix:semicolon
macro_line|#else
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
macro_line|#endif /* CONFIG_MMU */
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
multiline_comment|/* this will put all low memory onto the freelists */
id|for_each_online_node
c_func
(paren
id|nid
)paren
id|totalram_pages
op_add_assign
id|free_all_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nid
)paren
)paren
suffix:semicolon
id|reservedpages
op_assign
id|reservedpages_count
c_func
(paren
)paren
op_minus
id|hole_pages
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
id|KERN_INFO
l_string|&quot;Memory: %luk/%luk available (%dk kernel code, &quot;
l_string|&quot;%dk reserved, %dk data, %dk init)&bslash;n&quot;
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
id|num_physpages
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
)brace
multiline_comment|/*======================================================================*&n; * free_initmem() :&n; * orig : arch/sh/mm/init.c&n; *======================================================================*/
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
id|KERN_INFO
l_string|&quot;Freeing unused kernel memory: %dk freed&bslash;n&quot;
comma
"&bslash;"
(paren
r_int
)paren
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
multiline_comment|/*======================================================================*&n; * free_initrd_mem() :&n; * orig : arch/sh/mm/init.c&n; *======================================================================*/
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
id|KERN_INFO
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
eof
