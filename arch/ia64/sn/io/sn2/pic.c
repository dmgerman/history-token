multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2001-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/labelcl.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xwidget.h&gt;
macro_line|#include &lt;asm/sn/pci/bridge.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr_private.h&gt;
macro_line|#include &lt;asm/sn/pci/pci_defs.h&gt;
macro_line|#include &lt;asm/sn/prio.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xbow.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
DECL|macro|PCI_BUS_NO_1
mdefine_line|#define PCI_BUS_NO_1 1
r_extern
r_int
id|pcibr_attach2
c_func
(paren
id|vertex_hdl_t
comma
id|bridge_t
op_star
comma
id|vertex_hdl_t
comma
r_int
comma
id|pcibr_soft_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pcibr_driver_reg_callback
c_func
(paren
id|vertex_hdl_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|pcibr_driver_unreg_callback
c_func
(paren
id|vertex_hdl_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * copy inventory_t from conn_v to peer_conn_v&n; */
r_int
DECL|function|pic_bus1_inventory_dup
id|pic_bus1_inventory_dup
c_func
(paren
id|vertex_hdl_t
id|conn_v
comma
id|vertex_hdl_t
id|peer_conn_v
)paren
(brace
id|inventory_t
op_star
id|pinv
comma
op_star
id|peer_pinv
suffix:semicolon
r_if
c_cond
(paren
id|hwgraph_info_get_LBL
c_func
(paren
id|conn_v
comma
id|INFO_LBL_INVENT
comma
(paren
id|arbitrary_info_t
op_star
)paren
op_amp
id|pinv
)paren
op_eq
id|GRAPH_SUCCESS
)paren
(brace
id|NEW
c_func
(paren
id|peer_pinv
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|peer_pinv
comma
id|pinv
comma
r_sizeof
(paren
id|inventory_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwgraph_info_add_LBL
c_func
(paren
id|peer_conn_v
comma
id|INFO_LBL_INVENT
comma
(paren
id|arbitrary_info_t
)paren
id|peer_pinv
)paren
op_ne
id|GRAPH_SUCCESS
)paren
(brace
id|DEL
c_func
(paren
id|peer_pinv
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;pic_bus1_inventory_dup: cannot get INFO_LBL_INVENT from 0x%lx&bslash;n &quot;
comma
(paren
r_uint64
)paren
id|conn_v
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * copy xwidget_info_t from conn_v to peer_conn_v&n; */
r_int
DECL|function|pic_bus1_widget_info_dup
id|pic_bus1_widget_info_dup
c_func
(paren
id|vertex_hdl_t
id|conn_v
comma
id|vertex_hdl_t
id|peer_conn_v
comma
id|cnodeid_t
id|xbow_peer
)paren
(brace
id|xwidget_info_t
id|widget_info
comma
id|peer_widget_info
suffix:semicolon
r_char
id|peer_path
(braket
l_int|256
)braket
suffix:semicolon
id|vertex_hdl_t
id|peer_hubv
suffix:semicolon
id|hubinfo_t
id|peer_hub_info
suffix:semicolon
multiline_comment|/* get the peer hub&squot;s widgetid */
id|peer_hubv
op_assign
id|NODEPDA
c_func
(paren
id|xbow_peer
)paren
op_member_access_from_pointer
id|node_vertex
suffix:semicolon
id|peer_hub_info
op_assign
l_int|NULL
suffix:semicolon
id|hubinfo_get
c_func
(paren
id|peer_hubv
comma
op_amp
id|peer_hub_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|peer_hub_info
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hwgraph_info_get_LBL
c_func
(paren
id|conn_v
comma
id|INFO_LBL_XWIDGET
comma
(paren
id|arbitrary_info_t
op_star
)paren
op_amp
id|widget_info
)paren
op_eq
id|GRAPH_SUCCESS
)paren
(brace
id|NEW
c_func
(paren
id|peer_widget_info
)paren
suffix:semicolon
id|peer_widget_info-&gt;w_vertex
op_assign
id|peer_conn_v
suffix:semicolon
id|peer_widget_info-&gt;w_id
op_assign
id|widget_info-&gt;w_id
suffix:semicolon
id|peer_widget_info-&gt;w_master
op_assign
id|peer_hubv
suffix:semicolon
id|peer_widget_info-&gt;w_masterid
op_assign
id|peer_hub_info-&gt;h_widgetid
suffix:semicolon
multiline_comment|/* structure copy */
id|peer_widget_info-&gt;w_hwid
op_assign
id|widget_info-&gt;w_hwid
suffix:semicolon
id|peer_widget_info-&gt;w_efunc
op_assign
l_int|0
suffix:semicolon
id|peer_widget_info-&gt;w_einfo
op_assign
l_int|0
suffix:semicolon
id|peer_widget_info-&gt;w_name
op_assign
id|kmalloc
c_func
(paren
id|strlen
c_func
(paren
id|peer_path
)paren
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|peer_widget_info-&gt;w_name
comma
id|peer_path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwgraph_info_add_LBL
c_func
(paren
id|peer_conn_v
comma
id|INFO_LBL_XWIDGET
comma
(paren
id|arbitrary_info_t
)paren
id|peer_widget_info
)paren
op_ne
id|GRAPH_SUCCESS
)paren
(brace
id|DEL
c_func
(paren
id|peer_widget_info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|xwidget_info_set
c_func
(paren
id|peer_conn_v
comma
id|peer_widget_info
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;pic_bus1_widget_info_dup: &quot;
l_string|&quot;cannot get INFO_LBL_XWIDGET from 0x%lx&bslash;n&quot;
comma
(paren
r_uint64
)paren
id|conn_v
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * If this PIC is attached to two Cbricks (&quot;dual-ported&quot;) then&n; * attach each bus to opposite Cbricks.&n; *&n; * If successful, return a new vertex suitable for attaching the PIC bus.&n; * If not successful, return zero and both buses will attach to the&n; * vertex passed into pic_attach().&n; */
id|vertex_hdl_t
DECL|function|pic_bus1_redist
id|pic_bus1_redist
c_func
(paren
id|nasid_t
id|nasid
comma
id|vertex_hdl_t
id|conn_v
)paren
(brace
id|cnodeid_t
id|cnode
op_assign
id|NASID_TO_COMPACT_NODEID
c_func
(paren
id|nasid
)paren
suffix:semicolon
id|cnodeid_t
id|xbow_peer
op_assign
op_minus
l_int|1
suffix:semicolon
r_char
id|pathname
(braket
l_int|256
)braket
comma
id|peer_path
(braket
l_int|256
)braket
comma
id|tmpbuf
(braket
l_int|256
)braket
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|vertex_hdl_t
id|peer_conn_v
suffix:semicolon
r_int
id|pos
suffix:semicolon
id|slabid_t
id|slab
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
id|xbow_peer
op_ge
l_int|0
)paren
(brace
multiline_comment|/* if dual-ported */
multiline_comment|/* create a path for this widget on the peer Cbrick */
multiline_comment|/* pcibr widget hw/module/001c11/slab/0/Pbrick/xtalk/12 */
multiline_comment|/* sprintf(pathname, &quot;%v&quot;, conn_v); */
id|xbow_peer
op_assign
id|NASID_TO_COMPACT_NODEID
c_func
(paren
id|NODEPDA
c_func
(paren
id|cnode
)paren
op_member_access_from_pointer
id|xbow_peer
)paren
suffix:semicolon
id|pos
op_assign
id|hwgfs_generate_path
c_func
(paren
id|conn_v
comma
id|tmpbuf
comma
l_int|256
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|pathname
comma
op_amp
id|tmpbuf
(braket
id|pos
)braket
)paren
suffix:semicolon
id|p
op_assign
id|pathname
op_plus
id|strlen
c_func
(paren
l_string|&quot;hw/module/001c01/slab/0/&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|tmpbuf
comma
l_int|0
comma
l_int|16
)paren
suffix:semicolon
id|format_module_id
c_func
(paren
id|tmpbuf
comma
id|geo_module
c_func
(paren
(paren
id|NODEPDA
c_func
(paren
id|xbow_peer
)paren
)paren
op_member_access_from_pointer
id|geoid
)paren
comma
id|MODULE_FORMAT_BRIEF
)paren
suffix:semicolon
id|slab
op_assign
id|geo_slab
c_func
(paren
(paren
id|NODEPDA
c_func
(paren
id|xbow_peer
)paren
)paren
op_member_access_from_pointer
id|geoid
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|peer_path
comma
l_string|&quot;module/%s/slab/%d/%s&quot;
comma
id|tmpbuf
comma
(paren
r_int
)paren
id|slab
comma
id|p
)paren
suffix:semicolon
multiline_comment|/* Look for vertex for this widget on the peer Cbrick.&n;&t;&t; * Expect GRAPH_NOT_FOUND.&n;&t;&t; */
id|rc
op_assign
id|hwgraph_traverse
c_func
(paren
id|hwgraph_root
comma
id|peer_path
comma
op_amp
id|peer_conn_v
)paren
suffix:semicolon
r_if
c_cond
(paren
id|GRAPH_SUCCESS
op_eq
id|rc
)paren
id|printk
c_func
(paren
l_string|&quot;pic_attach: found unexpected vertex: 0x%lx&bslash;n&quot;
comma
(paren
r_uint64
)paren
id|peer_conn_v
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|GRAPH_NOT_FOUND
op_ne
id|rc
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pic_attach: hwgraph_traverse unexpectedly&quot;
l_string|&quot; returned 0x%x&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* try to add the widget vertex to the peer Cbrick */
id|rc
op_assign
id|hwgraph_path_add
c_func
(paren
id|hwgraph_root
comma
id|peer_path
comma
op_amp
id|peer_conn_v
)paren
suffix:semicolon
r_if
c_cond
(paren
id|GRAPH_SUCCESS
op_ne
id|rc
)paren
id|printk
c_func
(paren
l_string|&quot;pic_attach: hwgraph_path_add&quot;
l_string|&quot; failed with 0x%x&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_else
(brace
id|PCIBR_DEBUG_ALWAYS
c_func
(paren
(paren
id|PCIBR_DEBUG_ATTACH
comma
id|conn_v
comma
l_string|&quot;pic_bus1_redist: added vertex %v&bslash;n&quot;
comma
id|peer_conn_v
)paren
)paren
suffix:semicolon
multiline_comment|/* Now hang appropiate stuff off of the new&n;&t;&t;&t;     * vertex.&t;We bail out if we cannot add something.&n;&t;&t;&t;     * In that case, we don&squot;t remove the newly added&n;&t;&t;&t;     * vertex but that should be safe and we don&squot;t&n;&t;&t;&t;     * really expect the additions to fail anyway.&n;&t;&t;&t;     */
macro_line|#if 0
r_if
c_cond
(paren
op_logical_neg
id|pic_bus1_inventory_dup
c_func
(paren
id|conn_v
comma
id|peer_conn_v
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|pic_bus1_device_desc_dup
c_func
(paren
id|conn_v
comma
id|peer_conn_v
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|pic_bus1_widget_info_dup
c_func
(paren
id|conn_v
comma
id|peer_conn_v
comma
id|xbow_peer
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|peer_conn_v
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|pic_attach
id|pic_attach
c_func
(paren
id|vertex_hdl_t
id|conn_v
)paren
(brace
r_int
id|rc
suffix:semicolon
id|bridge_t
op_star
id|bridge0
comma
op_star
id|bridge1
op_assign
(paren
id|bridge_t
op_star
)paren
l_int|0
suffix:semicolon
id|vertex_hdl_t
id|pcibr_vhdl0
comma
id|pcibr_vhdl1
op_assign
(paren
id|vertex_hdl_t
)paren
l_int|0
suffix:semicolon
id|pcibr_soft_t
id|bus0_soft
comma
id|bus1_soft
op_assign
(paren
id|pcibr_soft_t
)paren
l_int|0
suffix:semicolon
id|vertex_hdl_t
id|conn_v0
comma
id|conn_v1
comma
id|peer_conn_v
suffix:semicolon
id|PCIBR_DEBUG_ALWAYS
c_func
(paren
(paren
id|PCIBR_DEBUG_ATTACH
comma
id|conn_v
comma
l_string|&quot;pic_attach()&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|bridge0
op_assign
(paren
id|bridge_t
op_star
)paren
id|xtalk_piotrans_addr
c_func
(paren
id|conn_v
comma
l_int|NULL
comma
l_int|0
comma
r_sizeof
(paren
id|bridge_t
)paren
comma
l_int|0
)paren
suffix:semicolon
id|bridge1
op_assign
(paren
id|bridge_t
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|bridge0
op_plus
id|PIC_BUS1_OFFSET
)paren
suffix:semicolon
id|PCIBR_DEBUG_ALWAYS
c_func
(paren
(paren
id|PCIBR_DEBUG_ATTACH
comma
id|conn_v
comma
l_string|&quot;pic_attach: bridge0=0x%x, bridge1=0x%x&bslash;n&quot;
comma
id|bridge0
comma
id|bridge1
)paren
)paren
suffix:semicolon
id|conn_v0
op_assign
id|conn_v1
op_assign
id|conn_v
suffix:semicolon
multiline_comment|/* If dual-ported then split the two PIC buses across both Cbricks */
r_if
c_cond
(paren
(paren
id|peer_conn_v
op_assign
(paren
id|pic_bus1_redist
c_func
(paren
id|NASID_GET
c_func
(paren
id|bridge0
)paren
comma
id|conn_v
)paren
)paren
)paren
)paren
id|conn_v1
op_assign
id|peer_conn_v
suffix:semicolon
multiline_comment|/*&n;&t; * Create the vertex for the PCI buses, which we&n;&t; * will also use to hold the pcibr_soft and&n;&t; * which will be the &quot;master&quot; vertex for all the&n;&t; * pciio connection points we will hang off it.&n;&t; * This needs to happen before we call nic_bridge_vertex_info&n;&t; * as we are some of the *_vmc functions need access to the edges.&n;&t; *&n;&t; * Opening this vertex will provide access to&n;&t; * the Bridge registers themselves.&n;&t; */
multiline_comment|/* FIXME: what should the hwgraph path look like ? */
id|rc
op_assign
id|hwgraph_path_add
c_func
(paren
id|conn_v0
comma
id|EDGE_LBL_PCIX_0
comma
op_amp
id|pcibr_vhdl0
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
id|hwgraph_path_add
c_func
(paren
id|conn_v1
comma
id|EDGE_LBL_PCIX_1
comma
op_amp
id|pcibr_vhdl1
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
id|PCIBR_DEBUG_ALWAYS
c_func
(paren
(paren
id|PCIBR_DEBUG_ATTACH
comma
id|conn_v
comma
l_string|&quot;pic_attach: pcibr_vhdl0=%v, pcibr_vhdl1=%v&bslash;n&quot;
comma
id|pcibr_vhdl0
comma
id|pcibr_vhdl1
)paren
)paren
suffix:semicolon
multiline_comment|/* register pci provider array */
id|pciio_provider_register
c_func
(paren
id|pcibr_vhdl0
comma
op_amp
id|pci_pic_provider
)paren
suffix:semicolon
id|pciio_provider_register
c_func
(paren
id|pcibr_vhdl1
comma
op_amp
id|pci_pic_provider
)paren
suffix:semicolon
id|pciio_provider_startup
c_func
(paren
id|pcibr_vhdl0
)paren
suffix:semicolon
id|pciio_provider_startup
c_func
(paren
id|pcibr_vhdl1
)paren
suffix:semicolon
id|pcibr_attach2
c_func
(paren
id|conn_v0
comma
id|bridge0
comma
id|pcibr_vhdl0
comma
l_int|0
comma
op_amp
id|bus0_soft
)paren
suffix:semicolon
id|pcibr_attach2
c_func
(paren
id|conn_v1
comma
id|bridge1
comma
id|pcibr_vhdl1
comma
l_int|1
comma
op_amp
id|bus1_soft
)paren
suffix:semicolon
multiline_comment|/* save a pointer to the PIC&squot;s other bus&squot;s soft struct */
id|bus0_soft-&gt;bs_peers_soft
op_assign
id|bus1_soft
suffix:semicolon
id|bus1_soft-&gt;bs_peers_soft
op_assign
id|bus0_soft
suffix:semicolon
id|PCIBR_DEBUG_ALWAYS
c_func
(paren
(paren
id|PCIBR_DEBUG_ATTACH
comma
id|conn_v
comma
l_string|&quot;pic_attach: bus0_soft=0x%x, bus1_soft=0x%x&bslash;n&quot;
comma
id|bus0_soft
comma
id|bus1_soft
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * pci provider functions&n; *&n; * mostly in pcibr.c but if any are needed here then&n; * this might be a way to get them here.&n; */
DECL|variable|pci_pic_provider
id|pciio_provider_t
id|pci_pic_provider
op_assign
(brace
(paren
id|pciio_piomap_alloc_f
op_star
)paren
id|pcibr_piomap_alloc
comma
(paren
id|pciio_piomap_free_f
op_star
)paren
id|pcibr_piomap_free
comma
(paren
id|pciio_piomap_addr_f
op_star
)paren
id|pcibr_piomap_addr
comma
(paren
id|pciio_piomap_done_f
op_star
)paren
id|pcibr_piomap_done
comma
(paren
id|pciio_piotrans_addr_f
op_star
)paren
id|pcibr_piotrans_addr
comma
(paren
id|pciio_piospace_alloc_f
op_star
)paren
id|pcibr_piospace_alloc
comma
(paren
id|pciio_piospace_free_f
op_star
)paren
id|pcibr_piospace_free
comma
(paren
id|pciio_dmamap_alloc_f
op_star
)paren
id|pcibr_dmamap_alloc
comma
(paren
id|pciio_dmamap_free_f
op_star
)paren
id|pcibr_dmamap_free
comma
(paren
id|pciio_dmamap_addr_f
op_star
)paren
id|pcibr_dmamap_addr
comma
(paren
id|pciio_dmamap_done_f
op_star
)paren
id|pcibr_dmamap_done
comma
(paren
id|pciio_dmatrans_addr_f
op_star
)paren
id|pcibr_dmatrans_addr
comma
(paren
id|pciio_dmamap_drain_f
op_star
)paren
id|pcibr_dmamap_drain
comma
(paren
id|pciio_dmaaddr_drain_f
op_star
)paren
id|pcibr_dmaaddr_drain
comma
(paren
id|pciio_dmalist_drain_f
op_star
)paren
id|pcibr_dmalist_drain
comma
(paren
id|pciio_intr_alloc_f
op_star
)paren
id|pcibr_intr_alloc
comma
(paren
id|pciio_intr_free_f
op_star
)paren
id|pcibr_intr_free
comma
(paren
id|pciio_intr_connect_f
op_star
)paren
id|pcibr_intr_connect
comma
(paren
id|pciio_intr_disconnect_f
op_star
)paren
id|pcibr_intr_disconnect
comma
(paren
id|pciio_intr_cpu_get_f
op_star
)paren
id|pcibr_intr_cpu_get
comma
(paren
id|pciio_provider_startup_f
op_star
)paren
id|pcibr_provider_startup
comma
(paren
id|pciio_provider_shutdown_f
op_star
)paren
id|pcibr_provider_shutdown
comma
(paren
id|pciio_reset_f
op_star
)paren
id|pcibr_reset
comma
(paren
id|pciio_write_gather_flush_f
op_star
)paren
id|pcibr_write_gather_flush
comma
(paren
id|pciio_endian_set_f
op_star
)paren
id|pcibr_endian_set
comma
(paren
id|pciio_priority_set_f
op_star
)paren
id|pcibr_priority_set
comma
(paren
id|pciio_config_get_f
op_star
)paren
id|pcibr_config_get
comma
(paren
id|pciio_config_set_f
op_star
)paren
id|pcibr_config_set
comma
(paren
id|pciio_error_devenable_f
op_star
)paren
l_int|0
comma
(paren
id|pciio_error_extract_f
op_star
)paren
l_int|0
comma
(paren
id|pciio_driver_reg_callback_f
op_star
)paren
id|pcibr_driver_reg_callback
comma
(paren
id|pciio_driver_unreg_callback_f
op_star
)paren
id|pcibr_driver_unreg_callback
comma
(paren
id|pciio_device_unregister_f
op_star
)paren
id|pcibr_device_unregister
comma
(paren
id|pciio_dma_enabled_f
op_star
)paren
id|pcibr_dma_enabled
comma
)brace
suffix:semicolon
eof
