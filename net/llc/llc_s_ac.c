multiline_comment|/*&n; * llc_s_ac.c - actions performed during sap state transition.&n; *&n; * Description :&n; *   Functions in this module are implementation of sap component actions.&n; *   Details of actions can be found in IEEE-802.2 standard document.&n; *   All functions have one sap and one event as input argument. All of&n; *   them return 0 On success and 1 otherwise.&n; *&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; *&t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/llc_if.h&gt;
macro_line|#include &lt;net/llc_sap.h&gt;
macro_line|#include &lt;net/llc_main.h&gt;
macro_line|#include &lt;net/llc_s_ev.h&gt;
macro_line|#include &lt;net/llc_pdu.h&gt;
macro_line|#include &lt;net/llc_mac.h&gt;
multiline_comment|/**&n; *&t;llc_sap_action_unit_data_ind - forward UI PDU to network layer&n; *&t;@sap: SAP&n; *&t;@ev: the event to forward&n; *&n; *&t;Received a UI PDU from MAC layer; forward to network layer as a&n; *&t;UNITDATA INDICATION; verify our event is the kind we expect&n; */
DECL|function|llc_sap_action_unitdata_ind
r_int
id|llc_sap_action_unitdata_ind
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|llc_sap_state_ev
op_star
id|ev
)paren
(brace
id|llc_sap_rtn_pdu
c_func
(paren
id|sap
comma
id|ev-&gt;data.pdu.skb
comma
id|ev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_action_send_ui - sends UI PDU resp to UNITDATA REQ to MAC layer&n; *&t;@sap: SAP&n; *&t;@ev: the event to send&n; *&n; *&t;Sends a UI PDU to the MAC layer in response to a UNITDATA REQUEST&n; *&t;primitive from the network layer. Verifies event is a primitive type of&n; *&t;event. Verify the primitive is a UNITDATA REQUEST.&n; */
DECL|function|llc_sap_action_send_ui
r_int
id|llc_sap_action_send_ui
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|llc_sap_state_ev
op_star
id|ev
)paren
(brace
r_struct
id|llc_prim_if_block
op_star
id|prim
op_assign
id|ev-&gt;data.prim.data
suffix:semicolon
r_struct
id|llc_prim_unit_data
op_star
id|prim_data
op_assign
op_amp
id|prim-&gt;data-&gt;udata
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|prim-&gt;data-&gt;udata.skb
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|llc_pdu_header_init
c_func
(paren
id|skb
comma
id|LLC_PDU_TYPE_U
comma
id|prim_data-&gt;saddr.lsap
comma
id|prim_data-&gt;daddr.lsap
comma
id|LLC_PDU_CMD
)paren
suffix:semicolon
id|rc
op_assign
id|llc_pdu_init_as_ui_cmd
c_func
(paren
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
id|rc
op_assign
id|lan_hdrs_init
c_func
(paren
id|skb
comma
id|prim_data-&gt;saddr.mac
comma
id|prim_data-&gt;daddr.mac
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|llc_sap_send_pdu
c_func
(paren
id|sap
comma
id|skb
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_action_send_xid_c - send XID PDU as response to XID REQ&n; *&t;@sap: SAP&n; *&t;@ev: the event to send&n; *&n; *&t;Send a XID command PDU to MAC layer in response to a XID REQUEST&n; *&t;primitive from the network layer. Verify event is a primitive type&n; *&t;event. Verify the primitive is a XID REQUEST.&n; */
DECL|function|llc_sap_action_send_xid_c
r_int
id|llc_sap_action_send_xid_c
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|llc_sap_state_ev
op_star
id|ev
)paren
(brace
r_struct
id|llc_prim_if_block
op_star
id|prim
op_assign
id|ev-&gt;data.prim.data
suffix:semicolon
r_struct
id|llc_prim_xid
op_star
id|prim_data
op_assign
op_amp
id|prim-&gt;data-&gt;xid
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|prim_data-&gt;skb
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|llc_pdu_header_init
c_func
(paren
id|skb
comma
id|LLC_PDU_TYPE_U
comma
id|prim_data-&gt;saddr.lsap
comma
id|prim_data-&gt;daddr.lsap
comma
id|LLC_PDU_CMD
)paren
suffix:semicolon
id|rc
op_assign
id|llc_pdu_init_as_xid_cmd
c_func
(paren
id|skb
comma
id|LLC_XID_NULL_CLASS_2
comma
l_int|0
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
id|rc
op_assign
id|lan_hdrs_init
c_func
(paren
id|skb
comma
id|prim_data-&gt;saddr.mac
comma
id|prim_data-&gt;daddr.mac
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|llc_sap_send_pdu
c_func
(paren
id|sap
comma
id|skb
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_action_send_xid_r - send XID PDU resp to MAC for received XID&n; *&t;@sap: SAP&n; *&t;@ev: the event to send&n; *&n; *&t;Send XID response PDU to MAC in response to an earlier received XID&n; *&t;command PDU. Verify event is a PDU type event&n; */
DECL|function|llc_sap_action_send_xid_r
r_int
id|llc_sap_action_send_xid_r
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|llc_sap_state_ev
op_star
id|ev
)paren
(brace
id|u8
id|mac_da
(braket
id|ETH_ALEN
)braket
comma
id|mac_sa
(braket
id|ETH_ALEN
)braket
comma
id|dsap
suffix:semicolon
r_int
id|rc
op_assign
l_int|1
suffix:semicolon
r_struct
id|sk_buff
op_star
id|ev_skb
op_assign
id|ev-&gt;data.pdu.skb
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|llc_pdu_decode_sa
c_func
(paren
id|ev_skb
comma
id|mac_da
)paren
suffix:semicolon
id|llc_pdu_decode_da
c_func
(paren
id|ev_skb
comma
id|mac_sa
)paren
suffix:semicolon
id|llc_pdu_decode_ssap
c_func
(paren
id|ev_skb
comma
op_amp
id|dsap
)paren
suffix:semicolon
id|skb
op_assign
id|llc_alloc_frame
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_goto
id|out
suffix:semicolon
id|skb-&gt;dev
op_assign
id|ev_skb-&gt;dev
suffix:semicolon
id|llc_pdu_header_init
c_func
(paren
id|skb
comma
id|LLC_PDU_TYPE_U
comma
id|sap-&gt;laddr.lsap
comma
id|dsap
comma
id|LLC_PDU_RSP
)paren
suffix:semicolon
id|rc
op_assign
id|llc_pdu_init_as_xid_rsp
c_func
(paren
id|skb
comma
id|LLC_XID_NULL_CLASS_2
comma
l_int|0
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
id|rc
op_assign
id|lan_hdrs_init
c_func
(paren
id|skb
comma
id|mac_sa
comma
id|mac_da
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|llc_sap_send_pdu
c_func
(paren
id|sap
comma
id|skb
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_action_send_test_c - send TEST PDU to MAC in resp to TEST REQ&n; *&t;@sap: SAP&n; *&t;@ev: the event to send&n; *&n; *&t;Send a TEST command PDU to the MAC layer in response to a TEST REQUEST&n; *&t;primitive from the network layer. Verify event is a primitive type&n; *&t;event; verify the primitive is a TEST REQUEST.&n; */
DECL|function|llc_sap_action_send_test_c
r_int
id|llc_sap_action_send_test_c
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|llc_sap_state_ev
op_star
id|ev
)paren
(brace
r_struct
id|llc_prim_if_block
op_star
id|prim
op_assign
id|ev-&gt;data.prim.data
suffix:semicolon
r_struct
id|llc_prim_test
op_star
id|prim_data
op_assign
op_amp
id|prim-&gt;data-&gt;test
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|prim_data-&gt;skb
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|llc_pdu_header_init
c_func
(paren
id|skb
comma
id|LLC_PDU_TYPE_U
comma
id|prim_data-&gt;saddr.lsap
comma
id|prim_data-&gt;daddr.lsap
comma
id|LLC_PDU_CMD
)paren
suffix:semicolon
id|rc
op_assign
id|llc_pdu_init_as_test_cmd
c_func
(paren
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
id|rc
op_assign
id|lan_hdrs_init
c_func
(paren
id|skb
comma
id|prim_data-&gt;saddr.mac
comma
id|prim_data-&gt;daddr.mac
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|llc_sap_send_pdu
c_func
(paren
id|sap
comma
id|skb
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|llc_sap_action_send_test_r
r_int
id|llc_sap_action_send_test_r
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|llc_sap_state_ev
op_star
id|ev
)paren
(brace
id|u8
id|mac_da
(braket
id|ETH_ALEN
)braket
comma
id|mac_sa
(braket
id|ETH_ALEN
)braket
comma
id|dsap
suffix:semicolon
r_int
id|rc
op_assign
l_int|1
suffix:semicolon
r_struct
id|sk_buff
op_star
id|ev_skb
op_assign
id|ev-&gt;data.pdu.skb
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|llc_pdu_decode_sa
c_func
(paren
id|ev_skb
comma
id|mac_da
)paren
suffix:semicolon
id|llc_pdu_decode_da
c_func
(paren
id|ev_skb
comma
id|mac_sa
)paren
suffix:semicolon
id|llc_pdu_decode_ssap
c_func
(paren
id|ev_skb
comma
op_amp
id|dsap
)paren
suffix:semicolon
id|skb
op_assign
id|llc_alloc_frame
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_goto
id|out
suffix:semicolon
id|skb-&gt;dev
op_assign
id|ev_skb-&gt;dev
suffix:semicolon
id|llc_pdu_header_init
c_func
(paren
id|skb
comma
id|LLC_PDU_TYPE_U
comma
id|sap-&gt;laddr.lsap
comma
id|dsap
comma
id|LLC_PDU_RSP
)paren
suffix:semicolon
id|rc
op_assign
id|llc_pdu_init_as_test_rsp
c_func
(paren
id|skb
comma
id|ev_skb
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
id|rc
op_assign
id|lan_hdrs_init
c_func
(paren
id|skb
comma
id|mac_sa
comma
id|mac_da
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|llc_sap_send_pdu
c_func
(paren
id|sap
comma
id|skb
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_action_report_status - report data link status to layer mgmt&n; *&t;@sap: SAP&n; *&t;@ev: the event to send&n; *&n; *&t;Report data link status to layer management. Verify our event is the&n; *&t;kind we expect.&n; */
DECL|function|llc_sap_action_report_status
r_int
id|llc_sap_action_report_status
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|llc_sap_state_ev
op_star
id|ev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_action_xid_ind - send XID PDU resp to net layer via XID IND&n; *&t;@sap: SAP&n; *&t;@ev: the event to send&n; *&n; *&t;Send a XID response PDU to the network layer via a XID INDICATION&n; *&t;primitive.&n; */
DECL|function|llc_sap_action_xid_ind
r_int
id|llc_sap_action_xid_ind
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|llc_sap_state_ev
op_star
id|ev
)paren
(brace
id|llc_sap_rtn_pdu
c_func
(paren
id|sap
comma
id|ev-&gt;data.pdu.skb
comma
id|ev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_action_test_ind - send TEST PDU to net layer via TEST IND&n; *&t;@sap: SAP&n; *&t;@ev: the event to send&n; *&n; *&t;Send a TEST response PDU to the network layer via a TEST INDICATION&n; *&t;primitive. Verify our event is a PDU type event.&n; */
DECL|function|llc_sap_action_test_ind
r_int
id|llc_sap_action_test_ind
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|llc_sap_state_ev
op_star
id|ev
)paren
(brace
id|llc_sap_rtn_pdu
c_func
(paren
id|sap
comma
id|ev-&gt;data.pdu.skb
comma
id|ev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof