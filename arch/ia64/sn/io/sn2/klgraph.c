multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
multiline_comment|/*&n; * klgraph.c-&n; *      This file specifies the interface between the kernel and the PROM&squot;s&n; *      configuration data structures.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/hcl_util.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
multiline_comment|/* #define KLGRAPH_DEBUG 1 */
macro_line|#ifdef KLGRAPH_DEBUG
DECL|macro|GRPRINTF
mdefine_line|#define GRPRINTF(x)&t;printk x
macro_line|#else
DECL|macro|GRPRINTF
mdefine_line|#define GRPRINTF(x)
macro_line|#endif
r_void
id|mark_cpuvertex_as_cpu
c_func
(paren
id|vertex_hdl_t
id|vhdl
comma
id|cpuid_t
id|cpuid
)paren
suffix:semicolon
multiline_comment|/* ARGSUSED */
r_static
r_void
id|__init
DECL|function|klhwg_add_hub
id|klhwg_add_hub
c_func
(paren
id|vertex_hdl_t
id|node_vertex
comma
id|klhub_t
op_star
id|hub
comma
id|cnodeid_t
id|cnode
)paren
(brace
id|vertex_hdl_t
id|myhubv
suffix:semicolon
id|vertex_hdl_t
id|hub_mon
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_extern
r_struct
id|file_operations
id|shub_mon_fops
suffix:semicolon
id|hwgraph_path_add
c_func
(paren
id|node_vertex
comma
id|EDGE_LBL_HUB
comma
op_amp
id|myhubv
)paren
suffix:semicolon
id|HWGRAPH_DEBUG
c_func
(paren
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|__LINE__
comma
id|myhubv
comma
l_int|NULL
comma
l_string|&quot;Created path for hub vertex for Shub node.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|rc
op_assign
id|device_master_set
c_func
(paren
id|myhubv
comma
id|node_vertex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;klhwg_add_hub: Unable to create hub vertex.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|hub_mon
op_assign
id|hwgraph_register
c_func
(paren
id|myhubv
comma
id|EDGE_LBL_PERFMON
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
op_or
id|S_IRGRP
comma
l_int|0
comma
l_int|0
comma
op_amp
id|shub_mon_fops
comma
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|cnode
)paren
suffix:semicolon
)brace
multiline_comment|/* ARGSUSED */
r_static
r_void
id|__init
DECL|function|klhwg_add_disabled_cpu
id|klhwg_add_disabled_cpu
c_func
(paren
id|vertex_hdl_t
id|node_vertex
comma
id|cnodeid_t
id|cnode
comma
id|klcpu_t
op_star
id|cpu
comma
id|slotid_t
id|slot
)paren
(brace
id|vertex_hdl_t
id|my_cpu
suffix:semicolon
r_char
id|name
(braket
l_int|120
)braket
suffix:semicolon
id|cpuid_t
id|cpu_id
suffix:semicolon
id|nasid_t
id|nasid
suffix:semicolon
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
suffix:semicolon
id|cpu_id
op_assign
id|nasid_slice_to_cpuid
c_func
(paren
id|nasid
comma
id|cpu-&gt;cpu_info.physid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_id
op_ne
op_minus
l_int|1
)paren
(brace
id|snprintf
c_func
(paren
id|name
comma
l_int|120
comma
l_string|&quot;%s/%s/%c&quot;
comma
id|EDGE_LBL_DISABLED
comma
id|EDGE_LBL_CPU
comma
l_char|&squot;a&squot;
op_plus
id|cpu-&gt;cpu_info.physid
)paren
suffix:semicolon
(paren
r_void
)paren
id|hwgraph_path_add
c_func
(paren
id|node_vertex
comma
id|name
comma
op_amp
id|my_cpu
)paren
suffix:semicolon
id|HWGRAPH_DEBUG
c_func
(paren
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|__LINE__
comma
id|my_cpu
comma
l_int|NULL
comma
l_string|&quot;Created path for disabled cpu slice.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|mark_cpuvertex_as_cpu
c_func
(paren
id|my_cpu
comma
id|cpu_id
)paren
suffix:semicolon
id|device_master_set
c_func
(paren
id|my_cpu
comma
id|node_vertex
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* ARGSUSED */
r_static
r_void
id|__init
DECL|function|klhwg_add_cpu
id|klhwg_add_cpu
c_func
(paren
id|vertex_hdl_t
id|node_vertex
comma
id|cnodeid_t
id|cnode
comma
id|klcpu_t
op_star
id|cpu
)paren
(brace
id|vertex_hdl_t
id|my_cpu
comma
id|cpu_dir
suffix:semicolon
r_char
id|name
(braket
l_int|120
)braket
suffix:semicolon
id|cpuid_t
id|cpu_id
suffix:semicolon
id|nasid_t
id|nasid
suffix:semicolon
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
suffix:semicolon
id|cpu_id
op_assign
id|nasid_slice_to_cpuid
c_func
(paren
id|nasid
comma
id|cpu-&gt;cpu_info.physid
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|name
comma
l_int|120
comma
l_string|&quot;%s/%d/%c&quot;
comma
id|EDGE_LBL_CPUBUS
comma
l_int|0
comma
l_char|&squot;a&squot;
op_plus
id|cpu-&gt;cpu_info.physid
)paren
suffix:semicolon
(paren
r_void
)paren
id|hwgraph_path_add
c_func
(paren
id|node_vertex
comma
id|name
comma
op_amp
id|my_cpu
)paren
suffix:semicolon
id|HWGRAPH_DEBUG
c_func
(paren
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|__LINE__
comma
id|my_cpu
comma
l_int|NULL
comma
l_string|&quot;Created path for active cpu slice.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|mark_cpuvertex_as_cpu
c_func
(paren
id|my_cpu
comma
id|cpu_id
)paren
suffix:semicolon
id|device_master_set
c_func
(paren
id|my_cpu
comma
id|node_vertex
)paren
suffix:semicolon
multiline_comment|/* Add an alias under the node&squot;s CPU directory */
r_if
c_cond
(paren
id|hwgraph_edge_get
c_func
(paren
id|node_vertex
comma
id|EDGE_LBL_CPU
comma
op_amp
id|cpu_dir
)paren
op_eq
id|GRAPH_SUCCESS
)paren
(brace
id|snprintf
c_func
(paren
id|name
comma
l_int|120
comma
l_string|&quot;%c&quot;
comma
l_char|&squot;a&squot;
op_plus
id|cpu-&gt;cpu_info.physid
)paren
suffix:semicolon
(paren
r_void
)paren
id|hwgraph_edge_add
c_func
(paren
id|cpu_dir
comma
id|my_cpu
comma
id|name
)paren
suffix:semicolon
id|HWGRAPH_DEBUG
c_func
(paren
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|__LINE__
comma
id|cpu_dir
comma
id|my_cpu
comma
l_string|&quot;Created % from vhdl1 to vhdl2.&bslash;n&quot;
comma
id|name
)paren
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
id|__init
DECL|function|klhwg_add_xbow
id|klhwg_add_xbow
c_func
(paren
id|cnodeid_t
id|cnode
comma
id|nasid_t
id|nasid
)paren
(brace
id|lboard_t
op_star
id|brd
suffix:semicolon
id|klxbow_t
op_star
id|xbow_p
suffix:semicolon
id|nasid_t
id|hub_nasid
suffix:semicolon
id|cnodeid_t
id|hub_cnode
suffix:semicolon
r_int
id|widgetnum
suffix:semicolon
id|vertex_hdl_t
id|xbow_v
comma
id|hubv
suffix:semicolon
multiline_comment|/*REFERENCED*/
id|graph_error_t
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|brd
op_assign
id|find_lboard_nasid
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
id|nasid
comma
id|KLTYPE_IOBRICK_XBOW
)paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|KL_CONFIG_DUPLICATE_BOARD
c_func
(paren
id|brd
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|xbow_p
op_assign
(paren
id|klxbow_t
op_star
)paren
id|find_component
c_func
(paren
id|brd
comma
l_int|NULL
comma
id|KLSTRUCT_XBOW
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|widgetnum
op_assign
id|HUB_WIDGET_ID_MIN
suffix:semicolon
id|widgetnum
op_le
id|HUB_WIDGET_ID_MAX
suffix:semicolon
id|widgetnum
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|XBOW_PORT_TYPE_HUB
c_func
(paren
id|xbow_p
comma
id|widgetnum
)paren
)paren
r_continue
suffix:semicolon
id|hub_nasid
op_assign
id|XBOW_PORT_NASID
c_func
(paren
id|xbow_p
comma
id|widgetnum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hub_nasid
op_eq
id|INVALID_NASID
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;hub widget %d, skipping xbow graph&bslash;n&quot;
comma
id|widgetnum
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|hub_cnode
op_assign
id|NASID_TO_COMPACT_NODEID
c_func
(paren
id|hub_nasid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hub_cnode
op_eq
id|INVALID_CNODEID
)paren
(brace
r_continue
suffix:semicolon
)brace
id|hubv
op_assign
id|cnodeid_to_vertex
c_func
(paren
id|hub_cnode
)paren
suffix:semicolon
id|err
op_assign
id|hwgraph_path_add
c_func
(paren
id|hubv
comma
id|EDGE_LBL_XTALK
comma
op_amp
id|xbow_v
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
id|GRAPH_SUCCESS
)paren
(brace
r_if
c_cond
(paren
id|err
op_eq
id|GRAPH_DUP
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;klhwg_add_xbow: Check for &quot;
l_string|&quot;working routers and router links!&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;klhwg_add_xbow: Failed to add &quot;
l_string|&quot;edge: vertex 0x%p to vertex 0x%p,&quot;
l_string|&quot;error %d&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|hubv
comma
(paren
r_void
op_star
)paren
id|xbow_v
comma
id|err
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|HWGRAPH_DEBUG
c_func
(paren
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|__LINE__
comma
id|xbow_v
comma
l_int|NULL
comma
l_string|&quot;Created path for xtalk.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|xswitch_vertex_init
c_func
(paren
id|xbow_v
)paren
suffix:semicolon
id|NODEPDA
c_func
(paren
id|hub_cnode
)paren
op_member_access_from_pointer
id|xbow_vhdl
op_assign
id|xbow_v
suffix:semicolon
multiline_comment|/*&n;&t;&t; * XXX - This won&squot;t work is we ever hook up two hubs&n;&t;&t; * by crosstown through a crossbow.&n;&t;&t; */
r_if
c_cond
(paren
id|hub_nasid
op_ne
id|nasid
)paren
(brace
id|NODEPDA
c_func
(paren
id|hub_cnode
)paren
op_member_access_from_pointer
id|xbow_peer
op_assign
id|nasid
suffix:semicolon
id|NODEPDA
c_func
(paren
id|NASID_TO_COMPACT_NODEID
c_func
(paren
id|nasid
)paren
)paren
op_member_access_from_pointer
id|xbow_peer
op_assign
id|hub_nasid
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* ARGSUSED */
r_static
r_void
id|__init
DECL|function|klhwg_add_node
id|klhwg_add_node
c_func
(paren
id|vertex_hdl_t
id|hwgraph_root
comma
id|cnodeid_t
id|cnode
)paren
(brace
id|nasid_t
id|nasid
suffix:semicolon
id|lboard_t
op_star
id|brd
suffix:semicolon
id|klhub_t
op_star
id|hub
suffix:semicolon
id|vertex_hdl_t
id|node_vertex
op_assign
l_int|NULL
suffix:semicolon
r_char
id|path_buffer
(braket
l_int|100
)braket
suffix:semicolon
r_int
id|rv
suffix:semicolon
r_char
op_star
id|s
suffix:semicolon
r_int
id|board_disabled
op_assign
l_int|0
suffix:semicolon
id|klcpu_t
op_star
id|cpu
suffix:semicolon
id|vertex_hdl_t
id|cpu_dir
suffix:semicolon
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
suffix:semicolon
id|brd
op_assign
id|find_lboard_any
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
id|KLTYPE_SNIA
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|brd
)paren
suffix:semicolon
multiline_comment|/* Generate a hardware graph path for this board. */
id|board_to_path
c_func
(paren
id|brd
comma
id|path_buffer
)paren
suffix:semicolon
id|rv
op_assign
id|hwgraph_path_add
c_func
(paren
id|hwgraph_root
comma
id|path_buffer
comma
op_amp
id|node_vertex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
op_ne
id|GRAPH_SUCCESS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Node vertex creation failed.  Path == %s&quot;
comma
id|path_buffer
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|HWGRAPH_DEBUG
c_func
(paren
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|__LINE__
comma
id|node_vertex
comma
l_int|NULL
comma
l_string|&quot;Created path for SHUB node.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|hub
op_assign
(paren
id|klhub_t
op_star
)paren
id|find_first_component
c_func
(paren
id|brd
comma
id|KLSTRUCT_HUB
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hub
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hub-&gt;hub_info.flags
op_amp
id|KLINFO_ENABLE
)paren
(brace
id|board_disabled
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|board_disabled
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|board_disabled
)paren
(brace
id|mark_nodevertex_as_node
c_func
(paren
id|node_vertex
comma
id|cnode
)paren
suffix:semicolon
id|s
op_assign
id|dev_to_name
c_func
(paren
id|node_vertex
comma
id|path_buffer
comma
r_sizeof
(paren
id|path_buffer
)paren
)paren
suffix:semicolon
id|NODEPDA
c_func
(paren
id|cnode
)paren
op_member_access_from_pointer
id|hwg_node_name
op_assign
id|kmalloc
c_func
(paren
id|strlen
c_func
(paren
id|s
)paren
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|NODEPDA
c_func
(paren
id|cnode
)paren
op_member_access_from_pointer
id|hwg_node_name
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: no memory&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|NODEPDA
c_func
(paren
id|cnode
)paren
op_member_access_from_pointer
id|hwg_node_name
comma
id|s
)paren
suffix:semicolon
id|hubinfo_set
c_func
(paren
id|node_vertex
comma
id|NODEPDA
c_func
(paren
id|cnode
)paren
op_member_access_from_pointer
id|pdinfo
)paren
suffix:semicolon
id|NODEPDA
c_func
(paren
id|cnode
)paren
op_member_access_from_pointer
id|slotdesc
op_assign
id|brd-&gt;brd_slot
suffix:semicolon
id|NODEPDA
c_func
(paren
id|cnode
)paren
op_member_access_from_pointer
id|geoid
op_assign
id|brd-&gt;brd_geoid
suffix:semicolon
id|NODEPDA
c_func
(paren
id|cnode
)paren
op_member_access_from_pointer
id|module
op_assign
id|module_lookup
c_func
(paren
id|geo_module
c_func
(paren
id|brd-&gt;brd_geoid
)paren
)paren
suffix:semicolon
id|klhwg_add_hub
c_func
(paren
id|node_vertex
comma
id|hub
comma
id|cnode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If there&squot;s at least 1 CPU, add a &quot;cpu&quot; directory to represent&n;&t; * the collection of all CPUs attached to this node.&n;&t; */
id|cpu
op_assign
(paren
id|klcpu_t
op_star
)paren
id|find_first_component
c_func
(paren
id|brd
comma
id|KLSTRUCT_CPU
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu
)paren
(brace
id|graph_error_t
id|rv
suffix:semicolon
id|rv
op_assign
id|hwgraph_path_add
c_func
(paren
id|node_vertex
comma
id|EDGE_LBL_CPU
comma
op_amp
id|cpu_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
op_ne
id|GRAPH_SUCCESS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;klhwg_add_node: Cannot create CPU directory&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|HWGRAPH_DEBUG
c_func
(paren
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|__LINE__
comma
id|cpu_dir
comma
l_int|NULL
comma
l_string|&quot;Created cpu directiry on SHUB node.&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cpu
)paren
(brace
id|cpuid_t
id|cpu_id
suffix:semicolon
id|cpu_id
op_assign
id|nasid_slice_to_cpuid
c_func
(paren
id|nasid
comma
id|cpu-&gt;cpu_info.physid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|cpu_id
)paren
)paren
id|klhwg_add_cpu
c_func
(paren
id|node_vertex
comma
id|cnode
comma
id|cpu
)paren
suffix:semicolon
r_else
id|klhwg_add_disabled_cpu
c_func
(paren
id|node_vertex
comma
id|cnode
comma
id|cpu
comma
id|brd-&gt;brd_slot
)paren
suffix:semicolon
id|cpu
op_assign
(paren
id|klcpu_t
op_star
)paren
id|find_component
c_func
(paren
id|brd
comma
(paren
id|klinfo_t
op_star
)paren
id|cpu
comma
id|KLSTRUCT_CPU
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* ARGSUSED */
r_static
r_void
id|__init
DECL|function|klhwg_add_all_routers
id|klhwg_add_all_routers
c_func
(paren
id|vertex_hdl_t
id|hwgraph_root
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
suffix:semicolon
id|vertex_hdl_t
id|node_vertex
suffix:semicolon
r_char
id|path_buffer
(braket
l_int|100
)braket
suffix:semicolon
r_int
id|rv
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
id|brd
op_assign
id|find_lboard_class_any
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
multiline_comment|/* No routers stored in this node&squot;s memory */
r_continue
suffix:semicolon
r_do
(brace
id|ASSERT
c_func
(paren
id|brd
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t add duplicate boards. */
r_if
c_cond
(paren
id|brd-&gt;brd_flags
op_amp
id|DUPLICATE_BOARD
)paren
r_continue
suffix:semicolon
multiline_comment|/* Generate a hardware graph path for this board. */
id|board_to_path
c_func
(paren
id|brd
comma
id|path_buffer
)paren
suffix:semicolon
multiline_comment|/* Add the router */
id|rv
op_assign
id|hwgraph_path_add
c_func
(paren
id|hwgraph_root
comma
id|path_buffer
comma
op_amp
id|node_vertex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
op_ne
id|GRAPH_SUCCESS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Router vertex creation &quot;
l_string|&quot;failed.  Path == %s&quot;
comma
id|path_buffer
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|HWGRAPH_DEBUG
c_func
(paren
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|__LINE__
comma
id|node_vertex
comma
l_int|NULL
comma
l_string|&quot;Created router path.&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* Find the rest of the routers stored on this node. */
)brace
r_while
c_loop
(paren
(paren
id|brd
op_assign
id|find_lboard_class_any
c_func
(paren
id|KLCF_NEXT_ANY
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
multiline_comment|/* ARGSUSED */
r_static
r_void
id|__init
DECL|function|klhwg_connect_one_router
id|klhwg_connect_one_router
c_func
(paren
id|vertex_hdl_t
id|hwgraph_root
comma
id|lboard_t
op_star
id|brd
comma
id|cnodeid_t
id|cnode
comma
id|nasid_t
id|nasid
)paren
(brace
id|klrou_t
op_star
id|router
suffix:semicolon
r_char
id|path_buffer
(braket
l_int|50
)braket
suffix:semicolon
r_char
id|dest_path
(braket
l_int|50
)braket
suffix:semicolon
id|vertex_hdl_t
id|router_hndl
suffix:semicolon
id|vertex_hdl_t
id|dest_hndl
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_int
id|port
suffix:semicolon
id|lboard_t
op_star
id|dest_brd
suffix:semicolon
multiline_comment|/* Don&squot;t add duplicate boards. */
r_if
c_cond
(paren
id|brd-&gt;brd_flags
op_amp
id|DUPLICATE_BOARD
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Generate a hardware graph path for this board. */
id|board_to_path
c_func
(paren
id|brd
comma
id|path_buffer
)paren
suffix:semicolon
id|rc
op_assign
id|hwgraph_traverse
c_func
(paren
id|hwgraph_root
comma
id|path_buffer
comma
op_amp
id|router_hndl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|GRAPH_SUCCESS
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|GRAPH_SUCCESS
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Can&squot;t find router: %s&quot;
comma
id|path_buffer
)paren
suffix:semicolon
multiline_comment|/* We don&squot;t know what to do with multiple router components */
r_if
c_cond
(paren
id|brd-&gt;brd_numcompts
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;klhwg_connect_one_router: %d cmpts on router&bslash;n&quot;
comma
id|brd-&gt;brd_numcompts
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Convert component 0 to klrou_t ptr */
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
multiline_comment|/* See if the port&squot;s active */
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
(brace
id|GRPRINTF
c_func
(paren
(paren
l_string|&quot;klhwg_connect_one_router: port %d inactive.&bslash;n&quot;
comma
id|port
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|NASID_TO_COMPACT_NODEID
c_func
(paren
id|router-&gt;rou_port
(braket
id|port
)braket
dot
id|port_nasid
)paren
op_eq
id|INVALID_CNODEID
)paren
(brace
r_continue
suffix:semicolon
)brace
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
multiline_comment|/* Generate a hardware graph path for this board. */
id|board_to_path
c_func
(paren
id|dest_brd
comma
id|dest_path
)paren
suffix:semicolon
id|rc
op_assign
id|hwgraph_traverse
c_func
(paren
id|hwgraph_root
comma
id|dest_path
comma
op_amp
id|dest_hndl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|GRAPH_SUCCESS
)paren
(brace
r_if
c_cond
(paren
id|KL_CONFIG_DUPLICATE_BOARD
c_func
(paren
id|dest_brd
)paren
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Can&squot;t find router: %s&quot;
comma
id|dest_path
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|dest_path
comma
l_string|&quot;%d&quot;
comma
id|port
)paren
suffix:semicolon
id|rc
op_assign
id|hwgraph_edge_add
c_func
(paren
id|router_hndl
comma
id|dest_hndl
comma
id|dest_path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
id|GRAPH_DUP
)paren
(brace
id|GRPRINTF
c_func
(paren
(paren
l_string|&quot;Skipping port %d. nasid %d %s/%s&bslash;n&quot;
comma
id|port
comma
id|router-&gt;rou_port
(braket
id|port
)braket
dot
id|port_nasid
comma
id|path_buffer
comma
id|dest_path
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rc
op_ne
id|GRAPH_SUCCESS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Can&squot;t create edge: %s/%s to vertex 0x%p error 0x%x&bslash;n&quot;
comma
id|path_buffer
comma
id|dest_path
comma
(paren
r_void
op_star
)paren
id|dest_hndl
comma
id|rc
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|HWGRAPH_DEBUG
c_func
(paren
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|__LINE__
comma
id|router_hndl
comma
id|dest_hndl
comma
l_string|&quot;Created edge %s from vhdl1 to vhdl2.&bslash;n&quot;
comma
id|dest_path
)paren
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
id|__init
DECL|function|klhwg_connect_routers
id|klhwg_connect_routers
c_func
(paren
id|vertex_hdl_t
id|hwgraph_root
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
id|brd
op_assign
id|find_lboard_class_any
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
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
suffix:semicolon
id|klhwg_connect_one_router
c_func
(paren
id|hwgraph_root
comma
id|brd
comma
id|cnode
comma
id|nasid
)paren
suffix:semicolon
multiline_comment|/* Find the rest of the routers stored on this node. */
)brace
r_while
c_loop
(paren
(paren
id|brd
op_assign
id|find_lboard_class_any
c_func
(paren
id|KLCF_NEXT_ANY
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
r_static
r_void
id|__init
DECL|function|klhwg_connect_hubs
id|klhwg_connect_hubs
c_func
(paren
id|vertex_hdl_t
id|hwgraph_root
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
suffix:semicolon
id|klhub_t
op_star
id|hub
suffix:semicolon
id|lboard_t
op_star
id|dest_brd
suffix:semicolon
id|vertex_hdl_t
id|hub_hndl
suffix:semicolon
id|vertex_hdl_t
id|dest_hndl
suffix:semicolon
r_char
id|path_buffer
(braket
l_int|50
)braket
suffix:semicolon
r_char
id|dest_path
(braket
l_int|50
)braket
suffix:semicolon
id|graph_error_t
id|rc
suffix:semicolon
r_int
id|port
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
id|numionodes
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
id|brd
op_assign
id|find_lboard_any
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
id|KLTYPE_SNIA
)paren
suffix:semicolon
id|hub
op_assign
(paren
id|klhub_t
op_star
)paren
id|find_first_component
c_func
(paren
id|brd
comma
id|KLSTRUCT_HUB
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hub
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
id|MAX_NI_PORTS
suffix:semicolon
id|port
op_increment
)paren
(brace
r_if
c_cond
(paren
id|hub-&gt;hub_port
(braket
id|port
)braket
dot
id|port_nasid
op_eq
id|INVALID_NASID
)paren
(brace
r_continue
suffix:semicolon
multiline_comment|/* Port not active */
)brace
r_if
c_cond
(paren
id|NASID_TO_COMPACT_NODEID
c_func
(paren
id|hub-&gt;hub_port
(braket
id|port
)braket
dot
id|port_nasid
)paren
op_eq
id|INVALID_CNODEID
)paren
r_continue
suffix:semicolon
multiline_comment|/* Generate a hardware graph path for this board. */
id|board_to_path
c_func
(paren
id|brd
comma
id|path_buffer
)paren
suffix:semicolon
id|rc
op_assign
id|hwgraph_traverse
c_func
(paren
id|hwgraph_root
comma
id|path_buffer
comma
op_amp
id|hub_hndl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|GRAPH_SUCCESS
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Can&squot;t find hub: %s&quot;
comma
id|path_buffer
)paren
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
id|hub-&gt;hub_port
(braket
id|port
)braket
dot
id|port_nasid
comma
id|hub-&gt;hub_port
(braket
id|port
)braket
dot
id|port_offset
)paren
suffix:semicolon
multiline_comment|/* Generate a hardware graph path for this board. */
id|board_to_path
c_func
(paren
id|dest_brd
comma
id|dest_path
)paren
suffix:semicolon
id|rc
op_assign
id|hwgraph_traverse
c_func
(paren
id|hwgraph_root
comma
id|dest_path
comma
op_amp
id|dest_hndl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|GRAPH_SUCCESS
)paren
(brace
r_if
c_cond
(paren
id|KL_CONFIG_DUPLICATE_BOARD
c_func
(paren
id|dest_brd
)paren
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Can&squot;t find board: %s&quot;
comma
id|dest_path
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
id|rc
op_assign
id|hwgraph_path_add
c_func
(paren
id|hub_hndl
comma
id|EDGE_LBL_INTERCONNECT
comma
op_amp
id|hub_hndl
)paren
suffix:semicolon
id|HWGRAPH_DEBUG
c_func
(paren
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|__LINE__
comma
id|hub_hndl
comma
l_int|NULL
comma
l_string|&quot;Created link path.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s/%s&quot;
comma
id|path_buffer
comma
id|EDGE_LBL_INTERCONNECT
)paren
suffix:semicolon
id|rc
op_assign
id|hwgraph_traverse
c_func
(paren
id|hwgraph_root
comma
id|buf
comma
op_amp
id|hub_hndl
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d&quot;
comma
id|port
)paren
suffix:semicolon
id|rc
op_assign
id|hwgraph_edge_add
c_func
(paren
id|hub_hndl
comma
id|dest_hndl
comma
id|buf
)paren
suffix:semicolon
id|HWGRAPH_DEBUG
c_func
(paren
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|__LINE__
comma
id|hub_hndl
comma
id|dest_hndl
comma
l_string|&quot;Created edge %s from vhdl1 to vhdl2.&bslash;n&quot;
comma
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|GRAPH_SUCCESS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Can&squot;t create edge: %s/%s to vertex 0x%p, error 0x%x&bslash;n&quot;
comma
id|path_buffer
comma
id|dest_path
comma
(paren
r_void
op_star
)paren
id|dest_hndl
comma
id|rc
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
r_void
id|__init
DECL|function|klhwg_add_all_modules
id|klhwg_add_all_modules
c_func
(paren
id|vertex_hdl_t
id|hwgraph_root
)paren
(brace
id|cmoduleid_t
id|cm
suffix:semicolon
r_char
id|name
(braket
l_int|128
)braket
suffix:semicolon
id|vertex_hdl_t
id|vhdl
suffix:semicolon
id|vertex_hdl_t
id|module_vhdl
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_char
id|buffer
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Add devices under each module */
r_for
c_loop
(paren
id|cm
op_assign
l_int|0
suffix:semicolon
id|cm
OL
id|nummodules
suffix:semicolon
id|cm
op_increment
)paren
(brace
multiline_comment|/* Use module as module vertex fastinfo */
id|memset
c_func
(paren
id|buffer
comma
l_int|0
comma
l_int|16
)paren
suffix:semicolon
id|format_module_id
c_func
(paren
id|buffer
comma
id|modules
(braket
id|cm
)braket
op_member_access_from_pointer
id|id
comma
id|MODULE_FORMAT_BRIEF
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
id|EDGE_LBL_MODULE
l_string|&quot;/%s&quot;
comma
id|buffer
)paren
suffix:semicolon
id|rc
op_assign
id|hwgraph_path_add
c_func
(paren
id|hwgraph_root
comma
id|name
comma
op_amp
id|module_vhdl
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|rc
op_eq
id|GRAPH_SUCCESS
)paren
suffix:semicolon
id|rc
op_assign
id|rc
suffix:semicolon
id|HWGRAPH_DEBUG
c_func
(paren
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|__LINE__
comma
id|module_vhdl
comma
l_int|NULL
comma
l_string|&quot;Created module path.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|hwgraph_fastinfo_set
c_func
(paren
id|module_vhdl
comma
(paren
id|arbitrary_info_t
)paren
id|modules
(braket
id|cm
)braket
)paren
suffix:semicolon
multiline_comment|/* Add system controller */
id|sprintf
c_func
(paren
id|name
comma
id|EDGE_LBL_MODULE
l_string|&quot;/%s/&quot;
id|EDGE_LBL_L1
comma
id|buffer
)paren
suffix:semicolon
id|rc
op_assign
id|hwgraph_path_add
c_func
(paren
id|hwgraph_root
comma
id|name
comma
op_amp
id|vhdl
)paren
suffix:semicolon
id|ASSERT_ALWAYS
c_func
(paren
id|rc
op_eq
id|GRAPH_SUCCESS
)paren
suffix:semicolon
id|rc
op_assign
id|rc
suffix:semicolon
id|HWGRAPH_DEBUG
c_func
(paren
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|__LINE__
comma
id|vhdl
comma
l_int|NULL
comma
l_string|&quot;Created L1 path.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|hwgraph_info_add_LBL
c_func
(paren
id|vhdl
comma
id|INFO_LBL_ELSC
comma
(paren
id|arbitrary_info_t
)paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_void
id|__init
DECL|function|klhwg_add_all_nodes
id|klhwg_add_all_nodes
c_func
(paren
id|vertex_hdl_t
id|hwgraph_root
)paren
(brace
id|cnodeid_t
id|cnode
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
id|numionodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
id|klhwg_add_node
c_func
(paren
id|hwgraph_root
comma
id|cnode
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
id|numionodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
id|klhwg_add_xbow
c_func
(paren
id|cnode
comma
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * As for router hardware inventory information, we set this&n;&t; * up in router.c. &n;&t; */
id|klhwg_add_all_routers
c_func
(paren
id|hwgraph_root
)paren
suffix:semicolon
id|klhwg_connect_routers
c_func
(paren
id|hwgraph_root
)paren
suffix:semicolon
id|klhwg_connect_hubs
c_func
(paren
id|hwgraph_root
)paren
suffix:semicolon
)brace
eof
