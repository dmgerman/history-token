multiline_comment|/*&n; * llc_sap.c - driver routines for SAP component.&n; *&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; * &t;&t; 2001-2003 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;net/llc.h&gt;
macro_line|#include &lt;net/llc_if.h&gt;
macro_line|#include &lt;net/llc_conn.h&gt;
macro_line|#include &lt;net/llc_pdu.h&gt;
macro_line|#include &lt;net/llc_sap.h&gt;
macro_line|#include &lt;net/llc_s_ac.h&gt;
macro_line|#include &lt;net/llc_s_ev.h&gt;
macro_line|#include &lt;net/llc_s_st.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/llc.h&gt;
multiline_comment|/**&n; *&t;llc_alloc_frame - allocates sk_buff for frame&n; *&n; *&t;Allocates an sk_buff for frame and initializes sk_buff fields.&n; *&t;Returns allocated skb or %NULL when out of memory.&n; */
DECL|function|llc_alloc_frame
r_struct
id|sk_buff
op_star
id|llc_alloc_frame
c_func
(paren
r_void
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|alloc_skb
c_func
(paren
l_int|128
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|skb_reserve
c_func
(paren
id|skb
comma
l_int|50
)paren
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_802_2
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev_base-&gt;next
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;head
suffix:semicolon
)brace
r_return
id|skb
suffix:semicolon
)brace
DECL|function|llc_save_primitive
r_void
id|llc_save_primitive
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|prim
)paren
(brace
r_struct
id|sockaddr_llc
op_star
id|addr
op_assign
id|llc_ui_skb_cb
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/* save primitive for use by the user. */
id|addr-&gt;sllc_family
op_assign
id|skb-&gt;sk-&gt;sk_family
suffix:semicolon
id|addr-&gt;sllc_arphrd
op_assign
id|skb-&gt;dev-&gt;type
suffix:semicolon
id|addr-&gt;sllc_test
op_assign
id|prim
op_eq
id|LLC_TEST_PRIM
suffix:semicolon
id|addr-&gt;sllc_xid
op_assign
id|prim
op_eq
id|LLC_XID_PRIM
suffix:semicolon
id|addr-&gt;sllc_ua
op_assign
id|prim
op_eq
id|LLC_DATAUNIT_PRIM
suffix:semicolon
id|llc_pdu_decode_sa
c_func
(paren
id|skb
comma
id|addr-&gt;sllc_smac
)paren
suffix:semicolon
id|llc_pdu_decode_da
c_func
(paren
id|skb
comma
id|addr-&gt;sllc_dmac
)paren
suffix:semicolon
id|llc_pdu_decode_dsap
c_func
(paren
id|skb
comma
op_amp
id|addr-&gt;sllc_dsap
)paren
suffix:semicolon
id|llc_pdu_decode_ssap
c_func
(paren
id|skb
comma
op_amp
id|addr-&gt;sllc_ssap
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_rtn_pdu - Informs upper layer on rx of an UI, XID or TEST pdu.&n; *&t;@sap: pointer to SAP&n; *&t;@skb: received pdu&n; */
DECL|function|llc_sap_rtn_pdu
r_void
id|llc_sap_rtn_pdu
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|llc_sap_state_ev
op_star
id|ev
op_assign
id|llc_sap_ev
c_func
(paren
id|skb
)paren
suffix:semicolon
r_struct
id|llc_pdu_un
op_star
id|pdu
op_assign
id|llc_pdu_un_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|LLC_U_PDU_RSP
c_func
(paren
id|pdu
)paren
)paren
(brace
r_case
id|LLC_1_PDU_CMD_TEST
suffix:colon
id|ev-&gt;prim
op_assign
id|LLC_TEST_PRIM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LLC_1_PDU_CMD_XID
suffix:colon
id|ev-&gt;prim
op_assign
id|LLC_XID_PRIM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LLC_1_PDU_CMD_UI
suffix:colon
id|ev-&gt;prim
op_assign
id|LLC_DATAUNIT_PRIM
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ev-&gt;ind_cfm_flag
op_assign
id|LLC_IND
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_find_sap_trans - finds transition for event&n; *&t;@sap: pointer to SAP&n; *&t;@skb: happened event&n; *&n; *&t;This function finds transition that matches with happened event.&n; *&t;Returns the pointer to found transition on success or %NULL for&n; *&t;failure.&n; */
DECL|function|llc_find_sap_trans
r_static
r_struct
id|llc_sap_state_trans
op_star
id|llc_find_sap_trans
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_struct
id|llc_sap_state_trans
op_star
id|rc
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|llc_sap_state_trans
op_star
op_star
id|next_trans
suffix:semicolon
r_struct
id|llc_sap_state
op_star
id|curr_state
op_assign
op_amp
id|llc_sap_state_table
(braket
id|sap-&gt;state
op_minus
l_int|1
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Search thru events for this state until list exhausted or until&n;&t; * its obvious the event is not valid for the current state&n;&t; */
r_for
c_loop
(paren
id|next_trans
op_assign
id|curr_state-&gt;transitions
suffix:semicolon
id|next_trans
(braket
id|i
)braket
op_member_access_from_pointer
id|ev
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|next_trans
(braket
id|i
)braket
op_member_access_from_pointer
id|ev
c_func
(paren
id|sap
comma
id|skb
)paren
)paren
(brace
id|rc
op_assign
id|next_trans
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* got event match; return it */
r_break
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_exec_sap_trans_actions - execute actions related to event&n; *&t;@sap: pointer to SAP&n; *&t;@trans: pointer to transition that it&squot;s actions must be performed&n; *&t;@skb: happened event.&n; *&n; *&t;This function executes actions that is related to happened event.&n; *&t;Returns 0 for success and 1 for failure of at least one action.&n; */
DECL|function|llc_exec_sap_trans_actions
r_static
r_int
id|llc_exec_sap_trans_actions
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|llc_sap_state_trans
op_star
id|trans
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|llc_sap_action_t
op_star
id|next_action
op_assign
id|trans-&gt;ev_actions
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|next_action
op_logical_and
op_star
id|next_action
suffix:semicolon
id|next_action
op_increment
)paren
r_if
c_cond
(paren
(paren
op_star
id|next_action
)paren
(paren
id|sap
comma
id|skb
)paren
)paren
id|rc
op_assign
l_int|1
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_next_state - finds transition, execs actions &amp; change SAP state&n; *&t;@sap: pointer to SAP&n; *&t;@skb: happened event&n; *&n; *&t;This function finds transition that matches with happened event, then&n; *&t;executes related actions and finally changes state of SAP. It returns&n; *&t;0 on success and 1 for failure.&n; */
DECL|function|llc_sap_next_state
r_static
r_int
id|llc_sap_next_state
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|rc
op_assign
l_int|1
suffix:semicolon
r_struct
id|llc_sap_state_trans
op_star
id|trans
suffix:semicolon
r_if
c_cond
(paren
id|sap-&gt;state
OG
id|LLC_NR_SAP_STATES
)paren
r_goto
id|out
suffix:semicolon
id|trans
op_assign
id|llc_find_sap_trans
c_func
(paren
id|sap
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|trans
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Got the state to which we next transition; perform the actions&n;&t; * associated with this transition before actually transitioning to the&n;&t; * next state&n;&t; */
id|rc
op_assign
id|llc_exec_sap_trans_actions
c_func
(paren
id|sap
comma
id|trans
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Transition SAP to next state if all actions execute successfully&n;&t; */
id|sap-&gt;state
op_assign
id|trans-&gt;next_state
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_state_process - sends event to SAP state machine&n; *&t;@sap: sap to use&n; *&t;@skb: pointer to occurred event&n; *&n; *&t;After executing actions of the event, upper layer will be indicated&n; *&t;if needed(on receiving an UI frame). sk can be null for the&n; *&t;datalink_proto case.&n; */
DECL|function|llc_sap_state_process
r_void
id|llc_sap_state_process
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|llc_sap_state_ev
op_star
id|ev
op_assign
id|llc_sap_ev
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We have to hold the skb, because llc_sap_next_state&n;&t; * will kfree it in the sending path and we need to&n;&t; * look at the skb-&gt;cb, where we encode llc_sap_state_ev.&n;&t; */
id|skb_get
c_func
(paren
id|skb
)paren
suffix:semicolon
id|ev-&gt;ind_cfm_flag
op_assign
l_int|0
suffix:semicolon
id|llc_sap_next_state
c_func
(paren
id|sap
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ev-&gt;ind_cfm_flag
op_eq
id|LLC_IND
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;sk-&gt;sk_state
op_eq
id|TCP_LISTEN
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_else
(brace
id|llc_save_primitive
c_func
(paren
id|skb
comma
id|ev-&gt;prim
)paren
suffix:semicolon
multiline_comment|/* queue skb to the user. */
r_if
c_cond
(paren
id|sock_queue_rcv_skb
c_func
(paren
id|skb-&gt;sk
comma
id|skb
)paren
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_build_and_send_test_pkt - TEST interface for upper layers.&n; *&t;@sap: sap to use&n; *&t;@skb: packet to send&n; *&t;@dmac: destination mac address&n; *&t;@dsap: destination sap&n; *&n; *&t;This function is called when upper layer wants to send a TEST pdu.&n; *&t;Returns 0 for success, 1 otherwise.&n; */
DECL|function|llc_build_and_send_test_pkt
r_void
id|llc_build_and_send_test_pkt
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|dmac
comma
id|u8
id|dsap
)paren
(brace
r_struct
id|llc_sap_state_ev
op_star
id|ev
op_assign
id|llc_sap_ev
c_func
(paren
id|skb
)paren
suffix:semicolon
id|ev-&gt;saddr.lsap
op_assign
id|sap-&gt;laddr.lsap
suffix:semicolon
id|ev-&gt;daddr.lsap
op_assign
id|dsap
suffix:semicolon
id|memcpy
c_func
(paren
id|ev-&gt;saddr.mac
comma
id|skb-&gt;dev-&gt;dev_addr
comma
id|IFHWADDRLEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ev-&gt;daddr.mac
comma
id|dmac
comma
id|IFHWADDRLEN
)paren
suffix:semicolon
id|ev-&gt;type
op_assign
id|LLC_SAP_EV_TYPE_PRIM
suffix:semicolon
id|ev-&gt;prim
op_assign
id|LLC_TEST_PRIM
suffix:semicolon
id|ev-&gt;prim_type
op_assign
id|LLC_PRIM_TYPE_REQ
suffix:semicolon
id|llc_sap_state_process
c_func
(paren
id|sap
comma
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_build_and_send_xid_pkt - XID interface for upper layers&n; *&t;@sap: sap to use&n; *&t;@skb: packet to send&n; *&t;@dmac: destination mac address&n; *&t;@dsap: destination sap&n; *&n; *&t;This function is called when upper layer wants to send a XID pdu.&n; *&t;Returns 0 for success, 1 otherwise.&n; */
DECL|function|llc_build_and_send_xid_pkt
r_void
id|llc_build_and_send_xid_pkt
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|dmac
comma
id|u8
id|dsap
)paren
(brace
r_struct
id|llc_sap_state_ev
op_star
id|ev
op_assign
id|llc_sap_ev
c_func
(paren
id|skb
)paren
suffix:semicolon
id|ev-&gt;saddr.lsap
op_assign
id|sap-&gt;laddr.lsap
suffix:semicolon
id|ev-&gt;daddr.lsap
op_assign
id|dsap
suffix:semicolon
id|memcpy
c_func
(paren
id|ev-&gt;saddr.mac
comma
id|skb-&gt;dev-&gt;dev_addr
comma
id|IFHWADDRLEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ev-&gt;daddr.mac
comma
id|dmac
comma
id|IFHWADDRLEN
)paren
suffix:semicolon
id|ev-&gt;type
op_assign
id|LLC_SAP_EV_TYPE_PRIM
suffix:semicolon
id|ev-&gt;prim
op_assign
id|LLC_XID_PRIM
suffix:semicolon
id|ev-&gt;prim_type
op_assign
id|LLC_PRIM_TYPE_REQ
suffix:semicolon
id|llc_sap_state_process
c_func
(paren
id|sap
comma
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_rcv - sends received pdus to the sap state machine&n; *&t;@sap: current sap component structure.&n; *&t;@skb: received frame.&n; *&n; *&t;Sends received pdus to the sap state machine.&n; */
DECL|function|llc_sap_rcv
r_static
r_void
id|llc_sap_rcv
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|llc_sap_state_ev
op_star
id|ev
op_assign
id|llc_sap_ev
c_func
(paren
id|skb
)paren
suffix:semicolon
id|ev-&gt;type
op_assign
id|LLC_SAP_EV_TYPE_PDU
suffix:semicolon
id|ev-&gt;reason
op_assign
l_int|0
suffix:semicolon
id|llc_sap_state_process
c_func
(paren
id|sap
comma
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_lookup_dgram - Finds dgram socket for the local sap/mac&n; *&t;@sap: SAP&n; *&t;@laddr: address of local LLC (MAC + SAP)&n; *&n; *&t;Search socket list of the SAP and finds connection using the local&n; *&t;mac, and local sap. Returns pointer for socket found, %NULL otherwise.&n; */
DECL|function|llc_lookup_dgram
r_struct
id|sock
op_star
id|llc_lookup_dgram
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|llc_addr
op_star
id|laddr
)paren
(brace
r_struct
id|sock
op_star
id|rc
suffix:semicolon
r_struct
id|hlist_node
op_star
id|node
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
id|sk_for_each
c_func
(paren
id|rc
comma
id|node
comma
op_amp
id|sap-&gt;sk_list.list
)paren
(brace
r_struct
id|llc_opt
op_star
id|llc
op_assign
id|llc_sk
c_func
(paren
id|rc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc-&gt;sk_type
op_eq
id|SOCK_DGRAM
op_logical_and
id|llc-&gt;laddr.lsap
op_eq
id|laddr-&gt;lsap
op_logical_and
id|llc_mac_match
c_func
(paren
id|llc-&gt;laddr.mac
comma
id|laddr-&gt;mac
)paren
)paren
(brace
id|sock_hold
c_func
(paren
id|rc
)paren
suffix:semicolon
r_goto
id|found
suffix:semicolon
)brace
)brace
id|rc
op_assign
l_int|NULL
suffix:semicolon
id|found
suffix:colon
id|read_unlock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|llc_sap_handler
r_void
id|llc_sap_handler
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|llc_addr
id|laddr
suffix:semicolon
r_struct
id|sock
op_star
id|sk
suffix:semicolon
id|llc_pdu_decode_da
c_func
(paren
id|skb
comma
id|laddr.mac
)paren
suffix:semicolon
id|llc_pdu_decode_dsap
c_func
(paren
id|skb
comma
op_amp
id|laddr.lsap
)paren
suffix:semicolon
id|sk
op_assign
id|llc_lookup_dgram
c_func
(paren
id|sap
comma
op_amp
id|laddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk
)paren
(brace
id|skb-&gt;sk
op_assign
id|sk
suffix:semicolon
id|llc_sap_rcv
c_func
(paren
id|sap
comma
id|skb
)paren
suffix:semicolon
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
eof
