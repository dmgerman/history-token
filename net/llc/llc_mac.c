multiline_comment|/*&n; * llc_mac.c - Manages interface between LLC and MAC&n; *&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; * &t;&t; 2001-2003 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/llc_mac.h&gt;
macro_line|#include &lt;net/llc_pdu.h&gt;
macro_line|#include &lt;net/llc_sap.h&gt;
macro_line|#include &lt;net/llc_main.h&gt;
macro_line|#if 0
mdefine_line|#define dprintk(args...) printk(KERN_DEBUG args)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(args...)
macro_line|#endif
multiline_comment|/*&n; * Packet handler for the station, registerable because in the minimal&n; * LLC core that is taking shape only the very minimal subset of LLC that&n; * is needed for things like IPX, Appletalk, etc will stay, with all the&n; * rest in the llc1 and llc2 modules.&n; */
DECL|variable|llc_station_handler
r_static
r_void
(paren
op_star
id|llc_station_handler
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/*&n; * Packet handlers for LLC_DEST_SAP and LLC_DEST_CONN.&n; */
DECL|variable|llc_type_handlers
r_static
r_void
(paren
op_star
id|llc_type_handlers
(braket
l_int|2
)braket
)paren
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
DECL|function|llc_add_pack
r_void
id|llc_add_pack
c_func
(paren
r_int
id|type
comma
r_void
(paren
op_star
id|handler
)paren
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
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|LLC_DEST_SAP
op_logical_or
id|type
op_eq
id|LLC_DEST_CONN
)paren
id|llc_type_handlers
(braket
id|type
)braket
op_assign
id|handler
suffix:semicolon
)brace
DECL|function|llc_remove_pack
r_void
id|llc_remove_pack
c_func
(paren
r_int
id|type
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|LLC_DEST_SAP
op_logical_or
id|type
op_eq
id|LLC_DEST_CONN
)paren
id|llc_type_handlers
(braket
id|type
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|llc_set_station_handler
r_void
id|llc_set_station_handler
c_func
(paren
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
)paren
(brace
id|llc_station_handler
op_assign
id|handler
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_pdu_type - returns which LLC component must handle for PDU&n; *&t;@skb: input skb&n; *&n; *&t;This function returns which LLC component must handle this PDU.&n; */
DECL|function|llc_pdu_type
r_static
id|__inline__
r_int
id|llc_pdu_type
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|type
op_assign
id|LLC_DEST_CONN
suffix:semicolon
multiline_comment|/* I-PDU or S-PDU type */
r_struct
id|llc_pdu_sn
op_star
id|pdu
op_assign
id|llc_pdu_sn_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pdu-&gt;ctrl_1
op_amp
id|LLC_PDU_TYPE_MASK
)paren
op_ne
id|LLC_PDU_TYPE_U
)paren
r_goto
id|out
suffix:semicolon
r_switch
c_cond
(paren
id|LLC_U_PDU_CMD
c_func
(paren
id|pdu
)paren
)paren
(brace
r_case
id|LLC_1_PDU_CMD_XID
suffix:colon
r_case
id|LLC_1_PDU_CMD_UI
suffix:colon
r_case
id|LLC_1_PDU_CMD_TEST
suffix:colon
id|type
op_assign
id|LLC_DEST_SAP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LLC_2_PDU_CMD_SABME
suffix:colon
r_case
id|LLC_2_PDU_CMD_DISC
suffix:colon
r_case
id|LLC_2_PDU_RSP_UA
suffix:colon
r_case
id|LLC_2_PDU_RSP_DM
suffix:colon
r_case
id|LLC_2_PDU_RSP_FRMR
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|type
op_assign
id|LLC_DEST_INVALID
suffix:semicolon
r_break
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|type
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_fixup_skb - initializes skb pointers&n; *&t;@skb: This argument points to incoming skb&n; *&n; *&t;Initializes internal skb pointer to start of network layer by deriving&n; *&t;length of LLC header; finds length of LLC control field in LLC header&n; *&t;by looking at the two lowest-order bits of the first control field&n; *&t;byte; field is either 3 or 4 bytes long.&n; */
DECL|function|llc_fixup_skb
r_static
r_inline
r_int
id|llc_fixup_skb
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|u8
id|llc_len
op_assign
l_int|2
suffix:semicolon
r_struct
id|llc_pdu_sn
op_star
id|pdu
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
op_star
id|pdu
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|pdu
op_assign
(paren
r_struct
id|llc_pdu_sn
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pdu-&gt;ctrl_1
op_amp
id|LLC_PDU_TYPE_MASK
)paren
op_eq
id|LLC_PDU_TYPE_U
)paren
id|llc_len
op_assign
l_int|1
suffix:semicolon
id|llc_len
op_add_assign
l_int|2
suffix:semicolon
id|skb-&gt;h.raw
op_add_assign
id|llc_len
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|llc_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;protocol
op_eq
id|htons
c_func
(paren
id|ETH_P_802_2
)paren
)paren
(brace
id|u16
id|pdulen
op_assign
(paren
(paren
r_struct
id|ethhdr
op_star
)paren
id|skb-&gt;mac.raw
)paren
op_member_access_from_pointer
id|h_proto
comma
id|data_size
op_assign
id|ntohs
c_func
(paren
id|pdulen
)paren
op_minus
id|llc_len
suffix:semicolon
id|skb_trim
c_func
(paren
id|skb
comma
id|data_size
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_rcv - 802.2 entry point from net lower layers&n; *&t;@skb: received pdu&n; *&t;@dev: device that receive pdu&n; *&t;@pt: packet type&n; *&n; *&t;When the system receives a 802.2 frame this function is called. It&n; *&t;checks SAP and connection of received pdu and passes frame to&n; *&t;llc_{station,sap,conn}_rcv for sending to proper state machine. If&n; *&t;the frame is related to a busy connection (a connection is sending&n; *&t;data now), it queues this frame in the connection&squot;s backlog.&n; */
DECL|function|llc_rcv
r_int
id|llc_rcv
c_func
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
(brace
r_struct
id|llc_sap
op_star
id|sap
suffix:semicolon
r_struct
id|llc_pdu_sn
op_star
id|pdu
suffix:semicolon
r_int
id|dest
suffix:semicolon
multiline_comment|/*&n;&t; * When the interface is in promisc. mode, drop all the crap that it&n;&t; * receives, do not try to analyse it.&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|skb-&gt;pkt_type
op_eq
id|PACKET_OTHERHOST
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;%s: PACKET_OTHERHOST&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|drop
suffix:semicolon
)brace
id|skb
op_assign
id|skb_share_check
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|skb
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|llc_fixup_skb
c_func
(paren
id|skb
)paren
)paren
)paren
r_goto
id|drop
suffix:semicolon
id|pdu
op_assign
id|llc_pdu_sn_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|pdu-&gt;dsap
)paren
)paren
multiline_comment|/* NULL DSAP, refer to station */
r_goto
id|handle_station
suffix:semicolon
id|sap
op_assign
id|llc_sap_find
c_func
(paren
id|pdu-&gt;dsap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|sap
)paren
)paren
(brace
multiline_comment|/* unknown SAP */
id|dprintk
c_func
(paren
l_string|&quot;%s: llc_sap_find(%02X) failed!&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|pdu-&gt;dsap
)paren
suffix:semicolon
r_goto
id|drop
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * First the upper layer protocols that don&squot;t need the full&n;&t; * LLC functionality&n;&t; */
r_if
c_cond
(paren
id|sap-&gt;rcv_func
)paren
(brace
id|sap
op_member_access_from_pointer
id|rcv_func
c_func
(paren
id|skb
comma
id|dev
comma
id|pt
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|dest
op_assign
id|llc_pdu_type
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|dest
op_logical_or
op_logical_neg
id|llc_type_handlers
(braket
id|dest
op_minus
l_int|1
)braket
)paren
)paren
r_goto
id|drop
suffix:semicolon
id|llc_type_handlers
(braket
id|dest
op_minus
l_int|1
)braket
(paren
id|sap
comma
id|skb
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
id|drop
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|handle_station
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|llc_station_handler
)paren
r_goto
id|drop
suffix:semicolon
id|llc_station_handler
c_func
(paren
id|skb
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|variable|llc_add_pack
id|EXPORT_SYMBOL
c_func
(paren
id|llc_add_pack
)paren
suffix:semicolon
DECL|variable|llc_remove_pack
id|EXPORT_SYMBOL
c_func
(paren
id|llc_remove_pack
)paren
suffix:semicolon
DECL|variable|llc_set_station_handler
id|EXPORT_SYMBOL
c_func
(paren
id|llc_set_station_handler
)paren
suffix:semicolon
eof
