multiline_comment|/*&n; * llc_stat.c - Implementation of LLC station component state machine&n; * &t;&t;transitions&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; * &t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/llc_if.h&gt;
macro_line|#include &lt;net/llc_sap.h&gt;
macro_line|#include &lt;net/llc_evnt.h&gt;
macro_line|#include &lt;net/llc_actn.h&gt;
macro_line|#include &lt;net/llc_stat.h&gt;
multiline_comment|/* COMMON STATION STATE transitions */
multiline_comment|/* dummy last-transition indicator; common to all state transition groups&n; * last entry for this state&n; * all members are zeros, .bss zeroes it&n; */
DECL|variable|llc_stat_state_trans_n
r_static
r_struct
id|llc_station_state_trans
id|llc_stat_state_trans_n
suffix:semicolon
multiline_comment|/* DOWN STATE transitions */
multiline_comment|/* state transition for LLC_STATION_EV_ENABLE_WITH_DUP_ADDR_CHECK event */
DECL|variable|llc_stat_down_state_actions_1
r_static
id|llc_station_action_t
id|llc_stat_down_state_actions_1
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_station_ac_start_ack_timer
comma
(braket
l_int|1
)braket
op_assign
id|llc_station_ac_set_retry_cnt_0
comma
(braket
l_int|2
)braket
op_assign
id|llc_station_ac_set_xid_r_cnt_0
comma
(braket
l_int|3
)braket
op_assign
id|llc_station_ac_send_null_dsap_xid_c
comma
(braket
l_int|4
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_stat_down_state_trans_1
r_static
r_struct
id|llc_station_state_trans
id|llc_stat_down_state_trans_1
op_assign
(brace
dot
id|ev
op_assign
id|llc_stat_ev_enable_with_dup_addr_check
comma
dot
id|next_state
op_assign
id|LLC_STATION_STATE_DUP_ADDR_CHK
comma
dot
id|ev_actions
op_assign
id|llc_stat_down_state_actions_1
comma
)brace
suffix:semicolon
multiline_comment|/* state transition for LLC_STATION_EV_ENABLE_WITHOUT_DUP_ADDR_CHECK event */
DECL|variable|llc_stat_down_state_actions_2
r_static
id|llc_station_action_t
id|llc_stat_down_state_actions_2
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_station_ac_report_status
comma
multiline_comment|/* STATION UP */
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_stat_down_state_trans_2
r_static
r_struct
id|llc_station_state_trans
id|llc_stat_down_state_trans_2
op_assign
(brace
dot
id|ev
op_assign
id|llc_stat_ev_enable_without_dup_addr_check
comma
dot
id|next_state
op_assign
id|LLC_STATION_STATE_UP
comma
dot
id|ev_actions
op_assign
id|llc_stat_down_state_actions_2
comma
)brace
suffix:semicolon
multiline_comment|/* array of pointers; one to each transition */
DECL|variable|llc_stat_dwn_state_trans
r_static
r_struct
id|llc_station_state_trans
op_star
id|llc_stat_dwn_state_trans
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
op_amp
id|llc_stat_down_state_trans_1
comma
(braket
l_int|1
)braket
op_assign
op_amp
id|llc_stat_down_state_trans_2
comma
(braket
l_int|2
)braket
op_assign
op_amp
id|llc_stat_state_trans_n
comma
)brace
suffix:semicolon
multiline_comment|/* UP STATE transitions */
multiline_comment|/* state transition for LLC_STATION_EV_DISABLE_REQ event */
DECL|variable|llc_stat_up_state_actions_1
r_static
id|llc_station_action_t
id|llc_stat_up_state_actions_1
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_station_ac_report_status
comma
multiline_comment|/* STATION DOWN */
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_stat_up_state_trans_1
r_static
r_struct
id|llc_station_state_trans
id|llc_stat_up_state_trans_1
op_assign
(brace
dot
id|ev
op_assign
id|llc_stat_ev_disable_req
comma
dot
id|next_state
op_assign
id|LLC_STATION_STATE_DOWN
comma
dot
id|ev_actions
op_assign
id|llc_stat_up_state_actions_1
comma
)brace
suffix:semicolon
multiline_comment|/* state transition for LLC_STATION_EV_RX_NULL_DSAP_XID_C event */
DECL|variable|llc_stat_up_state_actions_2
r_static
id|llc_station_action_t
id|llc_stat_up_state_actions_2
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_station_ac_send_xid_r
comma
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_stat_up_state_trans_2
r_static
r_struct
id|llc_station_state_trans
id|llc_stat_up_state_trans_2
op_assign
(brace
dot
id|ev
op_assign
id|llc_stat_ev_rx_null_dsap_xid_c
comma
dot
id|next_state
op_assign
id|LLC_STATION_STATE_UP
comma
dot
id|ev_actions
op_assign
id|llc_stat_up_state_actions_2
comma
)brace
suffix:semicolon
multiline_comment|/* state transition for LLC_STATION_EV_RX_NULL_DSAP_TEST_C event */
DECL|variable|llc_stat_up_state_actions_3
r_static
id|llc_station_action_t
id|llc_stat_up_state_actions_3
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_station_ac_send_test_r
comma
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_stat_up_state_trans_3
r_static
r_struct
id|llc_station_state_trans
id|llc_stat_up_state_trans_3
op_assign
(brace
dot
id|ev
op_assign
id|llc_stat_ev_rx_null_dsap_test_c
comma
dot
id|next_state
op_assign
id|LLC_STATION_STATE_UP
comma
dot
id|ev_actions
op_assign
id|llc_stat_up_state_actions_3
comma
)brace
suffix:semicolon
multiline_comment|/* array of pointers; one to each transition */
DECL|variable|llc_stat_up_state_trans
r_static
r_struct
id|llc_station_state_trans
op_star
id|llc_stat_up_state_trans
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
op_amp
id|llc_stat_up_state_trans_1
comma
(braket
l_int|1
)braket
op_assign
op_amp
id|llc_stat_up_state_trans_2
comma
(braket
l_int|2
)braket
op_assign
op_amp
id|llc_stat_up_state_trans_3
comma
(braket
l_int|3
)braket
op_assign
op_amp
id|llc_stat_state_trans_n
comma
)brace
suffix:semicolon
multiline_comment|/* DUP ADDR CHK STATE transitions */
multiline_comment|/* state transition for LLC_STATION_EV_RX_NULL_DSAP_0_XID_R_XID_R_CNT_EQ&n; * event&n; */
DECL|variable|llc_stat_dupaddr_state_actions_1
r_static
id|llc_station_action_t
id|llc_stat_dupaddr_state_actions_1
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_station_ac_inc_xid_r_cnt_by_1
comma
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_stat_dupaddr_state_trans_1
r_static
r_struct
id|llc_station_state_trans
id|llc_stat_dupaddr_state_trans_1
op_assign
(brace
dot
id|ev
op_assign
id|llc_stat_ev_rx_null_dsap_0_xid_r_xid_r_cnt_eq
comma
dot
id|next_state
op_assign
id|LLC_STATION_STATE_DUP_ADDR_CHK
comma
dot
id|ev_actions
op_assign
id|llc_stat_dupaddr_state_actions_1
comma
)brace
suffix:semicolon
multiline_comment|/* state transition for LLC_STATION_EV_RX_NULL_DSAP_1_XID_R_XID_R_CNT_EQ&n; * event&n; */
DECL|variable|llc_stat_dupaddr_state_actions_2
r_static
id|llc_station_action_t
id|llc_stat_dupaddr_state_actions_2
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_station_ac_report_status
comma
multiline_comment|/* DUPLICATE ADDRESS FOUND */
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_stat_dupaddr_state_trans_2
r_static
r_struct
id|llc_station_state_trans
id|llc_stat_dupaddr_state_trans_2
op_assign
(brace
dot
id|ev
op_assign
id|llc_stat_ev_rx_null_dsap_1_xid_r_xid_r_cnt_eq
comma
dot
id|next_state
op_assign
id|LLC_STATION_STATE_DOWN
comma
dot
id|ev_actions
op_assign
id|llc_stat_dupaddr_state_actions_2
comma
)brace
suffix:semicolon
multiline_comment|/* state transition for LLC_STATION_EV_RX_NULL_DSAP_XID_C event */
DECL|variable|llc_stat_dupaddr_state_actions_3
r_static
id|llc_station_action_t
id|llc_stat_dupaddr_state_actions_3
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_station_ac_send_xid_r
comma
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_stat_dupaddr_state_trans_3
r_static
r_struct
id|llc_station_state_trans
id|llc_stat_dupaddr_state_trans_3
op_assign
(brace
dot
id|ev
op_assign
id|llc_stat_ev_rx_null_dsap_xid_c
comma
dot
id|next_state
op_assign
id|LLC_STATION_STATE_DUP_ADDR_CHK
comma
dot
id|ev_actions
op_assign
id|llc_stat_dupaddr_state_actions_3
comma
)brace
suffix:semicolon
multiline_comment|/* state transition for LLC_STATION_EV_ACK_TMR_EXP_LT_RETRY_CNT_MAX_RETRY&n; * event&n; */
DECL|variable|llc_stat_dupaddr_state_actions_4
r_static
id|llc_station_action_t
id|llc_stat_dupaddr_state_actions_4
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_station_ac_start_ack_timer
comma
(braket
l_int|1
)braket
op_assign
id|llc_station_ac_inc_retry_cnt_by_1
comma
(braket
l_int|2
)braket
op_assign
id|llc_station_ac_set_xid_r_cnt_0
comma
(braket
l_int|3
)braket
op_assign
id|llc_station_ac_send_null_dsap_xid_c
comma
(braket
l_int|4
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_stat_dupaddr_state_trans_4
r_static
r_struct
id|llc_station_state_trans
id|llc_stat_dupaddr_state_trans_4
op_assign
(brace
dot
id|ev
op_assign
id|llc_stat_ev_ack_tmr_exp_lt_retry_cnt_max_retry
comma
dot
id|next_state
op_assign
id|LLC_STATION_STATE_DUP_ADDR_CHK
comma
dot
id|ev_actions
op_assign
id|llc_stat_dupaddr_state_actions_4
)brace
suffix:semicolon
multiline_comment|/* state transition for LLC_STATION_EV_ACK_TMR_EXP_EQ_RETRY_CNT_MAX_RETRY&n; * event&n; */
DECL|variable|llc_stat_dupaddr_state_actions_5
r_static
id|llc_station_action_t
id|llc_stat_dupaddr_state_actions_5
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_station_ac_report_status
comma
multiline_comment|/* STATION UP */
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_stat_dupaddr_state_trans_5
r_static
r_struct
id|llc_station_state_trans
id|llc_stat_dupaddr_state_trans_5
op_assign
(brace
dot
id|ev
op_assign
id|llc_stat_ev_ack_tmr_exp_eq_retry_cnt_max_retry
comma
dot
id|next_state
op_assign
id|LLC_STATION_STATE_UP
comma
dot
id|ev_actions
op_assign
id|llc_stat_dupaddr_state_actions_5
comma
)brace
suffix:semicolon
multiline_comment|/* state transition for LLC_STATION_EV_DISABLE_REQ event */
DECL|variable|llc_stat_dupaddr_state_actions_6
r_static
id|llc_station_action_t
id|llc_stat_dupaddr_state_actions_6
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_station_ac_report_status
comma
multiline_comment|/* STATION DOWN */
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_stat_dupaddr_state_trans_6
r_static
r_struct
id|llc_station_state_trans
id|llc_stat_dupaddr_state_trans_6
op_assign
(brace
dot
id|ev
op_assign
id|llc_stat_ev_disable_req
comma
dot
id|next_state
op_assign
id|LLC_STATION_STATE_DOWN
comma
dot
id|ev_actions
op_assign
id|llc_stat_dupaddr_state_actions_6
comma
)brace
suffix:semicolon
multiline_comment|/* array of pointers; one to each transition */
DECL|variable|llc_stat_dupaddr_state_trans
r_static
r_struct
id|llc_station_state_trans
op_star
id|llc_stat_dupaddr_state_trans
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
op_amp
id|llc_stat_dupaddr_state_trans_6
comma
multiline_comment|/* Request */
(braket
l_int|1
)braket
op_assign
op_amp
id|llc_stat_dupaddr_state_trans_4
comma
multiline_comment|/* Timer */
(braket
l_int|2
)braket
op_assign
op_amp
id|llc_stat_dupaddr_state_trans_5
comma
(braket
l_int|3
)braket
op_assign
op_amp
id|llc_stat_dupaddr_state_trans_1
comma
multiline_comment|/* Receive frame */
(braket
l_int|4
)braket
op_assign
op_amp
id|llc_stat_dupaddr_state_trans_2
comma
(braket
l_int|5
)braket
op_assign
op_amp
id|llc_stat_dupaddr_state_trans_3
comma
(braket
l_int|6
)braket
op_assign
op_amp
id|llc_stat_state_trans_n
)brace
suffix:semicolon
DECL|variable|llc_station_state_table
r_struct
id|llc_station_state
id|llc_station_state_table
(braket
id|LLC_NBR_STATION_STATES
)braket
op_assign
(brace
(brace
dot
id|curr_state
op_assign
id|LLC_STATION_STATE_DOWN
comma
dot
id|transitions
op_assign
id|llc_stat_dwn_state_trans
comma
)brace
comma
(brace
dot
id|curr_state
op_assign
id|LLC_STATION_STATE_DUP_ADDR_CHK
comma
dot
id|transitions
op_assign
id|llc_stat_dupaddr_state_trans
comma
)brace
comma
(brace
dot
id|curr_state
op_assign
id|LLC_STATION_STATE_UP
comma
dot
id|transitions
op_assign
id|llc_stat_up_state_trans
comma
)brace
)brace
suffix:semicolon
eof