multiline_comment|/*&n; * Copyright (c) 2004 Topspin Communications.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: mthca_mad.c 1349 2004-12-16 21:09:43Z roland $&n; */
macro_line|#include &lt;ib_verbs.h&gt;
macro_line|#include &lt;ib_mad.h&gt;
macro_line|#include &lt;ib_smi.h&gt;
macro_line|#include &quot;mthca_dev.h&quot;
macro_line|#include &quot;mthca_cmd.h&quot;
r_enum
(brace
DECL|enumerator|MTHCA_VENDOR_CLASS1
id|MTHCA_VENDOR_CLASS1
op_assign
l_int|0x9
comma
DECL|enumerator|MTHCA_VENDOR_CLASS2
id|MTHCA_VENDOR_CLASS2
op_assign
l_int|0xa
)brace
suffix:semicolon
DECL|struct|mthca_trap_mad
r_struct
id|mthca_trap_mad
(brace
DECL|member|mad
r_struct
id|ib_mad
op_star
id|mad
suffix:semicolon
id|DECLARE_PCI_UNMAP_ADDR
c_func
(paren
id|mapping
)paren
)brace
suffix:semicolon
DECL|function|update_sm_ah
r_static
r_void
id|update_sm_ah
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
id|u8
id|port_num
comma
id|u16
id|lid
comma
id|u8
id|sl
)paren
(brace
r_struct
id|ib_ah
op_star
id|new_ah
suffix:semicolon
r_struct
id|ib_ah_attr
id|ah_attr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;send_agent
(braket
id|port_num
op_minus
l_int|1
)braket
(braket
l_int|0
)braket
)paren
r_return
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ah_attr
comma
l_int|0
comma
r_sizeof
id|ah_attr
)paren
suffix:semicolon
id|ah_attr.dlid
op_assign
id|lid
suffix:semicolon
id|ah_attr.sl
op_assign
id|sl
suffix:semicolon
id|ah_attr.port_num
op_assign
id|port_num
suffix:semicolon
id|new_ah
op_assign
id|ib_create_ah
c_func
(paren
id|dev-&gt;send_agent
(braket
id|port_num
op_minus
l_int|1
)braket
(braket
l_int|0
)braket
op_member_access_from_pointer
id|qp-&gt;pd
comma
op_amp
id|ah_attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|new_ah
)paren
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dev-&gt;sm_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;sm_ah
(braket
id|port_num
op_minus
l_int|1
)braket
)paren
id|ib_destroy_ah
c_func
(paren
id|dev-&gt;sm_ah
(braket
id|port_num
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|dev-&gt;sm_ah
(braket
id|port_num
op_minus
l_int|1
)braket
op_assign
id|new_ah
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;sm_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Snoop SM MADs for port info and P_Key table sets, so we can&n; * synthesize LID change and P_Key change events.&n; */
DECL|function|smp_snoop
r_static
r_void
id|smp_snoop
c_func
(paren
r_struct
id|ib_device
op_star
id|ibdev
comma
id|u8
id|port_num
comma
r_struct
id|ib_mad
op_star
id|mad
)paren
(brace
r_struct
id|ib_event
id|event
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mad-&gt;mad_hdr.mgmt_class
op_eq
id|IB_MGMT_CLASS_SUBN_LID_ROUTED
op_logical_or
id|mad-&gt;mad_hdr.mgmt_class
op_eq
id|IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE
)paren
op_logical_and
id|mad-&gt;mad_hdr.method
op_eq
id|IB_MGMT_METHOD_SET
)paren
(brace
r_if
c_cond
(paren
id|mad-&gt;mad_hdr.attr_id
op_eq
id|IB_SMP_ATTR_PORT_INFO
)paren
(brace
id|update_sm_ah
c_func
(paren
id|to_mdev
c_func
(paren
id|ibdev
)paren
comma
id|port_num
comma
id|be16_to_cpup
c_func
(paren
(paren
id|__be16
op_star
)paren
(paren
id|mad-&gt;data
op_plus
l_int|58
)paren
)paren
comma
(paren
op_star
(paren
id|u8
op_star
)paren
(paren
id|mad-&gt;data
op_plus
l_int|76
)paren
)paren
op_amp
l_int|0xf
)paren
suffix:semicolon
id|event.device
op_assign
id|ibdev
suffix:semicolon
id|event.event
op_assign
id|IB_EVENT_LID_CHANGE
suffix:semicolon
id|event.element.port_num
op_assign
id|port_num
suffix:semicolon
id|ib_dispatch_event
c_func
(paren
op_amp
id|event
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mad-&gt;mad_hdr.attr_id
op_eq
id|IB_SMP_ATTR_PKEY_TABLE
)paren
(brace
id|event.device
op_assign
id|ibdev
suffix:semicolon
id|event.event
op_assign
id|IB_EVENT_PKEY_CHANGE
suffix:semicolon
id|event.element.port_num
op_assign
id|port_num
suffix:semicolon
id|ib_dispatch_event
c_func
(paren
op_amp
id|event
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|forward_trap
r_static
r_void
id|forward_trap
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
id|u8
id|port_num
comma
r_struct
id|ib_mad
op_star
id|mad
)paren
(brace
r_int
id|qpn
op_assign
id|mad-&gt;mad_hdr.mgmt_class
op_ne
id|IB_MGMT_CLASS_SUBN_LID_ROUTED
suffix:semicolon
r_struct
id|mthca_trap_mad
op_star
id|tmad
suffix:semicolon
r_struct
id|ib_sge
id|gather_list
suffix:semicolon
r_struct
id|ib_send_wr
op_star
id|bad_wr
comma
id|wr
op_assign
(brace
dot
id|opcode
op_assign
id|IB_WR_SEND
comma
dot
id|sg_list
op_assign
op_amp
id|gather_list
comma
dot
id|num_sge
op_assign
l_int|1
comma
dot
id|send_flags
op_assign
id|IB_SEND_SIGNALED
comma
dot
id|wr
op_assign
(brace
dot
id|ud
op_assign
(brace
dot
id|remote_qpn
op_assign
id|qpn
comma
dot
id|remote_qkey
op_assign
id|qpn
ques
c_cond
id|IB_QP1_QKEY
suffix:colon
l_int|0
comma
dot
id|timeout_ms
op_assign
l_int|0
)brace
)brace
)brace
suffix:semicolon
r_struct
id|ib_mad_agent
op_star
id|agent
op_assign
id|dev-&gt;send_agent
(braket
id|port_num
op_minus
l_int|1
)braket
(braket
id|qpn
)braket
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|agent
)paren
(brace
id|tmad
op_assign
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|tmad
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmad
)paren
r_return
suffix:semicolon
id|tmad-&gt;mad
op_assign
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|tmad-&gt;mad
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmad-&gt;mad
)paren
(brace
id|kfree
c_func
(paren
id|tmad
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|tmad-&gt;mad
comma
id|mad
comma
r_sizeof
op_star
id|mad
)paren
suffix:semicolon
id|wr.wr.ud.mad_hdr
op_assign
op_amp
id|tmad-&gt;mad-&gt;mad_hdr
suffix:semicolon
id|wr.wr_id
op_assign
(paren
r_int
r_int
)paren
id|tmad
suffix:semicolon
id|gather_list.addr
op_assign
id|dma_map_single
c_func
(paren
id|agent-&gt;device-&gt;dma_device
comma
id|tmad-&gt;mad
comma
r_sizeof
op_star
id|tmad-&gt;mad
comma
id|DMA_TO_DEVICE
)paren
suffix:semicolon
id|gather_list.length
op_assign
r_sizeof
op_star
id|tmad-&gt;mad
suffix:semicolon
id|gather_list.lkey
op_assign
id|to_mpd
c_func
(paren
id|agent-&gt;qp-&gt;pd
)paren
op_member_access_from_pointer
id|ntmr.ibmr.lkey
suffix:semicolon
id|pci_unmap_addr_set
c_func
(paren
id|tmad
comma
id|mapping
comma
id|gather_list.addr
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We rely here on the fact that MLX QPs don&squot;t use the&n;&t;&t; * address handle after the send is posted (this is&n;&t;&t; * wrong following the IB spec strictly, but we know&n;&t;&t; * it&squot;s OK for our devices).&n;&t;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dev-&gt;sm_lock
comma
id|flags
)paren
suffix:semicolon
id|wr.wr.ud.ah
op_assign
id|dev-&gt;sm_ah
(braket
id|port_num
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|wr.wr.ud.ah
)paren
id|ret
op_assign
id|ib_post_send_mad
c_func
(paren
id|agent
comma
op_amp
id|wr
comma
op_amp
id|bad_wr
)paren
suffix:semicolon
r_else
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;sm_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|dma_unmap_single
c_func
(paren
id|agent-&gt;device-&gt;dma_device
comma
id|pci_unmap_addr
c_func
(paren
id|tmad
comma
id|mapping
)paren
comma
r_sizeof
op_star
id|tmad-&gt;mad
comma
id|DMA_TO_DEVICE
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmad-&gt;mad
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmad
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|mthca_process_mad
r_int
id|mthca_process_mad
c_func
(paren
r_struct
id|ib_device
op_star
id|ibdev
comma
r_int
id|mad_flags
comma
id|u8
id|port_num
comma
id|u16
id|slid
comma
r_struct
id|ib_mad
op_star
id|in_mad
comma
r_struct
id|ib_mad
op_star
id|out_mad
)paren
(brace
r_int
id|err
suffix:semicolon
id|u8
id|status
suffix:semicolon
multiline_comment|/* Forward locally generated traps to the SM */
r_if
c_cond
(paren
id|in_mad-&gt;mad_hdr.method
op_eq
id|IB_MGMT_METHOD_TRAP
op_logical_and
id|slid
op_eq
l_int|0
)paren
(brace
id|forward_trap
c_func
(paren
id|to_mdev
c_func
(paren
id|ibdev
)paren
comma
id|port_num
comma
id|in_mad
)paren
suffix:semicolon
r_return
id|IB_MAD_RESULT_SUCCESS
op_or
id|IB_MAD_RESULT_CONSUMED
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Only handle SM gets, sets and trap represses for SM class&n;&t; *&n;&t; * Only handle PMA and Mellanox vendor-specific class gets and&n;&t; * sets for other classes.&n;&t; */
r_if
c_cond
(paren
id|in_mad-&gt;mad_hdr.mgmt_class
op_eq
id|IB_MGMT_CLASS_SUBN_LID_ROUTED
op_logical_or
id|in_mad-&gt;mad_hdr.mgmt_class
op_eq
id|IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE
)paren
(brace
r_if
c_cond
(paren
id|in_mad-&gt;mad_hdr.method
op_ne
id|IB_MGMT_METHOD_GET
op_logical_and
id|in_mad-&gt;mad_hdr.method
op_ne
id|IB_MGMT_METHOD_SET
op_logical_and
id|in_mad-&gt;mad_hdr.method
op_ne
id|IB_MGMT_METHOD_TRAP_REPRESS
)paren
r_return
id|IB_MAD_RESULT_SUCCESS
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Don&squot;t process SMInfo queries or vendor-specific&n;&t;&t; * MADs -- the SMA can&squot;t handle them.&n;&t;&t; */
r_if
c_cond
(paren
id|in_mad-&gt;mad_hdr.attr_id
op_eq
id|IB_SMP_ATTR_SM_INFO
op_logical_or
(paren
(paren
id|in_mad-&gt;mad_hdr.attr_id
op_amp
id|IB_SMP_ATTR_VENDOR_MASK
)paren
op_eq
id|IB_SMP_ATTR_VENDOR_MASK
)paren
)paren
r_return
id|IB_MAD_RESULT_SUCCESS
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|in_mad-&gt;mad_hdr.mgmt_class
op_eq
id|IB_MGMT_CLASS_PERF_MGMT
op_logical_or
id|in_mad-&gt;mad_hdr.mgmt_class
op_eq
id|MTHCA_VENDOR_CLASS1
op_logical_or
id|in_mad-&gt;mad_hdr.mgmt_class
op_eq
id|MTHCA_VENDOR_CLASS2
)paren
(brace
r_if
c_cond
(paren
id|in_mad-&gt;mad_hdr.method
op_ne
id|IB_MGMT_METHOD_GET
op_logical_and
id|in_mad-&gt;mad_hdr.method
op_ne
id|IB_MGMT_METHOD_SET
)paren
r_return
id|IB_MAD_RESULT_SUCCESS
suffix:semicolon
)brace
r_else
r_return
id|IB_MAD_RESULT_SUCCESS
suffix:semicolon
id|err
op_assign
id|mthca_MAD_IFC
c_func
(paren
id|to_mdev
c_func
(paren
id|ibdev
)paren
comma
op_logical_neg
op_logical_neg
(paren
id|mad_flags
op_amp
id|IB_MAD_IGNORE_MKEY
)paren
comma
id|port_num
comma
id|in_mad
comma
id|out_mad
comma
op_amp
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|mthca_err
c_func
(paren
id|to_mdev
c_func
(paren
id|ibdev
)paren
comma
l_string|&quot;MAD_IFC failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|IB_MAD_RESULT_FAILURE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_eq
id|MTHCA_CMD_STAT_BAD_PKT
)paren
r_return
id|IB_MAD_RESULT_SUCCESS
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|mthca_err
c_func
(paren
id|to_mdev
c_func
(paren
id|ibdev
)paren
comma
l_string|&quot;MAD_IFC returned status %02x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|IB_MAD_RESULT_FAILURE
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|out_mad-&gt;mad_hdr.status
)paren
id|smp_snoop
c_func
(paren
id|ibdev
comma
id|port_num
comma
id|in_mad
)paren
suffix:semicolon
multiline_comment|/* set return bit in status of directed route responses */
r_if
c_cond
(paren
id|in_mad-&gt;mad_hdr.mgmt_class
op_eq
id|IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE
)paren
id|out_mad-&gt;mad_hdr.status
op_or_assign
id|cpu_to_be16
c_func
(paren
l_int|1
op_lshift
l_int|15
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_mad-&gt;mad_hdr.method
op_eq
id|IB_MGMT_METHOD_TRAP_REPRESS
)paren
multiline_comment|/* no response for trap repress */
r_return
id|IB_MAD_RESULT_SUCCESS
op_or
id|IB_MAD_RESULT_CONSUMED
suffix:semicolon
r_return
id|IB_MAD_RESULT_SUCCESS
op_or
id|IB_MAD_RESULT_REPLY
suffix:semicolon
)brace
DECL|function|send_handler
r_static
r_void
id|send_handler
c_func
(paren
r_struct
id|ib_mad_agent
op_star
id|agent
comma
r_struct
id|ib_mad_send_wc
op_star
id|mad_send_wc
)paren
(brace
r_struct
id|mthca_trap_mad
op_star
id|tmad
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
r_int
)paren
id|mad_send_wc-&gt;wr_id
suffix:semicolon
id|dma_unmap_single
c_func
(paren
id|agent-&gt;device-&gt;dma_device
comma
id|pci_unmap_addr
c_func
(paren
id|tmad
comma
id|mapping
)paren
comma
r_sizeof
op_star
id|tmad-&gt;mad
comma
id|DMA_TO_DEVICE
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmad-&gt;mad
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmad
)paren
suffix:semicolon
)brace
DECL|function|mthca_create_agents
r_int
id|mthca_create_agents
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
(brace
r_struct
id|ib_mad_agent
op_star
id|agent
suffix:semicolon
r_int
id|p
comma
id|q
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|dev-&gt;sm_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
l_int|0
suffix:semicolon
id|p
OL
id|dev-&gt;limits.num_ports
suffix:semicolon
op_increment
id|p
)paren
r_for
c_loop
(paren
id|q
op_assign
l_int|0
suffix:semicolon
id|q
op_le
l_int|1
suffix:semicolon
op_increment
id|q
)paren
(brace
id|agent
op_assign
id|ib_register_mad_agent
c_func
(paren
op_amp
id|dev-&gt;ib_dev
comma
id|p
op_plus
l_int|1
comma
id|q
ques
c_cond
id|IB_QPT_GSI
suffix:colon
id|IB_QPT_SMI
comma
l_int|NULL
comma
l_int|0
comma
id|send_handler
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|agent
)paren
)paren
r_goto
id|err
suffix:semicolon
id|dev-&gt;send_agent
(braket
id|p
)braket
(braket
id|q
)braket
op_assign
id|agent
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|err
suffix:colon
r_for
c_loop
(paren
id|p
op_assign
l_int|0
suffix:semicolon
id|p
OL
id|dev-&gt;limits.num_ports
suffix:semicolon
op_increment
id|p
)paren
r_for
c_loop
(paren
id|q
op_assign
l_int|0
suffix:semicolon
id|q
op_le
l_int|1
suffix:semicolon
op_increment
id|q
)paren
r_if
c_cond
(paren
id|dev-&gt;send_agent
(braket
id|p
)braket
(braket
id|q
)braket
)paren
id|ib_unregister_mad_agent
c_func
(paren
id|dev-&gt;send_agent
(braket
id|p
)braket
(braket
id|q
)braket
)paren
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
id|agent
)paren
suffix:semicolon
)brace
DECL|function|mthca_free_agents
r_void
id|mthca_free_agents
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
(brace
r_struct
id|ib_mad_agent
op_star
id|agent
suffix:semicolon
r_int
id|p
comma
id|q
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
l_int|0
suffix:semicolon
id|p
OL
id|dev-&gt;limits.num_ports
suffix:semicolon
op_increment
id|p
)paren
(brace
r_for
c_loop
(paren
id|q
op_assign
l_int|0
suffix:semicolon
id|q
op_le
l_int|1
suffix:semicolon
op_increment
id|q
)paren
(brace
id|agent
op_assign
id|dev-&gt;send_agent
(braket
id|p
)braket
(braket
id|q
)braket
suffix:semicolon
id|dev-&gt;send_agent
(braket
id|p
)braket
(braket
id|q
)braket
op_assign
l_int|NULL
suffix:semicolon
id|ib_unregister_mad_agent
c_func
(paren
id|agent
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;sm_ah
(braket
id|p
)braket
)paren
id|ib_destroy_ah
c_func
(paren
id|dev-&gt;sm_ah
(braket
id|p
)braket
)paren
suffix:semicolon
)brace
)brace
eof
