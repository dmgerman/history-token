multiline_comment|/*&n; * Copyright (c) 2000, 2003 Silicon Graphics, Inc.  All rights reserved.&n; * Copyright (c) 2001 Intel Corp.&n; * Copyright (c) 2001 Tony Luck &lt;tony.luck@intel.com&gt;&n; * Copyright (c) 2002 NEC Corp.&n; * Copyright (c) 2002 Kimio Suganuma &lt;k-suganuma@da.jp.nec.com&gt;&n; */
multiline_comment|/*&n; * Platform initialization for Discontig Memory&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/efi.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/meminit.h&gt;
macro_line|#include &lt;asm/numa.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
multiline_comment|/*&n; * Track per-node information needed to setup the boot memory allocator, the&n; * per-node areas, and the real VM.&n; */
DECL|struct|early_node_data
r_struct
id|early_node_data
(brace
DECL|member|node_data
r_struct
id|ia64_node_data
op_star
id|node_data
suffix:semicolon
DECL|member|pgdat
id|pg_data_t
op_star
id|pgdat
suffix:semicolon
DECL|member|pernode_addr
r_int
r_int
id|pernode_addr
suffix:semicolon
DECL|member|pernode_size
r_int
r_int
id|pernode_size
suffix:semicolon
DECL|member|bootmem_data
r_struct
id|bootmem_data
id|bootmem_data
suffix:semicolon
DECL|member|num_physpages
r_int
r_int
id|num_physpages
suffix:semicolon
DECL|member|num_dma_physpages
r_int
r_int
id|num_dma_physpages
suffix:semicolon
DECL|member|min_pfn
r_int
r_int
id|min_pfn
suffix:semicolon
DECL|member|max_pfn
r_int
r_int
id|max_pfn
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|early_node_data
id|mem_data
(braket
id|NR_NODES
)braket
id|__initdata
suffix:semicolon
multiline_comment|/**&n; * reassign_cpu_only_nodes - called from find_memory to move CPU-only nodes to a memory node&n; *&n; * This function will move nodes with only CPUs (no memory)&n; * to a node with memory which is at the minimum numa_slit distance.&n; * Any reassigments will result in the compression of the nodes&n; * and renumbering the nid values where appropriate.&n; * The static declarations below are to avoid large stack size which&n; * makes the code not re-entrant.&n; */
DECL|function|reassign_cpu_only_nodes
r_static
r_void
id|__init
id|reassign_cpu_only_nodes
c_func
(paren
r_void
)paren
(brace
r_struct
id|node_memblk_s
op_star
id|p
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|k
comma
id|nnode
comma
id|nid
comma
id|cpu
comma
id|cpunid
suffix:semicolon
id|u8
id|cslit
comma
id|slit
suffix:semicolon
r_static
id|DECLARE_BITMAP
c_func
(paren
id|nodes_with_mem
comma
id|NR_NODES
)paren
id|__initdata
suffix:semicolon
r_static
id|u8
id|numa_slit_fix
(braket
id|MAX_NUMNODES
op_star
id|MAX_NUMNODES
)braket
id|__initdata
suffix:semicolon
r_static
r_int
id|node_flip
(braket
id|NR_NODES
)braket
id|__initdata
suffix:semicolon
r_for
c_loop
(paren
id|nnode
op_assign
l_int|0
comma
id|p
op_assign
op_amp
id|node_memblk
(braket
l_int|0
)braket
suffix:semicolon
id|p
OL
op_amp
id|node_memblk
(braket
id|num_node_memblks
)braket
suffix:semicolon
id|p
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|p-&gt;nid
comma
(paren
r_void
op_star
)paren
id|nodes_with_mem
)paren
)paren
(brace
id|set_bit
c_func
(paren
id|p-&gt;nid
comma
(paren
r_void
op_star
)paren
id|nodes_with_mem
)paren
suffix:semicolon
id|nnode
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * All nids with memory.&n;&t; */
r_if
c_cond
(paren
id|nnode
op_eq
id|numnodes
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Change nids and attempt to migrate CPU-only nodes&n;&t; * to the best numa_slit (closest neighbor) possible.&n;&t; * For reassigned CPU nodes a nid can&squot;t be arrived at&n;&t; * until after this loop because the target nid&squot;s new&n;&t; * identity might not have been established yet. So&n;&t; * new nid values are fabricated above numnodes and&n;&t; * mapped back later to their true value.&n;&t; */
r_for
c_loop
(paren
id|nid
op_assign
l_int|0
comma
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
id|test_bit
c_func
(paren
id|i
comma
(paren
r_void
op_star
)paren
id|nodes_with_mem
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Save original nid value for numa_slit&n;&t;&t;&t; * fixup and node_cpuid reassignments.&n;&t;&t;&t; */
id|node_flip
(braket
id|nid
)braket
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|nid
)paren
(brace
id|nid
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|node_memblk
(braket
l_int|0
)braket
suffix:semicolon
id|p
OL
op_amp
id|node_memblk
(braket
id|num_node_memblks
)braket
suffix:semicolon
id|p
op_increment
)paren
r_if
c_cond
(paren
id|p-&gt;nid
op_eq
id|i
)paren
id|p-&gt;nid
op_assign
id|nid
suffix:semicolon
id|cpunid
op_assign
id|nid
suffix:semicolon
id|nid
op_increment
suffix:semicolon
)brace
r_else
id|cpunid
op_assign
id|numnodes
suffix:semicolon
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
r_if
c_cond
(paren
id|node_cpuid
(braket
id|cpu
)braket
dot
id|nid
op_eq
id|i
)paren
(brace
multiline_comment|/* For nodes not being reassigned just fix the cpu&squot;s nid. */
r_if
c_cond
(paren
id|cpunid
OL
id|numnodes
)paren
(brace
id|node_cpuid
(braket
id|cpu
)braket
dot
id|nid
op_assign
id|cpunid
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t;&t; * For nodes being reassigned, find best node by&n;&t;&t;&t;&t; * numa_slit information and then make a temporary&n;&t;&t;&t;&t; * nid value based on current nid and numnodes.&n;&t;&t;&t;&t; */
r_for
c_loop
(paren
id|slit
op_assign
l_int|0xff
comma
id|k
op_assign
id|numnodes
op_plus
id|numnodes
comma
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|numnodes
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|i
op_eq
id|j
)paren
r_continue
suffix:semicolon
r_else
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|j
comma
(paren
r_void
op_star
)paren
id|nodes_with_mem
)paren
)paren
(brace
id|cslit
op_assign
id|numa_slit
(braket
id|i
op_star
id|numnodes
op_plus
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cslit
OL
id|slit
)paren
(brace
id|k
op_assign
id|numnodes
op_plus
id|j
suffix:semicolon
id|slit
op_assign
id|cslit
suffix:semicolon
)brace
)brace
id|node_cpuid
(braket
id|cpu
)braket
dot
id|nid
op_assign
id|k
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Fixup temporary nid values for CPU-only nodes.&n;&t; */
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
r_if
c_cond
(paren
id|node_cpuid
(braket
id|cpu
)braket
dot
id|nid
op_eq
(paren
id|numnodes
op_plus
id|numnodes
)paren
)paren
id|node_cpuid
(braket
id|cpu
)braket
dot
id|nid
op_assign
id|nnode
op_minus
l_int|1
suffix:semicolon
r_else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nnode
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|node_flip
(braket
id|i
)braket
op_eq
(paren
id|node_cpuid
(braket
id|cpu
)braket
dot
id|nid
op_minus
id|numnodes
)paren
)paren
(brace
id|node_cpuid
(braket
id|cpu
)braket
dot
id|nid
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Fix numa_slit by compressing from larger&n;&t; * nid array to reduced nid array.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nnode
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|nnode
suffix:semicolon
id|j
op_increment
)paren
id|numa_slit_fix
(braket
id|i
op_star
id|nnode
op_plus
id|j
)braket
op_assign
id|numa_slit
(braket
id|node_flip
(braket
id|i
)braket
op_star
id|numnodes
op_plus
id|node_flip
(braket
id|j
)braket
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|numa_slit
comma
id|numa_slit_fix
comma
r_sizeof
(paren
id|numa_slit
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nnode
suffix:semicolon
id|i
OL
id|numnodes
suffix:semicolon
id|i
op_increment
)paren
id|node_set_offline
c_func
(paren
id|i
)paren
suffix:semicolon
id|numnodes
op_assign
id|nnode
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * To prevent cache aliasing effects, align per-node structures so that they&n; * start at addresses that are strided by node number.&n; */
DECL|macro|NODEDATA_ALIGN
mdefine_line|#define NODEDATA_ALIGN(addr, node)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((((addr) + 1024*1024-1) &amp; ~(1024*1024-1)) + (node)*PERCPU_PAGE_SIZE)
multiline_comment|/**&n; * build_node_maps - callback to setup bootmem structs for each node&n; * @start: physical start of range&n; * @len: length of range&n; * @node: node where this range resides&n; *&n; * We allocate a struct bootmem_data for each piece of memory that we wish to&n; * treat as a virtually contiguous block (i.e. each node). Each such block&n; * must start on an %IA64_GRANULE_SIZE boundary, so we round the address down&n; * if necessary.  Any non-existent pages will simply be part of the virtual&n; * memmap.  We also update min_low_pfn and max_low_pfn here as we receive&n; * memory ranges from the caller.&n; */
DECL|function|build_node_maps
r_static
r_int
id|__init
id|build_node_maps
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|len
comma
r_int
id|node
)paren
(brace
r_int
r_int
id|cstart
comma
id|epfn
comma
id|end
op_assign
id|start
op_plus
id|len
suffix:semicolon
r_struct
id|bootmem_data
op_star
id|bdp
op_assign
op_amp
id|mem_data
(braket
id|node
)braket
dot
id|bootmem_data
suffix:semicolon
id|epfn
op_assign
id|GRANULEROUNDUP
c_func
(paren
id|end
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|cstart
op_assign
id|GRANULEROUNDDOWN
c_func
(paren
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdp-&gt;node_low_pfn
)paren
(brace
id|bdp-&gt;node_boot_start
op_assign
id|cstart
suffix:semicolon
id|bdp-&gt;node_low_pfn
op_assign
id|epfn
suffix:semicolon
)brace
r_else
(brace
id|bdp-&gt;node_boot_start
op_assign
id|min
c_func
(paren
id|cstart
comma
id|bdp-&gt;node_boot_start
)paren
suffix:semicolon
id|bdp-&gt;node_low_pfn
op_assign
id|max
c_func
(paren
id|epfn
comma
id|bdp-&gt;node_low_pfn
)paren
suffix:semicolon
)brace
id|min_low_pfn
op_assign
id|min
c_func
(paren
id|min_low_pfn
comma
id|bdp-&gt;node_boot_start
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|max_low_pfn
op_assign
id|max
c_func
(paren
id|max_low_pfn
comma
id|bdp-&gt;node_low_pfn
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * early_nr_cpus_node - return number of cpus on a given node&n; * @node: node to check&n; *&n; * Count the number of cpus on @node.  We can&squot;t use nr_cpus_node() yet because&n; * acpi_boot_init() (which builds the node_to_cpu_mask array) hasn&squot;t been&n; * called yet.&n; */
DECL|function|early_nr_cpus_node
r_static
r_int
id|early_nr_cpus_node
c_func
(paren
r_int
id|node
)paren
(brace
r_int
id|cpu
comma
id|n
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
r_if
c_cond
(paren
id|node
op_eq
id|node_cpuid
(braket
id|cpu
)braket
dot
id|nid
)paren
id|n
op_increment
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
multiline_comment|/**&n; * find_pernode_space - allocate memory for memory map and per-node structures&n; * @start: physical start of range&n; * @len: length of range&n; * @node: node where this range resides&n; *&n; * This routine reserves space for the per-cpu data struct, the list of&n; * pg_data_ts and the per-node data struct.  Each node will have something like&n; * the following in the first chunk of addr. space large enough to hold it.&n; *&n; *    ________________________&n; *   |                        |&n; *   |~~~~~~~~~~~~~~~~~~~~~~~~| &lt;-- NODEDATA_ALIGN(start, node) for the first&n; *   |    PERCPU_PAGE_SIZE *  |     start and length big enough&n; *   |        NR_CPUS         |&n; *   |------------------------|&n; *   |   local pg_data_t *    |&n; *   |------------------------|&n; *   |  local ia64_node_data  |&n; *   |------------------------|&n; *   |          ???           |&n; *   |________________________|&n; *&n; * Once this space has been set aside, the bootmem maps are initialized.  We&n; * could probably move the allocation of the per-cpu and ia64_node_data space&n; * outside of this function and use alloc_bootmem_node(), but doing it here&n; * is straightforward and we get the alignments we want so...&n; */
DECL|function|find_pernode_space
r_static
r_int
id|__init
id|find_pernode_space
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|len
comma
r_int
id|node
)paren
(brace
r_int
r_int
id|epfn
comma
id|cpu
comma
id|cpus
suffix:semicolon
r_int
r_int
id|pernodesize
op_assign
l_int|0
comma
id|pernode
comma
id|pages
comma
id|mapsize
suffix:semicolon
r_void
op_star
id|cpu_data
suffix:semicolon
r_struct
id|bootmem_data
op_star
id|bdp
op_assign
op_amp
id|mem_data
(braket
id|node
)braket
dot
id|bootmem_data
suffix:semicolon
id|epfn
op_assign
(paren
id|start
op_plus
id|len
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|pages
op_assign
id|bdp-&gt;node_low_pfn
op_minus
(paren
id|bdp-&gt;node_boot_start
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|mapsize
op_assign
id|bootmem_bootmap_pages
c_func
(paren
id|pages
)paren
op_lshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure this memory falls within this node&squot;s usable memory&n;&t; * since we may have thrown some away in build_maps().&n;&t; */
r_if
c_cond
(paren
id|start
template_param
id|bdp-&gt;node_low_pfn
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Don&squot;t setup this node&squot;s local space twice... */
r_if
c_cond
(paren
id|mem_data
(braket
id|node
)braket
dot
id|pernode_addr
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Calculate total size needed, incl. what&squot;s necessary&n;&t; * for good alignment and alias prevention.&n;&t; */
id|cpus
op_assign
id|early_nr_cpus_node
c_func
(paren
id|node
)paren
suffix:semicolon
id|pernodesize
op_add_assign
id|PERCPU_PAGE_SIZE
op_star
id|cpus
suffix:semicolon
id|pernodesize
op_add_assign
id|L1_CACHE_ALIGN
c_func
(paren
r_sizeof
(paren
id|pg_data_t
)paren
)paren
suffix:semicolon
id|pernodesize
op_add_assign
id|L1_CACHE_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ia64_node_data
)paren
)paren
suffix:semicolon
id|pernodesize
op_assign
id|PAGE_ALIGN
c_func
(paren
id|pernodesize
)paren
suffix:semicolon
id|pernode
op_assign
id|NODEDATA_ALIGN
c_func
(paren
id|start
comma
id|node
)paren
suffix:semicolon
multiline_comment|/* Is this range big enough for what we want to store here? */
r_if
c_cond
(paren
id|start
op_plus
id|len
OG
(paren
id|pernode
op_plus
id|pernodesize
op_plus
id|mapsize
)paren
)paren
(brace
id|mem_data
(braket
id|node
)braket
dot
id|pernode_addr
op_assign
id|pernode
suffix:semicolon
id|mem_data
(braket
id|node
)braket
dot
id|pernode_size
op_assign
id|pernodesize
suffix:semicolon
id|memset
c_func
(paren
id|__va
c_func
(paren
id|pernode
)paren
comma
l_int|0
comma
id|pernodesize
)paren
suffix:semicolon
id|cpu_data
op_assign
(paren
r_void
op_star
)paren
id|pernode
suffix:semicolon
id|pernode
op_add_assign
id|PERCPU_PAGE_SIZE
op_star
id|cpus
suffix:semicolon
id|mem_data
(braket
id|node
)braket
dot
id|pgdat
op_assign
id|__va
c_func
(paren
id|pernode
)paren
suffix:semicolon
id|pernode
op_add_assign
id|L1_CACHE_ALIGN
c_func
(paren
r_sizeof
(paren
id|pg_data_t
)paren
)paren
suffix:semicolon
id|mem_data
(braket
id|node
)braket
dot
id|node_data
op_assign
id|__va
c_func
(paren
id|pernode
)paren
suffix:semicolon
id|pernode
op_add_assign
id|L1_CACHE_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ia64_node_data
)paren
)paren
suffix:semicolon
id|mem_data
(braket
id|node
)braket
dot
id|pgdat-&gt;bdata
op_assign
id|bdp
suffix:semicolon
id|pernode
op_add_assign
id|L1_CACHE_ALIGN
c_func
(paren
r_sizeof
(paren
id|pg_data_t
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Copy the static per-cpu data into the region we&n;&t;&t; * just set aside and then setup __per_cpu_offset&n;&t;&t; * for each CPU on this node.&n;&t;&t; */
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
(brace
r_if
c_cond
(paren
id|node
op_eq
id|node_cpuid
(braket
id|cpu
)braket
dot
id|nid
)paren
(brace
id|memcpy
c_func
(paren
id|__va
c_func
(paren
id|cpu_data
)paren
comma
id|__phys_per_cpu_start
comma
id|__per_cpu_end
op_minus
id|__per_cpu_start
)paren
suffix:semicolon
id|__per_cpu_offset
(braket
id|cpu
)braket
op_assign
(paren
r_char
op_star
)paren
id|__va
c_func
(paren
id|cpu_data
)paren
op_minus
id|__per_cpu_start
suffix:semicolon
id|cpu_data
op_add_assign
id|PERCPU_PAGE_SIZE
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * free_node_bootmem - free bootmem allocator memory for use&n; * @start: physical start of range&n; * @len: length of range&n; * @node: node where this range resides&n; *&n; * Simply calls the bootmem allocator to free the specified ranged from&n; * the given pg_data_t&squot;s bdata struct.  After this function has been called&n; * for all the entries in the EFI memory map, the bootmem allocator will&n; * be ready to service allocation requests.&n; */
DECL|function|free_node_bootmem
r_static
r_int
id|__init
id|free_node_bootmem
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|len
comma
r_int
id|node
)paren
(brace
id|free_bootmem_node
c_func
(paren
id|mem_data
(braket
id|node
)braket
dot
id|pgdat
comma
id|start
comma
id|len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * reserve_pernode_space - reserve memory for per-node space&n; *&n; * Reserve the space used by the bootmem maps &amp; per-node space in the boot&n; * allocator so that when we actually create the real mem maps we don&squot;t&n; * use their memory.&n; */
DECL|function|reserve_pernode_space
r_static
r_void
id|__init
id|reserve_pernode_space
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|base
comma
id|size
comma
id|pages
suffix:semicolon
r_struct
id|bootmem_data
op_star
id|bdp
suffix:semicolon
r_int
id|node
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
id|pg_data_t
op_star
id|pdp
op_assign
id|mem_data
(braket
id|node
)braket
dot
id|pgdat
suffix:semicolon
id|bdp
op_assign
id|pdp-&gt;bdata
suffix:semicolon
multiline_comment|/* First the bootmem_map itself */
id|pages
op_assign
id|bdp-&gt;node_low_pfn
op_minus
(paren
id|bdp-&gt;node_boot_start
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|size
op_assign
id|bootmem_bootmap_pages
c_func
(paren
id|pages
)paren
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|base
op_assign
id|__pa
c_func
(paren
id|bdp-&gt;node_bootmem_map
)paren
suffix:semicolon
id|reserve_bootmem_node
c_func
(paren
id|pdp
comma
id|base
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* Now the per-node space */
id|size
op_assign
id|mem_data
(braket
id|node
)braket
dot
id|pernode_size
suffix:semicolon
id|base
op_assign
id|__pa
c_func
(paren
id|mem_data
(braket
id|node
)braket
dot
id|pernode_addr
)paren
suffix:semicolon
id|reserve_bootmem_node
c_func
(paren
id|pdp
comma
id|base
comma
id|size
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * initialize_pernode_data - fixup per-cpu &amp; per-node pointers&n; *&n; * Each node&squot;s per-node area has a copy of the global pg_data_t list, so&n; * we copy that to each node here, as well as setting the per-cpu pointer&n; * to the local node data structure.  The active_cpus field of the per-node&n; * structure gets setup by the platform_cpu_init() function later.&n; */
DECL|function|initialize_pernode_data
r_static
r_void
id|__init
id|initialize_pernode_data
c_func
(paren
r_void
)paren
(brace
r_int
id|cpu
comma
id|node
suffix:semicolon
id|pg_data_t
op_star
id|pgdat_list
(braket
id|NR_NODES
)braket
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
id|pgdat_list
(braket
id|node
)braket
op_assign
id|mem_data
(braket
id|node
)braket
dot
id|pgdat
suffix:semicolon
multiline_comment|/* Copy the pg_data_t list to each node and init the node field */
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
id|memcpy
c_func
(paren
id|mem_data
(braket
id|node
)braket
dot
id|node_data-&gt;pg_data_ptrs
comma
id|pgdat_list
comma
r_sizeof
(paren
id|pgdat_list
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the node_data pointer for each per-cpu struct */
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
(brace
id|node
op_assign
id|node_cpuid
(braket
id|cpu
)braket
dot
id|nid
suffix:semicolon
id|per_cpu
c_func
(paren
id|cpu_info
comma
id|cpu
)paren
dot
id|node_data
op_assign
id|mem_data
(braket
id|node
)braket
dot
id|node_data
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * find_memory - walk the EFI memory map and setup the bootmem allocator&n; *&n; * Called early in boot to setup the bootmem allocator, and to&n; * allocate the per-cpu and per-node structures.&n; */
DECL|function|find_memory
r_void
id|__init
id|find_memory
c_func
(paren
r_void
)paren
(brace
r_int
id|node
suffix:semicolon
id|reserve_memory
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|numnodes
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;node info missing!&bslash;n&quot;
)paren
suffix:semicolon
id|numnodes
op_assign
l_int|1
suffix:semicolon
)brace
id|min_low_pfn
op_assign
op_minus
l_int|1
suffix:semicolon
id|max_low_pfn
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|numnodes
OG
l_int|1
)paren
id|reassign_cpu_only_nodes
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* These actually end up getting called by call_pernode_memory() */
id|efi_memmap_walk
c_func
(paren
id|filter_rsvd_memory
comma
id|build_node_maps
)paren
suffix:semicolon
id|efi_memmap_walk
c_func
(paren
id|filter_rsvd_memory
comma
id|find_pernode_space
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the boot memory maps in reverse order since that&squot;s&n;&t; * what the bootmem allocator expects&n;&t; */
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
)paren
(brace
r_int
r_int
id|pernode
comma
id|pernodesize
comma
id|map
suffix:semicolon
r_struct
id|bootmem_data
op_star
id|bdp
suffix:semicolon
id|bdp
op_assign
op_amp
id|mem_data
(braket
id|node
)braket
dot
id|bootmem_data
suffix:semicolon
id|pernode
op_assign
id|mem_data
(braket
id|node
)braket
dot
id|pernode_addr
suffix:semicolon
id|pernodesize
op_assign
id|mem_data
(braket
id|node
)braket
dot
id|pernode_size
suffix:semicolon
id|map
op_assign
id|pernode
op_plus
id|pernodesize
suffix:semicolon
multiline_comment|/* Sanity check... */
r_if
c_cond
(paren
op_logical_neg
id|pernode
)paren
id|panic
c_func
(paren
l_string|&quot;pernode space for node %d &quot;
l_string|&quot;could not be allocated!&quot;
comma
id|node
)paren
suffix:semicolon
id|init_bootmem_node
c_func
(paren
id|mem_data
(braket
id|node
)braket
dot
id|pgdat
comma
id|map
op_rshift
id|PAGE_SHIFT
comma
id|bdp-&gt;node_boot_start
op_rshift
id|PAGE_SHIFT
comma
id|bdp-&gt;node_low_pfn
)paren
suffix:semicolon
)brace
id|efi_memmap_walk
c_func
(paren
id|filter_rsvd_memory
comma
id|free_node_bootmem
)paren
suffix:semicolon
id|reserve_pernode_space
c_func
(paren
)paren
suffix:semicolon
id|initialize_pernode_data
c_func
(paren
)paren
suffix:semicolon
id|max_pfn
op_assign
id|max_low_pfn
suffix:semicolon
id|find_initrd
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * per_cpu_init - setup per-cpu variables&n; *&n; * find_pernode_space() does most of this already, we just need to set&n; * local_per_cpu_offset&n; */
DECL|function|per_cpu_init
r_void
op_star
id|per_cpu_init
c_func
(paren
r_void
)paren
(brace
r_int
id|cpu
suffix:semicolon
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_eq
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
(brace
id|per_cpu
c_func
(paren
id|local_per_cpu_offset
comma
id|cpu
)paren
op_assign
id|__per_cpu_offset
(braket
id|cpu
)braket
suffix:semicolon
)brace
)brace
r_return
id|__per_cpu_start
op_plus
id|__per_cpu_offset
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
suffix:semicolon
)brace
multiline_comment|/**&n; * show_mem - give short summary of memory stats&n; *&n; * Shows a simple page count of reserved and used pages in the system.&n; * For discontig machines, it does this on a per-pgdat basis.&n; */
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
id|pg_data_t
op_star
id|pgdat
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
id|printk
c_func
(paren
l_string|&quot;Node ID: %d&bslash;n&quot;
comma
id|pgdat-&gt;node_id
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
id|pgdat-&gt;node_spanned_pages
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ia64_pfn_valid
c_func
(paren
id|pgdat-&gt;node_start_pfn
op_plus
id|i
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|pgdat-&gt;node_mem_map
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
id|pgdat-&gt;node_mem_map
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
id|pgdat-&gt;node_mem_map
op_plus
id|i
)paren
)paren
id|shared
op_add_assign
id|page_count
c_func
(paren
id|pgdat-&gt;node_mem_map
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
l_string|&quot;&bslash;t%ld pages of RAM&bslash;n&quot;
comma
id|pgdat-&gt;node_present_pages
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;t%d reserved pages&bslash;n&quot;
comma
id|reserved
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;t%d pages shared&bslash;n&quot;
comma
id|shared
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;t%d pages swap cached&bslash;n&quot;
comma
id|cached
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Total of %ld pages in page table cache&bslash;n&quot;
comma
id|pgtable_cache_size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d free buffer pages&bslash;n&quot;
comma
id|nr_free_buffer_pages
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * call_pernode_memory - use SRAT to call callback functions with node info&n; * @start: physical start of range&n; * @len: length of range&n; * @arg: function to call for each range&n; *&n; * efi_memmap_walk() knows nothing about layout of memory across nodes. Find&n; * out to which node a block of memory belongs.  Ignore memory that we cannot&n; * identify, and split blocks that run across multiple nodes.&n; *&n; * Take this opportunity to round the start address up and the end address&n; * down to page boundaries.&n; */
DECL|function|call_pernode_memory
r_void
id|call_pernode_memory
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|len
comma
r_void
op_star
id|arg
)paren
(brace
r_int
r_int
id|rs
comma
id|re
comma
id|end
op_assign
id|start
op_plus
id|len
suffix:semicolon
r_void
(paren
op_star
id|func
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
id|start
op_assign
id|PAGE_ALIGN
c_func
(paren
id|start
)paren
suffix:semicolon
id|end
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|end
)paren
r_return
suffix:semicolon
id|func
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|num_node_memblks
)paren
(brace
multiline_comment|/* No SRAT table, so assume one node (node 0) */
r_if
c_cond
(paren
id|start
OL
id|end
)paren
(paren
op_star
id|func
)paren
(paren
id|start
comma
id|end
op_minus
id|start
comma
l_int|0
)paren
suffix:semicolon
r_return
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
id|num_node_memblks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rs
op_assign
id|max
c_func
(paren
id|start
comma
id|node_memblk
(braket
id|i
)braket
dot
id|start_paddr
)paren
suffix:semicolon
id|re
op_assign
id|min
c_func
(paren
id|end
comma
id|node_memblk
(braket
id|i
)braket
dot
id|start_paddr
op_plus
id|node_memblk
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
id|rs
OL
id|re
)paren
(paren
op_star
id|func
)paren
(paren
id|rs
comma
id|re
op_minus
id|rs
comma
id|node_memblk
(braket
id|i
)braket
dot
id|nid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|re
op_eq
id|end
)paren
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * count_node_pages - callback to build per-node memory info structures&n; * @start: physical start of range&n; * @len: length of range&n; * @node: node where this range resides&n; *&n; * Each node has it&squot;s own number of physical pages, DMAable pages, start, and&n; * end page frame number.  This routine will be called by call_pernode_memory()&n; * for each piece of usable memory and will setup these values for each node.&n; * Very similar to build_maps().&n; */
DECL|function|count_node_pages
r_static
r_int
id|count_node_pages
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|len
comma
r_int
id|node
)paren
(brace
r_int
r_int
id|end
op_assign
id|start
op_plus
id|len
suffix:semicolon
id|mem_data
(braket
id|node
)braket
dot
id|num_physpages
op_add_assign
id|len
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|start
op_le
id|__pa
c_func
(paren
id|MAX_DMA_ADDRESS
)paren
)paren
id|mem_data
(braket
id|node
)braket
dot
id|num_dma_physpages
op_add_assign
(paren
id|min
c_func
(paren
id|end
comma
id|__pa
c_func
(paren
id|MAX_DMA_ADDRESS
)paren
)paren
op_minus
id|start
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|start
op_assign
id|GRANULEROUNDDOWN
c_func
(paren
id|start
)paren
suffix:semicolon
id|start
op_assign
id|ORDERROUNDDOWN
c_func
(paren
id|start
)paren
suffix:semicolon
id|end
op_assign
id|GRANULEROUNDUP
c_func
(paren
id|end
)paren
suffix:semicolon
id|mem_data
(braket
id|node
)braket
dot
id|max_pfn
op_assign
id|max
c_func
(paren
id|mem_data
(braket
id|node
)braket
dot
id|max_pfn
comma
id|end
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|mem_data
(braket
id|node
)braket
dot
id|min_pfn
op_assign
id|min
c_func
(paren
id|mem_data
(braket
id|node
)braket
dot
id|min_pfn
comma
id|start
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * paging_init - setup page tables&n; *&n; * paging_init() sets up the page tables for each node of the system and frees&n; * the bootmem allocator memory for general use.&n; */
DECL|function|paging_init
r_void
id|paging_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|max_dma
suffix:semicolon
r_int
r_int
id|zones_size
(braket
id|MAX_NR_ZONES
)braket
suffix:semicolon
r_int
r_int
id|zholes_size
(braket
id|MAX_NR_ZONES
)braket
suffix:semicolon
r_int
r_int
id|max_gap
comma
id|pfn_offset
op_assign
l_int|0
suffix:semicolon
r_int
id|node
suffix:semicolon
id|max_dma
op_assign
id|virt_to_phys
c_func
(paren
(paren
r_void
op_star
)paren
id|MAX_DMA_ADDRESS
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|max_gap
op_assign
l_int|0
suffix:semicolon
id|efi_memmap_walk
c_func
(paren
id|find_largest_hole
comma
op_amp
id|max_gap
)paren
suffix:semicolon
multiline_comment|/* so min() will work in count_node_pages */
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
id|mem_data
(braket
id|node
)braket
dot
id|min_pfn
op_assign
op_complement
l_int|0UL
suffix:semicolon
id|efi_memmap_walk
c_func
(paren
id|filter_rsvd_memory
comma
id|count_node_pages
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
id|memset
c_func
(paren
id|zones_size
comma
l_int|0
comma
r_sizeof
(paren
id|zones_size
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|zholes_size
comma
l_int|0
comma
r_sizeof
(paren
id|zholes_size
)paren
)paren
suffix:semicolon
id|num_physpages
op_add_assign
id|mem_data
(braket
id|node
)braket
dot
id|num_physpages
suffix:semicolon
r_if
c_cond
(paren
id|mem_data
(braket
id|node
)braket
dot
id|min_pfn
op_ge
id|max_dma
)paren
(brace
multiline_comment|/* All of this node&squot;s memory is above ZONE_DMA */
id|zones_size
(braket
id|ZONE_NORMAL
)braket
op_assign
id|mem_data
(braket
id|node
)braket
dot
id|max_pfn
op_minus
id|mem_data
(braket
id|node
)braket
dot
id|min_pfn
suffix:semicolon
id|zholes_size
(braket
id|ZONE_NORMAL
)braket
op_assign
id|mem_data
(braket
id|node
)braket
dot
id|max_pfn
op_minus
id|mem_data
(braket
id|node
)braket
dot
id|min_pfn
op_minus
id|mem_data
(braket
id|node
)braket
dot
id|num_physpages
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|mem_data
(braket
id|node
)braket
dot
id|max_pfn
OL
id|max_dma
)paren
(brace
multiline_comment|/* All of this node&squot;s memory is in ZONE_DMA */
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|mem_data
(braket
id|node
)braket
dot
id|max_pfn
op_minus
id|mem_data
(braket
id|node
)braket
dot
id|min_pfn
suffix:semicolon
id|zholes_size
(braket
id|ZONE_DMA
)braket
op_assign
id|mem_data
(braket
id|node
)braket
dot
id|max_pfn
op_minus
id|mem_data
(braket
id|node
)braket
dot
id|min_pfn
op_minus
id|mem_data
(braket
id|node
)braket
dot
id|num_dma_physpages
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* This node has memory in both zones */
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|max_dma
op_minus
id|mem_data
(braket
id|node
)braket
dot
id|min_pfn
suffix:semicolon
id|zholes_size
(braket
id|ZONE_DMA
)braket
op_assign
id|zones_size
(braket
id|ZONE_DMA
)braket
op_minus
id|mem_data
(braket
id|node
)braket
dot
id|num_dma_physpages
suffix:semicolon
id|zones_size
(braket
id|ZONE_NORMAL
)braket
op_assign
id|mem_data
(braket
id|node
)braket
dot
id|max_pfn
op_minus
id|max_dma
suffix:semicolon
id|zholes_size
(braket
id|ZONE_NORMAL
)braket
op_assign
id|zones_size
(braket
id|ZONE_NORMAL
)braket
op_minus
(paren
id|mem_data
(braket
id|node
)braket
dot
id|num_physpages
op_minus
id|mem_data
(braket
id|node
)braket
dot
id|num_dma_physpages
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|node
op_eq
l_int|0
)paren
(brace
id|vmalloc_end
op_sub_assign
id|PAGE_ALIGN
c_func
(paren
id|max_low_pfn
op_star
r_sizeof
(paren
r_struct
id|page
)paren
)paren
suffix:semicolon
id|vmem_map
op_assign
(paren
r_struct
id|page
op_star
)paren
id|vmalloc_end
suffix:semicolon
id|efi_memmap_walk
c_func
(paren
id|create_mem_map_page_table
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Virtual mem_map starts at 0x%p&bslash;n&quot;
comma
id|vmem_map
)paren
suffix:semicolon
)brace
id|pfn_offset
op_assign
id|mem_data
(braket
id|node
)braket
dot
id|min_pfn
suffix:semicolon
id|free_area_init_node
c_func
(paren
id|node
comma
id|NODE_DATA
c_func
(paren
id|node
)paren
comma
id|zones_size
comma
id|pfn_offset
comma
id|zholes_size
)paren
suffix:semicolon
)brace
id|zero_page_memmap_ptr
op_assign
id|virt_to_page
c_func
(paren
id|ia64_imva
c_func
(paren
id|empty_zero_page
)paren
)paren
suffix:semicolon
)brace
eof
