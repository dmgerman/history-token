multiline_comment|/*&n; * llc_s_ev.c - Defines SAP component events&n; *&n; * The followed event functions are SAP component events which are described&n; * in 802.2 LLC protocol standard document.&n; *&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; *&t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/llc_if.h&gt;
macro_line|#include &lt;net/llc_s_ev.h&gt;
macro_line|#include &lt;net/llc_pdu.h&gt;
DECL|function|llc_sap_ev_activation_req
r_int
id|llc_sap_ev_activation_req
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
r_return
id|ev-&gt;type
op_eq
id|LLC_SAP_EV_TYPE_SIMPLE
op_logical_and
id|ev-&gt;data.a.ev
op_eq
id|LLC_SAP_EV_ACTIVATION_REQ
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|llc_sap_ev_rx_ui
r_int
id|llc_sap_ev_rx_ui
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
r_return
id|ev-&gt;type
op_eq
id|LLC_SAP_EV_TYPE_PDU
op_logical_and
op_logical_neg
id|LLC_PDU_IS_CMD
c_func
(paren
id|pdu
)paren
op_logical_and
op_logical_neg
id|LLC_PDU_TYPE_IS_U
c_func
(paren
id|pdu
)paren
op_logical_and
id|LLC_U_PDU_CMD
c_func
(paren
id|pdu
)paren
op_eq
id|LLC_1_PDU_CMD_UI
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|llc_sap_ev_unitdata_req
r_int
id|llc_sap_ev_unitdata_req
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
r_return
id|ev-&gt;type
op_eq
id|LLC_SAP_EV_TYPE_PRIM
op_logical_and
id|ev-&gt;data.prim.prim
op_eq
id|LLC_DATAUNIT_PRIM
op_logical_and
id|ev-&gt;data.prim.type
op_eq
id|LLC_PRIM_TYPE_REQ
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|llc_sap_ev_xid_req
r_int
id|llc_sap_ev_xid_req
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
r_return
id|ev-&gt;type
op_eq
id|LLC_SAP_EV_TYPE_PRIM
op_logical_and
id|ev-&gt;data.prim.prim
op_eq
id|LLC_XID_PRIM
op_logical_and
id|ev-&gt;data.prim.type
op_eq
id|LLC_PRIM_TYPE_REQ
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|llc_sap_ev_rx_xid_c
r_int
id|llc_sap_ev_rx_xid_c
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
r_return
id|ev-&gt;type
op_eq
id|LLC_SAP_EV_TYPE_PDU
op_logical_and
op_logical_neg
id|LLC_PDU_IS_CMD
c_func
(paren
id|pdu
)paren
op_logical_and
op_logical_neg
id|LLC_PDU_TYPE_IS_U
c_func
(paren
id|pdu
)paren
op_logical_and
id|LLC_U_PDU_CMD
c_func
(paren
id|pdu
)paren
op_eq
id|LLC_1_PDU_CMD_XID
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|llc_sap_ev_rx_xid_r
r_int
id|llc_sap_ev_rx_xid_r
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
r_return
id|ev-&gt;type
op_eq
id|LLC_SAP_EV_TYPE_PDU
op_logical_and
op_logical_neg
id|LLC_PDU_IS_RSP
c_func
(paren
id|pdu
)paren
op_logical_and
op_logical_neg
id|LLC_PDU_TYPE_IS_U
c_func
(paren
id|pdu
)paren
op_logical_and
id|LLC_U_PDU_RSP
c_func
(paren
id|pdu
)paren
op_eq
id|LLC_1_PDU_CMD_XID
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|llc_sap_ev_test_req
r_int
id|llc_sap_ev_test_req
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
r_return
id|ev-&gt;type
op_eq
id|LLC_SAP_EV_TYPE_PRIM
op_logical_and
id|ev-&gt;data.prim.prim
op_eq
id|LLC_TEST_PRIM
op_logical_and
id|ev-&gt;data.prim.type
op_eq
id|LLC_PRIM_TYPE_REQ
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|llc_sap_ev_rx_test_c
r_int
id|llc_sap_ev_rx_test_c
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
r_return
id|ev-&gt;type
op_eq
id|LLC_SAP_EV_TYPE_PDU
op_logical_and
op_logical_neg
id|LLC_PDU_IS_CMD
c_func
(paren
id|pdu
)paren
op_logical_and
op_logical_neg
id|LLC_PDU_TYPE_IS_U
c_func
(paren
id|pdu
)paren
op_logical_and
id|LLC_U_PDU_CMD
c_func
(paren
id|pdu
)paren
op_eq
id|LLC_1_PDU_CMD_TEST
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|llc_sap_ev_rx_test_r
r_int
id|llc_sap_ev_rx_test_r
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
r_return
id|ev-&gt;type
op_eq
id|LLC_SAP_EV_TYPE_PDU
op_logical_and
op_logical_neg
id|LLC_PDU_IS_RSP
c_func
(paren
id|pdu
)paren
op_logical_and
op_logical_neg
id|LLC_PDU_TYPE_IS_U
c_func
(paren
id|pdu
)paren
op_logical_and
id|LLC_U_PDU_RSP
c_func
(paren
id|pdu
)paren
op_eq
id|LLC_1_PDU_CMD_TEST
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|llc_sap_ev_deactivation_req
r_int
id|llc_sap_ev_deactivation_req
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
r_return
id|ev-&gt;type
op_eq
id|LLC_SAP_EV_TYPE_SIMPLE
op_logical_and
id|ev-&gt;data.a.ev
op_eq
id|LLC_SAP_EV_DEACTIVATION_REQ
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
eof
