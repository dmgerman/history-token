multiline_comment|/*&n; * Written by: Patricia Gaughen &lt;gone@us.ibm.com&gt;, IBM Corporation&n; * August 2002: added remote node KVA remap - Martin J. Bligh &n; *&n; * Copyright (C) 2002, IBM Corp.&n; *&n; * All rights reserved.          &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_RAM
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/e820.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
DECL|variable|node_data
r_struct
id|pglist_data
op_star
id|node_data
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
DECL|variable|node0_bdata
id|bootmem_data_t
id|node0_bdata
suffix:semicolon
r_extern
r_int
r_int
id|find_max_low_pfn
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|find_max_pfn
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|one_highpage_init
c_func
(paren
r_struct
id|page
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|node_start_pfn
(braket
)braket
comma
id|node_end_pfn
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|e820map
id|e820
suffix:semicolon
r_extern
r_char
id|_end
suffix:semicolon
r_extern
r_int
r_int
id|highend_pfn
comma
id|highstart_pfn
suffix:semicolon
r_extern
r_int
r_int
id|max_low_pfn
suffix:semicolon
r_extern
r_int
r_int
id|totalram_pages
suffix:semicolon
r_extern
r_int
r_int
id|totalhigh_pages
suffix:semicolon
multiline_comment|/*&n; * Find the highest page frame number we have available for the node&n; */
DECL|function|find_max_pfn_node
r_static
r_void
id|__init
id|find_max_pfn_node
c_func
(paren
r_int
id|nid
)paren
(brace
r_if
c_cond
(paren
id|node_start_pfn
(braket
id|nid
)braket
op_ge
id|node_end_pfn
(braket
id|nid
)braket
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node_end_pfn
(braket
id|nid
)braket
OG
id|max_pfn
)paren
id|node_end_pfn
(braket
id|nid
)braket
op_assign
id|max_pfn
suffix:semicolon
)brace
multiline_comment|/* &n; * Allocate memory for the pg_data_t via a crude pre-bootmem method&n; * We ought to relocate these onto their own node later on during boot.&n; */
DECL|function|allocate_pgdat
r_static
r_void
id|__init
id|allocate_pgdat
c_func
(paren
r_int
id|nid
)paren
(brace
r_int
r_int
id|node_datasz
suffix:semicolon
id|node_datasz
op_assign
id|PFN_UP
c_func
(paren
r_sizeof
(paren
r_struct
id|pglist_data
)paren
)paren
suffix:semicolon
id|NODE_DATA
c_func
(paren
id|nid
)paren
op_assign
(paren
id|pg_data_t
op_star
)paren
(paren
id|__va
c_func
(paren
id|min_low_pfn
op_lshift
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
id|min_low_pfn
op_add_assign
id|node_datasz
suffix:semicolon
id|memset
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nid
)paren
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pglist_data
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Register fully available low RAM pages with the bootmem allocator.&n; */
DECL|function|register_bootmem_low_pages
r_static
r_void
id|__init
id|register_bootmem_low_pages
c_func
(paren
r_int
r_int
id|system_max_low_pfn
)paren
(brace
r_int
id|i
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
id|e820.nr_map
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|curr_pfn
comma
id|last_pfn
comma
id|size
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Reserve usable low memory&n;&t;&t; */
r_if
c_cond
(paren
id|e820.map
(braket
id|i
)braket
dot
id|type
op_ne
id|E820_RAM
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We are rounding up the start address of usable memory:&n;&t;&t; */
id|curr_pfn
op_assign
id|PFN_UP
c_func
(paren
id|e820.map
(braket
id|i
)braket
dot
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curr_pfn
op_ge
id|system_max_low_pfn
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * ... and at the end of the usable range downwards:&n;&t;&t; */
id|last_pfn
op_assign
id|PFN_DOWN
c_func
(paren
id|e820.map
(braket
id|i
)braket
dot
id|addr
op_plus
id|e820.map
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
id|last_pfn
OG
id|system_max_low_pfn
)paren
id|last_pfn
op_assign
id|system_max_low_pfn
suffix:semicolon
multiline_comment|/*&n;&t;&t; * .. finally, did all the rounding and playing&n;&t;&t; * around just make the area go away?&n;&t;&t; */
r_if
c_cond
(paren
id|last_pfn
op_le
id|curr_pfn
)paren
r_continue
suffix:semicolon
id|size
op_assign
id|last_pfn
op_minus
id|curr_pfn
suffix:semicolon
id|free_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
id|PFN_PHYS
c_func
(paren
id|curr_pfn
)paren
comma
id|PFN_PHYS
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|macro|LARGE_PAGE_BYTES
mdefine_line|#define LARGE_PAGE_BYTES (PTRS_PER_PTE * PAGE_SIZE)
DECL|variable|node_remap_start_pfn
r_int
r_int
id|node_remap_start_pfn
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
DECL|variable|node_remap_size
r_int
r_int
id|node_remap_size
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
DECL|variable|node_remap_offset
r_int
r_int
id|node_remap_offset
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
DECL|variable|node_remap_start_vaddr
r_void
op_star
id|node_remap_start_vaddr
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
r_extern
r_void
id|set_pmd_pfn
c_func
(paren
r_int
r_int
id|vaddr
comma
r_int
r_int
id|pfn
comma
id|pgprot_t
id|flags
)paren
suffix:semicolon
DECL|function|remap_numa_kva
r_void
id|__init
id|remap_numa_kva
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|vaddr
suffix:semicolon
r_int
r_int
id|pfn
suffix:semicolon
r_int
id|node
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
l_int|1
suffix:semicolon
id|node
OL
id|numnodes
suffix:semicolon
op_increment
id|node
)paren
(brace
r_for
c_loop
(paren
id|pfn
op_assign
l_int|0
suffix:semicolon
id|pfn
OL
id|node_remap_size
(braket
id|node
)braket
suffix:semicolon
id|pfn
op_add_assign
id|PTRS_PER_PTE
)paren
(brace
id|vaddr
op_assign
id|node_remap_start_vaddr
(braket
id|node
)braket
op_plus
(paren
id|pfn
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|set_pmd_pfn
c_func
(paren
(paren
id|ulong
)paren
id|vaddr
comma
id|node_remap_start_pfn
(braket
id|node
)braket
op_plus
id|pfn
comma
id|PAGE_KERNEL_LARGE
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|calculate_numa_remap_pages
r_static
r_int
r_int
id|calculate_numa_remap_pages
c_func
(paren
r_void
)paren
(brace
r_int
id|nid
suffix:semicolon
r_int
r_int
id|size
comma
id|reserve_pages
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|nid
op_assign
l_int|1
suffix:semicolon
id|nid
OL
id|numnodes
suffix:semicolon
id|nid
op_increment
)paren
(brace
multiline_comment|/* calculate the size of the mem_map needed in bytes */
id|size
op_assign
(paren
id|node_end_pfn
(braket
id|nid
)braket
op_minus
id|node_start_pfn
(braket
id|nid
)braket
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|page
)paren
suffix:semicolon
multiline_comment|/* convert size to large (pmd size) pages, rounding up */
id|size
op_assign
(paren
id|size
op_plus
id|LARGE_PAGE_BYTES
op_minus
l_int|1
)paren
op_div
id|LARGE_PAGE_BYTES
suffix:semicolon
multiline_comment|/* now the roundup is correct, convert to PAGE_SIZE pages */
id|size
op_assign
id|size
op_star
id|PTRS_PER_PTE
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Reserving %ld pages of KVA for lmem_map of node %d&bslash;n&quot;
comma
id|size
comma
id|nid
)paren
suffix:semicolon
id|node_remap_size
(braket
id|nid
)braket
op_assign
id|size
suffix:semicolon
id|reserve_pages
op_add_assign
id|size
suffix:semicolon
id|node_remap_offset
(braket
id|nid
)braket
op_assign
id|reserve_pages
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Shrinking node %d from %ld pages to %ld pages&bslash;n&quot;
comma
id|nid
comma
id|node_end_pfn
(braket
id|nid
)braket
comma
id|node_end_pfn
(braket
id|nid
)braket
op_minus
id|size
)paren
suffix:semicolon
id|node_end_pfn
(braket
id|nid
)braket
op_sub_assign
id|size
suffix:semicolon
id|node_remap_start_pfn
(braket
id|nid
)braket
op_assign
id|node_end_pfn
(braket
id|nid
)braket
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Reserving total of %ld pages for numa KVA remap&bslash;n&quot;
comma
id|reserve_pages
)paren
suffix:semicolon
r_return
id|reserve_pages
suffix:semicolon
)brace
DECL|function|setup_memory
r_int
r_int
id|__init
id|setup_memory
c_func
(paren
r_void
)paren
(brace
r_int
id|nid
suffix:semicolon
r_int
r_int
id|bootmap_size
comma
id|system_start_pfn
comma
id|system_max_low_pfn
suffix:semicolon
r_int
r_int
id|reserve_pages
suffix:semicolon
id|get_memcfg_numa
c_func
(paren
)paren
suffix:semicolon
id|reserve_pages
op_assign
id|calculate_numa_remap_pages
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* partially used pages are not usable - thus round upwards */
id|system_start_pfn
op_assign
id|min_low_pfn
op_assign
id|PFN_UP
c_func
(paren
id|__pa
c_func
(paren
op_amp
id|_end
)paren
)paren
suffix:semicolon
id|find_max_pfn
c_func
(paren
)paren
suffix:semicolon
id|system_max_low_pfn
op_assign
id|max_low_pfn
op_assign
id|find_max_low_pfn
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
id|highstart_pfn
op_assign
id|highend_pfn
op_assign
id|max_pfn
suffix:semicolon
r_if
c_cond
(paren
id|max_pfn
OG
id|system_max_low_pfn
)paren
id|highstart_pfn
op_assign
id|system_max_low_pfn
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%ldMB HIGHMEM available.&bslash;n&quot;
comma
id|pages_to_mb
c_func
(paren
id|highend_pfn
op_minus
id|highstart_pfn
)paren
)paren
suffix:semicolon
macro_line|#endif
id|system_max_low_pfn
op_assign
id|max_low_pfn
op_assign
id|max_low_pfn
op_minus
id|reserve_pages
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%ldMB LOWMEM available.&bslash;n&quot;
comma
id|pages_to_mb
c_func
(paren
id|system_max_low_pfn
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;min_low_pfn = %ld, max_low_pfn = %ld, highstart_pfn = %ld&bslash;n&quot;
comma
id|min_low_pfn
comma
id|max_low_pfn
comma
id|highstart_pfn
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Low memory ends at vaddr %08lx&bslash;n&quot;
comma
(paren
id|ulong
)paren
id|pfn_to_kaddr
c_func
(paren
id|max_low_pfn
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|nid
op_assign
l_int|0
suffix:semicolon
id|nid
OL
id|numnodes
suffix:semicolon
id|nid
op_increment
)paren
(brace
id|allocate_pgdat
c_func
(paren
id|nid
)paren
suffix:semicolon
id|node_remap_start_vaddr
(braket
id|nid
)braket
op_assign
id|pfn_to_kaddr
c_func
(paren
id|highstart_pfn
op_minus
id|node_remap_offset
(braket
id|nid
)braket
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;node %d will remap to vaddr %08lx - %08lx&bslash;n&quot;
comma
id|nid
comma
(paren
id|ulong
)paren
id|node_remap_start_vaddr
(braket
id|nid
)braket
comma
(paren
id|ulong
)paren
id|pfn_to_kaddr
c_func
(paren
id|highstart_pfn
op_minus
id|node_remap_offset
(braket
id|nid
)braket
op_plus
id|node_remap_size
(braket
id|nid
)braket
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;High memory starts at vaddr %08lx&bslash;n&quot;
comma
(paren
id|ulong
)paren
id|pfn_to_kaddr
c_func
(paren
id|highstart_pfn
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|nid
op_assign
l_int|0
suffix:semicolon
id|nid
OL
id|numnodes
suffix:semicolon
id|nid
op_increment
)paren
id|find_max_pfn_node
c_func
(paren
id|nid
)paren
suffix:semicolon
id|NODE_DATA
c_func
(paren
l_int|0
)paren
op_member_access_from_pointer
id|bdata
op_assign
op_amp
id|node0_bdata
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the boot-time allocator (with low memory only):&n;&t; */
id|bootmap_size
op_assign
id|init_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
id|min_low_pfn
comma
l_int|0
comma
id|system_max_low_pfn
)paren
suffix:semicolon
id|register_bootmem_low_pages
c_func
(paren
id|system_max_low_pfn
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Reserve the bootmem bitmap itself as well. We do this in two&n;&t; * steps (first step was init_bootmem()) because this catches&n;&t; * the (very unlikely) case of us accidentally initializing the&n;&t; * bootmem allocator with an invalid RAM area.&n;&t; */
id|reserve_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
id|HIGH_MEMORY
comma
(paren
id|PFN_PHYS
c_func
(paren
id|min_low_pfn
)paren
op_plus
id|bootmap_size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_minus
(paren
id|HIGH_MEMORY
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * reserve physical page 0 - it&squot;s a special BIOS page on many boxes,&n;&t; * enabling clean reboots, SMP operation, laptop functions.&n;&t; */
id|reserve_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * But first pinch a few for the stack/trampoline stuff&n;&t; * FIXME: Don&squot;t need the extra page at 4K, but need to fix&n;&t; * trampoline before removing it. (see the GDT stuff)&n;&t; */
id|reserve_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
id|PAGE_SIZE
comma
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ACPI_SLEEP
multiline_comment|/*&n;&t; * Reserve low memory region for sleep support.&n;&t; */
id|acpi_reserve_bootmem
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Find and reserve possible boot-time SMP configuration:&n;&t; */
id|find_smp_config
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*insert other nodes into pgdat_list*/
r_for
c_loop
(paren
id|nid
op_assign
l_int|1
suffix:semicolon
id|nid
OL
id|numnodes
suffix:semicolon
id|nid
op_increment
)paren
(brace
id|NODE_DATA
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|pgdat_next
op_assign
id|pgdat_list
suffix:semicolon
id|pgdat_list
op_assign
id|NODE_DATA
c_func
(paren
id|nid
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|LOADER_TYPE
op_logical_and
id|INITRD_START
)paren
(brace
r_if
c_cond
(paren
id|INITRD_START
op_plus
id|INITRD_SIZE
op_le
(paren
id|system_max_low_pfn
op_lshift
id|PAGE_SHIFT
)paren
)paren
(brace
id|reserve_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
id|INITRD_START
comma
id|INITRD_SIZE
)paren
suffix:semicolon
id|initrd_start
op_assign
id|INITRD_START
ques
c_cond
id|INITRD_START
op_plus
id|PAGE_OFFSET
suffix:colon
l_int|0
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|INITRD_SIZE
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;initrd extends beyond end of memory &quot;
l_string|&quot;(0x%08lx &gt; 0x%08lx)&bslash;ndisabling initrd&bslash;n&quot;
comma
id|INITRD_START
op_plus
id|INITRD_SIZE
comma
id|system_max_low_pfn
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|initrd_start
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
id|system_max_low_pfn
suffix:semicolon
)brace
DECL|function|zone_sizes_init
r_void
id|__init
id|zone_sizes_init
c_func
(paren
r_void
)paren
(brace
r_int
id|nid
suffix:semicolon
r_for
c_loop
(paren
id|nid
op_assign
l_int|0
suffix:semicolon
id|nid
OL
id|numnodes
suffix:semicolon
id|nid
op_increment
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
op_assign
id|max_low_pfn
suffix:semicolon
r_int
r_int
id|start
op_assign
id|node_start_pfn
(braket
id|nid
)braket
suffix:semicolon
r_int
r_int
id|high
op_assign
id|node_end_pfn
(braket
id|nid
)braket
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
r_if
c_cond
(paren
id|start
OG
id|low
)paren
(brace
macro_line|#ifdef CONFIG_HIGHMEM
id|zones_size
(braket
id|ZONE_HIGHMEM
)braket
op_assign
id|high
op_minus
id|start
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
r_if
c_cond
(paren
id|low
OL
id|max_dma
)paren
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|low
suffix:semicolon
r_else
(brace
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|max_dma
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
macro_line|#ifdef CONFIG_HIGHMEM
id|zones_size
(braket
id|ZONE_HIGHMEM
)braket
op_assign
id|high
op_minus
id|low
suffix:semicolon
macro_line|#endif
)brace
)brace
multiline_comment|/*&n;&t;&t; * We let the lmem_map for node 0 be allocated from the&n;&t;&t; * normal bootmem allocator, but other nodes come from the&n;&t;&t; * remapped KVA area - mbligh&n;&t;&t; */
r_if
c_cond
(paren
id|nid
)paren
id|free_area_init_node
c_func
(paren
id|nid
comma
id|NODE_DATA
c_func
(paren
id|nid
)paren
comma
id|node_remap_start_vaddr
(braket
id|nid
)braket
comma
id|zones_size
comma
id|start
comma
l_int|0
)paren
suffix:semicolon
r_else
id|free_area_init_node
c_func
(paren
id|nid
comma
id|NODE_DATA
c_func
(paren
id|nid
)paren
comma
l_int|0
comma
id|zones_size
comma
id|start
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|set_highmem_pages_init
r_void
id|__init
id|set_highmem_pages_init
c_func
(paren
r_int
id|bad_ppro
)paren
(brace
macro_line|#ifdef CONFIG_HIGHMEM
r_int
id|nid
suffix:semicolon
r_for
c_loop
(paren
id|nid
op_assign
l_int|0
suffix:semicolon
id|nid
OL
id|numnodes
suffix:semicolon
id|nid
op_increment
)paren
(brace
r_int
r_int
id|node_pfn
comma
id|node_high_size
comma
id|zone_start_pfn
suffix:semicolon
r_struct
id|page
op_star
id|zone_mem_map
suffix:semicolon
id|node_high_size
op_assign
id|NODE_DATA
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|node_zones
(braket
id|ZONE_HIGHMEM
)braket
dot
id|spanned_pages
suffix:semicolon
id|zone_mem_map
op_assign
id|NODE_DATA
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|node_zones
(braket
id|ZONE_HIGHMEM
)braket
dot
id|zone_mem_map
suffix:semicolon
id|zone_start_pfn
op_assign
id|NODE_DATA
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|node_zones
(braket
id|ZONE_HIGHMEM
)braket
dot
id|zone_start_pfn
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Initializing highpages for node %d&bslash;n&quot;
comma
id|nid
)paren
suffix:semicolon
r_for
c_loop
(paren
id|node_pfn
op_assign
l_int|0
suffix:semicolon
id|node_pfn
OL
id|node_high_size
suffix:semicolon
id|node_pfn
op_increment
)paren
(brace
id|one_highpage_init
c_func
(paren
(paren
r_struct
id|page
op_star
)paren
(paren
id|zone_mem_map
op_plus
id|node_pfn
)paren
comma
id|zone_start_pfn
op_plus
id|node_pfn
comma
id|bad_ppro
)paren
suffix:semicolon
)brace
)brace
id|totalram_pages
op_add_assign
id|totalhigh_pages
suffix:semicolon
macro_line|#endif
)brace
DECL|function|set_max_mapnr_init
r_void
id|__init
id|set_max_mapnr_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_HIGHMEM
id|highmem_start_page
op_assign
id|NODE_DATA
c_func
(paren
l_int|0
)paren
op_member_access_from_pointer
id|node_zones
(braket
id|ZONE_HIGHMEM
)braket
dot
id|zone_mem_map
suffix:semicolon
id|num_physpages
op_assign
id|highend_pfn
suffix:semicolon
macro_line|#else
id|num_physpages
op_assign
id|max_low_pfn
suffix:semicolon
macro_line|#endif
)brace
eof
