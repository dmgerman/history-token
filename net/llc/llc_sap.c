multiline_comment|/*&n; * llc_sap.c - driver routines for SAP component.&n; *&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; * &t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/llc_conn.h&gt;
macro_line|#include &lt;net/llc_sap.h&gt;
macro_line|#include &lt;net/llc_s_ev.h&gt;
macro_line|#include &lt;net/llc_s_ac.h&gt;
macro_line|#include &lt;net/llc_s_st.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/llc_main.h&gt;
macro_line|#include &lt;net/llc_mac.h&gt;
macro_line|#include &lt;net/llc_pdu.h&gt;
macro_line|#include &lt;linux/if_tr.h&gt;
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
suffix:semicolon
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
suffix:semicolon
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
suffix:semicolon
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
id|spin_lock_bh
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
id|list_add_tail
c_func
(paren
op_amp
id|llc_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|node
comma
op_amp
id|sap-&gt;sk_list.list
)paren
suffix:semicolon
id|sock_hold
c_func
(paren
id|sk
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_unassign_sock - removes a connection from SAP&n; *&t;@sap: SAP&n; *&t;@sk: pointer to connection&n; *&n; *&t;This function removes a connection from sk_list.list of a SAP.&n; */
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
id|spin_lock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|llc_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|node
)paren
suffix:semicolon
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_state_process - sends event to SAP state machine&n; *&t;@sap: pointer to SAP&n; *&t;@skb: pointer to occurred event&n; *&n; *&t;After executing actions of the event, upper layer will be indicated&n; *&t;if needed(on receiving an UI frame).&n; */
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
id|sap
op_member_access_from_pointer
id|ind
c_func
(paren
id|ev-&gt;prim
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ev-&gt;type
op_eq
id|LLC_SAP_EV_TYPE_PDU
)paren
id|kfree_skb
c_func
(paren
id|skb
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
id|llc_pdu_un
op_star
id|pdu
suffix:semicolon
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
id|llc_prim_if_block
op_star
id|prim
op_assign
op_amp
id|sap-&gt;llc_ind_prim
suffix:semicolon
r_union
id|llc_u_prim_data
op_star
id|prim_data
op_assign
id|prim-&gt;data
suffix:semicolon
id|u8
id|lfb
suffix:semicolon
id|llc_pdu_decode_sa
c_func
(paren
id|skb
comma
id|prim_data-&gt;udata.saddr.mac
)paren
suffix:semicolon
id|llc_pdu_decode_da
c_func
(paren
id|skb
comma
id|prim_data-&gt;udata.daddr.mac
)paren
suffix:semicolon
id|llc_pdu_decode_dsap
c_func
(paren
id|skb
comma
op_amp
id|prim_data-&gt;udata.daddr.lsap
)paren
suffix:semicolon
id|llc_pdu_decode_ssap
c_func
(paren
id|skb
comma
op_amp
id|prim_data-&gt;udata.saddr.lsap
)paren
suffix:semicolon
id|prim_data-&gt;udata.pri
op_assign
l_int|0
suffix:semicolon
id|prim_data-&gt;udata.skb
op_assign
id|skb
suffix:semicolon
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
id|prim-&gt;prim
op_assign
id|LLC_TEST_PRIM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LLC_1_PDU_CMD_XID
suffix:colon
id|prim-&gt;prim
op_assign
id|LLC_XID_PRIM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LLC_1_PDU_CMD_UI
suffix:colon
r_if
c_cond
(paren
id|skb-&gt;protocol
op_eq
id|ntohs
c_func
(paren
id|ETH_P_TR_802_2
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
r_struct
id|trh_hdr
op_star
)paren
id|skb-&gt;mac.raw
)paren
op_member_access_from_pointer
id|rcf
)paren
(brace
id|lfb
op_assign
id|ntohs
c_func
(paren
(paren
(paren
r_struct
id|trh_hdr
op_star
)paren
id|skb-&gt;mac.raw
)paren
op_member_access_from_pointer
id|rcf
)paren
op_amp
l_int|0x0070
suffix:semicolon
id|prim_data-&gt;udata.lfb
op_assign
id|lfb
op_rshift
l_int|4
suffix:semicolon
)brace
r_else
(brace
id|lfb
op_assign
l_int|0xFF
suffix:semicolon
id|prim_data-&gt;udata.lfb
op_assign
l_int|0xFF
suffix:semicolon
)brace
)brace
id|prim-&gt;prim
op_assign
id|LLC_DATAUNIT_PRIM
suffix:semicolon
r_break
suffix:semicolon
)brace
id|prim-&gt;data
op_assign
id|prim_data
suffix:semicolon
id|prim-&gt;sap
op_assign
id|sap
suffix:semicolon
id|ev-&gt;ind_cfm_flag
op_assign
id|LLC_IND
suffix:semicolon
id|ev-&gt;prim
op_assign
id|prim
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_send_pdu - Sends a frame to MAC layer for transmition&n; *&t;@sap: pointer to SAP&n; *&t;@skb: pdu that must be sent&n; */
DECL|function|llc_sap_send_pdu
r_void
id|llc_sap_send_pdu
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
id|mac_send_pdu
c_func
(paren
id|skb
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
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
op_le
id|LLC_NR_SAP_STATES
)paren
(brace
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
id|trans
)paren
(brace
multiline_comment|/* got the state to which we next transition; perform&n;&t;&t;&t; * the actions associated with this transition before&n;&t;&t;&t; * actually transitioning to the next state&n;&t;&t;&t; */
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
op_logical_neg
id|rc
)paren
multiline_comment|/* transition SAP to next state if all actions&n;&t;&t;&t;&t; * execute successfully&n;&t;&t;&t;&t; */
id|sap-&gt;state
op_assign
id|trans-&gt;next_state
suffix:semicolon
)brace
)brace
r_return
id|rc
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
multiline_comment|/* search thru events for this state until list exhausted or until&n;&t; * its obvious the event is not valid for the current state&n;&t; */
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
multiline_comment|/* got event match; return it */
id|rc
op_assign
id|next_trans
(braket
id|i
)braket
suffix:semicolon
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
eof
