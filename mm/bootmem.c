multiline_comment|/*&n; *  linux/mm/bootmem.c&n; *&n; *  Copyright (C) 1999 Ingo Molnar&n; *  Discontiguous memory support, Kanoj Sarcar, SGI, Nov 1999&n; *&n; *  simple boot-time physical memory area allocator and&n; *  free memory collector. It&squot;s used to deal with reserved&n; *  system memory and memory holes as well.&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;internal.h&quot;
multiline_comment|/*&n; * Access to this subsystem has to be serialized externally. (this is&n; * true for the boot process anyway)&n; */
DECL|variable|max_low_pfn
r_int
r_int
id|max_low_pfn
suffix:semicolon
DECL|variable|min_low_pfn
r_int
r_int
id|min_low_pfn
suffix:semicolon
DECL|variable|max_pfn
r_int
r_int
id|max_pfn
suffix:semicolon
DECL|variable|max_pfn
id|EXPORT_SYMBOL
c_func
(paren
id|max_pfn
)paren
suffix:semicolon
multiline_comment|/* This is exported so&n;&t;&t;&t;&t; * dma_get_required_mask(), which uses&n;&t;&t;&t;&t; * it, can be an inline function */
multiline_comment|/* return the number of _pages_ that will be allocated for the boot bitmap */
DECL|function|bootmem_bootmap_pages
r_int
r_int
id|__init
id|bootmem_bootmap_pages
(paren
r_int
r_int
id|pages
)paren
(brace
r_int
r_int
id|mapsize
suffix:semicolon
id|mapsize
op_assign
(paren
id|pages
op_plus
l_int|7
)paren
op_div
l_int|8
suffix:semicolon
id|mapsize
op_assign
(paren
id|mapsize
op_plus
op_complement
id|PAGE_MASK
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
id|mapsize
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
r_return
id|mapsize
suffix:semicolon
)brace
multiline_comment|/*&n; * Called once to set up the allocator itself.&n; */
DECL|function|init_bootmem_core
r_static
r_int
r_int
id|__init
id|init_bootmem_core
(paren
id|pg_data_t
op_star
id|pgdat
comma
r_int
r_int
id|mapstart
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
id|bootmem_data_t
op_star
id|bdata
op_assign
id|pgdat-&gt;bdata
suffix:semicolon
r_int
r_int
id|mapsize
op_assign
(paren
(paren
id|end
op_minus
id|start
)paren
op_plus
l_int|7
)paren
op_div
l_int|8
suffix:semicolon
id|pgdat-&gt;pgdat_next
op_assign
id|pgdat_list
suffix:semicolon
id|pgdat_list
op_assign
id|pgdat
suffix:semicolon
id|mapsize
op_assign
(paren
id|mapsize
op_plus
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1UL
)paren
)paren
op_amp
op_complement
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1UL
)paren
suffix:semicolon
id|bdata-&gt;node_bootmem_map
op_assign
id|phys_to_virt
c_func
(paren
id|mapstart
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|bdata-&gt;node_boot_start
op_assign
(paren
id|start
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|bdata-&gt;node_low_pfn
op_assign
id|end
suffix:semicolon
multiline_comment|/*&n;&t; * Initially all pages are reserved - setup_arch() has to&n;&t; * register free RAM areas explicitly.&n;&t; */
id|memset
c_func
(paren
id|bdata-&gt;node_bootmem_map
comma
l_int|0xff
comma
id|mapsize
)paren
suffix:semicolon
r_return
id|mapsize
suffix:semicolon
)brace
multiline_comment|/*&n; * Marks a particular physical memory range as unallocatable. Usable RAM&n; * might be used for boot-time allocations - or it might get added&n; * to the free page pool later on.&n; */
DECL|function|reserve_bootmem_core
r_static
r_void
id|__init
id|reserve_bootmem_core
c_func
(paren
id|bootmem_data_t
op_star
id|bdata
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * round up, partially reserved pages are considered&n;&t; * fully reserved.&n;&t; */
r_int
r_int
id|sidx
op_assign
(paren
id|addr
op_minus
id|bdata-&gt;node_boot_start
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
r_int
r_int
id|eidx
op_assign
(paren
id|addr
op_plus
id|size
op_minus
id|bdata-&gt;node_boot_start
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
r_int
r_int
id|end
op_assign
(paren
id|addr
op_plus
id|size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|size
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|sidx
op_ge
id|eidx
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
(paren
id|addr
op_rshift
id|PAGE_SHIFT
)paren
op_ge
id|bdata-&gt;node_low_pfn
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|end
OG
id|bdata-&gt;node_low_pfn
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|sidx
suffix:semicolon
id|i
OL
id|eidx
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|i
comma
id|bdata-&gt;node_bootmem_map
)paren
)paren
(brace
macro_line|#ifdef CONFIG_DEBUG_BOOTMEM
id|printk
c_func
(paren
l_string|&quot;hm, page %08lx reserved twice.&bslash;n&quot;
comma
id|i
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|function|free_bootmem_core
r_static
r_void
id|__init
id|free_bootmem_core
c_func
(paren
id|bootmem_data_t
op_star
id|bdata
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_int
r_int
id|start
suffix:semicolon
multiline_comment|/*&n;&t; * round down end of usable mem, partially free pages are&n;&t; * considered reserved.&n;&t; */
r_int
r_int
id|sidx
suffix:semicolon
r_int
r_int
id|eidx
op_assign
(paren
id|addr
op_plus
id|size
op_minus
id|bdata-&gt;node_boot_start
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
r_int
r_int
id|end
op_assign
(paren
id|addr
op_plus
id|size
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|size
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|end
OG
id|bdata-&gt;node_low_pfn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|bdata-&gt;last_success
)paren
id|bdata-&gt;last_success
op_assign
id|addr
suffix:semicolon
multiline_comment|/*&n;&t; * Round up the beginning of the address.&n;&t; */
id|start
op_assign
(paren
id|addr
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
id|sidx
op_assign
id|start
op_minus
(paren
id|bdata-&gt;node_boot_start
op_div
id|PAGE_SIZE
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|sidx
suffix:semicolon
id|i
OL
id|eidx
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|test_and_clear_bit
c_func
(paren
id|i
comma
id|bdata-&gt;node_bootmem_map
)paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * We &squot;merge&squot; subsequent allocations to save space. We might &squot;lose&squot;&n; * some fraction of a page if allocations cannot be satisfied due to&n; * size constraints on boxes where there is physical RAM space&n; * fragmentation - in these cases (mostly large memory boxes) this&n; * is not a problem.&n; *&n; * On low memory boxes we get it right in 100% of the cases.&n; *&n; * alignment has to be a power of 2 value.&n; *&n; * NOTE:  This function is _not_ reentrant.&n; */
r_static
r_void
op_star
id|__init
DECL|function|__alloc_bootmem_core
id|__alloc_bootmem_core
c_func
(paren
r_struct
id|bootmem_data
op_star
id|bdata
comma
r_int
r_int
id|size
comma
r_int
r_int
id|align
comma
r_int
r_int
id|goal
)paren
(brace
r_int
r_int
id|offset
comma
id|remaining_size
comma
id|areasize
comma
id|preferred
suffix:semicolon
r_int
r_int
id|i
comma
id|start
op_assign
l_int|0
comma
id|incr
comma
id|eidx
suffix:semicolon
r_void
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;__alloc_bootmem_core(): zero-sized request&bslash;n&quot;
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|BUG_ON
c_func
(paren
id|align
op_amp
(paren
id|align
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|eidx
op_assign
id|bdata-&gt;node_low_pfn
op_minus
(paren
id|bdata-&gt;node_boot_start
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|align
op_logical_and
(paren
id|bdata-&gt;node_boot_start
op_amp
(paren
id|align
op_minus
l_int|1UL
)paren
)paren
op_ne
l_int|0
)paren
id|offset
op_assign
(paren
id|align
op_minus
(paren
id|bdata-&gt;node_boot_start
op_amp
(paren
id|align
op_minus
l_int|1UL
)paren
)paren
)paren
suffix:semicolon
id|offset
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/*&n;&t; * We try to allocate bootmem pages above &squot;goal&squot;&n;&t; * first, then we try to allocate lower pages.&n;&t; */
r_if
c_cond
(paren
id|goal
op_logical_and
(paren
id|goal
op_ge
id|bdata-&gt;node_boot_start
)paren
op_logical_and
(paren
(paren
id|goal
op_rshift
id|PAGE_SHIFT
)paren
OL
id|bdata-&gt;node_low_pfn
)paren
)paren
(brace
id|preferred
op_assign
id|goal
op_minus
id|bdata-&gt;node_boot_start
suffix:semicolon
r_if
c_cond
(paren
id|bdata-&gt;last_success
op_ge
id|preferred
)paren
id|preferred
op_assign
id|bdata-&gt;last_success
suffix:semicolon
)brace
r_else
id|preferred
op_assign
l_int|0
suffix:semicolon
id|preferred
op_assign
(paren
(paren
id|preferred
op_plus
id|align
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|align
op_minus
l_int|1
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|preferred
op_add_assign
id|offset
suffix:semicolon
id|areasize
op_assign
(paren
id|size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
id|incr
op_assign
id|align
op_rshift
id|PAGE_SHIFT
ques
c_cond
suffix:colon
l_int|1
suffix:semicolon
id|restart_scan
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
id|preferred
suffix:semicolon
id|i
OL
id|eidx
suffix:semicolon
id|i
op_add_assign
id|incr
)paren
(brace
r_int
r_int
id|j
suffix:semicolon
id|i
op_assign
id|find_next_zero_bit
c_func
(paren
id|bdata-&gt;node_bootmem_map
comma
id|eidx
comma
id|i
)paren
suffix:semicolon
id|i
op_assign
id|ALIGN
c_func
(paren
id|i
comma
id|incr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
comma
id|bdata-&gt;node_bootmem_map
)paren
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
id|j
OL
id|i
op_plus
id|areasize
suffix:semicolon
op_increment
id|j
)paren
(brace
r_if
c_cond
(paren
id|j
op_ge
id|eidx
)paren
r_goto
id|fail_block
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
(paren
id|j
comma
id|bdata-&gt;node_bootmem_map
)paren
)paren
r_goto
id|fail_block
suffix:semicolon
)brace
id|start
op_assign
id|i
suffix:semicolon
r_goto
id|found
suffix:semicolon
id|fail_block
suffix:colon
id|i
op_assign
id|ALIGN
c_func
(paren
id|j
comma
id|incr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|preferred
OG
id|offset
)paren
(brace
id|preferred
op_assign
id|offset
suffix:semicolon
r_goto
id|restart_scan
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
id|found
suffix:colon
id|bdata-&gt;last_success
op_assign
id|start
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|BUG_ON
c_func
(paren
id|start
op_ge
id|eidx
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Is the next page of the previous allocation-end the start&n;&t; * of this allocation&squot;s buffer? If yes then we can &squot;merge&squot;&n;&t; * the previous partial page with this allocation.&n;&t; */
r_if
c_cond
(paren
id|align
OL
id|PAGE_SIZE
op_logical_and
id|bdata-&gt;last_offset
op_logical_and
id|bdata-&gt;last_pos
op_plus
l_int|1
op_eq
id|start
)paren
(brace
id|offset
op_assign
(paren
id|bdata-&gt;last_offset
op_plus
id|align
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|align
op_minus
l_int|1
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|offset
OG
id|PAGE_SIZE
)paren
suffix:semicolon
id|remaining_size
op_assign
id|PAGE_SIZE
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
id|remaining_size
)paren
(brace
id|areasize
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* last_pos unchanged */
id|bdata-&gt;last_offset
op_assign
id|offset
op_plus
id|size
suffix:semicolon
id|ret
op_assign
id|phys_to_virt
c_func
(paren
id|bdata-&gt;last_pos
op_star
id|PAGE_SIZE
op_plus
id|offset
op_plus
id|bdata-&gt;node_boot_start
)paren
suffix:semicolon
)brace
r_else
(brace
id|remaining_size
op_assign
id|size
op_minus
id|remaining_size
suffix:semicolon
id|areasize
op_assign
(paren
id|remaining_size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
id|ret
op_assign
id|phys_to_virt
c_func
(paren
id|bdata-&gt;last_pos
op_star
id|PAGE_SIZE
op_plus
id|offset
op_plus
id|bdata-&gt;node_boot_start
)paren
suffix:semicolon
id|bdata-&gt;last_pos
op_assign
id|start
op_plus
id|areasize
op_minus
l_int|1
suffix:semicolon
id|bdata-&gt;last_offset
op_assign
id|remaining_size
suffix:semicolon
)brace
id|bdata-&gt;last_offset
op_and_assign
op_complement
id|PAGE_MASK
suffix:semicolon
)brace
r_else
(brace
id|bdata-&gt;last_pos
op_assign
id|start
op_plus
id|areasize
op_minus
l_int|1
suffix:semicolon
id|bdata-&gt;last_offset
op_assign
id|size
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|ret
op_assign
id|phys_to_virt
c_func
(paren
id|start
op_star
id|PAGE_SIZE
op_plus
id|bdata-&gt;node_boot_start
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Reserve the area now:&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
id|start
suffix:semicolon
id|i
OL
id|start
op_plus
id|areasize
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|test_and_set_bit
c_func
(paren
id|i
comma
id|bdata-&gt;node_bootmem_map
)paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ret
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|free_all_bootmem_core
r_static
r_int
r_int
id|__init
id|free_all_bootmem_core
c_func
(paren
id|pg_data_t
op_star
id|pgdat
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|bootmem_data_t
op_star
id|bdata
op_assign
id|pgdat-&gt;bdata
suffix:semicolon
r_int
r_int
id|i
comma
id|count
comma
id|total
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|idx
suffix:semicolon
r_int
r_int
op_star
id|map
suffix:semicolon
r_int
id|gofast
op_assign
l_int|0
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|bdata-&gt;node_bootmem_map
)paren
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* first extant page of the node */
id|page
op_assign
id|virt_to_page
c_func
(paren
id|phys_to_virt
c_func
(paren
id|bdata-&gt;node_boot_start
)paren
)paren
suffix:semicolon
id|idx
op_assign
id|bdata-&gt;node_low_pfn
op_minus
(paren
id|bdata-&gt;node_boot_start
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|map
op_assign
id|bdata-&gt;node_bootmem_map
suffix:semicolon
multiline_comment|/* Check physaddr is O(LOG2(BITS_PER_LONG)) page aligned */
r_if
c_cond
(paren
id|bdata-&gt;node_boot_start
op_eq
l_int|0
op_logical_or
id|ffs
c_func
(paren
id|bdata-&gt;node_boot_start
)paren
op_minus
id|PAGE_SHIFT
OG
id|ffs
c_func
(paren
id|BITS_PER_LONG
)paren
)paren
id|gofast
op_assign
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
id|idx
suffix:semicolon
)paren
(brace
r_int
r_int
id|v
op_assign
op_complement
id|map
(braket
id|i
op_div
id|BITS_PER_LONG
)braket
suffix:semicolon
r_if
c_cond
(paren
id|gofast
op_logical_and
id|v
op_eq
op_complement
l_int|0UL
)paren
(brace
r_int
id|j
comma
id|order
suffix:semicolon
id|count
op_add_assign
id|BITS_PER_LONG
suffix:semicolon
id|__ClearPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
id|order
op_assign
id|ffs
c_func
(paren
id|BITS_PER_LONG
)paren
op_minus
l_int|1
suffix:semicolon
id|set_page_refs
c_func
(paren
id|page
comma
id|order
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
id|BITS_PER_LONG
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|j
op_plus
l_int|16
OL
id|BITS_PER_LONG
)paren
id|prefetchw
c_func
(paren
id|page
op_plus
id|j
op_plus
l_int|16
)paren
suffix:semicolon
id|__ClearPageReserved
c_func
(paren
id|page
op_plus
id|j
)paren
suffix:semicolon
)brace
id|__free_pages
c_func
(paren
id|page
comma
id|order
)paren
suffix:semicolon
id|i
op_add_assign
id|BITS_PER_LONG
suffix:semicolon
id|page
op_add_assign
id|BITS_PER_LONG
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|v
)paren
(brace
r_int
r_int
id|m
suffix:semicolon
r_for
c_loop
(paren
id|m
op_assign
l_int|1
suffix:semicolon
id|m
op_logical_and
id|i
OL
id|idx
suffix:semicolon
id|m
op_lshift_assign
l_int|1
comma
id|page
op_increment
comma
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|v
op_amp
id|m
)paren
(brace
id|count
op_increment
suffix:semicolon
id|__ClearPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_page_refs
c_func
(paren
id|page
comma
l_int|0
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
id|i
op_add_assign
id|BITS_PER_LONG
suffix:semicolon
id|page
op_add_assign
id|BITS_PER_LONG
suffix:semicolon
)brace
)brace
id|total
op_add_assign
id|count
suffix:semicolon
multiline_comment|/*&n;&t; * Now free the allocator bitmap itself, it&squot;s not&n;&t; * needed anymore:&n;&t; */
id|page
op_assign
id|virt_to_page
c_func
(paren
id|bdata-&gt;node_bootmem_map
)paren
suffix:semicolon
id|count
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
(paren
(paren
id|bdata-&gt;node_low_pfn
op_minus
(paren
id|bdata-&gt;node_boot_start
op_rshift
id|PAGE_SHIFT
)paren
)paren
op_div
l_int|8
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
id|i
op_increment
comma
id|page
op_increment
)paren
(brace
id|count
op_increment
suffix:semicolon
id|__ClearPageReserved
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
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|total
op_add_assign
id|count
suffix:semicolon
id|bdata-&gt;node_bootmem_map
op_assign
l_int|NULL
suffix:semicolon
r_return
id|total
suffix:semicolon
)brace
DECL|function|init_bootmem_node
r_int
r_int
id|__init
id|init_bootmem_node
(paren
id|pg_data_t
op_star
id|pgdat
comma
r_int
r_int
id|freepfn
comma
r_int
r_int
id|startpfn
comma
r_int
r_int
id|endpfn
)paren
(brace
r_return
id|init_bootmem_core
c_func
(paren
id|pgdat
comma
id|freepfn
comma
id|startpfn
comma
id|endpfn
)paren
suffix:semicolon
)brace
DECL|function|reserve_bootmem_node
r_void
id|__init
id|reserve_bootmem_node
(paren
id|pg_data_t
op_star
id|pgdat
comma
r_int
r_int
id|physaddr
comma
r_int
r_int
id|size
)paren
(brace
id|reserve_bootmem_core
c_func
(paren
id|pgdat-&gt;bdata
comma
id|physaddr
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|free_bootmem_node
r_void
id|__init
id|free_bootmem_node
(paren
id|pg_data_t
op_star
id|pgdat
comma
r_int
r_int
id|physaddr
comma
r_int
r_int
id|size
)paren
(brace
id|free_bootmem_core
c_func
(paren
id|pgdat-&gt;bdata
comma
id|physaddr
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|free_all_bootmem_node
r_int
r_int
id|__init
id|free_all_bootmem_node
(paren
id|pg_data_t
op_star
id|pgdat
)paren
(brace
r_return
id|free_all_bootmem_core
c_func
(paren
id|pgdat
)paren
suffix:semicolon
)brace
DECL|function|init_bootmem
r_int
r_int
id|__init
id|init_bootmem
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|pages
)paren
(brace
id|max_low_pfn
op_assign
id|pages
suffix:semicolon
id|min_low_pfn
op_assign
id|start
suffix:semicolon
r_return
id|init_bootmem_core
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
id|start
comma
l_int|0
comma
id|pages
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_HAVE_ARCH_BOOTMEM_NODE
DECL|function|reserve_bootmem
r_void
id|__init
id|reserve_bootmem
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
id|reserve_bootmem_core
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
op_member_access_from_pointer
id|bdata
comma
id|addr
comma
id|size
)paren
suffix:semicolon
)brace
macro_line|#endif /* !CONFIG_HAVE_ARCH_BOOTMEM_NODE */
DECL|function|free_bootmem
r_void
id|__init
id|free_bootmem
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
id|free_bootmem_core
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
op_member_access_from_pointer
id|bdata
comma
id|addr
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|free_all_bootmem
r_int
r_int
id|__init
id|free_all_bootmem
(paren
r_void
)paren
(brace
r_return
id|free_all_bootmem_core
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
DECL|function|__alloc_bootmem
r_void
op_star
id|__init
id|__alloc_bootmem
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|align
comma
r_int
r_int
id|goal
)paren
(brace
id|pg_data_t
op_star
id|pgdat
op_assign
id|pgdat_list
suffix:semicolon
r_void
op_star
id|ptr
suffix:semicolon
id|for_each_pgdat
c_func
(paren
id|pgdat
)paren
r_if
c_cond
(paren
(paren
id|ptr
op_assign
id|__alloc_bootmem_core
c_func
(paren
id|pgdat-&gt;bdata
comma
id|size
comma
id|align
comma
id|goal
)paren
)paren
)paren
r_return
id|ptr
suffix:semicolon
multiline_comment|/*&n;&t; * Whoops, we cannot satisfy the allocation request.&n;&t; */
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;bootmem alloc of %lu bytes failed!&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Out of memory&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|__alloc_bootmem_node
r_void
op_star
id|__init
id|__alloc_bootmem_node
(paren
id|pg_data_t
op_star
id|pgdat
comma
r_int
r_int
id|size
comma
r_int
r_int
id|align
comma
r_int
r_int
id|goal
)paren
(brace
r_void
op_star
id|ptr
suffix:semicolon
id|ptr
op_assign
id|__alloc_bootmem_core
c_func
(paren
id|pgdat-&gt;bdata
comma
id|size
comma
id|align
comma
id|goal
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
)paren
r_return
(paren
id|ptr
)paren
suffix:semicolon
r_return
id|__alloc_bootmem
c_func
(paren
id|size
comma
id|align
comma
id|goal
)paren
suffix:semicolon
)brace
eof
