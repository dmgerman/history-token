multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 by Ralf Baechle&n; * Copyright (C) 2000 by Silicon Graphics, Inc.&n; *&n; * On SGI IP27 the ARC memory configuration data is completly bogus but&n; * alternate easier to use mechanisms are available.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/mmzone.h&gt;
multiline_comment|/* ip27-klnuma.c   */
r_extern
id|pfn_t
id|node_getfirstfree
c_func
(paren
id|cnodeid_t
id|cnode
)paren
suffix:semicolon
DECL|macro|PFN_UP
mdefine_line|#define PFN_UP(x)&t;(((x) + PAGE_SIZE-1) &gt;&gt; PAGE_SHIFT)
DECL|macro|SLOT_IGNORED
mdefine_line|#define SLOT_IGNORED&t;0xffff
DECL|variable|slot_lastfilled_cache
r_int
id|slot_lastfilled_cache
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
DECL|variable|slot_psize_cache
r_int
r_int
id|slot_psize_cache
(braket
id|MAX_COMPACT_NODES
)braket
(braket
id|MAX_MEM_SLOTS
)braket
suffix:semicolon
DECL|variable|numpages
r_static
id|pfn_t
id|numpages
suffix:semicolon
DECL|variable|plat_node_data
id|plat_pg_data_t
op_star
id|plat_node_data
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
DECL|variable|plat_node_bdata
id|bootmem_data_t
id|plat_node_bdata
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
DECL|function|numa_debug
r_int
id|numa_debug
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NUMA debug&bslash;n&quot;
)paren
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
l_int|0
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the number of pages of memory provided by the given slot&n; * on the specified node.&n; */
DECL|function|slot_getsize
id|pfn_t
id|slot_getsize
c_func
(paren
id|cnodeid_t
id|node
comma
r_int
id|slot
)paren
(brace
r_return
(paren
id|pfn_t
)paren
id|slot_psize_cache
(braket
id|node
)braket
(braket
id|slot
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Return highest slot filled&n; */
DECL|function|node_getlastslot
r_int
id|node_getlastslot
c_func
(paren
id|cnodeid_t
id|node
)paren
(brace
r_return
(paren
r_int
)paren
id|slot_lastfilled_cache
(braket
id|node
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the pfn of the last free page of memory on a node.&n; */
DECL|function|node_getmaxclick
id|pfn_t
id|node_getmaxclick
c_func
(paren
id|cnodeid_t
id|node
)paren
(brace
id|pfn_t
id|slot_psize
suffix:semicolon
r_int
id|slot
suffix:semicolon
multiline_comment|/*&n;&t; * Start at the top slot. When we find a slot with memory in it,&n;&t; * that&squot;s the winner.&n;&t; */
r_for
c_loop
(paren
id|slot
op_assign
(paren
id|node_getnumslots
c_func
(paren
id|node
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|slot
op_ge
l_int|0
suffix:semicolon
id|slot
op_decrement
)paren
(brace
r_if
c_cond
(paren
(paren
id|slot_psize
op_assign
id|slot_getsize
c_func
(paren
id|node
comma
id|slot
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|slot_psize
op_eq
id|SLOT_IGNORED
)paren
r_continue
suffix:semicolon
multiline_comment|/* Return the basepfn + the slot size, minus 1. */
r_return
id|slot_getbasepfn
c_func
(paren
id|node
comma
id|slot
)paren
op_plus
id|slot_psize
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * If there&squot;s no memory on the node, return 0. This is likely&n;&t; * to cause problems.&n;&t; */
r_return
(paren
id|pfn_t
)paren
l_int|0
suffix:semicolon
)brace
DECL|function|slot_psize_compute
r_static
id|pfn_t
id|slot_psize_compute
c_func
(paren
id|cnodeid_t
id|node
comma
r_int
id|slot
)paren
(brace
id|nasid_t
id|nasid
suffix:semicolon
id|lboard_t
op_star
id|brd
suffix:semicolon
id|klmembnk_t
op_star
id|banks
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|node
)paren
suffix:semicolon
multiline_comment|/* Find the node board */
id|brd
op_assign
id|find_lboard
c_func
(paren
(paren
id|lboard_t
op_star
)paren
id|KL_CONFIG_INFO
c_func
(paren
id|nasid
)paren
comma
id|KLTYPE_IP27
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|brd
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Get the memory bank structure */
id|banks
op_assign
(paren
id|klmembnk_t
op_star
)paren
id|find_first_component
c_func
(paren
id|brd
comma
id|KLSTRUCT_MEMBNK
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|banks
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Size in _Megabytes_ */
id|size
op_assign
(paren
r_int
r_int
)paren
id|banks-&gt;membnk_bnksz
(braket
id|slot
op_div
l_int|4
)braket
suffix:semicolon
multiline_comment|/* hack for 128 dimm banks */
r_if
c_cond
(paren
id|size
op_le
l_int|128
)paren
(brace
r_if
c_cond
(paren
id|slot
op_mod
l_int|4
op_eq
l_int|0
)paren
(brace
id|size
op_lshift_assign
l_int|20
suffix:semicolon
multiline_comment|/* size in bytes */
r_return
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|size
op_div_assign
l_int|4
suffix:semicolon
id|size
op_lshift_assign
l_int|20
suffix:semicolon
r_return
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
)brace
)brace
DECL|function|szmem
id|pfn_t
id|szmem
c_func
(paren
id|pfn_t
id|fpage
comma
id|pfn_t
id|maxpmem
)paren
(brace
id|cnodeid_t
id|node
suffix:semicolon
r_int
id|slot
comma
id|numslots
suffix:semicolon
id|pfn_t
id|num_pages
op_assign
l_int|0
comma
id|slot_psize
suffix:semicolon
id|pfn_t
id|slot0sz
op_assign
l_int|0
comma
id|nodebytes
suffix:semicolon
multiline_comment|/* Hack to detect problem configs */
r_int
id|ignore
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
id|numslots
op_assign
id|node_getnumslots
c_func
(paren
id|node
)paren
suffix:semicolon
id|ignore
op_assign
id|nodebytes
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
l_int|0
suffix:semicolon
id|slot
OL
id|numslots
suffix:semicolon
id|slot
op_increment
)paren
(brace
id|slot_psize
op_assign
id|slot_psize_compute
c_func
(paren
id|node
comma
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
l_int|0
)paren
id|slot0sz
op_assign
id|slot_psize
suffix:semicolon
multiline_comment|/* &n;&t;&t;&t; * We need to refine the hack when we have replicated&n;&t;&t;&t; * kernel text.&n;&t;&t;&t; */
id|nodebytes
op_add_assign
id|SLOT_SIZE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nodebytes
op_rshift
id|PAGE_SHIFT
)paren
op_star
(paren
r_sizeof
(paren
r_struct
id|page
)paren
)paren
OG
(paren
id|slot0sz
op_lshift
id|PAGE_SHIFT
)paren
)paren
id|ignore
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ignore
op_logical_and
id|slot_psize
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Ignoring slot %d onwards on node %d&bslash;n&quot;
comma
id|slot
comma
id|node
)paren
suffix:semicolon
id|slot_psize_cache
(braket
id|node
)braket
(braket
id|slot
)braket
op_assign
id|SLOT_IGNORED
suffix:semicolon
id|slot
op_assign
id|numslots
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|num_pages
op_add_assign
id|slot_psize
suffix:semicolon
id|slot_psize_cache
(braket
id|node
)braket
(braket
id|slot
)braket
op_assign
(paren
r_int
r_int
)paren
id|slot_psize
suffix:semicolon
r_if
c_cond
(paren
id|slot_psize
)paren
id|slot_lastfilled_cache
(braket
id|node
)braket
op_assign
id|slot
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|maxpmem
)paren
r_return
(paren
id|maxpmem
OG
id|num_pages
)paren
ques
c_cond
id|num_pages
suffix:colon
id|maxpmem
suffix:semicolon
r_else
r_return
id|num_pages
suffix:semicolon
)brace
multiline_comment|/*&n; * Currently, the intranode memory hole support assumes that each slot&n; * contains at least 32 MBytes of memory. We assume all bootmem data&n; * fits on the first slot.&n; */
DECL|function|prom_meminit
r_void
id|__init
id|prom_meminit
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|mlreset
c_func
(paren
r_void
)paren
suffix:semicolon
id|cnodeid_t
id|node
suffix:semicolon
id|pfn_t
id|slot_firstpfn
comma
id|slot_lastpfn
comma
id|slot_freepfn
suffix:semicolon
r_int
r_int
id|bootmap_size
suffix:semicolon
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
id|plat_pg_data_t
)paren
)paren
suffix:semicolon
id|mlreset
c_func
(paren
)paren
suffix:semicolon
id|numpages
op_assign
id|szmem
c_func
(paren
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
(paren
id|numnodes
op_minus
l_int|1
)paren
suffix:semicolon
id|node
op_ge
l_int|0
suffix:semicolon
id|node
op_decrement
)paren
(brace
id|slot_firstpfn
op_assign
id|slot_getbasepfn
c_func
(paren
id|node
comma
l_int|0
)paren
suffix:semicolon
id|slot_lastpfn
op_assign
id|slot_firstpfn
op_plus
id|slot_getsize
c_func
(paren
id|node
comma
l_int|0
)paren
suffix:semicolon
id|slot_freepfn
op_assign
id|node_getfirstfree
c_func
(paren
id|node
)paren
suffix:semicolon
multiline_comment|/* Foll line hack for non discontigmem; remove once discontigmem&n;&t;&t; * becomes the default. */
id|max_low_pfn
op_assign
(paren
id|slot_lastpfn
op_minus
id|slot_firstpfn
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Allocate the node data structure on the node first.&n;&t;&t; */
id|plat_node_data
(braket
id|node
)braket
op_assign
(paren
id|plat_pg_data_t
op_star
)paren
(paren
id|__va
c_func
(paren
id|slot_freepfn
"&bslash;"
op_lshift
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
id|NODE_DATA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|bdata
op_assign
id|plat_node_bdata
op_plus
id|node
suffix:semicolon
id|slot_freepfn
op_add_assign
id|node_datasz
suffix:semicolon
id|bootmap_size
op_assign
id|init_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|node
)paren
comma
id|slot_freepfn
comma
id|slot_firstpfn
comma
id|slot_lastpfn
)paren
suffix:semicolon
id|free_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|node
)paren
comma
id|slot_firstpfn
op_lshift
id|PAGE_SHIFT
comma
(paren
id|slot_lastpfn
op_minus
id|slot_firstpfn
)paren
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|reserve_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|node
)paren
comma
id|slot_firstpfn
op_lshift
id|PAGE_SHIFT
comma
(paren
(paren
id|slot_freepfn
op_minus
id|slot_firstpfn
)paren
op_lshift
id|PAGE_SHIFT
)paren
op_plus
id|bootmap_size
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Total memory probed : 0x%lx pages&bslash;n&quot;
comma
id|numpages
)paren
suffix:semicolon
)brace
DECL|function|page_is_ram
r_int
id|__init
id|page_is_ram
c_func
(paren
r_int
r_int
id|pagenr
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_void
id|__init
DECL|function|prom_free_prom_memory
id|prom_free_prom_memory
(paren
r_void
)paren
(brace
multiline_comment|/* We got nothing to free here ...  */
)brace
macro_line|#ifdef CONFIG_DISCONTIGMEM
DECL|variable|pagenr
r_static
id|pfn_t
id|pagenr
op_assign
l_int|0
suffix:semicolon
DECL|function|paging_init
r_void
id|__init
id|paging_init
c_func
(paren
r_void
)paren
(brace
id|pmd_t
op_star
id|pmd
op_assign
id|kpmdtbl
suffix:semicolon
id|pte_t
op_star
id|pte
op_assign
id|kptbl
suffix:semicolon
id|cnodeid_t
id|node
suffix:semicolon
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
id|i
suffix:semicolon
multiline_comment|/* Initialize the entire pgd.  */
id|pgd_init
c_func
(paren
(paren
r_int
r_int
)paren
id|swapper_pg_dir
)paren
suffix:semicolon
id|pmd_init
c_func
(paren
(paren
r_int
r_int
)paren
id|invalid_pmd_table
comma
(paren
r_int
r_int
)paren
id|invalid_pte_table
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|invalid_pte_table
comma
l_int|0
comma
r_sizeof
(paren
id|pte_t
)paren
op_star
id|PTRS_PER_PTE
)paren
suffix:semicolon
multiline_comment|/* This is for vmalloc  */
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|kptbl
comma
l_int|0
comma
id|PAGE_SIZE
op_lshift
id|KPTBL_PAGE_ORDER
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|kpmdtbl
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|pgd_set
c_func
(paren
id|swapper_pg_dir
comma
id|kpmdtbl
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
(paren
l_int|1
op_lshift
id|KPTBL_PAGE_ORDER
)paren
suffix:semicolon
id|pmd
op_increment
comma
id|i
op_increment
comma
id|pte
op_add_assign
id|PTRS_PER_PTE
)paren
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
op_assign
(paren
r_int
r_int
)paren
id|pte
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
id|pfn_t
id|start_pfn
op_assign
id|slot_getbasepfn
c_func
(paren
id|node
comma
l_int|0
)paren
suffix:semicolon
id|pfn_t
id|end_pfn
op_assign
id|node_getmaxclick
c_func
(paren
id|node
)paren
suffix:semicolon
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|end_pfn
op_plus
l_int|1
op_minus
id|start_pfn
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
l_int|0
comma
id|zones_size
comma
id|start_pfn
comma
l_int|0
)paren
suffix:semicolon
)brace
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
r_char
id|_stext
comma
id|_etext
comma
id|_fdata
comma
id|_edata
suffix:semicolon
r_extern
r_char
id|__init_begin
comma
id|__init_end
suffix:semicolon
r_extern
r_int
r_int
id|setup_zero_pages
c_func
(paren
r_void
)paren
suffix:semicolon
id|cnodeid_t
id|nid
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_int
r_int
id|codesize
comma
id|datasize
comma
id|initsize
suffix:semicolon
r_int
id|slot
comma
id|numslots
suffix:semicolon
r_struct
id|page
op_star
id|pg
comma
op_star
id|pslot
suffix:semicolon
id|num_physpages
op_assign
id|numpages
suffix:semicolon
multiline_comment|/* memory already sized by szmem */
id|max_mapnr
op_assign
id|pagenr
suffix:semicolon
multiline_comment|/* already found during paging_init */
id|high_memory
op_assign
(paren
r_void
op_star
)paren
id|__va
c_func
(paren
id|max_mapnr
op_lshift
id|PAGE_SHIFT
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
multiline_comment|/*&n;&t;&t; * Hack till free_area_init_core() zeroes free_pages&n;&t;&t; */
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|MAX_NR_ZONES
suffix:semicolon
id|tmp
op_increment
)paren
id|PLAT_NODE_DATA
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|gendata.node_zones
(braket
id|tmp
)braket
dot
id|free_pages
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; &t; * This will free up the bootmem, ie, slot 0 memory.&n;&t; &t; */
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
multiline_comment|/*&n;&t;&t; * We need to manually do the other slots.&n;&t;&t; */
id|pg
op_assign
id|NODE_DATA
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|node_mem_map
op_plus
id|slot_getsize
c_func
(paren
id|nid
comma
l_int|0
)paren
suffix:semicolon
id|numslots
op_assign
id|node_getlastslot
c_func
(paren
id|nid
)paren
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
l_int|1
suffix:semicolon
id|slot
op_le
id|numslots
suffix:semicolon
id|slot
op_increment
)paren
(brace
id|pslot
op_assign
id|NODE_DATA
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|node_mem_map
op_plus
id|slot_getbasepfn
c_func
(paren
id|nid
comma
id|slot
)paren
op_minus
id|slot_getbasepfn
c_func
(paren
id|nid
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Mark holes in previous slot. May also want to&n;&t;&t;&t; * free up the pages that hold the memmap entries.&n;&t;&t;&t; */
r_while
c_loop
(paren
id|pg
OL
id|pslot
)paren
(brace
id|pg
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Free valid memory in current slot.&n;&t;&t;&t; */
id|pslot
op_add_assign
id|slot_getsize
c_func
(paren
id|nid
comma
id|slot
)paren
suffix:semicolon
r_while
c_loop
(paren
id|pg
OL
id|pslot
)paren
(brace
multiline_comment|/* if (!page_is_ram(pgnr)) continue; */
multiline_comment|/* commented out until page_is_ram works */
id|ClearPageReserved
c_func
(paren
id|pg
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|pg-&gt;count
comma
l_int|1
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|pg
)paren
suffix:semicolon
id|totalram_pages
op_increment
suffix:semicolon
id|pg
op_increment
suffix:semicolon
id|pgnr
op_increment
suffix:semicolon
)brace
)brace
)brace
id|totalram_pages
op_sub_assign
id|setup_zero_pages
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* This comes from node 0 */
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
id|_stext
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
id|_fdata
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
id|tmp
op_assign
(paren
r_int
r_int
)paren
id|nr_free_pages
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Memory: %luk/%luk available (%ldk kernel code, %ldk reserved, &quot;
l_string|&quot;%ldk data, %ldk init)&bslash;n&quot;
comma
id|tmp
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
(paren
id|num_physpages
op_minus
id|tmp
)paren
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
macro_line|#endif /* CONFIG_DISCONTIGMEM */
eof
