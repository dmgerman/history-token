multiline_comment|/*&n; * Written by: Patricia Gaughen, IBM Corporation&n; *&n; * Copyright (C) 2002, IBM Corp.&n; *&n; * All rights reserved.          &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;gone@us.ibm.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;asm/numaq.h&gt;
multiline_comment|/* These are needed before the pgdat&squot;s are created */
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
DECL|macro|MB_TO_PAGES
mdefine_line|#define&t;MB_TO_PAGES(addr) ((addr) &lt;&lt; (20 - PAGE_SHIFT))
multiline_comment|/*&n; * Function: smp_dump_qct()&n; *&n; * Description: gets memory layout from the quad config table.  This&n; * function also increments numnodes with the number of nodes (quads)&n; * present.&n; */
DECL|function|smp_dump_qct
r_static
r_void
id|__init
id|smp_dump_qct
c_func
(paren
r_void
)paren
(brace
r_int
id|node
suffix:semicolon
r_struct
id|eachquadmem
op_star
id|eq
suffix:semicolon
r_struct
id|sys_cfg_data
op_star
id|scd
op_assign
(paren
r_struct
id|sys_cfg_data
op_star
)paren
id|__va
c_func
(paren
id|SYS_CFG_DATA_PRIV_ADDR
)paren
suffix:semicolon
id|numnodes
op_assign
l_int|0
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
id|MAX_NUMNODES
suffix:semicolon
id|node
op_increment
)paren
(brace
r_if
c_cond
(paren
id|scd-&gt;quads_present31_0
op_amp
(paren
l_int|1
op_lshift
id|node
)paren
)paren
(brace
id|numnodes
op_increment
suffix:semicolon
id|eq
op_assign
op_amp
id|scd-&gt;eq
(braket
id|node
)braket
suffix:semicolon
multiline_comment|/* Convert to pages */
id|node_start_pfn
(braket
id|node
)braket
op_assign
id|MB_TO_PAGES
c_func
(paren
id|eq-&gt;hi_shrd_mem_start
op_minus
id|eq-&gt;priv_mem_size
)paren
suffix:semicolon
id|node_end_pfn
(braket
id|node
)braket
op_assign
id|MB_TO_PAGES
c_func
(paren
id|eq-&gt;hi_shrd_mem_start
op_plus
id|eq-&gt;hi_shrd_mem_size
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * -----------------------------------------&n; *&n; * functions related to physnode_map&n; *&n; * -----------------------------------------&n; */
multiline_comment|/*&n; * physnode_map keeps track of the physical memory layout of the&n; * numaq nodes on a 256Mb break (each element of the array will&n; * represent 256Mb of memory and will be marked by the node id.  so,&n; * if the first gig is on node 0, and the second gig is on node 1&n; * physnode_map will contain:&n; * physnode_map[0-3] = 0;&n; * physnode_map[4-7] = 1;&n; * physnode_map[8- ] = -1;&n; */
DECL|variable|physnode_map
r_int
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
DECL|macro|MB_TO_ELEMENT
mdefine_line|#define MB_TO_ELEMENT(x) (x &gt;&gt; ELEMENT_REPRESENTS)
DECL|macro|PA_TO_MB
mdefine_line|#define PA_TO_MB(pa) (pa &gt;&gt; 20) &t;/* assumption: a physical address is in bytes */
DECL|function|pa_to_nid
r_int
id|pa_to_nid
c_func
(paren
id|u64
id|pa
)paren
(brace
r_int
id|nid
suffix:semicolon
id|nid
op_assign
id|physnode_map
(braket
id|MB_TO_ELEMENT
c_func
(paren
id|PA_TO_MB
c_func
(paren
id|pa
)paren
)paren
)braket
suffix:semicolon
multiline_comment|/* the physical address passed in is not in the map for the system */
r_if
c_cond
(paren
id|nid
op_eq
op_minus
l_int|1
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
id|nid
suffix:semicolon
)brace
DECL|function|pfn_to_nid
r_int
id|pfn_to_nid
c_func
(paren
r_int
r_int
id|pfn
)paren
(brace
r_return
id|pa_to_nid
c_func
(paren
(paren
(paren
id|u64
)paren
id|pfn
)paren
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * for each node mark the regions&n; *        TOPOFMEM = hi_shrd_mem_start + hi_shrd_mem_size&n; *&n; * need to be very careful to not mark 1024+ as belonging&n; * to node 0. will want 1027 to show as belonging to node 1&n; * example:&n; *  TOPOFMEM = 1024&n; * 1024 &gt;&gt; 8 = 4 (subtract 1 for starting at 0]&n; * tmpvar = TOPOFMEM - 256 = 768&n; * 1024 &gt;&gt; 8 = 4 (subtract 1 for starting at 0]&n; * &n; */
DECL|function|initialize_physnode_map
r_static
r_void
id|__init
id|initialize_physnode_map
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
id|topofmem
comma
id|cur
suffix:semicolon
r_struct
id|eachquadmem
op_star
id|eq
suffix:semicolon
r_struct
id|sys_cfg_data
op_star
id|scd
op_assign
(paren
r_struct
id|sys_cfg_data
op_star
)paren
id|__va
c_func
(paren
id|SYS_CFG_DATA_PRIV_ADDR
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
r_if
c_cond
(paren
id|scd-&gt;quads_present31_0
op_amp
(paren
l_int|1
op_lshift
id|nid
)paren
)paren
(brace
id|eq
op_assign
op_amp
id|scd-&gt;eq
(braket
id|nid
)braket
suffix:semicolon
id|cur
op_assign
id|eq-&gt;hi_shrd_mem_start
suffix:semicolon
id|topofmem
op_assign
id|eq-&gt;hi_shrd_mem_start
op_plus
id|eq-&gt;hi_shrd_mem_size
suffix:semicolon
r_while
c_loop
(paren
id|cur
OL
id|topofmem
)paren
(brace
id|physnode_map
(braket
id|cur
op_rshift
l_int|8
)braket
op_assign
id|nid
suffix:semicolon
id|cur
op_add_assign
(paren
id|ELEMENT_REPRESENTS
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|get_memcfg_numaq
r_void
id|__init
id|get_memcfg_numaq
c_func
(paren
r_void
)paren
(brace
id|smp_dump_qct
c_func
(paren
)paren
suffix:semicolon
id|initialize_physnode_map
c_func
(paren
)paren
suffix:semicolon
)brace
eof
