multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/hcl_util.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr_private.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xtalkaddrs.h&gt;
macro_line|#include &lt;asm/sn/ksys/l1.h&gt;
multiline_comment|/* #define IOGRAPH_DEBUG */
macro_line|#ifdef IOGRAPH_DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif /* IOGRAPH_DEBUG */
multiline_comment|/* At most 2 hubs can be connected to an xswitch */
DECL|macro|NUM_XSWITCH_VOLUNTEER
mdefine_line|#define NUM_XSWITCH_VOLUNTEER 2
multiline_comment|/*&n; * Track which hubs have volunteered to manage devices hanging off of&n; * a Crosstalk Switch (e.g. xbow).  This structure is allocated,&n; * initialized, and hung off the xswitch vertex early on when the&n; * xswitch vertex is created.&n; */
DECL|struct|xswitch_vol_s
r_typedef
r_struct
id|xswitch_vol_s
(brace
DECL|member|xswitch_volunteer_mutex
r_struct
id|semaphore
id|xswitch_volunteer_mutex
suffix:semicolon
DECL|member|xswitch_volunteer_count
r_int
id|xswitch_volunteer_count
suffix:semicolon
DECL|member|xswitch_volunteer
id|vertex_hdl_t
id|xswitch_volunteer
(braket
id|NUM_XSWITCH_VOLUNTEER
)braket
suffix:semicolon
DECL|typedef|xswitch_vol_t
)brace
op_star
id|xswitch_vol_t
suffix:semicolon
r_void
DECL|function|xswitch_vertex_init
id|xswitch_vertex_init
c_func
(paren
id|vertex_hdl_t
id|xswitch
)paren
(brace
id|xswitch_vol_t
id|xvolinfo
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|xvolinfo
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|xswitch_vol_s
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xvolinfo
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;xswitch_vertex_init(): Unable to &quot;
l_string|&quot;allocate memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memset
c_func
(paren
id|xvolinfo
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|xswitch_vol_s
)paren
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|xvolinfo-&gt;xswitch_volunteer_mutex
)paren
suffix:semicolon
id|rc
op_assign
id|hwgraph_info_add_LBL
c_func
(paren
id|xswitch
comma
id|INFO_LBL_XSWITCH_VOL
comma
(paren
id|arbitrary_info_t
)paren
id|xvolinfo
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
)brace
multiline_comment|/*&n; * When assignment of hubs to widgets is complete, we no longer need the&n; * xswitch volunteer structure hanging around.  Destroy it.&n; */
r_static
r_void
DECL|function|xswitch_volunteer_delete
id|xswitch_volunteer_delete
c_func
(paren
id|vertex_hdl_t
id|xswitch
)paren
(brace
id|xswitch_vol_t
id|xvolinfo
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|hwgraph_info_remove_LBL
c_func
(paren
id|xswitch
comma
id|INFO_LBL_XSWITCH_VOL
comma
(paren
id|arbitrary_info_t
op_star
)paren
op_amp
id|xvolinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xvolinfo
OG
l_int|0
)paren
id|kfree
c_func
(paren
id|xvolinfo
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * A Crosstalk master volunteers to manage xwidgets on the specified xswitch.&n; */
multiline_comment|/* ARGSUSED */
r_static
r_void
DECL|function|volunteer_for_widgets
id|volunteer_for_widgets
c_func
(paren
id|vertex_hdl_t
id|xswitch
comma
id|vertex_hdl_t
id|master
)paren
(brace
id|xswitch_vol_t
id|xvolinfo
op_assign
l_int|NULL
suffix:semicolon
id|vertex_hdl_t
id|hubv
suffix:semicolon
id|hubinfo_t
id|hubinfo
suffix:semicolon
(paren
r_void
)paren
id|hwgraph_info_get_LBL
c_func
(paren
id|xswitch
comma
id|INFO_LBL_XSWITCH_VOL
comma
(paren
id|arbitrary_info_t
op_star
)paren
op_amp
id|xvolinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xvolinfo
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_headless_node_vertex
c_func
(paren
id|master
)paren
)paren
(brace
r_char
id|name
(braket
id|MAXDEVNAME
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;volunteer for widgets: vertex %s has no info label&quot;
comma
id|vertex_to_name
c_func
(paren
id|xswitch
comma
id|name
comma
id|MAXDEVNAME
)paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|xvolinfo-&gt;xswitch_volunteer_mutex
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|xvolinfo-&gt;xswitch_volunteer_count
OL
id|NUM_XSWITCH_VOLUNTEER
)paren
suffix:semicolon
id|xvolinfo-&gt;xswitch_volunteer
(braket
id|xvolinfo-&gt;xswitch_volunteer_count
)braket
op_assign
id|master
suffix:semicolon
id|xvolinfo-&gt;xswitch_volunteer_count
op_increment
suffix:semicolon
multiline_comment|/*&n;&t; * if dual ported, make the lowest widgetid always be &n;&t; * xswitch_volunteer[0].&n;&t; */
r_if
c_cond
(paren
id|xvolinfo-&gt;xswitch_volunteer_count
op_eq
id|NUM_XSWITCH_VOLUNTEER
)paren
(brace
id|hubv
op_assign
id|xvolinfo-&gt;xswitch_volunteer
(braket
l_int|0
)braket
suffix:semicolon
id|hubinfo_get
c_func
(paren
id|hubv
comma
op_amp
id|hubinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hubinfo-&gt;h_widgetid
op_ne
id|XBOW_HUBLINK_LOW
)paren
(brace
id|xvolinfo-&gt;xswitch_volunteer
(braket
l_int|0
)braket
op_assign
id|xvolinfo-&gt;xswitch_volunteer
(braket
l_int|1
)braket
suffix:semicolon
id|xvolinfo-&gt;xswitch_volunteer
(braket
l_int|1
)braket
op_assign
id|hubv
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|xvolinfo-&gt;xswitch_volunteer_mutex
)paren
suffix:semicolon
)brace
r_extern
r_int
id|xbow_port_io_enabled
c_func
(paren
id|nasid_t
id|nasid
comma
r_int
id|widgetnum
)paren
suffix:semicolon
multiline_comment|/*&n; * Assign all the xwidgets hanging off the specified xswitch to the&n; * Crosstalk masters that have volunteered for xswitch duty.&n; */
multiline_comment|/* ARGSUSED */
r_static
r_void
DECL|function|assign_widgets_to_volunteers
id|assign_widgets_to_volunteers
c_func
(paren
id|vertex_hdl_t
id|xswitch
comma
id|vertex_hdl_t
id|hubv
)paren
(brace
id|xswitch_info_t
id|xswitch_info
suffix:semicolon
id|xswitch_vol_t
id|xvolinfo
op_assign
l_int|NULL
suffix:semicolon
id|xwidgetnum_t
id|widgetnum
suffix:semicolon
r_int
id|num_volunteer
suffix:semicolon
id|nasid_t
id|nasid
suffix:semicolon
id|hubinfo_t
id|hubinfo
suffix:semicolon
r_extern
r_int
id|iobrick_type_get_nasid
c_func
(paren
id|nasid_t
)paren
suffix:semicolon
id|hubinfo_get
c_func
(paren
id|hubv
comma
op_amp
id|hubinfo
)paren
suffix:semicolon
id|nasid
op_assign
id|hubinfo-&gt;h_nasid
suffix:semicolon
id|xswitch_info
op_assign
id|xswitch_info_get
c_func
(paren
id|xswitch
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|xswitch_info
op_ne
l_int|NULL
)paren
suffix:semicolon
(paren
r_void
)paren
id|hwgraph_info_get_LBL
c_func
(paren
id|xswitch
comma
id|INFO_LBL_XSWITCH_VOL
comma
(paren
id|arbitrary_info_t
op_star
)paren
op_amp
id|xvolinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xvolinfo
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_headless_node_vertex
c_func
(paren
id|hubv
)paren
)paren
(brace
r_char
id|name
(braket
id|MAXDEVNAME
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;assign_widgets_to_volunteers:vertex %s has &quot;
l_string|&quot; no info label&quot;
comma
id|vertex_to_name
c_func
(paren
id|xswitch
comma
id|name
comma
id|MAXDEVNAME
)paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|num_volunteer
op_assign
id|xvolinfo-&gt;xswitch_volunteer_count
suffix:semicolon
id|ASSERT
c_func
(paren
id|num_volunteer
OG
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Assign master hub for xswitch itself.  */
r_if
c_cond
(paren
id|HUB_WIDGET_ID_MIN
OG
l_int|0
)paren
(brace
id|hubv
op_assign
id|xvolinfo-&gt;xswitch_volunteer
(braket
l_int|0
)braket
suffix:semicolon
id|xswitch_info_master_assignment_set
c_func
(paren
id|xswitch_info
comma
(paren
id|xwidgetnum_t
)paren
l_int|0
comma
id|hubv
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * TBD: Use administrative information to alter assignment of&n;&t; * widgets to hubs.&n;&t; */
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
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xbow_port_io_enabled
c_func
(paren
id|nasid
comma
id|widgetnum
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If this is the master IO board, assign it to the same &n;&t;&t; * hub that owned it in the prom.&n;&t;&t; */
r_if
c_cond
(paren
id|is_master_baseio_nasid_widget
c_func
(paren
id|nasid
comma
id|widgetnum
)paren
)paren
(brace
r_extern
id|nasid_t
id|snia_get_master_baseio_nasid
c_func
(paren
r_void
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
id|num_volunteer
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hubv
op_assign
id|xvolinfo-&gt;xswitch_volunteer
(braket
id|i
)braket
suffix:semicolon
id|hubinfo_get
c_func
(paren
id|hubv
comma
op_amp
id|hubinfo
)paren
suffix:semicolon
id|nasid
op_assign
id|hubinfo-&gt;h_nasid
suffix:semicolon
r_if
c_cond
(paren
id|nasid
op_eq
id|snia_get_master_baseio_nasid
c_func
(paren
)paren
)paren
r_goto
id|do_assignment
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Nasid == %d, console nasid == %d&quot;
comma
id|nasid
comma
id|snia_get_master_baseio_nasid
c_func
(paren
)paren
)paren
suffix:semicolon
id|nasid
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Assuming that we&squot;re dual-hosted and that PCI cards &n;&t;&t; * are naturally placed left-to-right, alternate PCI &n;&t;&t; * buses across both Cbricks.   For Pbricks, and Ibricks,&n;                 * io_brick_map_widget() returns the PCI bus number&n;                 * associated with the given brick type and widget number.&n;                 * For Xbricks, it returns the XIO slot number.&n;&t;&t; */
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|num_volunteer
OG
l_int|1
)paren
(brace
r_int
id|bt
suffix:semicolon
id|bt
op_assign
id|iobrick_type_get_nasid
c_func
(paren
id|nasid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bt
op_ge
l_int|0
)paren
(brace
id|i
op_assign
id|io_brick_map_widget
c_func
(paren
id|bt
comma
id|widgetnum
)paren
op_amp
l_int|1
suffix:semicolon
)brace
)brace
id|hubv
op_assign
id|xvolinfo-&gt;xswitch_volunteer
(braket
id|i
)braket
suffix:semicolon
id|do_assignment
suffix:colon
multiline_comment|/*&n;&t;&t; * At this point, we want to make hubv the master of widgetnum.&n;&t;&t; */
id|xswitch_info_master_assignment_set
c_func
(paren
id|xswitch_info
comma
id|widgetnum
comma
id|hubv
)paren
suffix:semicolon
)brace
id|xswitch_volunteer_delete
c_func
(paren
id|xswitch
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * Probe to see if this hub&squot;s xtalk link is active.  If so,&n; * return the Crosstalk Identification of the widget that we talk to.  &n; * This is called before any of the Crosstalk infrastructure for &n; * this hub is set up.  It&squot;s usually called on the node that we&squot;re&n; * probing, but not always.&n; *&n; * TBD: Prom code should actually do this work, and pass through &n; * hwid for our use.&n; */
r_static
r_void
DECL|function|early_probe_for_widget
id|early_probe_for_widget
c_func
(paren
id|vertex_hdl_t
id|hubv
comma
id|xwidget_hwid_t
id|hwid
)paren
(brace
id|nasid_t
id|nasid
suffix:semicolon
id|hubinfo_t
id|hubinfo
suffix:semicolon
id|hubreg_t
id|llp_csr_reg
suffix:semicolon
id|widgetreg_t
id|widget_id
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|hwid-&gt;part_num
op_assign
id|XWIDGET_PART_NUM_NONE
suffix:semicolon
id|hwid-&gt;rev_num
op_assign
id|XWIDGET_REV_NUM_NONE
suffix:semicolon
id|hwid-&gt;mfg_num
op_assign
id|XWIDGET_MFG_NUM_NONE
suffix:semicolon
id|hubinfo_get
c_func
(paren
id|hubv
comma
op_amp
id|hubinfo
)paren
suffix:semicolon
id|nasid
op_assign
id|hubinfo-&gt;h_nasid
suffix:semicolon
id|llp_csr_reg
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|nasid
comma
id|IIO_LLP_CSR
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|llp_csr_reg
op_amp
id|IIO_LLP_CSR_IS_UP
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* Read the Cross-Talk Widget Id on the other end */
id|result
op_assign
id|snia_badaddr_val
c_func
(paren
(paren
r_volatile
r_void
op_star
)paren
(paren
id|RAW_NODE_SWIN_BASE
c_func
(paren
id|nasid
comma
l_int|0x0
)paren
op_plus
id|WIDGET_ID
)paren
comma
l_int|4
comma
(paren
r_void
op_star
)paren
op_amp
id|widget_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Found something connected */
id|hwid-&gt;part_num
op_assign
id|XWIDGET_PART_NUM
c_func
(paren
id|widget_id
)paren
suffix:semicolon
id|hwid-&gt;rev_num
op_assign
id|XWIDGET_REV_NUM
c_func
(paren
id|widget_id
)paren
suffix:semicolon
id|hwid-&gt;mfg_num
op_assign
id|XWIDGET_MFG_NUM
c_func
(paren
id|widget_id
)paren
suffix:semicolon
multiline_comment|/* TBD: link reset */
)brace
r_else
(brace
id|hwid-&gt;part_num
op_assign
id|XWIDGET_PART_NUM_NONE
suffix:semicolon
id|hwid-&gt;rev_num
op_assign
id|XWIDGET_REV_NUM_NONE
suffix:semicolon
id|hwid-&gt;mfg_num
op_assign
id|XWIDGET_MFG_NUM_NONE
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * io_xswitch_widget_init&n; *&t;&n; */
r_static
r_void
DECL|function|io_xswitch_widget_init
id|io_xswitch_widget_init
c_func
(paren
id|vertex_hdl_t
id|xswitchv
comma
id|vertex_hdl_t
id|hubv
comma
id|xwidgetnum_t
id|widgetnum
)paren
(brace
id|xswitch_info_t
id|xswitch_info
suffix:semicolon
id|xwidgetnum_t
id|hub_widgetid
suffix:semicolon
id|vertex_hdl_t
id|widgetv
suffix:semicolon
id|cnodeid_t
id|cnode
suffix:semicolon
id|widgetreg_t
id|widget_id
suffix:semicolon
id|nasid_t
id|nasid
comma
id|peer_nasid
suffix:semicolon
r_struct
id|xwidget_hwid_s
id|hwid
suffix:semicolon
id|hubinfo_t
id|hubinfo
suffix:semicolon
multiline_comment|/*REFERENCED*/
r_int
id|rc
suffix:semicolon
r_char
id|pathname
(braket
l_int|128
)braket
suffix:semicolon
id|lboard_t
op_star
id|board
op_assign
l_int|NULL
suffix:semicolon
r_char
id|buffer
(braket
l_int|16
)braket
suffix:semicolon
r_char
id|bt
suffix:semicolon
id|moduleid_t
id|io_module
suffix:semicolon
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
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;&bslash;nio_xswitch_widget_init: hubv 0x%p, xswitchv 0x%p, widgetnum 0x%x&bslash;n&quot;
comma
id|hubv
comma
id|xswitchv
comma
id|widgetnum
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Verify that xswitchv is indeed an attached xswitch.&n;&t; */
id|xswitch_info
op_assign
id|xswitch_info_get
c_func
(paren
id|xswitchv
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|xswitch_info
op_ne
l_int|NULL
)paren
suffix:semicolon
id|hubinfo_get
c_func
(paren
id|hubv
comma
op_amp
id|hubinfo
)paren
suffix:semicolon
id|nasid
op_assign
id|hubinfo-&gt;h_nasid
suffix:semicolon
id|cnode
op_assign
id|nasid_to_cnodeid
c_func
(paren
id|nasid
)paren
suffix:semicolon
id|hub_widgetid
op_assign
id|hubinfo-&gt;h_widgetid
suffix:semicolon
multiline_comment|/*&n;&t; * Check that the widget is an io widget and is enabled&n;&t; * on this nasid or the `peer&squot; nasid.  The peer nasid&n;&t; * is the other hub/bedrock connected to the xbow.&n;&t; */
id|peer_nasid
op_assign
id|NODEPDA
c_func
(paren
id|cnode
)paren
op_member_access_from_pointer
id|xbow_peer
suffix:semicolon
r_if
c_cond
(paren
id|peer_nasid
op_eq
id|INVALID_NASID
)paren
multiline_comment|/* If I don&squot;t have a peer, use myself. */
id|peer_nasid
op_assign
id|nasid
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xbow_port_io_enabled
c_func
(paren
id|nasid
comma
id|widgetnum
)paren
op_logical_and
op_logical_neg
id|xbow_port_io_enabled
c_func
(paren
id|peer_nasid
comma
id|widgetnum
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xswitch_info_link_ok
c_func
(paren
id|xswitch_info
comma
id|widgetnum
)paren
)paren
(brace
r_char
id|name
(braket
l_int|4
)braket
suffix:semicolon
id|lboard_t
id|dummy
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the current hub is not supposed to be the master &n;&t;&t; * for this widgetnum, then skip this widget.&n;&t;&t; */
r_if
c_cond
(paren
id|xswitch_info_master_assignment_get
c_func
(paren
id|xswitch_info
comma
id|widgetnum
)paren
op_ne
id|hubv
)paren
(brace
r_return
suffix:semicolon
)brace
id|board
op_assign
id|find_lboard_class_nasid
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
id|KLCLASS_IOBRICK
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|board
op_logical_and
id|NODEPDA
c_func
(paren
id|cnode
)paren
op_member_access_from_pointer
id|xbow_peer
op_ne
id|INVALID_NASID
)paren
(brace
id|board
op_assign
id|find_lboard_class_nasid
c_func
(paren
(paren
id|lboard_t
op_star
)paren
id|KL_CONFIG_INFO
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
comma
id|NODEPDA
c_func
(paren
id|cnode
)paren
op_member_access_from_pointer
id|xbow_peer
comma
id|KLCLASS_IOBRICK
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|board
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;io_xswitch_widget_init: Found KLTYPE_IOBRICK Board 0x%p brd_type 0x%x&bslash;n&quot;
comma
id|board
comma
id|board-&gt;brd_type
)paren
suffix:semicolon
)brace
r_else
(brace
id|DBG
c_func
(paren
l_string|&quot;io_xswitch_widget_init: FIXME did not find IOBOARD&bslash;n&quot;
)paren
suffix:semicolon
id|board
op_assign
op_amp
id|dummy
suffix:semicolon
)brace
multiline_comment|/* Copy over the nodes&squot; geoid info */
(brace
id|lboard_t
op_star
id|brd
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
r_if
c_cond
(paren
id|brd
op_ne
(paren
id|lboard_t
op_star
)paren
l_int|0
)paren
(brace
id|board-&gt;brd_geoid
op_assign
id|brd-&gt;brd_geoid
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; &t;&t; * Make sure we really want to say xbrick, pbrick,&n;&t;&t; * etc. rather than XIO, graphics, etc.&n; &t;&t; */
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
id|geo_module
c_func
(paren
id|board-&gt;brd_geoid
)paren
comma
id|MODULE_FORMAT_BRIEF
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|pathname
comma
id|EDGE_LBL_MODULE
l_string|&quot;/%s/&quot;
id|EDGE_LBL_SLAB
l_string|&quot;/%d&quot;
l_string|&quot;/%s&quot;
l_string|&quot;/%s/%d&quot;
comma
id|buffer
comma
id|geo_slab
c_func
(paren
id|board-&gt;brd_geoid
)paren
comma
(paren
id|board-&gt;brd_type
op_eq
id|KLTYPE_PXBRICK
)paren
ques
c_cond
id|EDGE_LBL_PXBRICK
suffix:colon
(paren
id|board-&gt;brd_type
op_eq
id|KLTYPE_IXBRICK
)paren
ques
c_cond
id|EDGE_LBL_IXBRICK
suffix:colon
(paren
id|board-&gt;brd_type
op_eq
id|KLTYPE_CGBRICK
)paren
ques
c_cond
id|EDGE_LBL_CGBRICK
suffix:colon
(paren
id|board-&gt;brd_type
op_eq
id|KLTYPE_OPUSBRICK
)paren
ques
c_cond
id|EDGE_LBL_OPUSBRICK
suffix:colon
l_string|&quot;?brick&quot;
comma
id|EDGE_LBL_XTALK
comma
id|widgetnum
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;io_xswitch_widget_init: path= %s&bslash;n&quot;
comma
id|pathname
)paren
suffix:semicolon
id|rc
op_assign
id|hwgraph_path_add
c_func
(paren
id|hwgraph_root
comma
id|pathname
comma
op_amp
id|widgetv
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
multiline_comment|/* This is needed to let the user programs to map the&n;&t;&t; * module,slot numbers to the corresponding widget numbers&n;&t;&t; * on the crossbow.&n;&t;&t; */
id|device_master_set
c_func
(paren
id|hwgraph_connectpt_get
c_func
(paren
id|widgetv
)paren
comma
id|hubv
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%d&quot;
comma
id|widgetnum
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;io_xswitch_widget_init: FIXME hwgraph_edge_add %s xswitchv 0x%p, widgetv 0x%p&bslash;n&quot;
comma
id|name
comma
id|xswitchv
comma
id|widgetv
)paren
suffix:semicolon
id|rc
op_assign
id|hwgraph_edge_add
c_func
(paren
id|xswitchv
comma
id|widgetv
comma
id|name
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * crosstalk switch code tracks which&n;&t;&t; * widget is attached to each link.&n;&t;&t; */
id|xswitch_info_vhdl_set
c_func
(paren
id|xswitch_info
comma
id|widgetnum
comma
id|widgetv
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Peek at the widget to get its crosstalk part and&n;&t;&t; * mfgr numbers, then present it to the generic xtalk&n;&t;&t; * bus provider to have its driver attach routine&n;&t;&t; * called (or not).&n;&t;&t; */
id|widget_id
op_assign
id|XWIDGET_ID_READ
c_func
(paren
id|nasid
comma
id|widgetnum
)paren
suffix:semicolon
id|hwid.part_num
op_assign
id|XWIDGET_PART_NUM
c_func
(paren
id|widget_id
)paren
suffix:semicolon
id|hwid.rev_num
op_assign
id|XWIDGET_REV_NUM
c_func
(paren
id|widget_id
)paren
suffix:semicolon
id|hwid.mfg_num
op_assign
id|XWIDGET_MFG_NUM
c_func
(paren
id|widget_id
)paren
suffix:semicolon
(paren
r_void
)paren
id|xwidget_register
c_func
(paren
op_amp
id|hwid
comma
id|widgetv
comma
id|widgetnum
comma
id|hubv
comma
id|hub_widgetid
)paren
suffix:semicolon
id|io_module
op_assign
id|iomoduleid_get
c_func
(paren
id|nasid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io_module
op_ge
l_int|0
)paren
(brace
r_char
id|buffer
(braket
l_int|16
)braket
suffix:semicolon
id|vertex_hdl_t
id|to
comma
id|from
suffix:semicolon
r_char
op_star
id|brick_name
suffix:semicolon
r_extern
r_char
op_star
id|iobrick_L1bricktype_to_name
c_func
(paren
r_int
id|type
)paren
suffix:semicolon
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
id|geo_module
c_func
(paren
id|board-&gt;brd_geoid
)paren
comma
id|MODULE_FORMAT_BRIEF
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isupper
c_func
(paren
id|MODULE_GET_BTCHAR
c_func
(paren
id|io_module
)paren
)paren
)paren
(brace
id|bt
op_assign
id|tolower
c_func
(paren
id|MODULE_GET_BTCHAR
c_func
(paren
id|io_module
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|bt
op_assign
id|MODULE_GET_BTCHAR
c_func
(paren
id|io_module
)paren
suffix:semicolon
)brace
id|brick_name
op_assign
id|iobrick_L1bricktype_to_name
c_func
(paren
id|bt
)paren
suffix:semicolon
multiline_comment|/* Add a helper vertex so xbow monitoring&n;&t;&t;&t;* can identify the brick type. It&squot;s simply&n;&t;&t;&t;* an edge from the widget 0 vertex to the&n;&t;&t;&t;*  brick vertex.&n;&t;&t;&t;*/
id|sprintf
c_func
(paren
id|pathname
comma
id|EDGE_LBL_HW
l_string|&quot;/&quot;
id|EDGE_LBL_MODULE
l_string|&quot;/%s/&quot;
id|EDGE_LBL_SLAB
l_string|&quot;/%d/&quot;
id|EDGE_LBL_NODE
l_string|&quot;/&quot;
id|EDGE_LBL_XTALK
l_string|&quot;/&quot;
l_string|&quot;0&quot;
comma
id|buffer
comma
id|geo_slab
c_func
(paren
id|board-&gt;brd_geoid
)paren
)paren
suffix:semicolon
id|from
op_assign
id|hwgraph_path_to_vertex
c_func
(paren
id|pathname
)paren
suffix:semicolon
id|ASSERT_ALWAYS
c_func
(paren
id|from
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|pathname
comma
id|EDGE_LBL_HW
l_string|&quot;/&quot;
id|EDGE_LBL_MODULE
l_string|&quot;/%s/&quot;
id|EDGE_LBL_SLAB
l_string|&quot;/%d/&quot;
l_string|&quot;%s&quot;
comma
id|buffer
comma
id|geo_slab
c_func
(paren
id|board-&gt;brd_geoid
)paren
comma
id|brick_name
)paren
suffix:semicolon
id|to
op_assign
id|hwgraph_path_to_vertex
c_func
(paren
id|pathname
)paren
suffix:semicolon
id|ASSERT_ALWAYS
c_func
(paren
id|to
)paren
suffix:semicolon
id|rc
op_assign
id|hwgraph_edge_add
c_func
(paren
id|from
comma
id|to
comma
id|EDGE_LBL_INTERCONNECT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
op_minus
id|EEXIST
op_logical_and
id|rc
op_ne
id|GRAPH_SUCCESS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Unable to establish link&quot;
l_string|&quot; for xbmon.&quot;
comma
id|pathname
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
r_static
r_void
DECL|function|io_init_xswitch_widgets
id|io_init_xswitch_widgets
c_func
(paren
id|vertex_hdl_t
id|xswitchv
comma
id|cnodeid_t
id|cnode
)paren
(brace
id|xwidgetnum_t
id|widgetnum
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;io_init_xswitch_widgets: xswitchv 0x%p for cnode %d&bslash;n&quot;
comma
id|xswitchv
comma
id|cnode
)paren
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
id|io_xswitch_widget_init
c_func
(paren
id|xswitchv
comma
id|cnodeid_to_vertex
c_func
(paren
id|cnode
)paren
comma
id|widgetnum
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Initialize all I/O on the specified node.&n; */
r_static
r_void
DECL|function|io_init_node
id|io_init_node
c_func
(paren
id|cnodeid_t
id|cnodeid
)paren
(brace
multiline_comment|/*REFERENCED*/
id|vertex_hdl_t
id|hubv
comma
id|switchv
comma
id|widgetv
suffix:semicolon
r_struct
id|xwidget_hwid_s
id|hwid
suffix:semicolon
id|hubinfo_t
id|hubinfo
suffix:semicolon
r_int
id|is_xswitch
suffix:semicolon
id|nodepda_t
op_star
id|npdap
suffix:semicolon
r_struct
id|semaphore
op_star
id|peer_sema
op_assign
l_int|0
suffix:semicolon
r_uint32
id|widget_partnum
suffix:semicolon
id|npdap
op_assign
id|NODEPDA
c_func
(paren
id|cnodeid
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get the &quot;top&quot; vertex for this node&squot;s hardware&n;&t; * graph; it will carry the per-hub hub-specific&n;&t; * data, and act as the crosstalk provider master.&n;&t; * It&squot;s canonical path is probably something of the&n;&t; * form /hw/module/%M/slot/%d/node&n;&t; */
id|hubv
op_assign
id|cnodeid_to_vertex
c_func
(paren
id|cnodeid
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;io_init_node: Initialize IO for cnode %d hubv(node) 0x%p npdap 0x%p&bslash;n&quot;
comma
id|cnodeid
comma
id|hubv
comma
id|npdap
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hubv
op_ne
id|GRAPH_VERTEX_NONE
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * If nothing connected to this hub&squot;s xtalk port, we&squot;re done.&n;&t; */
id|early_probe_for_widget
c_func
(paren
id|hubv
comma
op_amp
id|hwid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwid.part_num
op_eq
id|XWIDGET_PART_NUM_NONE
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;**** io_init_node: Node&squot;s 0x%p hub widget has XWIDGET_PART_NUM_NONE ****&bslash;n&quot;
comma
id|hubv
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* NOTREACHED */
)brace
multiline_comment|/* &n;&t; * attach our hub_provider information to hubv,&n;&t; * so we can use it as a crosstalk provider &quot;master&quot;&n;&t; * vertex.&n;&t; */
id|xtalk_provider_register
c_func
(paren
id|hubv
comma
op_amp
id|hub_provider
)paren
suffix:semicolon
id|xtalk_provider_startup
c_func
(paren
id|hubv
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Create a vertex to represent the crosstalk bus&n;&t; * attached to this hub, and a vertex to be used&n;&t; * as the connect point for whatever is out there&n;&t; * on the other side of our crosstalk connection.&n;&t; *&n;&t; * Crosstalk Switch drivers &quot;climb up&quot; from their&n;&t; * connection point to try and take over the switch&n;&t; * point.&n;&t; *&n;&t; * Of course, the edges and verticies may already&n;&t; * exist, in which case our net effect is just to&n;&t; * associate the &quot;xtalk_&quot; driver with the connection&n;&t; * point for the device.&n;&t; */
(paren
r_void
)paren
id|hwgraph_path_add
c_func
(paren
id|hubv
comma
id|EDGE_LBL_XTALK
comma
op_amp
id|switchv
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;io_init_node: Created &squot;xtalk&squot; entry to &squot;../node/&squot; xtalk vertex 0x%p&bslash;n&quot;
comma
id|switchv
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|switchv
op_ne
id|GRAPH_VERTEX_NONE
)paren
suffix:semicolon
(paren
r_void
)paren
id|hwgraph_edge_add
c_func
(paren
id|hubv
comma
id|switchv
comma
id|EDGE_LBL_IO
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;io_init_node: Created symlink &squot;io&squot; from ../node/io to ../node/xtalk &bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We need to find the widget id and update the basew_id field&n;&t; * accordingly. In particular, SN00 has direct connected bridge,&n;&t; * and hence widget id is Not 0.&n;&t; */
id|widget_partnum
op_assign
(paren
(paren
(paren
op_star
(paren
r_volatile
r_int32
op_star
)paren
(paren
id|NODE_SWIN_BASE
(paren
id|cnodeid_to_nasid
c_func
(paren
id|cnodeid
)paren
comma
l_int|0
)paren
op_plus
id|WIDGET_ID
)paren
)paren
)paren
op_amp
id|WIDGET_PART_NUM
)paren
op_rshift
id|WIDGET_PART_NUM_SHFT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|widget_partnum
op_eq
id|XBOW_WIDGET_PART_NUM
)paren
op_logical_or
(paren
id|widget_partnum
op_eq
id|XXBOW_WIDGET_PART_NUM
)paren
op_logical_or
(paren
id|widget_partnum
op_eq
id|PXBOW_WIDGET_PART_NUM
)paren
)paren
(brace
multiline_comment|/* &n;&t;&t; * Xbow control register does not have the widget ID field.&n;&t;&t; * So, hard code the widget ID to be zero.&n;&t;&t; */
id|DBG
c_func
(paren
l_string|&quot;io_init_node: Found XBOW widget_partnum= 0x%x&bslash;n&quot;
comma
id|widget_partnum
)paren
suffix:semicolon
id|npdap-&gt;basew_id
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_void
op_star
id|bridge
suffix:semicolon
id|bridge
op_assign
(paren
r_void
op_star
)paren
id|NODE_SWIN_BASE
c_func
(paren
id|cnodeid_to_nasid
c_func
(paren
id|cnodeid
)paren
comma
l_int|0
)paren
suffix:semicolon
id|npdap-&gt;basew_id
op_assign
id|pcireg_bridge_control_get
c_func
(paren
id|bridge
)paren
op_amp
id|WIDGET_WIDGET_ID
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; ****io_init_node: Unknown Widget Part Number 0x%x Widget ID 0x%x attached to Hubv 0x%p ****&bslash;n&quot;
comma
id|widget_partnum
comma
id|npdap-&gt;basew_id
comma
(paren
r_void
op_star
)paren
id|hubv
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
(brace
r_char
id|widname
(braket
l_int|10
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|widname
comma
l_string|&quot;%x&quot;
comma
id|npdap-&gt;basew_id
)paren
suffix:semicolon
(paren
r_void
)paren
id|hwgraph_path_add
c_func
(paren
id|switchv
comma
id|widname
comma
op_amp
id|widgetv
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;io_init_node: Created &squot;%s&squot; to &squot;..node/xtalk/&squot; vertex 0x%p&bslash;n&quot;
comma
id|widname
comma
id|widgetv
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|widgetv
op_ne
id|GRAPH_VERTEX_NONE
)paren
suffix:semicolon
)brace
id|nodepda-&gt;basew_xc
op_assign
id|widgetv
suffix:semicolon
id|is_xswitch
op_assign
id|xwidget_hwid_is_xswitch
c_func
(paren
op_amp
id|hwid
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Try to become the master of the widget.  If this is an xswitch&n;&t; * with multiple hubs connected, only one will succeed.  Mastership&n;&t; * of an xswitch is used only when touching registers on that xswitch.&n;&t; * The slave xwidgets connected to the xswitch can be owned by various&n;&t; * masters.&n;&t; */
r_if
c_cond
(paren
id|device_master_set
c_func
(paren
id|widgetv
comma
id|hubv
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Only one hub (thread) per Crosstalk device or switch makes&n;&t;&t; * it to here.&n;&t;&t; */
multiline_comment|/* &n;&t;&t; * Initialize whatever xwidget is hanging off our hub.&n;&t;&t; * Whatever it is, it&squot;s accessible through widgetnum 0.&n;&t;&t; */
id|hubinfo_get
c_func
(paren
id|hubv
comma
op_amp
id|hubinfo
)paren
suffix:semicolon
(paren
r_void
)paren
id|xwidget_register
c_func
(paren
op_amp
id|hwid
comma
id|widgetv
comma
id|npdap-&gt;basew_id
comma
id|hubv
comma
id|hubinfo-&gt;h_widgetid
)paren
suffix:semicolon
multiline_comment|/* &n;&t;&t; * Special handling for Crosstalk Switches (e.g. xbow).&n;&t;&t; * We need to do things in roughly the following order:&n;&t;&t; *&t;1) Initialize xswitch hardware (done above)&n;&t;&t; *&t;2) Determine which hubs are available to be widget masters&n;&t;&t; *&t;3) Discover which links are active from the xswitch&n;&t;&t; *&t;4) Assign xwidgets hanging off the xswitch to hubs&n;&t;&t; *&t;5) Initialize all xwidgets on the xswitch&n;&t;&t; */
id|volunteer_for_widgets
c_func
(paren
id|switchv
comma
id|hubv
)paren
suffix:semicolon
multiline_comment|/* If there&squot;s someone else on this crossbow, recognize him */
r_if
c_cond
(paren
id|npdap-&gt;xbow_peer
op_ne
id|INVALID_NASID
)paren
(brace
id|nodepda_t
op_star
id|peer_npdap
op_assign
id|NODEPDA
c_func
(paren
id|nasid_to_cnodeid
c_func
(paren
id|npdap-&gt;xbow_peer
)paren
)paren
suffix:semicolon
id|peer_sema
op_assign
op_amp
id|peer_npdap-&gt;xbow_sema
suffix:semicolon
id|volunteer_for_widgets
c_func
(paren
id|switchv
comma
id|peer_npdap-&gt;node_vertex
)paren
suffix:semicolon
)brace
id|assign_widgets_to_volunteers
c_func
(paren
id|switchv
comma
id|hubv
)paren
suffix:semicolon
multiline_comment|/* Signal that we&squot;re done */
r_if
c_cond
(paren
id|peer_sema
)paren
(brace
id|up
c_func
(paren
id|peer_sema
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Wait &squot;til master is done assigning widgets. */
id|down
c_func
(paren
op_amp
id|npdap-&gt;xbow_sema
)paren
suffix:semicolon
)brace
multiline_comment|/* Now both nodes can safely inititialize widgets */
id|io_init_xswitch_widgets
c_func
(paren
id|switchv
comma
id|cnodeid
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;&bslash;nio_init_node: DONE INITIALIZED ALL I/O FOR CNODEID %d&bslash;n&bslash;n&quot;
comma
id|cnodeid
)paren
suffix:semicolon
)brace
macro_line|#include &lt;asm/sn/ioerror_handling.h&gt;
multiline_comment|/*&n; * Initialize all I/O devices.  Starting closest to nodes, probe and&n; * initialize outward.&n; */
r_void
DECL|function|init_all_devices
id|init_all_devices
c_func
(paren
r_void
)paren
(brace
id|cnodeid_t
id|cnodeid
comma
id|active
suffix:semicolon
id|active
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cnodeid
op_assign
l_int|0
suffix:semicolon
id|cnodeid
OL
id|numionodes
suffix:semicolon
id|cnodeid
op_increment
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;init_all_devices: Calling io_init_node() for cnode %d&bslash;n&quot;
comma
id|cnodeid
)paren
suffix:semicolon
id|io_init_node
c_func
(paren
id|cnodeid
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;init_all_devices: Done io_init_node() for cnode %d&bslash;n&quot;
comma
id|cnodeid
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|cnodeid
op_assign
l_int|0
suffix:semicolon
id|cnodeid
OL
id|numnodes
suffix:semicolon
id|cnodeid
op_increment
)paren
(brace
multiline_comment|/*&n;&t; &t; * Update information generated by IO init.&n;&t;&t; */
id|update_node_information
c_func
(paren
id|cnodeid
)paren
suffix:semicolon
)brace
)brace
r_static
DECL|variable|io_brick_tab
r_struct
id|io_brick_map_s
id|io_brick_tab
(braket
)braket
op_assign
(brace
multiline_comment|/* PXbrick widget number to PCI bus number map */
(brace
id|MODULE_PXBRICK
comma
multiline_comment|/* PXbrick type   */
multiline_comment|/*  PCI Bus #                                  Widget #       */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x0 - 0x7      */
l_int|0
comma
multiline_comment|/* 0x8            */
l_int|0
comma
multiline_comment|/* 0x9            */
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0xa - 0xb      */
l_int|1
comma
multiline_comment|/* 0xc            */
l_int|5
comma
multiline_comment|/* 0xd            */
l_int|0
comma
multiline_comment|/* 0xe            */
l_int|3
multiline_comment|/* 0xf            */
)brace
)brace
comma
multiline_comment|/* OPUSbrick widget number to PCI bus number map */
(brace
id|MODULE_OPUSBRICK
comma
multiline_comment|/* OPUSbrick type */
multiline_comment|/*  PCI Bus #                                  Widget #       */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x0 - 0x7      */
l_int|0
comma
multiline_comment|/* 0x8            */
l_int|0
comma
multiline_comment|/* 0x9            */
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0xa - 0xb      */
l_int|0
comma
multiline_comment|/* 0xc            */
l_int|0
comma
multiline_comment|/* 0xd            */
l_int|0
comma
multiline_comment|/* 0xe            */
l_int|1
multiline_comment|/* 0xf            */
)brace
)brace
comma
multiline_comment|/* IXbrick widget number to PCI bus number map */
(brace
id|MODULE_IXBRICK
comma
multiline_comment|/* IXbrick type   */
multiline_comment|/*  PCI Bus #                                  Widget #       */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x0 - 0x7      */
l_int|0
comma
multiline_comment|/* 0x8            */
l_int|0
comma
multiline_comment|/* 0x9            */
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0xa - 0xb      */
l_int|1
comma
multiline_comment|/* 0xc            */
l_int|5
comma
multiline_comment|/* 0xd            */
l_int|0
comma
multiline_comment|/* 0xe            */
l_int|3
multiline_comment|/* 0xf            */
)brace
)brace
comma
multiline_comment|/* CG brick widget number to PCI bus number map */
(brace
id|MODULE_CGBRICK
comma
multiline_comment|/* CG brick       */
multiline_comment|/*  PCI Bus #                                  Widget #       */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x0 - 0x7      */
l_int|0
comma
multiline_comment|/* 0x8            */
l_int|0
comma
multiline_comment|/* 0x9            */
l_int|0
comma
l_int|1
comma
multiline_comment|/* 0xa - 0xb      */
l_int|0
comma
multiline_comment|/* 0xc            */
l_int|0
comma
multiline_comment|/* 0xd            */
l_int|0
comma
multiline_comment|/* 0xe            */
l_int|0
multiline_comment|/* 0xf            */
)brace
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Use the brick&squot;s type to map a widget number to a meaningful int&n; */
r_int
DECL|function|io_brick_map_widget
id|io_brick_map_widget
c_func
(paren
r_int
id|brick_type
comma
r_int
id|widget_num
)paren
(brace
r_int
id|num_bricks
comma
id|i
suffix:semicolon
multiline_comment|/* Calculate number of bricks in table */
id|num_bricks
op_assign
r_sizeof
(paren
id|io_brick_tab
)paren
op_div
r_sizeof
(paren
id|io_brick_tab
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* Look for brick prefix in table */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_bricks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|brick_type
op_eq
id|io_brick_tab
(braket
id|i
)braket
dot
id|ibm_type
)paren
r_return
id|io_brick_tab
(braket
id|i
)braket
dot
id|ibm_map_wid
(braket
id|widget_num
)braket
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
