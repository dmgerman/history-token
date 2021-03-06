macro_line|#ifndef LLC_IF_H
DECL|macro|LLC_IF_H
mdefine_line|#define LLC_IF_H
multiline_comment|/*&n; * Copyright (c) 1997 by Procom Technology,Inc.&n; * &t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
multiline_comment|/* Defines LLC interface to network layer */
multiline_comment|/* Available primitives */
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/llc.h&gt;
macro_line|#include &lt;net/llc.h&gt;
DECL|macro|LLC_DATAUNIT_PRIM
mdefine_line|#define LLC_DATAUNIT_PRIM&t;1
DECL|macro|LLC_CONN_PRIM
mdefine_line|#define LLC_CONN_PRIM&t;&t;2
DECL|macro|LLC_DATA_PRIM
mdefine_line|#define LLC_DATA_PRIM&t;&t;3
DECL|macro|LLC_DISC_PRIM
mdefine_line|#define LLC_DISC_PRIM&t;&t;4
DECL|macro|LLC_RESET_PRIM
mdefine_line|#define LLC_RESET_PRIM&t;&t;5
DECL|macro|LLC_FLOWCONTROL_PRIM
mdefine_line|#define LLC_FLOWCONTROL_PRIM&t;6 /* Not supported at this time */
DECL|macro|LLC_DISABLE_PRIM
mdefine_line|#define LLC_DISABLE_PRIM&t;7
DECL|macro|LLC_XID_PRIM
mdefine_line|#define LLC_XID_PRIM&t;&t;8
DECL|macro|LLC_TEST_PRIM
mdefine_line|#define LLC_TEST_PRIM&t;&t;9
DECL|macro|LLC_SAP_ACTIVATION
mdefine_line|#define LLC_SAP_ACTIVATION     10
DECL|macro|LLC_SAP_DEACTIVATION
mdefine_line|#define LLC_SAP_DEACTIVATION   11
DECL|macro|LLC_NBR_PRIMITIVES
mdefine_line|#define LLC_NBR_PRIMITIVES     11
DECL|macro|LLC_IND
mdefine_line|#define LLC_IND&t;&t;&t;1
DECL|macro|LLC_CONFIRM
mdefine_line|#define LLC_CONFIRM&t;&t;2
multiline_comment|/* Primitive type */
DECL|macro|LLC_PRIM_TYPE_REQ
mdefine_line|#define LLC_PRIM_TYPE_REQ&t;1
DECL|macro|LLC_PRIM_TYPE_IND
mdefine_line|#define LLC_PRIM_TYPE_IND&t;2
DECL|macro|LLC_PRIM_TYPE_RESP
mdefine_line|#define LLC_PRIM_TYPE_RESP&t;3
DECL|macro|LLC_PRIM_TYPE_CONFIRM
mdefine_line|#define LLC_PRIM_TYPE_CONFIRM&t;4
multiline_comment|/* Reset reasons, remote entity or local LLC */
DECL|macro|LLC_RESET_REASON_REMOTE
mdefine_line|#define LLC_RESET_REASON_REMOTE&t;1
DECL|macro|LLC_RESET_REASON_LOCAL
mdefine_line|#define LLC_RESET_REASON_LOCAL&t;2
multiline_comment|/* Disconnect reasons */
DECL|macro|LLC_DISC_REASON_RX_DM_RSP_PDU
mdefine_line|#define LLC_DISC_REASON_RX_DM_RSP_PDU&t;0
DECL|macro|LLC_DISC_REASON_RX_DISC_CMD_PDU
mdefine_line|#define LLC_DISC_REASON_RX_DISC_CMD_PDU&t;1
DECL|macro|LLC_DISC_REASON_ACK_TMR_EXP
mdefine_line|#define LLC_DISC_REASON_ACK_TMR_EXP&t;2
multiline_comment|/* Confirm reasons */
DECL|macro|LLC_STATUS_CONN
mdefine_line|#define LLC_STATUS_CONN&t;&t;0 /* connect confirm &amp; reset confirm */
DECL|macro|LLC_STATUS_DISC
mdefine_line|#define LLC_STATUS_DISC&t;&t;1 /* connect confirm &amp; reset confirm */
DECL|macro|LLC_STATUS_FAILED
mdefine_line|#define LLC_STATUS_FAILED&t;2 /* connect confirm &amp; reset confirm */
DECL|macro|LLC_STATUS_IMPOSSIBLE
mdefine_line|#define LLC_STATUS_IMPOSSIBLE&t;3 /* connect confirm */
DECL|macro|LLC_STATUS_RECEIVED
mdefine_line|#define LLC_STATUS_RECEIVED&t;4 /* data conn */
DECL|macro|LLC_STATUS_REMOTE_BUSY
mdefine_line|#define LLC_STATUS_REMOTE_BUSY&t;5 /* data conn */
DECL|macro|LLC_STATUS_REFUSE
mdefine_line|#define LLC_STATUS_REFUSE&t;6 /* data conn */
DECL|macro|LLC_STATUS_CONFLICT
mdefine_line|#define LLC_STATUS_CONFLICT&t;7 /* disconnect conn */
DECL|macro|LLC_STATUS_RESET_DONE
mdefine_line|#define LLC_STATUS_RESET_DONE&t;8 /*  */
r_extern
id|u8
id|llc_mac_null_var
(braket
id|IFHWADDRLEN
)braket
suffix:semicolon
multiline_comment|/**&n; *      llc_mac_null - determines if a address is a null mac address&n; *      @mac: Mac address to test if null.&n; *&n; *      Determines if a given address is a null mac address.  Returns 0 if the&n; *      address is not a null mac, 1 if the address is a null mac.&n; */
DECL|function|llc_mac_null
r_static
id|__inline__
r_int
id|llc_mac_null
c_func
(paren
id|u8
op_star
id|mac
)paren
(brace
r_return
op_logical_neg
id|memcmp
c_func
(paren
id|mac
comma
id|llc_mac_null_var
comma
id|IFHWADDRLEN
)paren
suffix:semicolon
)brace
DECL|function|llc_addrany
r_static
id|__inline__
r_int
id|llc_addrany
c_func
(paren
r_struct
id|llc_addr
op_star
id|addr
)paren
(brace
r_return
id|llc_mac_null
c_func
(paren
id|addr-&gt;mac
)paren
op_logical_and
op_logical_neg
id|addr-&gt;lsap
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_mac_match - determines if two mac addresses are the same&n; *&t;@mac1: First mac address to compare.&n; *&t;@mac2: Second mac address to compare.&n; *&n; *&t;Determines if two given mac address are the same.  Returns 0 if there&n; *&t;is not a complete match up to len, 1 if a complete match up to len is&n; *&t;found.&n; */
DECL|function|llc_mac_match
r_static
id|__inline__
r_int
id|llc_mac_match
c_func
(paren
id|u8
op_star
id|mac1
comma
id|u8
op_star
id|mac2
)paren
(brace
r_return
op_logical_neg
id|memcmp
c_func
(paren
id|mac1
comma
id|mac2
comma
id|IFHWADDRLEN
)paren
suffix:semicolon
)brace
r_extern
r_int
id|llc_establish_connection
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
id|u8
op_star
id|lmac
comma
id|u8
op_star
id|dmac
comma
id|u8
id|dsap
)paren
suffix:semicolon
r_extern
r_int
id|llc_build_and_send_pkt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|llc_send_disc
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
macro_line|#endif /* LLC_IF_H */
eof
