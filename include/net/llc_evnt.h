macro_line|#ifndef LLC_EVNT_H
DECL|macro|LLC_EVNT_H
mdefine_line|#define LLC_EVNT_H
multiline_comment|/*&n; * Copyright (c) 1997 by Procom Technology,Inc.&n; * &t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
multiline_comment|/* Station component state transition events */
multiline_comment|/* Types of events (possible values in &squot;ev-&gt;type&squot;) */
DECL|macro|LLC_STATION_EV_TYPE_SIMPLE
mdefine_line|#define LLC_STATION_EV_TYPE_SIMPLE&t;1
DECL|macro|LLC_STATION_EV_TYPE_CONDITION
mdefine_line|#define LLC_STATION_EV_TYPE_CONDITION&t;2
DECL|macro|LLC_STATION_EV_TYPE_PRIM
mdefine_line|#define LLC_STATION_EV_TYPE_PRIM&t;3
DECL|macro|LLC_STATION_EV_TYPE_PDU
mdefine_line|#define LLC_STATION_EV_TYPE_PDU&t;&t;4       /* command/response PDU */
DECL|macro|LLC_STATION_EV_TYPE_ACK_TMR
mdefine_line|#define LLC_STATION_EV_TYPE_ACK_TMR&t;5
DECL|macro|LLC_STATION_EV_TYPE_RPT_STATUS
mdefine_line|#define LLC_STATION_EV_TYPE_RPT_STATUS&t;6
multiline_comment|/* Events */
DECL|macro|LLC_STATION_EV_ENABLE_WITH_DUP_ADDR_CHECK
mdefine_line|#define LLC_STATION_EV_ENABLE_WITH_DUP_ADDR_CHECK&t;&t;1
DECL|macro|LLC_STATION_EV_ENABLE_WITHOUT_DUP_ADDR_CHECK
mdefine_line|#define LLC_STATION_EV_ENABLE_WITHOUT_DUP_ADDR_CHECK&t;&t;2
DECL|macro|LLC_STATION_EV_ACK_TMR_EXP_LT_RETRY_CNT_MAX_RETRY
mdefine_line|#define LLC_STATION_EV_ACK_TMR_EXP_LT_RETRY_CNT_MAX_RETRY&t;3
DECL|macro|LLC_STATION_EV_ACK_TMR_EXP_EQ_RETRY_CNT_MAX_RETRY
mdefine_line|#define LLC_STATION_EV_ACK_TMR_EXP_EQ_RETRY_CNT_MAX_RETRY&t;4
DECL|macro|LLC_STATION_EV_RX_NULL_DSAP_XID_C
mdefine_line|#define LLC_STATION_EV_RX_NULL_DSAP_XID_C&t;&t;&t;5
DECL|macro|LLC_STATION_EV_RX_NULL_DSAP_0_XID_R_XID_R_CNT_EQ
mdefine_line|#define LLC_STATION_EV_RX_NULL_DSAP_0_XID_R_XID_R_CNT_EQ&t;6
DECL|macro|LLC_STATION_EV_RX_NULL_DSAP_1_XID_R_XID_R_CNT_EQ
mdefine_line|#define LLC_STATION_EV_RX_NULL_DSAP_1_XID_R_XID_R_CNT_EQ&t;7
DECL|macro|LLC_STATION_EV_RX_NULL_DSAP_TEST_C
mdefine_line|#define LLC_STATION_EV_RX_NULL_DSAP_TEST_C&t;&t;&t;8
DECL|macro|LLC_STATION_EV_DISABLE_REQ
mdefine_line|#define LLC_STATION_EV_DISABLE_REQ&t;&t;&t;&t;9
DECL|struct|llc_station_state_ev
r_struct
id|llc_station_state_ev
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|prim
id|u8
id|prim
suffix:semicolon
DECL|member|prim_type
id|u8
id|prim_type
suffix:semicolon
DECL|member|reason
id|u8
id|reason
suffix:semicolon
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
multiline_comment|/* node in station-&gt;ev_q.list */
)brace
suffix:semicolon
r_static
id|__inline__
r_struct
id|llc_station_state_ev
op_star
DECL|function|llc_station_ev
id|llc_station_ev
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
(paren
r_struct
id|llc_station_state_ev
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
)brace
DECL|typedef|llc_station_ev_t
r_typedef
r_int
(paren
op_star
id|llc_station_ev_t
)paren
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
r_int
id|llc_stat_ev_enable_with_dup_addr_check
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
r_int
id|llc_stat_ev_enable_without_dup_addr_check
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
r_int
id|llc_stat_ev_ack_tmr_exp_lt_retry_cnt_max_retry
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
r_int
id|llc_stat_ev_ack_tmr_exp_eq_retry_cnt_max_retry
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
r_int
id|llc_stat_ev_rx_null_dsap_xid_c
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
r_int
id|llc_stat_ev_rx_null_dsap_0_xid_r_xid_r_cnt_eq
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
r_int
id|llc_stat_ev_rx_null_dsap_1_xid_r_xid_r_cnt_eq
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
r_int
id|llc_stat_ev_rx_null_dsap_test_c
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
r_int
id|llc_stat_ev_disable_req
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
macro_line|#endif /* LLC_EVNT_H */
eof
