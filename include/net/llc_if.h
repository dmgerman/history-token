macro_line|#ifndef LLC_IF_H
DECL|macro|LLC_IF_H
mdefine_line|#define LLC_IF_H
multiline_comment|/*&n; * Copyright (c) 1997 by Procom Technology,Inc.&n; * &t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
multiline_comment|/* Defines LLC interface to network layer */
multiline_comment|/* Available primitives */
macro_line|#include &lt;linux/if.h&gt;
DECL|macro|LLC_DATAUNIT_PRIM
mdefine_line|#define LLC_DATAUNIT_PRIM&t;0
DECL|macro|LLC_CONN_PRIM
mdefine_line|#define LLC_CONN_PRIM&t;&t;1
DECL|macro|LLC_DATA_PRIM
mdefine_line|#define LLC_DATA_PRIM&t;&t;2
DECL|macro|LLC_DISC_PRIM
mdefine_line|#define LLC_DISC_PRIM&t;&t;3
DECL|macro|LLC_RESET_PRIM
mdefine_line|#define LLC_RESET_PRIM&t;&t;4
DECL|macro|LLC_FLOWCONTROL_PRIM
mdefine_line|#define LLC_FLOWCONTROL_PRIM&t;5
DECL|macro|LLC_DISABLE_PRIM
mdefine_line|#define LLC_DISABLE_PRIM&t;6
DECL|macro|LLC_XID_PRIM
mdefine_line|#define LLC_XID_PRIM&t;&t;7
DECL|macro|LLC_TEST_PRIM
mdefine_line|#define LLC_TEST_PRIM&t;&t;8
DECL|macro|LLC_SAP_ACTIVATION
mdefine_line|#define LLC_SAP_ACTIVATION      9
DECL|macro|LLC_SAP_DEACTIVATION
mdefine_line|#define LLC_SAP_DEACTIVATION   10
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
multiline_comment|/* Structures and types */
multiline_comment|/* SAP/MAC Address pair */
DECL|struct|llc_addr
r_struct
id|llc_addr
(brace
DECL|member|lsap
id|u8
id|lsap
suffix:semicolon
DECL|member|mac
id|u8
id|mac
(braket
id|IFHWADDRLEN
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Primitive-specific data */
DECL|struct|llc_prim_conn
r_struct
id|llc_prim_conn
(brace
DECL|member|saddr
r_struct
id|llc_addr
id|saddr
suffix:semicolon
multiline_comment|/* used by request only */
DECL|member|daddr
r_struct
id|llc_addr
id|daddr
suffix:semicolon
multiline_comment|/* used by request only */
DECL|member|status
id|u8
id|status
suffix:semicolon
multiline_comment|/* reason for failure */
DECL|member|pri
id|u8
id|pri
suffix:semicolon
multiline_comment|/* service_class */
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
multiline_comment|/* returned from REQUEST */
DECL|member|handler
r_void
op_star
id|handler
suffix:semicolon
multiline_comment|/* upper layer use,&n;&t;&t;&t;&t;&t;   stored in llc_opt-&gt;handler */
DECL|member|link
id|u16
id|link
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* received SABME  */
)brace
suffix:semicolon
DECL|struct|llc_prim_disc
r_struct
id|llc_prim_disc
(brace
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|link
id|u16
id|link
suffix:semicolon
DECL|member|reason
id|u8
id|reason
suffix:semicolon
multiline_comment|/* not used by request */
)brace
suffix:semicolon
DECL|struct|llc_prim_reset
r_struct
id|llc_prim_reset
(brace
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|link
id|u16
id|link
suffix:semicolon
DECL|member|reason
id|u8
id|reason
suffix:semicolon
multiline_comment|/* used only by indicate */
)brace
suffix:semicolon
DECL|struct|llc_prim_flow_ctrl
r_struct
id|llc_prim_flow_ctrl
(brace
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|link
id|u16
id|link
suffix:semicolon
DECL|member|amount
id|u32
id|amount
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|llc_prim_data
r_struct
id|llc_prim_data
(brace
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|link
id|u16
id|link
suffix:semicolon
DECL|member|pri
id|u8
id|pri
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* pointer to frame */
DECL|member|status
id|u8
id|status
suffix:semicolon
multiline_comment|/* reason */
)brace
suffix:semicolon
multiline_comment|/* Sending data in conection-less mode */
DECL|struct|llc_prim_unit_data
r_struct
id|llc_prim_unit_data
(brace
DECL|member|saddr
r_struct
id|llc_addr
id|saddr
suffix:semicolon
DECL|member|daddr
r_struct
id|llc_addr
id|daddr
suffix:semicolon
DECL|member|pri
id|u8
id|pri
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* pointer to frame */
DECL|member|lfb
id|u8
id|lfb
suffix:semicolon
multiline_comment|/* largest frame bit (TR) */
)brace
suffix:semicolon
DECL|struct|llc_prim_xid
r_struct
id|llc_prim_xid
(brace
DECL|member|saddr
r_struct
id|llc_addr
id|saddr
suffix:semicolon
DECL|member|daddr
r_struct
id|llc_addr
id|daddr
suffix:semicolon
DECL|member|pri
id|u8
id|pri
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|llc_prim_test
r_struct
id|llc_prim_test
(brace
DECL|member|saddr
r_struct
id|llc_addr
id|saddr
suffix:semicolon
DECL|member|daddr
r_struct
id|llc_addr
id|daddr
suffix:semicolon
DECL|member|pri
id|u8
id|pri
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* pointer to frame */
)brace
suffix:semicolon
DECL|union|llc_u_prim_data
r_union
id|llc_u_prim_data
(brace
DECL|member|conn
r_struct
id|llc_prim_conn
id|conn
suffix:semicolon
DECL|member|disc
r_struct
id|llc_prim_disc
id|disc
suffix:semicolon
DECL|member|res
r_struct
id|llc_prim_reset
id|res
suffix:semicolon
DECL|member|fc
r_struct
id|llc_prim_flow_ctrl
id|fc
suffix:semicolon
DECL|member|data
r_struct
id|llc_prim_data
id|data
suffix:semicolon
multiline_comment|/* data */
DECL|member|udata
r_struct
id|llc_prim_unit_data
id|udata
suffix:semicolon
multiline_comment|/* unit data */
DECL|member|xid
r_struct
id|llc_prim_xid
id|xid
suffix:semicolon
DECL|member|test
r_struct
id|llc_prim_test
id|test
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|llc_sap
suffix:semicolon
multiline_comment|/* Information block passed with all called primitives */
DECL|struct|llc_prim_if_block
r_struct
id|llc_prim_if_block
(brace
DECL|member|sap
r_struct
id|llc_sap
op_star
id|sap
suffix:semicolon
DECL|member|prim
id|u8
id|prim
suffix:semicolon
DECL|member|data
r_union
id|llc_u_prim_data
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|llc_prim_call_t
r_typedef
r_int
(paren
op_star
id|llc_prim_call_t
)paren
(paren
r_struct
id|llc_prim_if_block
op_star
id|prim_if
)paren
suffix:semicolon
r_extern
r_struct
id|llc_sap
op_star
id|llc_sap_open
c_func
(paren
id|llc_prim_call_t
id|network_indicate
comma
id|llc_prim_call_t
id|network_confirm
comma
id|u8
id|lsap
)paren
suffix:semicolon
r_extern
r_void
id|llc_sap_close
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
)paren
suffix:semicolon
macro_line|#endif /* LLC_IF_H */
eof
