multiline_comment|/*&n; * llc_sap.c - driver routines for SAP component.&n; *&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; * &t;&t; 2001-2003 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/llc_conn.h&gt;
macro_line|#include &lt;net/llc_sap.h&gt;
macro_line|#include &lt;net/llc_s_ev.h&gt;
macro_line|#include &lt;net/llc_s_ac.h&gt;
macro_line|#include &lt;net/llc_s_st.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;net/llc_main.h&gt;
macro_line|#include &lt;net/llc_pdu.h&gt;
macro_line|#include &lt;linux/if_tr.h&gt;
multiline_comment|/**&n; *&t;llc_sap_assign_sock - adds a connection to a SAP&n; *&t;@sap: pointer to SAP.&n; *&t;@conn: pointer to connection.&n; *&n; *&t;This function adds a connection to connection_list of a SAP.&n; */
DECL|function|llc_sap_assign_sock
r_void
id|llc_sap_assign_sock
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
id|llc_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|sap
op_assign
id|sap
suffix:semicolon
id|sk_add_node
c_func
(paren
id|sk
comma
op_amp
id|sap-&gt;sk_list.list
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_unassign_sock - removes a connection from SAP&n; *&t;@sap: SAP&n; *&t;@sk: pointer to connection&n; *&n; *&t;This function removes a connection from sk_list.list of a SAP if&n; *&t;the connection was in this list.&n; */
DECL|function|llc_sap_unassign_sock
r_void
id|llc_sap_unassign_sock
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
id|sk_del_node_init
c_func
(paren
id|sk
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
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
multiline_comment|/**&n; *&t;llc_sap_alloc - allocates and initializes sap.&n; *&n; *&t;Allocates and initializes sap.&n; */
DECL|function|llc_sap_alloc
r_struct
id|llc_sap
op_star
id|llc_sap_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|llc_sap
op_star
id|sap
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|sap
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sap
)paren
(brace
id|memset
c_func
(paren
id|sap
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sap
)paren
)paren
suffix:semicolon
id|sap-&gt;state
op_assign
id|LLC_SAP_STATE_ACTIVE
suffix:semicolon
id|memcpy
c_func
(paren
id|sap-&gt;laddr.mac
comma
id|llc_main_station.mac_sa
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|rwlock_init
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
)brace
r_return
id|sap
suffix:semicolon
)brace
multiline_comment|/*&n; * FIXME: this will go away as soon as sap-&gt;release_connections is introduced&n; * in the next changesets.&n; */
r_extern
r_int
id|llc_release_connections
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;llc_free_sap - frees a sap&n; *&t;@sap: Address of the sap&n; *&n; * &t;Frees all associated connections (if any), removes this sap from&n; * &t;the list of saps in te station and them frees the memory for this sap.&n; */
DECL|function|llc_free_sap
r_void
id|llc_free_sap
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
)paren
(brace
id|llc_release_connections
c_func
(paren
id|sap
)paren
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|sap-&gt;station-&gt;sap_list.lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|sap-&gt;node
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|sap-&gt;station-&gt;sap_list.lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sap
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_open - open interface to the upper layers.&n; *&t;@lsap: SAP number.&n; *&t;@func: rcv func for datalink protos&n; *&n; *&t;Interface function to upper layer. Each one who wants to get a SAP&n; *&t;(for example NetBEUI) should call this function. Returns the opened&n; *&t;SAP for success, NULL for failure.&n; */
DECL|function|llc_sap_open
r_struct
id|llc_sap
op_star
id|llc_sap_open
c_func
(paren
id|u8
id|lsap
comma
r_int
(paren
op_star
id|func
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|packet_type
op_star
id|pt
)paren
)paren
(brace
multiline_comment|/* verify this SAP is not already open; if so, return error */
r_struct
id|llc_sap
op_star
id|sap
suffix:semicolon
id|sap
op_assign
id|llc_sap_find
c_func
(paren
id|lsap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sap
)paren
(brace
multiline_comment|/* SAP already exists */
id|sap
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* sap requested does not yet exist */
id|sap
op_assign
id|llc_sap_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sap
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* allocated a SAP; initialize it and clear out its memory pool */
id|sap-&gt;laddr.lsap
op_assign
id|lsap
suffix:semicolon
id|sap-&gt;rcv_func
op_assign
id|func
suffix:semicolon
id|sap-&gt;station
op_assign
op_amp
id|llc_main_station
suffix:semicolon
multiline_comment|/* initialized SAP; add it to list of SAPs this station manages */
id|llc_sap_save
c_func
(paren
id|sap
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|sap
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_close - close interface for upper layers.&n; *&t;@sap: SAP to be closed.&n; *&n; *&t;Close interface function to upper layer. Each one who wants to&n; *&t;close an open SAP (for example NetBEUI) should call this function.&n; */
DECL|function|llc_sap_close
r_void
id|llc_sap_close
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
)paren
(brace
id|llc_free_sap
c_func
(paren
id|sap
)paren
suffix:semicolon
)brace
DECL|variable|llc_sap_open
id|EXPORT_SYMBOL
c_func
(paren
id|llc_sap_open
)paren
suffix:semicolon
DECL|variable|llc_sap_close
id|EXPORT_SYMBOL
c_func
(paren
id|llc_sap_close
)paren
suffix:semicolon
eof
