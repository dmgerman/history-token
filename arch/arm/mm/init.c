multiline_comment|/*&n; *  linux/arch/arm/mm/init.c&n; *&n; *  Copyright (C) 1995-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#ifdef CONFIG_CPU_32
DECL|macro|TABLE_OFFSET
mdefine_line|#define TABLE_OFFSET&t;(PTRS_PER_PTE)
macro_line|#else
DECL|macro|TABLE_OFFSET
mdefine_line|#define TABLE_OFFSET&t;0
macro_line|#endif
DECL|macro|TABLE_SIZE
mdefine_line|#define TABLE_SIZE&t;((TABLE_OFFSET + PTRS_PER_PTE) * sizeof(pte_t))
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|mmu_gather
comma
id|mmu_gathers
)paren
suffix:semicolon
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
r_extern
r_char
id|_stext
comma
id|_text
comma
id|_etext
comma
id|_end
comma
id|__init_begin
comma
id|__init_end
suffix:semicolon
r_extern
r_int
r_int
id|phys_initrd_start
suffix:semicolon
r_extern
r_int
r_int
id|phys_initrd_size
suffix:semicolon
multiline_comment|/*&n; * The sole use of this is to pass memory configuration&n; * data from paging_init to mem_init.&n; */
DECL|variable|__initdata
r_static
r_struct
id|meminfo
id|meminfo
id|__initdata
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * empty_zero_page is a special page that is used for&n; * zero-initialized data and COW.&n; */
DECL|variable|empty_zero_page
r_struct
id|page
op_star
id|empty_zero_page
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
id|free
op_assign
l_int|0
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
comma
id|slab
op_assign
l_int|0
comma
id|node
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
r_for
c_loop
(paren
id|node
op_assign
l_int|0
suffix:semicolon
id|node
OL
id|numnodes
suffix:semicolon
id|node
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
comma
op_star
id|end
suffix:semicolon
id|page
op_assign
id|NODE_MEM_MAP
c_func
(paren
id|node
)paren
suffix:semicolon
id|end
op_assign
id|page
op_plus
id|NODE_DATA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|node_spanned_pages
suffix:semicolon
r_do
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
id|PageSlab
c_func
(paren
id|page
)paren
)paren
id|slab
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|page_count
c_func
(paren
id|page
)paren
)paren
id|free
op_increment
suffix:semicolon
r_else
id|shared
op_add_assign
id|atomic_read
c_func
(paren
op_amp
id|page-&gt;count
)paren
op_minus
l_int|1
suffix:semicolon
id|page
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|page
OL
id|end
)paren
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
l_string|&quot;%d free pages&bslash;n&quot;
comma
id|free
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
l_string|&quot;%d slab pages&bslash;n&quot;
comma
id|slab
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
DECL|struct|node_info
r_struct
id|node_info
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
DECL|member|bootmap_pages
r_int
id|bootmap_pages
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|O_PFN_DOWN
mdefine_line|#define O_PFN_DOWN(x)&t;((x) &gt;&gt; PAGE_SHIFT)
DECL|macro|V_PFN_DOWN
mdefine_line|#define V_PFN_DOWN(x)&t;O_PFN_DOWN(__pa(x))
DECL|macro|O_PFN_UP
mdefine_line|#define O_PFN_UP(x)&t;(PAGE_ALIGN(x) &gt;&gt; PAGE_SHIFT)
DECL|macro|V_PFN_UP
mdefine_line|#define V_PFN_UP(x)&t;O_PFN_UP(__pa(x))
DECL|macro|PFN_SIZE
mdefine_line|#define PFN_SIZE(x)&t;((x) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_RANGE
mdefine_line|#define PFN_RANGE(s,e)&t;PFN_SIZE(PAGE_ALIGN((unsigned long)(e)) - &bslash;&n;&t;&t;&t;&t;(((unsigned long)(s)) &amp; PAGE_MASK))
multiline_comment|/*&n; * FIXME: We really want to avoid allocating the bootmap bitmap&n; * over the top of the initrd.  Hopefully, this is located towards&n; * the start of a bank, so if we allocate the bootmap bitmap at&n; * the end, we won&squot;t clash.&n; */
r_static
r_int
r_int
id|__init
DECL|function|find_bootmap_pfn
id|find_bootmap_pfn
c_func
(paren
r_int
id|node
comma
r_struct
id|meminfo
op_star
id|mi
comma
r_int
r_int
id|bootmap_pages
)paren
(brace
r_int
r_int
id|start_pfn
comma
id|bank
comma
id|bootmap_pfn
suffix:semicolon
id|start_pfn
op_assign
id|V_PFN_UP
c_func
(paren
op_amp
id|_end
)paren
suffix:semicolon
id|bootmap_pfn
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|bank
op_assign
l_int|0
suffix:semicolon
id|bank
OL
id|mi-&gt;nr_banks
suffix:semicolon
id|bank
op_increment
)paren
(brace
r_int
r_int
id|start
comma
id|end
suffix:semicolon
r_if
c_cond
(paren
id|mi-&gt;bank
(braket
id|bank
)braket
dot
id|node
op_ne
id|node
)paren
r_continue
suffix:semicolon
id|start
op_assign
id|O_PFN_UP
c_func
(paren
id|mi-&gt;bank
(braket
id|bank
)braket
dot
id|start
)paren
suffix:semicolon
id|end
op_assign
id|O_PFN_DOWN
c_func
(paren
id|mi-&gt;bank
(braket
id|bank
)braket
dot
id|size
op_plus
id|mi-&gt;bank
(braket
id|bank
)braket
dot
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
OL
id|start_pfn
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
id|start_pfn
)paren
id|start
op_assign
id|start_pfn
suffix:semicolon
r_if
c_cond
(paren
id|end
op_le
id|start
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|end
op_minus
id|start
op_ge
id|bootmap_pages
)paren
(brace
id|bootmap_pfn
op_assign
id|start
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|bootmap_pfn
op_eq
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
id|bootmap_pfn
suffix:semicolon
)brace
multiline_comment|/*&n; * Scan the memory info structure and pull out:&n; *  - the end of memory&n; *  - the number of nodes&n; *  - the pfn range of each node&n; *  - the number of bootmem bitmap pages&n; */
r_static
r_int
r_int
id|__init
DECL|function|find_memend_and_nodes
id|find_memend_and_nodes
c_func
(paren
r_struct
id|meminfo
op_star
id|mi
comma
r_struct
id|node_info
op_star
id|np
)paren
(brace
r_int
r_int
id|i
comma
id|bootmem_pages
op_assign
l_int|0
comma
id|memend_pfn
op_assign
l_int|0
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
id|MAX_NUMNODES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|np
(braket
id|i
)braket
dot
id|start
op_assign
op_minus
l_int|1U
suffix:semicolon
id|np
(braket
id|i
)braket
dot
id|end
op_assign
l_int|0
suffix:semicolon
id|np
(braket
id|i
)braket
dot
id|bootmap_pages
op_assign
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|mi-&gt;nr_banks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|start
comma
id|end
suffix:semicolon
r_int
id|node
suffix:semicolon
r_if
c_cond
(paren
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|size
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Mark this bank with an invalid node number&n;&t;&t;&t; */
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|node
op_assign
op_minus
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|node
op_assign
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|node
suffix:semicolon
r_if
c_cond
(paren
id|node
op_ge
id|numnodes
)paren
(brace
id|numnodes
op_assign
id|node
op_plus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Make sure we haven&squot;t exceeded the maximum number&n;&t;&t;&t; * of nodes that we have in this configuration.  If&n;&t;&t;&t; * we have, we&squot;re in trouble.  (maybe we ought to&n;&t;&t;&t; * limit, instead of bugging?)&n;&t;&t;&t; */
r_if
c_cond
(paren
id|numnodes
OG
id|MAX_NUMNODES
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Get the start and end pfns for this bank&n;&t;&t; */
id|start
op_assign
id|O_PFN_UP
c_func
(paren
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|start
)paren
suffix:semicolon
id|end
op_assign
id|O_PFN_DOWN
c_func
(paren
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|start
op_plus
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
(braket
id|node
)braket
dot
id|start
OG
id|start
)paren
id|np
(braket
id|node
)braket
dot
id|start
op_assign
id|start
suffix:semicolon
r_if
c_cond
(paren
id|np
(braket
id|node
)braket
dot
id|end
OL
id|end
)paren
id|np
(braket
id|node
)braket
dot
id|end
op_assign
id|end
suffix:semicolon
r_if
c_cond
(paren
id|memend_pfn
OL
id|end
)paren
id|memend_pfn
op_assign
id|end
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Calculate the number of pages we require to&n;&t; * store the bootmem bitmaps.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|numnodes
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|np
(braket
id|i
)braket
dot
id|end
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|np
(braket
id|i
)braket
dot
id|bootmap_pages
op_assign
id|bootmem_bootmap_pages
c_func
(paren
id|np
(braket
id|i
)braket
dot
id|end
op_minus
id|np
(braket
id|i
)braket
dot
id|start
)paren
suffix:semicolon
id|bootmem_pages
op_add_assign
id|np
(braket
id|i
)braket
dot
id|bootmap_pages
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This doesn&squot;t seem to be used by the Linux memory&n;&t; * manager any more.  If we can get rid of it, we&n;&t; * also get rid of some of the stuff above as well.&n;&t; */
id|max_low_pfn
op_assign
id|memend_pfn
op_minus
id|O_PFN_DOWN
c_func
(paren
id|PHYS_OFFSET
)paren
suffix:semicolon
id|max_pfn
op_assign
id|memend_pfn
op_minus
id|O_PFN_DOWN
c_func
(paren
id|PHYS_OFFSET
)paren
suffix:semicolon
id|mi-&gt;end
op_assign
id|memend_pfn
op_lshift
id|PAGE_SHIFT
suffix:semicolon
r_return
id|bootmem_pages
suffix:semicolon
)brace
DECL|function|check_initrd
r_static
r_int
id|__init
id|check_initrd
c_func
(paren
r_struct
id|meminfo
op_star
id|mi
)paren
(brace
r_int
id|initrd_node
op_assign
op_minus
l_int|2
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_int
r_int
id|end
op_assign
id|phys_initrd_start
op_plus
id|phys_initrd_size
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure that the initrd is within a valid area of&n;&t; * memory.&n;&t; */
r_if
c_cond
(paren
id|phys_initrd_size
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|initrd_node
op_assign
op_minus
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
id|mi-&gt;nr_banks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|bank_end
suffix:semicolon
id|bank_end
op_assign
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|start
op_plus
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|start
op_le
id|phys_initrd_start
op_logical_and
id|end
op_le
id|bank_end
)paren
id|initrd_node
op_assign
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|node
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|initrd_node
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;initrd (0x%08lx - 0x%08lx) extends beyond &quot;
l_string|&quot;physical memory - disabling initrd&bslash;n&quot;
comma
id|phys_initrd_start
comma
id|end
)paren
suffix:semicolon
id|phys_initrd_start
op_assign
id|phys_initrd_size
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_return
id|initrd_node
suffix:semicolon
)brace
multiline_comment|/*&n; * Reserve the various regions of node 0&n; */
DECL|function|reserve_node_zero
r_static
id|__init
r_void
id|reserve_node_zero
c_func
(paren
r_int
r_int
id|bootmap_pfn
comma
r_int
r_int
id|bootmap_pages
)paren
(brace
id|pg_data_t
op_star
id|pgdat
op_assign
id|NODE_DATA
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Register the kernel text and data with bootmem.&n;&t; * Note that this can only be in node 0.&n;&t; */
id|reserve_bootmem_node
c_func
(paren
id|pgdat
comma
id|__pa
c_func
(paren
op_amp
id|_stext
)paren
comma
op_amp
id|_end
op_minus
op_amp
id|_stext
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_32
multiline_comment|/*&n;&t; * Reserve the page tables.  These are already in use,&n;&t; * and can only be in node 0.&n;&t; */
id|reserve_bootmem_node
c_func
(paren
id|pgdat
comma
id|__pa
c_func
(paren
id|swapper_pg_dir
)paren
comma
id|PTRS_PER_PGD
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * And don&squot;t forget to reserve the allocator bitmap,&n;&t; * which will be freed later.&n;&t; */
id|reserve_bootmem_node
c_func
(paren
id|pgdat
comma
id|bootmap_pfn
op_lshift
id|PAGE_SHIFT
comma
id|bootmap_pages
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Hmm... This should go elsewhere, but we really really&n;&t; * need to stop things allocating the low memory; we need&n;&t; * a better implementation of GFP_DMA which does not assume&n;&t; * that DMA-able memory starts at zero.&n;&t; */
r_if
c_cond
(paren
id|machine_is_integrator
c_func
(paren
)paren
)paren
id|reserve_bootmem_node
c_func
(paren
id|pgdat
comma
l_int|0
comma
id|__pa
c_func
(paren
id|swapper_pg_dir
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * These should likewise go elsewhere.  They pre-reserve&n;&t; * the screen memory region at the start of main system&n;&t; * memory.&n;&t; */
r_if
c_cond
(paren
id|machine_is_archimedes
c_func
(paren
)paren
op_logical_or
id|machine_is_a5k
c_func
(paren
)paren
)paren
id|reserve_bootmem_node
c_func
(paren
id|pgdat
comma
l_int|0x02000000
comma
l_int|0x00080000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_edb7211
c_func
(paren
)paren
)paren
id|reserve_bootmem_node
c_func
(paren
id|pgdat
comma
l_int|0xc0000000
comma
l_int|0x00020000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_p720t
c_func
(paren
)paren
)paren
id|reserve_bootmem_node
c_func
(paren
id|pgdat
comma
id|PHYS_OFFSET
comma
l_int|0x00014000
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SA1111
multiline_comment|/*&n;&t; * Because of the SA1111 DMA bug, we want to preserve&n;&t; * our precious DMA-able memory...&n;&t; */
id|reserve_bootmem_node
c_func
(paren
id|pgdat
comma
id|PHYS_OFFSET
comma
id|__pa
c_func
(paren
id|swapper_pg_dir
)paren
op_minus
id|PHYS_OFFSET
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Register all available RAM in this node with the bootmem allocator.&n; */
DECL|function|free_bootmem_node_bank
r_static
r_inline
r_void
id|free_bootmem_node_bank
c_func
(paren
r_int
id|node
comma
r_struct
id|meminfo
op_star
id|mi
)paren
(brace
id|pg_data_t
op_star
id|pgdat
op_assign
id|NODE_DATA
c_func
(paren
id|node
)paren
suffix:semicolon
r_int
id|bank
suffix:semicolon
r_for
c_loop
(paren
id|bank
op_assign
l_int|0
suffix:semicolon
id|bank
OL
id|mi-&gt;nr_banks
suffix:semicolon
id|bank
op_increment
)paren
r_if
c_cond
(paren
id|mi-&gt;bank
(braket
id|bank
)braket
dot
id|node
op_eq
id|node
)paren
id|free_bootmem_node
c_func
(paren
id|pgdat
comma
id|mi-&gt;bank
(braket
id|bank
)braket
dot
id|start
comma
id|mi-&gt;bank
(braket
id|bank
)braket
dot
id|size
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialise the bootmem allocator for all nodes.  This is called&n; * early during the architecture specific initialisation.&n; */
DECL|function|bootmem_init
r_void
id|__init
id|bootmem_init
c_func
(paren
r_struct
id|meminfo
op_star
id|mi
)paren
(brace
r_struct
id|node_info
id|node_info
(braket
id|MAX_NUMNODES
)braket
comma
op_star
id|np
op_assign
id|node_info
suffix:semicolon
r_int
r_int
id|bootmap_pages
comma
id|bootmap_pfn
comma
id|map_pg
suffix:semicolon
r_int
id|node
comma
id|initrd_node
suffix:semicolon
id|bootmap_pages
op_assign
id|find_memend_and_nodes
c_func
(paren
id|mi
comma
id|np
)paren
suffix:semicolon
id|bootmap_pfn
op_assign
id|find_bootmap_pfn
c_func
(paren
l_int|0
comma
id|mi
comma
id|bootmap_pages
)paren
suffix:semicolon
id|initrd_node
op_assign
id|check_initrd
c_func
(paren
id|mi
)paren
suffix:semicolon
id|map_pg
op_assign
id|bootmap_pfn
suffix:semicolon
multiline_comment|/*&n;&t; * Initialise the bootmem nodes.&n;&t; *&n;&t; * What we really want to do is:&n;&t; *&n;&t; *   unmap_all_regions_except_kernel();&n;&t; *   for_each_node_in_reverse_order(node) {&n;&t; *     map_node(node);&n;&t; *     allocate_bootmem_map(node);&n;&t; *     init_bootmem_node(node);&n;&t; *     free_bootmem_node(node);&n;&t; *   }&n;&t; *&n;&t; * but this is a 2.5-type change.  For now, we just set&n;&t; * the nodes up in reverse order.&n;&t; *&n;&t; * (we could also do with rolling bootmem_init and paging_init&n;&t; * into one generic &quot;memory_init&quot; type function).&n;&t; */
id|np
op_add_assign
id|numnodes
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
id|numnodes
op_minus
l_int|1
suffix:semicolon
id|node
op_ge
l_int|0
suffix:semicolon
id|node
op_decrement
comma
id|np
op_decrement
)paren
(brace
multiline_comment|/*&n;&t;&t; * If there are no pages in this node, ignore it.&n;&t;&t; * Note that node 0 must always have some pages.&n;&t;&t; */
r_if
c_cond
(paren
id|np-&gt;end
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|node
op_eq
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Initialise the bootmem allocator.&n;&t;&t; */
id|init_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|node
)paren
comma
id|map_pg
comma
id|np-&gt;start
comma
id|np-&gt;end
)paren
suffix:semicolon
id|free_bootmem_node_bank
c_func
(paren
id|node
comma
id|mi
)paren
suffix:semicolon
id|map_pg
op_add_assign
id|np-&gt;bootmap_pages
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If this is node 0, we need to reserve some areas ASAP -&n;&t;&t; * we may use bootmem on node 0 to setup the other nodes.&n;&t;&t; */
r_if
c_cond
(paren
id|node
op_eq
l_int|0
)paren
id|reserve_node_zero
c_func
(paren
id|bootmap_pfn
comma
id|bootmap_pages
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|phys_initrd_size
op_logical_and
id|initrd_node
op_ge
l_int|0
)paren
(brace
id|reserve_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|initrd_node
)paren
comma
id|phys_initrd_start
comma
id|phys_initrd_size
)paren
suffix:semicolon
id|initrd_start
op_assign
id|__phys_to_virt
c_func
(paren
id|phys_initrd_start
)paren
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|phys_initrd_size
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|map_pg
op_ne
id|bootmap_pfn
op_plus
id|bootmap_pages
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * paging_init() sets up the page tables, initialises the zone memory&n; * maps, and sets up the zero page, bad page and bad page tables.&n; */
DECL|function|paging_init
r_void
id|__init
id|paging_init
c_func
(paren
r_struct
id|meminfo
op_star
id|mi
comma
r_struct
id|machine_desc
op_star
id|mdesc
)paren
(brace
r_void
op_star
id|zero_page
suffix:semicolon
r_int
id|node
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|meminfo
comma
id|mi
comma
r_sizeof
(paren
id|meminfo
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * allocate the zero page.  Note that we count on this going ok.&n;&t; */
id|zero_page
op_assign
id|alloc_bootmem_low_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * initialise the page tables.&n;&t; */
id|memtable_init
c_func
(paren
id|mi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mdesc-&gt;map_io
)paren
id|mdesc
op_member_access_from_pointer
id|map_io
c_func
(paren
)paren
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * initialise the zones within each node&n;&t; */
r_for
c_loop
(paren
id|node
op_assign
l_int|0
suffix:semicolon
id|node
OL
id|numnodes
suffix:semicolon
id|node
op_increment
)paren
(brace
r_int
r_int
id|zone_size
(braket
id|MAX_NR_ZONES
)braket
suffix:semicolon
r_int
r_int
id|zhole_size
(braket
id|MAX_NR_ZONES
)braket
suffix:semicolon
r_struct
id|bootmem_data
op_star
id|bdata
suffix:semicolon
id|pg_data_t
op_star
id|pgdat
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Initialise the zone size information.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_NR_ZONES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|zone_size
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|zhole_size
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|pgdat
op_assign
id|NODE_DATA
c_func
(paren
id|node
)paren
suffix:semicolon
id|bdata
op_assign
id|pgdat-&gt;bdata
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The size of this node has already been determined.&n;&t;&t; * If we need to do anything fancy with the allocation&n;&t;&t; * of this memory to the zones, now is the time to do&n;&t;&t; * it.&n;&t;&t; */
id|zone_size
(braket
l_int|0
)braket
op_assign
id|bdata-&gt;node_low_pfn
op_minus
(paren
id|bdata-&gt;node_boot_start
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If this zone has zero size, skip it.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|zone_size
(braket
l_int|0
)braket
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * For each bank in this node, calculate the size of the&n;&t;&t; * holes.  holes = node_size - sum(bank_sizes_in_node)&n;&t;&t; */
id|zhole_size
(braket
l_int|0
)braket
op_assign
id|zone_size
(braket
l_int|0
)braket
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
id|mi-&gt;nr_banks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|node
op_ne
id|node
)paren
r_continue
suffix:semicolon
id|zhole_size
(braket
l_int|0
)braket
op_sub_assign
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Adjust the sizes according to any special&n;&t;&t; * requirements for this machine type.&n;&t;&t; */
id|arch_adjust_zones
c_func
(paren
id|node
comma
id|zone_size
comma
id|zhole_size
)paren
suffix:semicolon
id|free_area_init_node
c_func
(paren
id|node
comma
id|pgdat
comma
l_int|0
comma
id|zone_size
comma
id|bdata-&gt;node_boot_start
op_rshift
id|PAGE_SHIFT
comma
id|zhole_size
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_DISCONTIGMEM
id|mem_map
op_assign
id|contig_page_data.node_mem_map
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * finish off the bad pages once&n;&t; * the mem_map is initialised&n;&t; */
id|memzero
c_func
(paren
id|zero_page
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|empty_zero_page
op_assign
id|virt_to_page
c_func
(paren
id|zero_page
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|empty_zero_page
)paren
suffix:semicolon
)brace
DECL|function|free_area
r_static
r_inline
r_void
id|free_area
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|end
comma
r_char
op_star
id|s
)paren
(brace
r_int
r_int
id|size
op_assign
(paren
id|end
op_minus
id|addr
)paren
op_rshift
l_int|10
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|addr
)paren
suffix:semicolon
id|ClearPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|page
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
r_if
c_cond
(paren
id|size
op_logical_and
id|s
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Freeing %s memory: %dK&bslash;n&quot;
comma
id|s
comma
id|size
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * mem_init() marks the free areas in the mem_map and tells us how much&n; * memory is free.  This is done after various parts of the system have&n; * claimed their memory after the kernel image.&n; */
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
r_int
id|codepages
comma
id|datapages
comma
id|initpages
suffix:semicolon
r_int
id|i
comma
id|node
suffix:semicolon
id|codepages
op_assign
op_amp
id|_etext
op_minus
op_amp
id|_text
suffix:semicolon
id|datapages
op_assign
op_amp
id|_end
op_minus
op_amp
id|_etext
suffix:semicolon
id|initpages
op_assign
op_amp
id|__init_end
op_minus
op_amp
id|__init_begin
suffix:semicolon
id|high_memory
op_assign
(paren
r_void
op_star
)paren
id|__va
c_func
(paren
id|meminfo.end
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_DISCONTIGMEM
id|max_mapnr
op_assign
id|virt_to_page
c_func
(paren
id|high_memory
)paren
op_minus
id|mem_map
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * We may have non-contiguous memory.&n;&t; */
r_if
c_cond
(paren
id|meminfo.nr_banks
op_ne
l_int|1
)paren
id|create_memmap_holes
c_func
(paren
op_amp
id|meminfo
)paren
suffix:semicolon
multiline_comment|/* this will put all unused low memory onto the freelists */
r_for
c_loop
(paren
id|node
op_assign
l_int|0
suffix:semicolon
id|node
OL
id|numnodes
suffix:semicolon
id|node
op_increment
)paren
(brace
id|pg_data_t
op_star
id|pgdat
op_assign
id|NODE_DATA
c_func
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgdat-&gt;node_spanned_pages
op_ne
l_int|0
)paren
id|totalram_pages
op_add_assign
id|free_all_bootmem_node
c_func
(paren
id|pgdat
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SA1111
multiline_comment|/* now that our DMA memory is actually so designated, we can free it */
id|free_area
c_func
(paren
id|PAGE_OFFSET
comma
(paren
r_int
r_int
)paren
id|swapper_pg_dir
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Since our memory may not be contiguous, calculate the&n;&t; * real number of pages we have in this system&n;&t; */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Memory:&quot;
)paren
suffix:semicolon
id|num_physpages
op_assign
l_int|0
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
id|meminfo.nr_banks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|num_physpages
op_add_assign
id|meminfo.bank
(braket
id|i
)braket
dot
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; %ldMB&quot;
comma
id|meminfo.bank
(braket
id|i
)braket
dot
id|size
op_rshift
l_int|20
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; = %luMB total&bslash;n&quot;
comma
id|num_physpages
op_rshift
(paren
l_int|20
op_minus
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Memory: %luKB available (%dK code, &quot;
l_string|&quot;%dK data, %dK init)&bslash;n&quot;
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
id|codepages
op_rshift
l_int|10
comma
id|datapages
op_rshift
l_int|10
comma
id|initpages
op_rshift
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PAGE_SIZE
op_ge
l_int|16384
op_logical_and
id|num_physpages
op_le
l_int|128
)paren
(brace
r_extern
r_int
id|sysctl_overcommit_memory
suffix:semicolon
multiline_comment|/*&n;&t;&t; * On a machine this small we won&squot;t get&n;&t;&t; * anywhere without overcommit, so turn&n;&t;&t; * it on by default.&n;&t;&t; */
id|sysctl_overcommit_memory
op_assign
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|free_initmem
r_void
id|free_initmem
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|machine_is_integrator
c_func
(paren
)paren
)paren
(brace
id|free_area
c_func
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|__init_begin
)paren
comma
(paren
r_int
r_int
)paren
(paren
op_amp
id|__init_end
)paren
comma
l_string|&quot;init&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
DECL|variable|keep_initrd
r_static
r_int
id|keep_initrd
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
id|keep_initrd
)paren
id|free_area
c_func
(paren
id|start
comma
id|end
comma
l_string|&quot;initrd&quot;
)paren
suffix:semicolon
)brace
DECL|function|keepinitrd_setup
r_static
r_int
id|__init
id|keepinitrd_setup
c_func
(paren
r_char
op_star
id|__unused
)paren
(brace
id|keep_initrd
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;keepinitrd&quot;
comma
id|keepinitrd_setup
)paren
suffix:semicolon
macro_line|#endif
eof
