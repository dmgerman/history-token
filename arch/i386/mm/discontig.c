multiline_comment|/*&n; * Written by: Patricia Gaughen &lt;gone@us.ibm.com&gt;, IBM Corporation&n; * August 2002: added remote node KVA remap - Martin J. Bligh &n; *&n; * Copyright (C) 2002, IBM Corp.&n; *&n; * All rights reserved.          &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/nodemask.h&gt;
macro_line|#include &lt;asm/e820.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mmzone.h&gt;
macro_line|#include &lt;bios_ebda.h&gt;
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
multiline_comment|/*&n; * numa interface - we expect the numa architecture specfic code to have&n; *                  populated the following initialisation.&n; *&n; * 1) node_online_map  - the map of all nodes configured (online) in the system&n; * 2) physnode_map     - the mapping between a pfn and owning node&n; * 3) node_start_pfn   - the starting page frame number for a node&n; * 3) node_end_pfn     - the ending page fram number for a node&n; */
multiline_comment|/*&n; * physnode_map keeps track of the physical memory layout of a generic&n; * numa node on a 256Mb break (each element of the array will&n; * represent 256Mb of memory and will be marked by the node id.  so,&n; * if the first gig is on node 0, and the second gig is on node 1&n; * physnode_map will contain:&n; *&n; *     physnode_map[0-3] = 0;&n; *     physnode_map[4-7] = 1;&n; *     physnode_map[8- ] = -1;&n; */
DECL|variable|physnode_map
id|s8
id|physnode_map
(braket
id|MAX_ELEMENTS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
(paren
id|MAX_ELEMENTS
op_minus
l_int|1
)paren
)braket
op_assign
op_minus
l_int|1
)brace
suffix:semicolon
DECL|function|memory_present
r_void
id|memory_present
c_func
(paren
r_int
id|nid
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
id|pfn
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Node: %d, start_pfn: %ld, end_pfn: %ld&bslash;n&quot;
comma
id|nid
comma
id|start
comma
id|end
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;  Setting physnode_map array to node %d for pfns:&bslash;n&quot;
comma
id|nid
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;  &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pfn
op_assign
id|start
suffix:semicolon
id|pfn
OL
id|end
suffix:semicolon
id|pfn
op_add_assign
id|PAGES_PER_ELEMENT
)paren
(brace
id|physnode_map
(braket
id|pfn
op_div
id|PAGES_PER_ELEMENT
)braket
op_assign
id|nid
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%ld &quot;
comma
id|pfn
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|node_memmap_size_bytes
r_int
r_int
id|node_memmap_size_bytes
c_func
(paren
r_int
id|nid
comma
r_int
r_int
id|start_pfn
comma
r_int
r_int
id|end_pfn
)paren
(brace
r_int
r_int
id|nr_pages
op_assign
id|end_pfn
op_minus
id|start_pfn
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_pages
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
id|nr_pages
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
)brace
DECL|variable|node_start_pfn
r_int
r_int
id|node_start_pfn
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
DECL|variable|node_end_pfn
r_int
r_int
id|node_end_pfn
(braket
id|MAX_NUMNODES
)braket
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
r_struct
id|e820map
id|e820
suffix:semicolon
r_extern
r_int
r_int
id|init_pg_tables_end
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
multiline_comment|/*&n; * FLAT - support for basic PC memory model with discontig enabled, essentially&n; *        a single node with all available processors in it with a flat&n; *        memory map.&n; */
DECL|function|get_memcfg_numa_flat
r_int
id|__init
id|get_memcfg_numa_flat
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NUMA - single node, flat memory mode&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Run the memory configuration and find the top of memory. */
id|find_max_pfn
c_func
(paren
)paren
suffix:semicolon
id|node_start_pfn
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|node_end_pfn
(braket
l_int|0
)braket
op_assign
id|max_pfn
suffix:semicolon
id|memory_present
c_func
(paren
l_int|0
comma
l_int|0
comma
id|max_pfn
)paren
suffix:semicolon
multiline_comment|/* Indicate there is one node available. */
id|nodes_clear
c_func
(paren
id|node_online_map
)paren
suffix:semicolon
id|node_set_online
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
multiline_comment|/*&n;&t; * if a user has given mem=XXXX, then we need to make sure &n;&t; * that the node _starts_ before that, too, not just ends&n;&t; */
r_if
c_cond
(paren
id|node_start_pfn
(braket
id|nid
)braket
OG
id|max_pfn
)paren
id|node_start_pfn
(braket
id|nid
)braket
op_assign
id|max_pfn
suffix:semicolon
r_if
c_cond
(paren
id|node_start_pfn
(braket
id|nid
)braket
OG
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
)brace
multiline_comment|/* &n; * Allocate memory for the pg_data_t for this node via a crude pre-bootmem&n; * method.  For node zero take this from the bottom of memory, for&n; * subsequent nodes place them at node_remap_start_vaddr which contains&n; * node local data in physically node local memory.  See setup_memory()&n; * for details.&n; */
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
r_if
c_cond
(paren
id|nid
op_logical_and
id|node_has_online_mem
c_func
(paren
id|nid
)paren
)paren
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
id|node_remap_start_vaddr
(braket
id|nid
)braket
suffix:semicolon
r_else
(brace
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
id|PFN_UP
c_func
(paren
r_sizeof
(paren
id|pg_data_t
)paren
)paren
suffix:semicolon
)brace
)brace
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
id|for_each_online_node
c_func
(paren
id|node
)paren
(brace
r_if
c_cond
(paren
id|node
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
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
id|for_each_online_node
c_func
(paren
id|nid
)paren
(brace
r_if
c_cond
(paren
id|nid
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node_remap_size
(braket
id|nid
)braket
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The acpi/srat node info can show hot-add memroy zones&n;&t;&t; * where memory could be added but not currently present.&n;&t;&t; */
r_if
c_cond
(paren
id|node_start_pfn
(braket
id|nid
)braket
OG
id|max_pfn
)paren
r_continue
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
multiline_comment|/* ensure the remap includes space for the pgdat. */
id|size
op_assign
id|node_remap_size
(braket
id|nid
)braket
op_plus
r_sizeof
(paren
id|pg_data_t
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
r_extern
r_void
id|setup_bootmem_allocator
c_func
(paren
r_void
)paren
suffix:semicolon
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
id|system_start_pfn
comma
id|system_max_low_pfn
suffix:semicolon
r_int
r_int
id|reserve_pages
suffix:semicolon
multiline_comment|/*&n;&t; * When mapping a NUMA machine we allocate the node_mem_map arrays&n;&t; * from node local memory.  They are then mapped directly into KVA&n;&t; * between zone normal and vmalloc space.  Calculate the size of&n;&t; * this space and use it to adjust the boundry between ZONE_NORMAL&n;&t; * and ZONE_HIGHMEM.&n;&t; */
id|find_max_pfn
c_func
(paren
)paren
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
id|init_pg_tables_end
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
op_minus
id|reserve_pages
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;reserve_pages = %ld find_max_low_pfn() ~ %ld&bslash;n&quot;
comma
id|reserve_pages
comma
id|max_low_pfn
op_plus
id|reserve_pages
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;max_pfn = %ld&bslash;n&quot;
comma
id|max_pfn
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
id|for_each_online_node
c_func
(paren
id|nid
)paren
(brace
id|node_remap_start_vaddr
(braket
id|nid
)braket
op_assign
id|pfn_to_kaddr
c_func
(paren
(paren
id|highstart_pfn
op_plus
id|reserve_pages
)paren
op_minus
id|node_remap_offset
(braket
id|nid
)braket
)paren
suffix:semicolon
id|allocate_pgdat
c_func
(paren
id|nid
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
op_plus
id|reserve_pages
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
id|vmalloc_earlyreserve
op_assign
id|reserve_pages
op_star
id|PAGE_SIZE
suffix:semicolon
id|for_each_online_node
c_func
(paren
id|nid
)paren
id|find_max_pfn_node
c_func
(paren
id|nid
)paren
suffix:semicolon
id|memset
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
l_int|0
)paren
op_member_access_from_pointer
id|bdata
op_assign
op_amp
id|node0_bdata
suffix:semicolon
id|setup_bootmem_allocator
c_func
(paren
)paren
suffix:semicolon
r_return
id|max_low_pfn
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
multiline_comment|/*&n;&t; * Insert nodes into pgdat_list backward so they appear in order.&n;&t; * Clobber node 0&squot;s links and NULL out pgdat_list before starting.&n;&t; */
id|pgdat_list
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|nid
op_assign
id|MAX_NUMNODES
op_minus
l_int|1
suffix:semicolon
id|nid
op_ge
l_int|0
suffix:semicolon
id|nid
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|node_online
c_func
(paren
id|nid
)paren
)paren
r_continue
suffix:semicolon
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
id|for_each_online_node
c_func
(paren
id|nid
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
op_star
id|zholes_size
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
id|node_has_online_mem
c_func
(paren
id|nid
)paren
)paren
(brace
r_if
c_cond
(paren
id|start
OG
id|low
)paren
(brace
macro_line|#ifdef CONFIG_HIGHMEM
id|BUG_ON
c_func
(paren
id|start
OG
id|high
)paren
suffix:semicolon
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
id|BUG_ON
c_func
(paren
id|max_dma
OG
id|low
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|low
OG
id|high
)paren
suffix:semicolon
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
)brace
id|zholes_size
op_assign
id|get_zholes_size
c_func
(paren
id|nid
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We let the lmem_map for node 0 be allocated from the&n;&t;&t; * normal bootmem allocator, but other nodes come from the&n;&t;&t; * remapped KVA area - mbligh&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
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
id|zones_size
comma
id|start
comma
id|zholes_size
)paren
suffix:semicolon
r_else
(brace
r_int
r_int
id|lmem_map
suffix:semicolon
id|lmem_map
op_assign
(paren
r_int
r_int
)paren
id|node_remap_start_vaddr
(braket
id|nid
)braket
suffix:semicolon
id|lmem_map
op_add_assign
r_sizeof
(paren
id|pg_data_t
)paren
op_plus
id|PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
id|lmem_map
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|NODE_DATA
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|node_mem_map
op_assign
(paren
r_struct
id|page
op_star
)paren
id|lmem_map
suffix:semicolon
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
id|zones_size
comma
id|start
comma
id|zholes_size
)paren
suffix:semicolon
)brace
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
r_struct
id|zone
op_star
id|zone
suffix:semicolon
id|for_each_zone
c_func
(paren
id|zone
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
r_if
c_cond
(paren
op_logical_neg
id|is_highmem
c_func
(paren
id|zone
)paren
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Initializing %s for node %d&bslash;n&quot;
comma
id|zone-&gt;name
comma
id|zone-&gt;zone_pgdat-&gt;node_id
)paren
suffix:semicolon
id|node_high_size
op_assign
id|zone-&gt;spanned_pages
suffix:semicolon
id|zone_mem_map
op_assign
id|zone-&gt;zone_mem_map
suffix:semicolon
id|zone_start_pfn
op_assign
id|zone-&gt;zone_start_pfn
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
eof
