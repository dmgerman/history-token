multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 by Ralf Baechle&n; * Copyright (C) 2000 by Silicon Graphics, Inc.&n; * Copyright (C) 2004 by Christoph Hellwig&n; *&n; * On SGI IP27 the ARC memory configuration data is completly bogus but&n; * alternate easier to use mechanisms are available.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/hub.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
DECL|macro|PFN_UP
mdefine_line|#define PFN_UP(x)&t;&t;(((x) + PAGE_SIZE-1) &gt;&gt; PAGE_SHIFT)
DECL|macro|SLOT_PFNSHIFT
mdefine_line|#define SLOT_PFNSHIFT           (SLOT_SHIFT - PAGE_SHIFT)
DECL|macro|PFN_NASIDSHFT
mdefine_line|#define PFN_NASIDSHFT           (NASID_SHFT - PAGE_SHIFT)
DECL|macro|SLOT_IGNORED
mdefine_line|#define SLOT_IGNORED&t;&t;0xffff
DECL|variable|slot_lastfilled_cache
r_static
r_int
id|__initdata
id|slot_lastfilled_cache
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
DECL|variable|slot_psize_cache
r_static
r_int
r_int
id|__initdata
id|slot_psize_cache
(braket
id|MAX_COMPACT_NODES
)braket
(braket
id|MAX_MEM_SLOTS
)braket
suffix:semicolon
DECL|variable|plat_node_bdata
r_static
r_struct
id|bootmem_data
id|__initdata
id|plat_node_bdata
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
DECL|variable|__node_data
r_struct
id|node_data
op_star
id|__node_data
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
DECL|variable|__node_data
id|EXPORT_SYMBOL
c_func
(paren
id|__node_data
)paren
suffix:semicolon
DECL|variable|fine_mode
r_static
r_int
id|fine_mode
suffix:semicolon
DECL|function|is_fine_dirmode
r_static
r_int
id|is_fine_dirmode
c_func
(paren
r_void
)paren
(brace
r_return
(paren
(paren
(paren
id|LOCAL_HUB_L
c_func
(paren
id|NI_STATUS_REV_ID
)paren
op_amp
id|NSRI_REGIONSIZE_MASK
)paren
op_rshift
id|NSRI_REGIONSIZE_SHFT
)paren
op_amp
id|REGIONSIZE_FINE
)paren
suffix:semicolon
)brace
DECL|function|get_region
r_static
id|hubreg_t
id|get_region
c_func
(paren
id|cnodeid_t
id|cnode
)paren
(brace
r_if
c_cond
(paren
id|fine_mode
)paren
r_return
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
op_rshift
id|NASID_TO_FINEREG_SHFT
suffix:semicolon
r_else
r_return
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
op_rshift
id|NASID_TO_COARSEREG_SHFT
suffix:semicolon
)brace
DECL|variable|region_mask
r_static
id|hubreg_t
id|region_mask
suffix:semicolon
DECL|function|gen_region_mask
r_static
r_void
id|gen_region_mask
c_func
(paren
id|hubreg_t
op_star
id|region_mask
comma
r_int
id|maxnodes
)paren
(brace
id|cnodeid_t
id|cnode
suffix:semicolon
(paren
op_star
id|region_mask
)paren
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|maxnodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
(paren
op_star
id|region_mask
)paren
op_or_assign
l_int|1ULL
op_lshift
id|get_region
c_func
(paren
id|cnode
)paren
suffix:semicolon
)brace
)brace
DECL|macro|rou_rflag
mdefine_line|#define&t;rou_rflag&t;rou_flags
DECL|variable|router_distance
r_static
r_int
id|router_distance
suffix:semicolon
DECL|function|router_recurse
r_static
r_void
id|router_recurse
c_func
(paren
id|klrou_t
op_star
id|router_a
comma
id|klrou_t
op_star
id|router_b
comma
r_int
id|depth
)paren
(brace
id|klrou_t
op_star
id|router
suffix:semicolon
id|lboard_t
op_star
id|brd
suffix:semicolon
r_int
id|port
suffix:semicolon
r_if
c_cond
(paren
id|router_a-&gt;rou_rflag
op_eq
l_int|1
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|depth
op_ge
id|router_distance
)paren
r_return
suffix:semicolon
id|router_a-&gt;rou_rflag
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
l_int|1
suffix:semicolon
id|port
op_le
id|MAX_ROUTER_PORTS
suffix:semicolon
id|port
op_increment
)paren
(brace
r_if
c_cond
(paren
id|router_a-&gt;rou_port
(braket
id|port
)braket
dot
id|port_nasid
op_eq
id|INVALID_NASID
)paren
r_continue
suffix:semicolon
id|brd
op_assign
(paren
id|lboard_t
op_star
)paren
id|NODE_OFFSET_TO_K0
c_func
(paren
id|router_a-&gt;rou_port
(braket
id|port
)braket
dot
id|port_nasid
comma
id|router_a-&gt;rou_port
(braket
id|port
)braket
dot
id|port_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|brd-&gt;brd_type
op_eq
id|KLTYPE_ROUTER
)paren
(brace
id|router
op_assign
(paren
id|klrou_t
op_star
)paren
id|NODE_OFFSET_TO_K0
c_func
(paren
id|NASID_GET
c_func
(paren
id|brd
)paren
comma
id|brd-&gt;brd_compts
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|router
op_eq
id|router_b
)paren
(brace
r_if
c_cond
(paren
id|depth
OL
id|router_distance
)paren
id|router_distance
op_assign
id|depth
suffix:semicolon
)brace
r_else
id|router_recurse
c_func
(paren
id|router
comma
id|router_b
comma
id|depth
op_plus
l_int|1
)paren
suffix:semicolon
)brace
)brace
id|router_a-&gt;rou_rflag
op_assign
l_int|0
suffix:semicolon
)brace
DECL|variable|__node_distances
r_int
r_char
id|__node_distances
(braket
id|MAX_COMPACT_NODES
)braket
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
DECL|function|compute_node_distance
r_static
r_int
id|__init
id|compute_node_distance
c_func
(paren
id|nasid_t
id|nasid_a
comma
id|nasid_t
id|nasid_b
)paren
(brace
id|klrou_t
op_star
id|router
comma
op_star
id|router_a
op_assign
l_int|NULL
comma
op_star
id|router_b
op_assign
l_int|NULL
suffix:semicolon
id|lboard_t
op_star
id|brd
comma
op_star
id|dest_brd
suffix:semicolon
id|cnodeid_t
id|cnode
suffix:semicolon
id|nasid_t
id|nasid
suffix:semicolon
r_int
id|port
suffix:semicolon
multiline_comment|/* Figure out which routers nodes in question are connected to */
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nasid
op_eq
op_minus
l_int|1
)paren
r_continue
suffix:semicolon
id|brd
op_assign
id|find_lboard_class
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
id|KLTYPE_ROUTER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|brd
)paren
r_continue
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|brd-&gt;brd_flags
op_amp
id|DUPLICATE_BOARD
)paren
r_continue
suffix:semicolon
id|router
op_assign
(paren
id|klrou_t
op_star
)paren
id|NODE_OFFSET_TO_K0
c_func
(paren
id|NASID_GET
c_func
(paren
id|brd
)paren
comma
id|brd-&gt;brd_compts
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|router-&gt;rou_rflag
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
l_int|1
suffix:semicolon
id|port
op_le
id|MAX_ROUTER_PORTS
suffix:semicolon
id|port
op_increment
)paren
(brace
r_if
c_cond
(paren
id|router-&gt;rou_port
(braket
id|port
)braket
dot
id|port_nasid
op_eq
id|INVALID_NASID
)paren
r_continue
suffix:semicolon
id|dest_brd
op_assign
(paren
id|lboard_t
op_star
)paren
id|NODE_OFFSET_TO_K0
c_func
(paren
id|router-&gt;rou_port
(braket
id|port
)braket
dot
id|port_nasid
comma
id|router-&gt;rou_port
(braket
id|port
)braket
dot
id|port_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dest_brd-&gt;brd_type
op_eq
id|KLTYPE_IP27
)paren
(brace
r_if
c_cond
(paren
id|dest_brd-&gt;brd_nasid
op_eq
id|nasid_a
)paren
id|router_a
op_assign
id|router
suffix:semicolon
r_if
c_cond
(paren
id|dest_brd-&gt;brd_nasid
op_eq
id|nasid_b
)paren
id|router_b
op_assign
id|router
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
(paren
id|brd
op_assign
id|find_lboard_class
c_func
(paren
id|KLCF_NEXT
c_func
(paren
id|brd
)paren
comma
id|KLTYPE_ROUTER
)paren
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|router_a
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;node_distance: router_a NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|router_b
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;node_distance: router_b NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nasid_a
op_eq
id|nasid_b
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|router_a
op_eq
id|router_b
)paren
r_return
l_int|1
suffix:semicolon
id|router_distance
op_assign
l_int|100
suffix:semicolon
id|router_recurse
c_func
(paren
id|router_a
comma
id|router_b
comma
l_int|2
)paren
suffix:semicolon
r_return
id|router_distance
suffix:semicolon
)brace
DECL|function|init_topology_matrix
r_static
r_void
id|__init
id|init_topology_matrix
c_func
(paren
r_void
)paren
(brace
id|nasid_t
id|nasid
comma
id|nasid2
suffix:semicolon
id|cnodeid_t
id|row
comma
id|col
suffix:semicolon
r_for
c_loop
(paren
id|row
op_assign
l_int|0
suffix:semicolon
id|row
OL
id|MAX_COMPACT_NODES
suffix:semicolon
id|row
op_increment
)paren
r_for
c_loop
(paren
id|col
op_assign
l_int|0
suffix:semicolon
id|col
OL
id|MAX_COMPACT_NODES
suffix:semicolon
id|col
op_increment
)paren
id|__node_distances
(braket
id|row
)braket
(braket
id|col
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|row
op_assign
l_int|0
suffix:semicolon
id|row
OL
id|numnodes
suffix:semicolon
id|row
op_increment
)paren
(brace
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|row
)paren
suffix:semicolon
r_for
c_loop
(paren
id|col
op_assign
l_int|0
suffix:semicolon
id|col
OL
id|numnodes
suffix:semicolon
id|col
op_increment
)paren
(brace
id|nasid2
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|col
)paren
suffix:semicolon
id|__node_distances
(braket
id|row
)braket
(braket
id|col
)braket
op_assign
id|compute_node_distance
c_func
(paren
id|nasid
comma
id|nasid2
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|dump_topology
r_static
r_void
id|__init
id|dump_topology
c_func
(paren
r_void
)paren
(brace
id|nasid_t
id|nasid
suffix:semicolon
id|cnodeid_t
id|cnode
suffix:semicolon
id|lboard_t
op_star
id|brd
comma
op_star
id|dest_brd
suffix:semicolon
r_int
id|port
suffix:semicolon
r_int
id|router_num
op_assign
l_int|0
suffix:semicolon
id|klrou_t
op_star
id|router
suffix:semicolon
id|cnodeid_t
id|row
comma
id|col
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;************** Topology ********************&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;    &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|col
op_assign
l_int|0
suffix:semicolon
id|col
OL
id|numnodes
suffix:semicolon
id|col
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02d &quot;
comma
id|col
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|row
op_assign
l_int|0
suffix:semicolon
id|row
OL
id|numnodes
suffix:semicolon
id|row
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%02d  &quot;
comma
id|row
)paren
suffix:semicolon
r_for
c_loop
(paren
id|col
op_assign
l_int|0
suffix:semicolon
id|col
OL
id|numnodes
suffix:semicolon
id|col
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%2d &quot;
comma
id|node_distance
c_func
(paren
id|row
comma
id|col
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nasid
op_eq
op_minus
l_int|1
)paren
r_continue
suffix:semicolon
id|brd
op_assign
id|find_lboard_class
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
id|KLTYPE_ROUTER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|brd
)paren
r_continue
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|brd-&gt;brd_flags
op_amp
id|DUPLICATE_BOARD
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Router %d:&quot;
comma
id|router_num
)paren
suffix:semicolon
id|router_num
op_increment
suffix:semicolon
id|router
op_assign
(paren
id|klrou_t
op_star
)paren
id|NODE_OFFSET_TO_K0
c_func
(paren
id|NASID_GET
c_func
(paren
id|brd
)paren
comma
id|brd-&gt;brd_compts
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
l_int|1
suffix:semicolon
id|port
op_le
id|MAX_ROUTER_PORTS
suffix:semicolon
id|port
op_increment
)paren
(brace
r_if
c_cond
(paren
id|router-&gt;rou_port
(braket
id|port
)braket
dot
id|port_nasid
op_eq
id|INVALID_NASID
)paren
r_continue
suffix:semicolon
id|dest_brd
op_assign
(paren
id|lboard_t
op_star
)paren
id|NODE_OFFSET_TO_K0
c_func
(paren
id|router-&gt;rou_port
(braket
id|port
)braket
dot
id|port_nasid
comma
id|router-&gt;rou_port
(braket
id|port
)braket
dot
id|port_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dest_brd-&gt;brd_type
op_eq
id|KLTYPE_IP27
)paren
id|printk
c_func
(paren
l_string|&quot; %d&quot;
comma
id|dest_brd-&gt;brd_nasid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dest_brd-&gt;brd_type
op_eq
id|KLTYPE_ROUTER
)paren
id|printk
c_func
(paren
l_string|&quot; r&quot;
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
r_while
c_loop
(paren
(paren
id|brd
op_assign
id|find_lboard_class
c_func
(paren
id|KLCF_NEXT
c_func
(paren
id|brd
)paren
comma
id|KLTYPE_ROUTER
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|slot_getbasepfn
r_static
id|pfn_t
id|__init
id|slot_getbasepfn
c_func
(paren
id|cnodeid_t
id|cnode
comma
r_int
id|slot
)paren
(brace
id|nasid_t
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
suffix:semicolon
r_return
(paren
(paren
id|pfn_t
)paren
id|nasid
op_lshift
id|PFN_NASIDSHFT
)paren
op_or
(paren
id|slot
op_lshift
id|SLOT_PFNSHIFT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the number of pages of memory provided by the given slot&n; * on the specified node.&n; */
DECL|function|slot_getsize
r_static
id|pfn_t
id|__init
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
r_static
r_int
id|__init
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
r_static
id|pfn_t
id|__init
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
id|MAX_MEM_SLOTS
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
l_int|0
suffix:semicolon
)brace
DECL|function|slot_psize_compute
r_static
id|pfn_t
id|__init
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
r_return
l_int|0
suffix:semicolon
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
DECL|function|mlreset
r_static
r_void
id|__init
id|mlreset
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|master_nasid
op_assign
id|get_nasid
c_func
(paren
)paren
suffix:semicolon
id|fine_mode
op_assign
id|is_fine_dirmode
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Probe for all CPUs - this creates the cpumask and sets up the&n;&t; * mapping tables.  We need to do this as early as possible.&n;&t; */
macro_line|#ifdef CONFIG_SMP
id|cpu_node_probe
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|init_topology_matrix
c_func
(paren
)paren
suffix:semicolon
id|dump_topology
c_func
(paren
)paren
suffix:semicolon
id|gen_region_mask
c_func
(paren
op_amp
id|region_mask
comma
id|numnodes
)paren
suffix:semicolon
id|setup_replication_mask
c_func
(paren
id|numnodes
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set all nodes&squot; calias sizes to 8k&n;&t; */
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
id|nasid_t
id|nasid
suffix:semicolon
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|i
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Always have node 0 in the region mask, otherwise&n;&t;&t; * CALIAS accesses get exceptions since the hub&n;&t;&t; * thinks it is a node 0 address.&n;&t;&t; */
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|PI_REGION_PRESENT
comma
(paren
id|region_mask
op_or
l_int|1
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_REPLICATE_EXHANDLERS
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|PI_CALIAS_SIZE
comma
id|PI_CALIAS_SIZE_8K
)paren
suffix:semicolon
macro_line|#else
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|PI_CALIAS_SIZE
comma
id|PI_CALIAS_SIZE_0
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef LATER
multiline_comment|/*&n;&t;&t; * Set up all hubs to have a big window pointing at&n;&t;&t; * widget 0. Memory mode, widget 0, offset 0&n;&t;&t; */
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|IIO_ITTE
c_func
(paren
id|SWIN0_BIGWIN
)paren
comma
(paren
(paren
id|HUB_PIO_MAP_TO_MEM
op_lshift
id|IIO_ITTE_IOSP_SHIFT
)paren
op_or
(paren
l_int|0
op_lshift
id|IIO_ITTE_WIDGET_SHIFT
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|function|szmem
r_static
r_void
id|__init
id|szmem
c_func
(paren
r_void
)paren
(brace
id|pfn_t
id|slot_psize
comma
id|slot0sz
op_assign
l_int|0
comma
id|nodebytes
suffix:semicolon
multiline_comment|/* Hack to detect problem configs */
r_int
id|slot
comma
id|ignore
suffix:semicolon
id|cnodeid_t
id|node
suffix:semicolon
id|num_physpages
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
id|numnodes
suffix:semicolon
id|node
op_increment
)paren
(brace
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
id|MAX_MEM_SLOTS
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
multiline_comment|/*&n;&t;&t;&t; * We need to refine the hack when we have replicated&n;&t;&t;&t; * kernel text.&n;&t;&t;&t; */
id|nodebytes
op_add_assign
(paren
l_int|1LL
op_lshift
id|SLOT_SHIFT
)paren
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
id|MAX_MEM_SLOTS
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|num_physpages
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
)brace
DECL|function|node_mem_init
r_static
r_void
id|__init
id|node_mem_init
c_func
(paren
id|cnodeid_t
id|node
)paren
(brace
id|pfn_t
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
id|pfn_t
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
id|pfn_t
id|slot_freepfn
op_assign
id|node_getfirstfree
c_func
(paren
id|node
)paren
suffix:semicolon
r_struct
id|pglist_data
op_star
id|pd
suffix:semicolon
r_int
r_int
id|bootmap_size
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate the node data structures on the node first.&n;&t; */
id|__node_data
(braket
id|node
)braket
op_assign
id|__va
c_func
(paren
id|slot_freepfn
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|pd
op_assign
id|NODE_DATA
c_func
(paren
id|node
)paren
suffix:semicolon
id|pd-&gt;bdata
op_assign
op_amp
id|plat_node_bdata
(braket
id|node
)braket
suffix:semicolon
id|cpus_clear
c_func
(paren
id|hub_data
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|h_cpus
)paren
suffix:semicolon
id|slot_freepfn
op_add_assign
id|PFN_UP
c_func
(paren
r_sizeof
(paren
r_struct
id|pglist_data
)paren
op_plus
r_sizeof
(paren
r_struct
id|hub_data
)paren
)paren
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
multiline_comment|/*&n; * A node with nothing.  We use it to avoid any special casing in&n; * node_to_cpumask&n; */
DECL|variable|null_node
r_static
r_struct
id|node_data
id|null_node
op_assign
(brace
dot
id|hub
op_assign
(brace
dot
id|h_cpus
op_assign
id|CPU_MASK_NONE
)brace
)brace
suffix:semicolon
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
id|cnodeid_t
id|node
suffix:semicolon
id|mlreset
c_func
(paren
)paren
suffix:semicolon
id|szmem
c_func
(paren
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
id|MAX_COMPACT_NODES
suffix:semicolon
id|node
op_increment
)paren
(brace
r_if
c_cond
(paren
id|node
OL
id|numnodes
)paren
(brace
id|node_mem_init
c_func
(paren
id|node
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|__node_data
(braket
id|node
)braket
op_assign
op_amp
id|null_node
suffix:semicolon
)brace
)brace
DECL|function|prom_free_prom_memory
r_int
r_int
id|__init
id|prom_free_prom_memory
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* We got nothing to free here ...  */
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_void
id|pagetable_init
c_func
(paren
r_void
)paren
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
DECL|function|paging_init
r_void
id|__init
id|paging_init
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
id|node
suffix:semicolon
id|pagetable_init
c_func
(paren
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
op_plus
l_int|1
suffix:semicolon
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|end_pfn
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
id|zones_size
comma
id|start_pfn
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end_pfn
OG
id|max_low_pfn
)paren
id|max_low_pfn
op_assign
id|end_pfn
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
r_int
r_int
id|codesize
comma
id|datasize
comma
id|initsize
comma
id|tmp
suffix:semicolon
r_int
id|node
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
id|num_physpages
op_lshift
id|PAGE_SHIFT
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
r_int
id|slot
comma
id|numslots
suffix:semicolon
r_struct
id|page
op_star
id|end
comma
op_star
id|p
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
id|node
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We need to manually do the other slots.&n;&t;&t; */
id|numslots
op_assign
id|node_getlastslot
c_func
(paren
id|node
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
id|p
op_assign
id|NODE_DATA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|node_mem_map
op_plus
(paren
id|slot_getbasepfn
c_func
(paren
id|node
comma
id|slot
)paren
op_minus
id|slot_getbasepfn
c_func
(paren
id|node
comma
l_int|0
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Free valid memory in current slot.&n;&t;&t;&t; */
r_for
c_loop
(paren
id|end
op_assign
id|p
op_plus
id|slot_getsize
c_func
(paren
id|node
comma
id|slot
)paren
suffix:semicolon
id|p
OL
id|end
suffix:semicolon
id|p
op_increment
)paren
(brace
multiline_comment|/* if (!page_is_ram(pgnr)) continue; */
multiline_comment|/* commented out until page_is_ram works */
id|ClearPageReserved
c_func
(paren
id|p
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|p
comma
l_int|1
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|p
)paren
suffix:semicolon
id|totalram_pages
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
id|tmp
op_assign
id|nr_free_pages
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Memory: %luk/%luk available (%ldk kernel code, &quot;
l_string|&quot;%ldk reserved, %ldk data, %ldk init, %ldk highmem)&bslash;n&quot;
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
comma
(paren
r_int
r_int
)paren
(paren
id|totalhigh_pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
)paren
suffix:semicolon
)brace
eof
