multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/labelcl.h&gt;
macro_line|#include &lt;asm/sn/pci/bridge.h&gt;
macro_line|#include &lt;asm/sn/ioerror_handling.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/slotnum.h&gt;
macro_line|#include &lt;asm/sn/vector.h&gt;
multiline_comment|/******&n; ****** hack defines ......&n; ******/
DECL|variable|pcibr_prefetch_enable_rev
DECL|variable|pcibr_wg_enable_rev
r_int
id|pcibr_prefetch_enable_rev
comma
id|pcibr_wg_enable_rev
suffix:semicolon
DECL|variable|default_intr_pri
r_int
id|default_intr_pri
suffix:semicolon
DECL|variable|force_fire_and_forget
r_int
id|force_fire_and_forget
suffix:semicolon
DECL|variable|ignore_conveyor_override
r_int
id|ignore_conveyor_override
suffix:semicolon
DECL|variable|dummy_vrtx
id|devfs_handle_t
id|dummy_vrtx
suffix:semicolon
multiline_comment|/* Needed for cpuid_to_vertex() in hack.h */
multiline_comment|/* ARGSUSED */
DECL|function|hub_widgetdev_enable
r_void
id|hub_widgetdev_enable
c_func
(paren
id|devfs_handle_t
id|xconn_vhdl
comma
r_int
id|devnum
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;hub_widgetdev_enable&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* ARGSUSED */
DECL|function|hub_widgetdev_shutdown
r_void
id|hub_widgetdev_shutdown
c_func
(paren
id|devfs_handle_t
id|xconn_vhdl
comma
r_int
id|devnum
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;hub_widgetdev_shutdown&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* ARGSUSED */
DECL|function|hub_widget_reset
r_void
id|hub_widget_reset
c_func
(paren
id|devfs_handle_t
id|hubv
comma
id|xwidgetnum_t
id|widget
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;hub_widget_reset&quot;
)paren
suffix:semicolon
)brace
id|boolean_t
DECL|function|is_sys_critical_vertex
id|is_sys_critical_vertex
c_func
(paren
id|devfs_handle_t
id|x
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;is_sys_critical_vertex : returns 0&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_char
op_star
DECL|function|nic_bridge_vertex_info
id|nic_bridge_vertex_info
c_func
(paren
id|devfs_handle_t
id|v
comma
id|nic_data_t
id|mcr
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;nic_bridge_vertex_info : returns NULL&quot;
)paren
suffix:semicolon
r_return
(paren
r_char
op_star
)paren
l_int|0
suffix:semicolon
)brace
r_void
op_star
DECL|function|kmem_alloc_node
id|kmem_alloc_node
c_func
(paren
r_register
r_int
id|size
comma
r_register
r_int
id|flags
comma
id|cnodeid_t
id|node
)paren
(brace
multiline_comment|/* Allocates on node &squot;node&squot; */
id|FIXME
c_func
(paren
l_string|&quot;kmem_alloc_node : use kmalloc&quot;
)paren
suffix:semicolon
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
r_void
op_star
DECL|function|kmem_zalloc_node
id|kmem_zalloc_node
c_func
(paren
r_register
r_int
id|size
comma
r_register
r_int
id|flags
comma
id|cnodeid_t
id|node
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;kmem_zalloc_node : use kmalloc&quot;
)paren
suffix:semicolon
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
r_void
DECL|function|kmem_free
id|kmem_free
c_func
(paren
r_void
op_star
id|where
comma
r_int
id|size
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;kmem_free : use kfree&quot;
)paren
suffix:semicolon
r_return
id|kfree
c_func
(paren
id|where
)paren
suffix:semicolon
)brace
r_void
op_star
DECL|function|kmem_zone_alloc
id|kmem_zone_alloc
c_func
(paren
r_register
id|zone_t
op_star
id|zone
comma
r_int
id|flags
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;kmem_zone_alloc : return null&quot;
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|kmem_zone_free
id|kmem_zone_free
c_func
(paren
r_register
id|zone_t
op_star
id|zone
comma
r_void
op_star
id|ptr
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;kmem_zone_free : no-op&quot;
)paren
suffix:semicolon
)brace
id|zone_t
op_star
DECL|function|kmem_zone_init
id|kmem_zone_init
c_func
(paren
r_register
r_int
id|size
comma
r_char
op_star
id|zone_name
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;kmem_zone_free : returns NULL&quot;
)paren
suffix:semicolon
r_return
(paren
id|zone_t
op_star
)paren
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|compare_and_swap_ptr
id|compare_and_swap_ptr
c_func
(paren
r_void
op_star
op_star
id|location
comma
r_void
op_star
id|old_ptr
comma
r_void
op_star
id|new_ptr
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;compare_and_swap_ptr : NOT ATOMIC&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|location
op_eq
id|old_ptr
)paren
(brace
op_star
id|location
op_assign
id|new_ptr
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_void
op_star
DECL|function|swap_ptr
id|swap_ptr
c_func
(paren
r_void
op_star
op_star
id|loc
comma
r_void
op_star
r_new
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;swap_ptr : returns null&quot;
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
l_int|0
suffix:semicolon
)brace
multiline_comment|/* For ml/SN/SN1/slots.c */
multiline_comment|/* ARGSUSED */
DECL|function|get_widget_slotnum
id|slotid_t
id|get_widget_slotnum
c_func
(paren
r_int
id|xbow
comma
r_int
id|widget
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;get_widget_slotnum&quot;
)paren
suffix:semicolon
r_return
(paren
r_int
r_char
)paren
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* For router */
r_int
DECL|function|router_init
id|router_init
c_func
(paren
id|cnodeid_t
id|cnode
comma
r_int
id|writeid
comma
r_void
op_star
id|npda_rip
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;router_init&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* From io/ioerror_handling.c */
id|error_return_code_t
DECL|function|sys_critical_graph_vertex_add
id|sys_critical_graph_vertex_add
c_func
(paren
id|devfs_handle_t
id|parent
comma
id|devfs_handle_t
id|child
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;sys_critical_graph_vertex_add&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* From io/ioc3.c */
id|devfs_handle_t
DECL|function|ioc3_console_vhdl_get
id|ioc3_console_vhdl_get
c_func
(paren
r_void
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;ioc3_console_vhdl_get&quot;
)paren
suffix:semicolon
r_return
(paren
id|devfs_handle_t
)paren
op_minus
l_int|1
suffix:semicolon
)brace
r_void
DECL|function|nic_vmc_check
id|nic_vmc_check
c_func
(paren
id|devfs_handle_t
id|vhdl
comma
r_char
op_star
id|nicinfo
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;nic_vmc_check&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_char
op_star
DECL|function|nic_vertex_info_get
id|nic_vertex_info_get
c_func
(paren
id|devfs_handle_t
id|v
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;nic_vertex_info_get&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_int
DECL|function|vector_read_node
id|vector_read_node
c_func
(paren
id|net_vec_t
id|dest
comma
id|nasid_t
id|nasid
comma
r_int
id|write_id
comma
r_int
id|address
comma
r_uint64
op_star
id|value
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;vector_read_node&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|vector_write_node
id|vector_write_node
c_func
(paren
id|net_vec_t
id|dest
comma
id|nasid_t
id|nasid
comma
r_int
id|write_id
comma
r_int
id|address
comma
r_uint64
id|value
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;vector_write_node&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
