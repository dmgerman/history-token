macro_line|#ifndef LLC_MAIN_H
DECL|macro|LLC_MAIN_H
mdefine_line|#define LLC_MAIN_H
multiline_comment|/*&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; * &t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
DECL|macro|LLC_EVENT
mdefine_line|#define LLC_EVENT&t;&t; 1
DECL|macro|LLC_PACKET
mdefine_line|#define LLC_PACKET&t;&t; 2
DECL|macro|LLC_TYPE_1
mdefine_line|#define LLC_TYPE_1&t;&t; 1
DECL|macro|LLC_TYPE_2
mdefine_line|#define LLC_TYPE_2&t;&t; 2
DECL|macro|LLC_P_TIME
mdefine_line|#define LLC_P_TIME&t;&t; 2
DECL|macro|LLC_ACK_TIME
mdefine_line|#define LLC_ACK_TIME&t;&t; 3
DECL|macro|LLC_REJ_TIME
mdefine_line|#define LLC_REJ_TIME&t;&t; 3
DECL|macro|LLC_BUSY_TIME
mdefine_line|#define LLC_BUSY_TIME&t;&t; 3
DECL|macro|LLC_SENDACK_TIME
mdefine_line|#define LLC_SENDACK_TIME&t;50
DECL|macro|LLC_DEST_INVALID
mdefine_line|#define LLC_DEST_INVALID&t; 0&t;/* Invalid LLC PDU type */
DECL|macro|LLC_DEST_SAP
mdefine_line|#define LLC_DEST_SAP&t;&t; 1&t;/* Type 1 goes here */
DECL|macro|LLC_DEST_CONN
mdefine_line|#define LLC_DEST_CONN&t;&t; 2&t;/* Type 2 goes here */
multiline_comment|/* LLC Layer global default parameters */
DECL|macro|LLC_GLOBAL_DEFAULT_MAX_NBR_SAPS
mdefine_line|#define LLC_GLOBAL_DEFAULT_MAX_NBR_SAPS&t;&t;4
DECL|macro|LLC_GLOBAL_DEFAULT_MAX_NBR_CONNS
mdefine_line|#define LLC_GLOBAL_DEFAULT_MAX_NBR_CONNS&t;64
r_extern
r_struct
id|llc_prim_if_block
id|llc_ind_prim
comma
id|llc_cfm_prim
suffix:semicolon
multiline_comment|/* LLC station component (SAP and connection resource manager) */
multiline_comment|/* Station component; one per adapter */
DECL|struct|llc_station
r_struct
id|llc_station
(brace
DECL|member|state
id|u8
id|state
suffix:semicolon
multiline_comment|/* state of station */
DECL|member|xid_r_count
id|u8
id|xid_r_count
suffix:semicolon
multiline_comment|/* XID response PDU counter */
DECL|member|ack_timer
r_struct
id|timer_list
id|ack_timer
suffix:semicolon
DECL|member|ack_tmr_running
id|u8
id|ack_tmr_running
suffix:semicolon
multiline_comment|/* 1 or 0 */
DECL|member|retry_count
id|u8
id|retry_count
suffix:semicolon
DECL|member|maximum_retry
id|u8
id|maximum_retry
suffix:semicolon
DECL|member|mac_sa
id|u8
id|mac_sa
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* MAC source address */
r_struct
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|sap_list
)brace
id|sap_list
suffix:semicolon
multiline_comment|/* list of related SAPs */
r_struct
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|ev_q
)brace
id|ev_q
suffix:semicolon
multiline_comment|/* events entering state mach. */
DECL|member|mac_pdu_q
r_struct
id|sk_buff_head
id|mac_pdu_q
suffix:semicolon
multiline_comment|/* PDUs ready to send to MAC */
)brace
suffix:semicolon
r_struct
id|llc_station_state_ev
suffix:semicolon
r_extern
r_struct
id|llc_sap
op_star
id|llc_sap_alloc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|llc_sap_save
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
)paren
suffix:semicolon
r_extern
r_void
id|llc_free_sap
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
)paren
suffix:semicolon
r_extern
r_struct
id|llc_sap
op_star
id|llc_sap_find
c_func
(paren
id|u8
id|lsap
)paren
suffix:semicolon
r_extern
r_struct
id|llc_station
op_star
id|llc_station_get
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|llc_station_state_ev
op_star
id|llc_station_alloc_ev
c_func
(paren
r_struct
id|llc_station
op_star
id|station
)paren
suffix:semicolon
r_extern
r_void
id|llc_station_send_ev
c_func
(paren
r_struct
id|llc_station
op_star
id|station
comma
r_struct
id|llc_station_state_ev
op_star
id|ev
)paren
suffix:semicolon
r_extern
r_void
id|llc_station_send_pdu
c_func
(paren
r_struct
id|llc_station
op_star
id|station
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|llc_alloc_frame
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* LLC_MAIN_H */
eof
