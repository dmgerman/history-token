multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997, 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/driver.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/sn/pio.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xwidget.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/hcl_util.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xtalkaddrs.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/sn2/shub_mmr.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
multiline_comment|/* ARGSUSED */
r_void
DECL|function|hub_intr_init
id|hub_intr_init
c_func
(paren
id|vertex_hdl_t
id|hubv
)paren
(brace
)brace
id|xwidgetnum_t
DECL|function|hub_widget_id
id|hub_widget_id
c_func
(paren
id|nasid_t
id|nasid
)paren
(brace
id|hubii_wcr_t
id|ii_wcr
suffix:semicolon
multiline_comment|/* the control status register */
id|ii_wcr.wcr_reg_value
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|nasid
comma
id|IIO_WCR
)paren
suffix:semicolon
r_return
id|ii_wcr.wcr_fields_s.wcr_widget_id
suffix:semicolon
)brace
r_static
id|hub_intr_t
DECL|function|do_hub_intr_alloc
id|do_hub_intr_alloc
c_func
(paren
id|vertex_hdl_t
id|dev
comma
id|device_desc_t
id|dev_desc
comma
id|vertex_hdl_t
id|owner_dev
comma
r_int
id|uncond_nothread
)paren
(brace
id|cpuid_t
id|cpu
op_assign
l_int|0
suffix:semicolon
r_int
id|vector
suffix:semicolon
id|hub_intr_t
id|intr_hdl
suffix:semicolon
id|cnodeid_t
id|cnode
suffix:semicolon
r_int
id|cpuphys
comma
id|slice
suffix:semicolon
r_int
id|nasid
suffix:semicolon
id|iopaddr_t
id|xtalk_addr
suffix:semicolon
r_struct
id|xtalk_intr_s
op_star
id|xtalk_info
suffix:semicolon
id|xwidget_info_t
id|xwidget_info
suffix:semicolon
id|ilvl_t
id|intr_swlevel
op_assign
l_int|0
suffix:semicolon
id|cpu
op_assign
id|intr_heuristic
c_func
(paren
id|dev
comma
op_minus
l_int|1
comma
op_amp
id|vector
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_eq
id|CPU_NONE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to allocate interrupt for 0x%p&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|owner_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cpuphys
op_assign
id|cpu_physical_id
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|slice
op_assign
id|cpu_physical_id_to_slice
c_func
(paren
id|cpuphys
)paren
suffix:semicolon
id|nasid
op_assign
id|cpu_physical_id_to_nasid
c_func
(paren
id|cpuphys
)paren
suffix:semicolon
id|cnode
op_assign
id|cpuid_to_cnodeid
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slice
)paren
(brace
id|xtalk_addr
op_assign
id|SH_II_INT1
op_or
(paren
(paren
r_int
r_int
)paren
id|nasid
op_lshift
l_int|36
)paren
op_or
(paren
l_int|1UL
op_lshift
l_int|47
)paren
suffix:semicolon
)brace
r_else
(brace
id|xtalk_addr
op_assign
id|SH_II_INT0
op_or
(paren
(paren
r_int
r_int
)paren
id|nasid
op_lshift
l_int|36
)paren
op_or
(paren
l_int|1UL
op_lshift
l_int|47
)paren
suffix:semicolon
)brace
id|intr_hdl
op_assign
id|snia_kmem_alloc_node
c_func
(paren
r_sizeof
(paren
r_struct
id|hub_intr_s
)paren
comma
id|KM_NOSLEEP
comma
id|cnode
)paren
suffix:semicolon
id|ASSERT_ALWAYS
c_func
(paren
id|intr_hdl
)paren
suffix:semicolon
id|xtalk_info
op_assign
op_amp
id|intr_hdl-&gt;i_xtalk_info
suffix:semicolon
id|xtalk_info-&gt;xi_dev
op_assign
id|dev
suffix:semicolon
id|xtalk_info-&gt;xi_vector
op_assign
id|vector
suffix:semicolon
id|xtalk_info-&gt;xi_addr
op_assign
id|xtalk_addr
suffix:semicolon
id|xwidget_info
op_assign
id|xwidget_info_get
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xwidget_info
)paren
(brace
id|xtalk_info-&gt;xi_target
op_assign
id|xwidget_info_masterid_get
c_func
(paren
id|xwidget_info
)paren
suffix:semicolon
)brace
id|intr_hdl-&gt;i_swlevel
op_assign
id|intr_swlevel
suffix:semicolon
id|intr_hdl-&gt;i_cpuid
op_assign
id|cpu
suffix:semicolon
id|intr_hdl-&gt;i_bit
op_assign
id|vector
suffix:semicolon
id|intr_hdl-&gt;i_flags
op_or_assign
id|HUB_INTR_IS_ALLOCED
suffix:semicolon
r_return
id|intr_hdl
suffix:semicolon
)brace
id|hub_intr_t
DECL|function|hub_intr_alloc
id|hub_intr_alloc
c_func
(paren
id|vertex_hdl_t
id|dev
comma
id|device_desc_t
id|dev_desc
comma
id|vertex_hdl_t
id|owner_dev
)paren
(brace
r_return
id|do_hub_intr_alloc
c_func
(paren
id|dev
comma
id|dev_desc
comma
id|owner_dev
comma
l_int|0
)paren
suffix:semicolon
)brace
id|hub_intr_t
DECL|function|hub_intr_alloc_nothd
id|hub_intr_alloc_nothd
c_func
(paren
id|vertex_hdl_t
id|dev
comma
id|device_desc_t
id|dev_desc
comma
id|vertex_hdl_t
id|owner_dev
)paren
(brace
r_return
id|do_hub_intr_alloc
c_func
(paren
id|dev
comma
id|dev_desc
comma
id|owner_dev
comma
l_int|1
)paren
suffix:semicolon
)brace
r_void
DECL|function|hub_intr_free
id|hub_intr_free
c_func
(paren
id|hub_intr_t
id|intr_hdl
)paren
(brace
id|cpuid_t
id|cpu
op_assign
id|intr_hdl-&gt;i_cpuid
suffix:semicolon
r_int
id|vector
op_assign
id|intr_hdl-&gt;i_bit
suffix:semicolon
id|xtalk_intr_t
id|xtalk_info
suffix:semicolon
r_if
c_cond
(paren
id|intr_hdl-&gt;i_flags
op_amp
id|HUB_INTR_IS_CONNECTED
)paren
(brace
id|xtalk_info
op_assign
op_amp
id|intr_hdl-&gt;i_xtalk_info
suffix:semicolon
id|xtalk_info-&gt;xi_dev
op_assign
l_int|0
suffix:semicolon
id|xtalk_info-&gt;xi_vector
op_assign
l_int|0
suffix:semicolon
id|xtalk_info-&gt;xi_addr
op_assign
l_int|0
suffix:semicolon
id|hub_intr_disconnect
c_func
(paren
id|intr_hdl
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|intr_hdl-&gt;i_flags
op_amp
id|HUB_INTR_IS_ALLOCED
)paren
(brace
id|kfree
c_func
(paren
id|intr_hdl
)paren
suffix:semicolon
)brace
id|intr_unreserve_level
c_func
(paren
id|cpu
comma
id|vector
)paren
suffix:semicolon
)brace
r_int
DECL|function|hub_intr_connect
id|hub_intr_connect
c_func
(paren
id|hub_intr_t
id|intr_hdl
comma
id|intr_func_t
id|intr_func
comma
multiline_comment|/* xtalk intr handler */
r_void
op_star
id|intr_arg
comma
multiline_comment|/* arg to intr handler */
id|xtalk_intr_setfunc_t
id|setfunc
comma
r_void
op_star
id|setfunc_arg
)paren
(brace
r_int
id|rv
suffix:semicolon
id|cpuid_t
id|cpu
op_assign
id|intr_hdl-&gt;i_cpuid
suffix:semicolon
r_int
id|vector
op_assign
id|intr_hdl-&gt;i_bit
suffix:semicolon
id|ASSERT
c_func
(paren
id|intr_hdl-&gt;i_flags
op_amp
id|HUB_INTR_IS_ALLOCED
)paren
suffix:semicolon
id|rv
op_assign
id|intr_connect_level
c_func
(paren
id|cpu
comma
id|vector
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
OL
l_int|0
)paren
r_return
id|rv
suffix:semicolon
id|intr_hdl-&gt;i_xtalk_info.xi_setfunc
op_assign
id|setfunc
suffix:semicolon
id|intr_hdl-&gt;i_xtalk_info.xi_sfarg
op_assign
id|setfunc_arg
suffix:semicolon
r_if
c_cond
(paren
id|setfunc
)paren
(brace
(paren
op_star
id|setfunc
)paren
(paren
(paren
id|xtalk_intr_t
)paren
id|intr_hdl
)paren
suffix:semicolon
)brace
id|intr_hdl-&gt;i_flags
op_or_assign
id|HUB_INTR_IS_CONNECTED
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Disassociate handler with the specified interrupt.&n; */
r_void
DECL|function|hub_intr_disconnect
id|hub_intr_disconnect
c_func
(paren
id|hub_intr_t
id|intr_hdl
)paren
(brace
multiline_comment|/*REFERENCED*/
r_int
id|rv
suffix:semicolon
id|cpuid_t
id|cpu
op_assign
id|intr_hdl-&gt;i_cpuid
suffix:semicolon
r_int
id|bit
op_assign
id|intr_hdl-&gt;i_bit
suffix:semicolon
id|xtalk_intr_setfunc_t
id|setfunc
suffix:semicolon
id|setfunc
op_assign
id|intr_hdl-&gt;i_xtalk_info.xi_setfunc
suffix:semicolon
multiline_comment|/* TBD: send disconnected interrupts somewhere harmless */
r_if
c_cond
(paren
id|setfunc
)paren
(paren
op_star
id|setfunc
)paren
(paren
(paren
id|xtalk_intr_t
)paren
id|intr_hdl
)paren
suffix:semicolon
id|rv
op_assign
id|intr_disconnect_level
c_func
(paren
id|cpu
comma
id|bit
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|rv
op_eq
l_int|0
)paren
suffix:semicolon
id|intr_hdl-&gt;i_flags
op_and_assign
op_complement
id|HUB_INTR_IS_CONNECTED
suffix:semicolon
)brace
eof
