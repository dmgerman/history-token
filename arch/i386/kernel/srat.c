multiline_comment|/*&n; * Some of the code in this file has been gleaned from the 64 bit &n; * discontigmem support code base.&n; *&n; * Copyright (C) 2002, IBM Corp.&n; *&n; * All rights reserved.          &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to Pat Gaughen &lt;gone@us.ibm.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/nodemask.h&gt;
macro_line|#include &lt;asm/srat.h&gt;
macro_line|#include &lt;asm/topology.h&gt;
multiline_comment|/*&n; * proximity macros and definitions&n; */
DECL|macro|NODE_ARRAY_INDEX
mdefine_line|#define NODE_ARRAY_INDEX(x)&t;((x) / 8)&t;/* 8 bits/char */
DECL|macro|NODE_ARRAY_OFFSET
mdefine_line|#define NODE_ARRAY_OFFSET(x)&t;((x) % 8)&t;/* 8 bits/char */
DECL|macro|BMAP_SET
mdefine_line|#define BMAP_SET(bmap, bit)&t;((bmap)[NODE_ARRAY_INDEX(bit)] |= 1 &lt;&lt; NODE_ARRAY_OFFSET(bit))
DECL|macro|BMAP_TEST
mdefine_line|#define BMAP_TEST(bmap, bit)&t;((bmap)[NODE_ARRAY_INDEX(bit)] &amp; (1 &lt;&lt; NODE_ARRAY_OFFSET(bit)))
DECL|macro|MAX_PXM_DOMAINS
mdefine_line|#define MAX_PXM_DOMAINS&t;&t;256&t;/* 1 byte and no promises about values */
multiline_comment|/* bitmap length; _PXM is at most 255 */
DECL|macro|PXM_BITMAP_LEN
mdefine_line|#define PXM_BITMAP_LEN (MAX_PXM_DOMAINS / 8) 
DECL|variable|pxm_bitmap
r_static
id|u8
id|pxm_bitmap
(braket
id|PXM_BITMAP_LEN
)braket
suffix:semicolon
multiline_comment|/* bitmap of proximity domains */
DECL|macro|MAX_CHUNKS_PER_NODE
mdefine_line|#define MAX_CHUNKS_PER_NODE&t;4
DECL|macro|MAXCHUNKS
mdefine_line|#define MAXCHUNKS&t;&t;(MAX_CHUNKS_PER_NODE * MAX_NUMNODES)
DECL|struct|node_memory_chunk_s
r_struct
id|node_memory_chunk_s
(brace
DECL|member|start_pfn
r_int
r_int
id|start_pfn
suffix:semicolon
DECL|member|end_pfn
r_int
r_int
id|end_pfn
suffix:semicolon
DECL|member|pxm
id|u8
id|pxm
suffix:semicolon
singleline_comment|// proximity domain of node
DECL|member|nid
id|u8
id|nid
suffix:semicolon
singleline_comment|// which cnode contains this chunk?
DECL|member|bank
id|u8
id|bank
suffix:semicolon
singleline_comment|// which mem bank on this node
)brace
suffix:semicolon
DECL|variable|node_memory_chunk
r_static
r_struct
id|node_memory_chunk_s
id|node_memory_chunk
(braket
id|MAXCHUNKS
)braket
suffix:semicolon
DECL|variable|num_memory_chunks
r_static
r_int
id|num_memory_chunks
suffix:semicolon
multiline_comment|/* total number of memory chunks */
DECL|variable|zholes_size_init
r_static
r_int
id|zholes_size_init
suffix:semicolon
DECL|variable|zholes_size
r_static
r_int
r_int
id|zholes_size
(braket
id|MAX_NUMNODES
op_star
id|MAX_NR_ZONES
)braket
suffix:semicolon
r_extern
r_void
op_star
id|boot_ioremap
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Identify CPU proximity domains */
DECL|function|parse_cpu_affinity_structure
r_static
r_void
id|__init
id|parse_cpu_affinity_structure
c_func
(paren
r_char
op_star
id|p
)paren
(brace
r_struct
id|acpi_table_processor_affinity
op_star
id|cpu_affinity
op_assign
(paren
r_struct
id|acpi_table_processor_affinity
op_star
)paren
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_affinity-&gt;flags.enabled
)paren
r_return
suffix:semicolon
multiline_comment|/* empty entry */
multiline_comment|/* mark this node as &quot;seen&quot; in node bitmap */
id|BMAP_SET
c_func
(paren
id|pxm_bitmap
comma
id|cpu_affinity-&gt;proximity_domain
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU 0x%02X in proximity domain 0x%02X&bslash;n&quot;
comma
id|cpu_affinity-&gt;apic_id
comma
id|cpu_affinity-&gt;proximity_domain
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Identify memory proximity domains and hot-remove capabilities.&n; * Fill node memory chunk list structure.&n; */
DECL|function|parse_memory_affinity_structure
r_static
r_void
id|__init
id|parse_memory_affinity_structure
(paren
r_char
op_star
id|sratp
)paren
(brace
r_int
r_int
r_int
id|paddr
comma
id|size
suffix:semicolon
r_int
r_int
id|start_pfn
comma
id|end_pfn
suffix:semicolon
id|u8
id|pxm
suffix:semicolon
r_struct
id|node_memory_chunk_s
op_star
id|p
comma
op_star
id|q
comma
op_star
id|pend
suffix:semicolon
r_struct
id|acpi_table_memory_affinity
op_star
id|memory_affinity
op_assign
(paren
r_struct
id|acpi_table_memory_affinity
op_star
)paren
id|sratp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memory_affinity-&gt;flags.enabled
)paren
r_return
suffix:semicolon
multiline_comment|/* empty entry */
multiline_comment|/* mark this node as &quot;seen&quot; in node bitmap */
id|BMAP_SET
c_func
(paren
id|pxm_bitmap
comma
id|memory_affinity-&gt;proximity_domain
)paren
suffix:semicolon
multiline_comment|/* calculate info for memory chunk structure */
id|paddr
op_assign
id|memory_affinity-&gt;base_addr_hi
suffix:semicolon
id|paddr
op_assign
(paren
id|paddr
op_lshift
l_int|32
)paren
op_or
id|memory_affinity-&gt;base_addr_lo
suffix:semicolon
id|size
op_assign
id|memory_affinity-&gt;length_hi
suffix:semicolon
id|size
op_assign
(paren
id|size
op_lshift
l_int|32
)paren
op_or
id|memory_affinity-&gt;length_lo
suffix:semicolon
id|start_pfn
op_assign
id|paddr
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|end_pfn
op_assign
(paren
id|paddr
op_plus
id|size
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|pxm
op_assign
id|memory_affinity-&gt;proximity_domain
suffix:semicolon
r_if
c_cond
(paren
id|num_memory_chunks
op_ge
id|MAXCHUNKS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Too many mem chunks in SRAT. Ignoring %lld MBytes at %llx&bslash;n&quot;
comma
id|size
op_div
(paren
l_int|1024
op_star
l_int|1024
)paren
comma
id|paddr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Insertion sort based on base address */
id|pend
op_assign
op_amp
id|node_memory_chunk
(braket
id|num_memory_chunks
)braket
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|node_memory_chunk
(braket
l_int|0
)braket
suffix:semicolon
id|p
OL
id|pend
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|start_pfn
OL
id|p-&gt;start_pfn
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
OL
id|pend
)paren
(brace
r_for
c_loop
(paren
id|q
op_assign
id|pend
suffix:semicolon
id|q
op_ge
id|p
suffix:semicolon
id|q
op_decrement
)paren
op_star
(paren
id|q
op_plus
l_int|1
)paren
op_assign
op_star
id|q
suffix:semicolon
)brace
id|p-&gt;start_pfn
op_assign
id|start_pfn
suffix:semicolon
id|p-&gt;end_pfn
op_assign
id|end_pfn
suffix:semicolon
id|p-&gt;pxm
op_assign
id|pxm
suffix:semicolon
id|num_memory_chunks
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Memory range 0x%lX to 0x%lX (type 0x%X) in proximity domain 0x%02X %s&bslash;n&quot;
comma
id|start_pfn
comma
id|end_pfn
comma
id|memory_affinity-&gt;memory_type
comma
id|memory_affinity-&gt;proximity_domain
comma
(paren
id|memory_affinity-&gt;flags.hot_pluggable
ques
c_cond
l_string|&quot;enabled and removable&quot;
suffix:colon
l_string|&quot;enabled&quot;
)paren
)paren
suffix:semicolon
)brace
macro_line|#if MAX_NR_ZONES != 3
macro_line|#error &quot;MAX_NR_ZONES != 3, chunk_to_zone requires review&quot;
macro_line|#endif
multiline_comment|/* Take a chunk of pages from page frame cstart to cend and count the number&n; * of pages in each zone, returned via zones[].&n; */
DECL|function|chunk_to_zones
r_static
id|__init
r_void
id|chunk_to_zones
c_func
(paren
r_int
r_int
id|cstart
comma
r_int
r_int
id|cend
comma
r_int
r_int
op_star
id|zones
)paren
(brace
r_int
r_int
id|max_dma
suffix:semicolon
r_extern
r_int
r_int
id|max_low_pfn
suffix:semicolon
r_int
id|z
suffix:semicolon
r_int
r_int
id|rend
suffix:semicolon
multiline_comment|/* FIXME: MAX_DMA_ADDRESS and max_low_pfn are trying to provide&n;&t; * similarly scoped information and should be handled in a consistant&n;&t; * manner.&n;&t; */
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
multiline_comment|/* Split the hole into the zones in which it falls.  Repeatedly&n;&t; * take the segment in which the remaining hole starts, round it&n;&t; * to the end of that zone.&n;&t; */
id|memset
c_func
(paren
id|zones
comma
l_int|0
comma
id|MAX_NR_ZONES
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|cstart
OL
id|cend
)paren
(brace
r_if
c_cond
(paren
id|cstart
OL
id|max_dma
)paren
(brace
id|z
op_assign
id|ZONE_DMA
suffix:semicolon
id|rend
op_assign
(paren
id|cend
OL
id|max_dma
)paren
ques
c_cond
id|cend
suffix:colon
id|max_dma
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cstart
OL
id|max_low_pfn
)paren
(brace
id|z
op_assign
id|ZONE_NORMAL
suffix:semicolon
id|rend
op_assign
(paren
id|cend
OL
id|max_low_pfn
)paren
ques
c_cond
id|cend
suffix:colon
id|max_low_pfn
suffix:semicolon
)brace
r_else
(brace
id|z
op_assign
id|ZONE_HIGHMEM
suffix:semicolon
id|rend
op_assign
id|cend
suffix:semicolon
)brace
id|zones
(braket
id|z
)braket
op_add_assign
id|rend
op_minus
id|cstart
suffix:semicolon
id|cstart
op_assign
id|rend
suffix:semicolon
)brace
)brace
multiline_comment|/* Parse the ACPI Static Resource Affinity Table */
DECL|function|acpi20_parse_srat
r_static
r_int
id|__init
id|acpi20_parse_srat
c_func
(paren
r_struct
id|acpi_table_srat
op_star
id|sratp
)paren
(brace
id|u8
op_star
id|start
comma
op_star
id|end
comma
op_star
id|p
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|nid
suffix:semicolon
id|u8
id|pxm_to_nid_map
(braket
id|MAX_PXM_DOMAINS
)braket
suffix:semicolon
multiline_comment|/* _PXM to logical node ID map */
id|u8
id|nid_to_pxm_map
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
multiline_comment|/* logical node ID to _PXM map */
id|start
op_assign
(paren
id|u8
op_star
)paren
(paren
op_amp
(paren
id|sratp-&gt;reserved
)paren
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* skip header */
id|p
op_assign
id|start
suffix:semicolon
id|end
op_assign
(paren
id|u8
op_star
)paren
id|sratp
op_plus
id|sratp-&gt;header.length
suffix:semicolon
id|memset
c_func
(paren
id|pxm_bitmap
comma
l_int|0
comma
r_sizeof
(paren
id|pxm_bitmap
)paren
)paren
suffix:semicolon
multiline_comment|/* init proximity domain bitmap */
id|memset
c_func
(paren
id|node_memory_chunk
comma
l_int|0
comma
r_sizeof
(paren
id|node_memory_chunk
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
multiline_comment|/* -1 in these maps means not available */
id|memset
c_func
(paren
id|pxm_to_nid_map
comma
op_minus
l_int|1
comma
r_sizeof
(paren
id|pxm_to_nid_map
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|nid_to_pxm_map
comma
op_minus
l_int|1
comma
r_sizeof
(paren
id|nid_to_pxm_map
)paren
)paren
suffix:semicolon
id|num_memory_chunks
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|p
OL
id|end
)paren
(brace
r_switch
c_cond
(paren
op_star
id|p
)paren
(brace
r_case
id|ACPI_SRAT_PROCESSOR_AFFINITY
suffix:colon
id|parse_cpu_affinity_structure
c_func
(paren
id|p
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_SRAT_MEMORY_AFFINITY
suffix:colon
id|parse_memory_affinity_structure
c_func
(paren
id|p
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ACPI 2.0 SRAT: unknown entry skipped: type=0x%02X, len=%d&bslash;n&quot;
comma
id|p
(braket
l_int|0
)braket
comma
id|p
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|p
op_add_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|p
(braket
l_int|1
)braket
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;acpi20_parse_srat: Entry length value is zero;&quot;
l_string|&quot; can&squot;t parse any further!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|num_memory_chunks
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;could not finy any ACPI SRAT memory areas.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_fail
suffix:semicolon
)brace
multiline_comment|/* Calculate total number of nodes in system from PXM bitmap and create&n;&t; * a set of sequential node IDs starting at zero.  (ACPI doesn&squot;t seem&n;&t; * to specify the range of _PXM values.)&n;&t; */
multiline_comment|/*&n;&t; * MCD - we no longer HAVE to number nodes sequentially.  PXM domain&n;&t; * numbers could go as high as 256, and MAX_NUMNODES for i386 is typically&n;&t; * 32, so we will continue numbering them in this manner until MAX_NUMNODES&n;&t; * approaches MAX_PXM_DOMAINS for i386.&n;&t; */
id|nodes_clear
c_func
(paren
id|node_online_map
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
id|MAX_PXM_DOMAINS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|BMAP_TEST
c_func
(paren
id|pxm_bitmap
comma
id|i
)paren
)paren
(brace
id|nid
op_assign
id|num_online_nodes
c_func
(paren
)paren
suffix:semicolon
id|pxm_to_nid_map
(braket
id|i
)braket
op_assign
id|nid
suffix:semicolon
id|nid_to_pxm_map
(braket
id|nid
)braket
op_assign
id|i
suffix:semicolon
id|node_set_online
c_func
(paren
id|nid
)paren
suffix:semicolon
)brace
)brace
id|BUG_ON
c_func
(paren
id|num_online_nodes
c_func
(paren
)paren
op_eq
l_int|0
)paren
suffix:semicolon
multiline_comment|/* set cnode id in memory chunk structure */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_memory_chunks
suffix:semicolon
id|i
op_increment
)paren
id|node_memory_chunk
(braket
id|i
)braket
dot
id|nid
op_assign
id|pxm_to_nid_map
(braket
id|node_memory_chunk
(braket
id|i
)braket
dot
id|pxm
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pxm bitmap: &quot;
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
r_sizeof
(paren
id|pxm_bitmap
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%02X &quot;
comma
id|pxm_bitmap
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Number of logical nodes in system = %d&bslash;n&quot;
comma
id|num_online_nodes
c_func
(paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Number of memory chunks in system = %d&bslash;n&quot;
comma
id|num_memory_chunks
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|num_memory_chunks
suffix:semicolon
id|j
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;chunk %d nid %d start_pfn %08lx end_pfn %08lx&bslash;n&quot;
comma
id|j
comma
id|node_memory_chunk
(braket
id|j
)braket
dot
id|nid
comma
id|node_memory_chunk
(braket
id|j
)braket
dot
id|start_pfn
comma
id|node_memory_chunk
(braket
id|j
)braket
dot
id|end_pfn
)paren
suffix:semicolon
)brace
multiline_comment|/*calculate node_start_pfn/node_end_pfn arrays*/
id|for_each_online_node
c_func
(paren
id|nid
)paren
(brace
r_int
id|been_here_before
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|num_memory_chunks
suffix:semicolon
id|j
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Only add present memroy to node_end/start_pfn&n;&t;&t;&t; * There is no guarantee from the srat that the memory&n;&t;&t;&t; * is present at boot time.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|node_memory_chunk
(braket
id|j
)braket
dot
id|start_pfn
op_ge
id|max_pfn
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Ignoring chunk of memory reported in the SRAT (could be hot-add zone?)&bslash;n&quot;
)paren
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;chunk is reported from pfn %04x to %04x&bslash;n&quot;
comma
id|node_memory_chunk
(braket
id|j
)braket
dot
id|start_pfn
comma
id|node_memory_chunk
(braket
id|j
)braket
dot
id|end_pfn
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|node_memory_chunk
(braket
id|j
)braket
dot
id|nid
op_eq
id|nid
)paren
(brace
r_if
c_cond
(paren
id|been_here_before
op_eq
l_int|0
)paren
(brace
id|node_start_pfn
(braket
id|nid
)braket
op_assign
id|node_memory_chunk
(braket
id|j
)braket
dot
id|start_pfn
suffix:semicolon
id|node_end_pfn
(braket
id|nid
)braket
op_assign
id|node_memory_chunk
(braket
id|j
)braket
dot
id|end_pfn
suffix:semicolon
id|been_here_before
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* We&squot;ve found another chunk of memory for the node */
r_if
c_cond
(paren
id|node_start_pfn
(braket
id|nid
)braket
OL
id|node_memory_chunk
(braket
id|j
)braket
dot
id|start_pfn
)paren
(brace
id|node_end_pfn
(braket
id|nid
)braket
op_assign
id|node_memory_chunk
(braket
id|j
)braket
dot
id|end_pfn
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
id|for_each_online_node
c_func
(paren
id|nid
)paren
(brace
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
id|end
op_assign
id|node_end_pfn
(braket
id|nid
)braket
suffix:semicolon
id|memory_present
c_func
(paren
id|nid
comma
id|start
comma
id|end
)paren
suffix:semicolon
id|node_remap_size
(braket
id|nid
)braket
op_assign
id|node_memmap_size_bytes
c_func
(paren
id|nid
comma
id|start
comma
id|end
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
id|out_fail
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_memcfg_from_srat
r_int
id|__init
id|get_memcfg_from_srat
c_func
(paren
r_void
)paren
(brace
r_struct
id|acpi_table_header
op_star
id|header
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_table_rsdp
op_star
id|rsdp
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_table_rsdt
op_star
id|rsdt
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_pointer
op_star
id|rsdp_address
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_table_rsdt
id|saved_rsdt
suffix:semicolon
r_int
id|tables
op_assign
l_int|0
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|acpi_find_root_pointer
c_func
(paren
id|ACPI_PHYSICAL_ADDRESSING
comma
id|rsdp_address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rsdp_address-&gt;pointer_type
op_eq
id|ACPI_PHYSICAL_POINTER
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: assigning address to rsdp&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|rsdp
op_assign
(paren
r_struct
id|acpi_table_rsdp
op_star
)paren
(paren
id|u32
)paren
id|rsdp_address-&gt;pointer.physical
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;%s: rsdp_address is not a physical pointer&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|rsdp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Didn&squot;t find ACPI root!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%.8s v%d [%.6s]&bslash;n&quot;
comma
id|rsdp-&gt;signature
comma
id|rsdp-&gt;revision
comma
id|rsdp-&gt;oem_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|rsdp-&gt;signature
comma
id|RSDP_SIG
comma
id|strlen
c_func
(paren
id|RSDP_SIG
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: RSDP table signature incorrect&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
id|rsdt
op_assign
(paren
r_struct
id|acpi_table_rsdt
op_star
)paren
id|boot_ioremap
c_func
(paren
id|rsdp-&gt;rsdt_address
comma
r_sizeof
(paren
r_struct
id|acpi_table_rsdt
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rsdt
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: ACPI: Invalid root system description tables (RSDT)&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
id|header
op_assign
op_amp
id|rsdt-&gt;header
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|header-&gt;signature
comma
id|RSDT_SIG
comma
id|strlen
c_func
(paren
id|RSDT_SIG
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ACPI: RSDT signature incorrect&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * The number of tables is computed by taking the &n;&t; * size of all entries (header size minus total &n;&t; * size of RSDT) divided by the size of each entry&n;&t; * (4-byte table pointers).&n;&t; */
id|tables
op_assign
(paren
id|header-&gt;length
op_minus
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
op_div
l_int|4
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tables
)paren
r_goto
id|out_err
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|saved_rsdt
comma
id|rsdt
comma
r_sizeof
(paren
id|saved_rsdt
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved_rsdt.header.length
OG
r_sizeof
(paren
id|saved_rsdt
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ACPI: Too big length in RSDT: %d&bslash;n&quot;
comma
id|saved_rsdt.header.length
)paren
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Begin SRAT table scan....&bslash;n&quot;
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
id|tables
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Map in header, then map in full table length. */
id|header
op_assign
(paren
r_struct
id|acpi_table_header
op_star
)paren
id|boot_ioremap
c_func
(paren
id|saved_rsdt.entry
(braket
id|i
)braket
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|header
)paren
r_break
suffix:semicolon
id|header
op_assign
(paren
r_struct
id|acpi_table_header
op_star
)paren
id|boot_ioremap
c_func
(paren
id|saved_rsdt.entry
(braket
id|i
)braket
comma
id|header-&gt;length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|header
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|header-&gt;signature
comma
l_string|&quot;SRAT&quot;
comma
l_int|4
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* we&squot;ve found the srat table. don&squot;t need to look at any more tables */
r_return
id|acpi20_parse_srat
c_func
(paren
(paren
r_struct
id|acpi_table_srat
op_star
)paren
id|header
)paren
suffix:semicolon
)brace
id|out_err
suffix:colon
id|printk
c_func
(paren
l_string|&quot;failed to get NUMA memory information from SRAT table&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* For each node run the memory list to determine whether there are&n; * any memory holes.  For each hole determine which ZONE they fall&n; * into.&n; *&n; * NOTE#1: this requires knowledge of the zone boundries and so&n; * _cannot_ be performed before those are calculated in setup_memory.&n; * &n; * NOTE#2: we rely on the fact that the memory chunks are ordered by&n; * start pfn number during setup.&n; */
DECL|function|get_zholes_init
r_static
r_void
id|__init
id|get_zholes_init
c_func
(paren
r_void
)paren
(brace
r_int
id|nid
suffix:semicolon
r_int
id|c
suffix:semicolon
r_int
id|first
suffix:semicolon
r_int
r_int
id|end
op_assign
l_int|0
suffix:semicolon
id|for_each_online_node
c_func
(paren
id|nid
)paren
(brace
id|first
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|c
op_assign
l_int|0
suffix:semicolon
id|c
OL
id|num_memory_chunks
suffix:semicolon
id|c
op_increment
)paren
(brace
r_if
c_cond
(paren
id|node_memory_chunk
(braket
id|c
)braket
dot
id|nid
op_eq
id|nid
)paren
(brace
r_if
c_cond
(paren
id|first
)paren
(brace
id|end
op_assign
id|node_memory_chunk
(braket
id|c
)braket
dot
id|end_pfn
suffix:semicolon
id|first
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Record any gap between this chunk&n;&t;&t;&t;&t;&t; * and the previous chunk on this node&n;&t;&t;&t;&t;&t; * against the zones it spans.&n;&t;&t;&t;&t;&t; */
id|chunk_to_zones
c_func
(paren
id|end
comma
id|node_memory_chunk
(braket
id|c
)braket
dot
id|start_pfn
comma
op_amp
id|zholes_size
(braket
id|nid
op_star
id|MAX_NR_ZONES
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
DECL|function|get_zholes_size
r_int
r_int
op_star
id|__init
id|get_zholes_size
c_func
(paren
r_int
id|nid
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|zholes_size_init
)paren
(brace
id|zholes_size_init
op_increment
suffix:semicolon
id|get_zholes_init
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nid
op_ge
id|MAX_NUMNODES
op_logical_or
op_logical_neg
id|node_online
c_func
(paren
id|nid
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;%s: nid = %d is invalid/offline. num_online_nodes = %d&quot;
comma
id|__FUNCTION__
comma
id|nid
comma
id|num_online_nodes
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
op_amp
id|zholes_size
(braket
id|nid
op_star
id|MAX_NR_ZONES
)braket
suffix:semicolon
)brace
eof
