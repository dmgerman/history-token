multiline_comment|/*&n; * Written by Kanoj Sarcar, SGI, Aug 1999&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
DECL|variable|numnodes
r_int
id|numnodes
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Initialized for UMA platforms */
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|variable|contig_bootmem_data
r_static
id|bootmem_data_t
id|contig_bootmem_data
suffix:semicolon
DECL|variable|contig_page_data
id|pg_data_t
id|contig_page_data
op_assign
(brace
dot
id|bdata
op_assign
op_amp
id|contig_bootmem_data
)brace
suffix:semicolon
multiline_comment|/*&n; * This is meant to be invoked by platforms whose physical memory starts&n; * at a considerably higher value than 0. Examples are Super-H, ARM, m68k.&n; * Should be invoked with paramters (0, 0, unsigned long *[], start_paddr).&n; */
DECL|function|free_area_init_node
r_void
id|__init
id|free_area_init_node
c_func
(paren
r_int
id|nid
comma
id|pg_data_t
op_star
id|pgdat
comma
r_struct
id|page
op_star
id|pmap
comma
r_int
r_int
op_star
id|zones_size
comma
r_int
r_int
id|node_start_pfn
comma
r_int
r_int
op_star
id|zholes_size
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
id|pgdat
op_assign
op_amp
id|contig_page_data
suffix:semicolon
id|contig_page_data.node_id
op_assign
l_int|0
suffix:semicolon
id|contig_page_data.node_start_pfn
op_assign
id|node_start_pfn
suffix:semicolon
id|calculate_totalpages
(paren
op_amp
id|contig_page_data
comma
id|zones_size
comma
id|zholes_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmap
op_eq
(paren
r_struct
id|page
op_star
)paren
l_int|0
)paren
(brace
id|size
op_assign
(paren
id|pgdat-&gt;node_size
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
id|pmap
op_assign
(paren
r_struct
id|page
op_star
)paren
id|alloc_bootmem_node
c_func
(paren
id|pgdat
comma
id|size
)paren
suffix:semicolon
)brace
id|contig_page_data.node_mem_map
op_assign
id|pmap
suffix:semicolon
id|free_area_init_core
c_func
(paren
op_amp
id|contig_page_data
comma
id|zones_size
comma
id|zholes_size
)paren
suffix:semicolon
id|mem_map
op_assign
id|contig_page_data.node_mem_map
suffix:semicolon
)brace
macro_line|#else /* CONFIG_DISCONTIGMEM */
DECL|macro|LONG_ALIGN
mdefine_line|#define LONG_ALIGN(x) (((x)+(sizeof(long))-1)&amp;~((sizeof(long))-1))
multiline_comment|/*&n; * Nodes can be initialized parallely, in no particular order.&n; */
DECL|function|free_area_init_node
r_void
id|__init
id|free_area_init_node
c_func
(paren
r_int
id|nid
comma
id|pg_data_t
op_star
id|pgdat
comma
r_struct
id|page
op_star
id|pmap
comma
r_int
r_int
op_star
id|zones_size
comma
r_int
r_int
id|node_start_pfn
comma
r_int
r_int
op_star
id|zholes_size
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|pgdat-&gt;node_id
op_assign
id|nid
suffix:semicolon
id|pgdat-&gt;node_start_pfn
op_assign
id|node_start_pfn
suffix:semicolon
id|calculate_totalpages
(paren
id|pgdat
comma
id|zones_size
comma
id|zholes_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmap
op_eq
(paren
r_struct
id|page
op_star
)paren
l_int|0
)paren
(brace
id|size
op_assign
(paren
id|pgdat-&gt;node_size
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
id|pmap
op_assign
(paren
r_struct
id|page
op_star
)paren
id|alloc_bootmem_node
c_func
(paren
id|pgdat
comma
id|size
)paren
suffix:semicolon
)brace
id|pgdat-&gt;node_mem_map
op_assign
id|pmap
suffix:semicolon
id|free_area_init_core
c_func
(paren
id|pgdat
comma
id|zones_size
comma
id|zholes_size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get space for the valid bitmap.&n;&t; */
id|size
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
id|MAX_NR_ZONES
suffix:semicolon
id|i
op_increment
)paren
id|size
op_add_assign
id|zones_size
(braket
id|i
)braket
suffix:semicolon
id|size
op_assign
id|LONG_ALIGN
c_func
(paren
(paren
id|size
op_plus
l_int|7
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|pgdat-&gt;valid_addr_bitmap
op_assign
(paren
r_int
r_int
op_star
)paren
id|alloc_bootmem_node
c_func
(paren
id|pgdat
comma
id|size
)paren
suffix:semicolon
id|memset
c_func
(paren
id|pgdat-&gt;valid_addr_bitmap
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_DISCONTIGMEM */
eof
