multiline_comment|/*&n; * llc_s_st.c - Defines SAP component state machine transitions.&n; *&n; * The followed transitions are SAP component state machine transitions&n; * which are described in 802.2 LLC protocol standard document.&n; *&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; *&t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/llc_if.h&gt;
macro_line|#include &lt;net/llc_s_ev.h&gt;
macro_line|#include &lt;net/llc_s_ac.h&gt;
macro_line|#include &lt;net/llc_s_st.h&gt;
multiline_comment|/* dummy last-transition indicator; common to all state transition groups&n; * last entry for this state&n; * all members are zeros, .bss zeroes it&n; */
DECL|variable|llc_sap_state_trans_end
r_static
r_struct
id|llc_sap_state_trans
id|llc_sap_state_trans_end
suffix:semicolon
multiline_comment|/* state LLC_SAP_STATE_INACTIVE transition for&n; * LLC_SAP_EV_ACTIVATION_REQ event&n; */
DECL|variable|llc_sap_inactive_state_actions_1
r_static
id|llc_sap_action_t
id|llc_sap_inactive_state_actions_1
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_sap_action_report_status
comma
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_sap_inactive_state_trans_1
r_static
r_struct
id|llc_sap_state_trans
id|llc_sap_inactive_state_trans_1
op_assign
(brace
dot
id|ev
op_assign
id|llc_sap_ev_activation_req
comma
dot
id|next_state
op_assign
id|LLC_SAP_STATE_ACTIVE
comma
dot
id|ev_actions
op_assign
id|llc_sap_inactive_state_actions_1
comma
)brace
suffix:semicolon
multiline_comment|/* array of pointers; one to each transition */
DECL|variable|llc_sap_inactive_state_transitions
r_static
r_struct
id|llc_sap_state_trans
op_star
id|llc_sap_inactive_state_transitions
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
op_amp
id|llc_sap_inactive_state_trans_1
comma
(braket
l_int|1
)braket
op_assign
op_amp
id|llc_sap_state_trans_end
comma
)brace
suffix:semicolon
multiline_comment|/* state LLC_SAP_STATE_ACTIVE transition for LLC_SAP_EV_RX_UI event */
DECL|variable|llc_sap_active_state_actions_1
r_static
id|llc_sap_action_t
id|llc_sap_active_state_actions_1
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_sap_action_unitdata_ind
comma
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_sap_active_state_trans_1
r_static
r_struct
id|llc_sap_state_trans
id|llc_sap_active_state_trans_1
op_assign
(brace
dot
id|ev
op_assign
id|llc_sap_ev_rx_ui
comma
dot
id|next_state
op_assign
id|LLC_SAP_STATE_ACTIVE
comma
dot
id|ev_actions
op_assign
id|llc_sap_active_state_actions_1
comma
)brace
suffix:semicolon
multiline_comment|/* state LLC_SAP_STATE_ACTIVE transition for LLC_SAP_EV_UNITDATA_REQ event */
DECL|variable|llc_sap_active_state_actions_2
r_static
id|llc_sap_action_t
id|llc_sap_active_state_actions_2
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_sap_action_send_ui
comma
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_sap_active_state_trans_2
r_static
r_struct
id|llc_sap_state_trans
id|llc_sap_active_state_trans_2
op_assign
(brace
dot
id|ev
op_assign
id|llc_sap_ev_unitdata_req
comma
dot
id|next_state
op_assign
id|LLC_SAP_STATE_ACTIVE
comma
dot
id|ev_actions
op_assign
id|llc_sap_active_state_actions_2
comma
)brace
suffix:semicolon
multiline_comment|/* state LLC_SAP_STATE_ACTIVE transition for LLC_SAP_EV_XID_REQ event */
DECL|variable|llc_sap_active_state_actions_3
r_static
id|llc_sap_action_t
id|llc_sap_active_state_actions_3
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_sap_action_send_xid_c
comma
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_sap_active_state_trans_3
r_static
r_struct
id|llc_sap_state_trans
id|llc_sap_active_state_trans_3
op_assign
(brace
dot
id|ev
op_assign
id|llc_sap_ev_xid_req
comma
dot
id|next_state
op_assign
id|LLC_SAP_STATE_ACTIVE
comma
dot
id|ev_actions
op_assign
id|llc_sap_active_state_actions_3
comma
)brace
suffix:semicolon
multiline_comment|/* state LLC_SAP_STATE_ACTIVE transition for LLC_SAP_EV_RX_XID_C event */
DECL|variable|llc_sap_active_state_actions_4
r_static
id|llc_sap_action_t
id|llc_sap_active_state_actions_4
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_sap_action_send_xid_r
comma
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_sap_active_state_trans_4
r_static
r_struct
id|llc_sap_state_trans
id|llc_sap_active_state_trans_4
op_assign
(brace
dot
id|ev
op_assign
id|llc_sap_ev_rx_xid_c
comma
dot
id|next_state
op_assign
id|LLC_SAP_STATE_ACTIVE
comma
dot
id|ev_actions
op_assign
id|llc_sap_active_state_actions_4
comma
)brace
suffix:semicolon
multiline_comment|/* state LLC_SAP_STATE_ACTIVE transition for LLC_SAP_EV_RX_XID_R event */
DECL|variable|llc_sap_active_state_actions_5
r_static
id|llc_sap_action_t
id|llc_sap_active_state_actions_5
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_sap_action_xid_ind
comma
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_sap_active_state_trans_5
r_static
r_struct
id|llc_sap_state_trans
id|llc_sap_active_state_trans_5
op_assign
(brace
dot
id|ev
op_assign
id|llc_sap_ev_rx_xid_r
comma
dot
id|next_state
op_assign
id|LLC_SAP_STATE_ACTIVE
comma
dot
id|ev_actions
op_assign
id|llc_sap_active_state_actions_5
comma
)brace
suffix:semicolon
multiline_comment|/* state LLC_SAP_STATE_ACTIVE transition for LLC_SAP_EV_TEST_REQ event */
DECL|variable|llc_sap_active_state_actions_6
r_static
id|llc_sap_action_t
id|llc_sap_active_state_actions_6
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_sap_action_send_test_c
comma
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_sap_active_state_trans_6
r_static
r_struct
id|llc_sap_state_trans
id|llc_sap_active_state_trans_6
op_assign
(brace
dot
id|ev
op_assign
id|llc_sap_ev_test_req
comma
dot
id|next_state
op_assign
id|LLC_SAP_STATE_ACTIVE
comma
dot
id|ev_actions
op_assign
id|llc_sap_active_state_actions_6
comma
)brace
suffix:semicolon
multiline_comment|/* state LLC_SAP_STATE_ACTIVE transition for LLC_SAP_EV_RX_TEST_C event */
DECL|variable|llc_sap_active_state_actions_7
r_static
id|llc_sap_action_t
id|llc_sap_active_state_actions_7
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_sap_action_send_test_r
comma
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_sap_active_state_trans_7
r_static
r_struct
id|llc_sap_state_trans
id|llc_sap_active_state_trans_7
op_assign
(brace
dot
id|ev
op_assign
id|llc_sap_ev_rx_test_c
comma
dot
id|next_state
op_assign
id|LLC_SAP_STATE_ACTIVE
comma
dot
id|ev_actions
op_assign
id|llc_sap_active_state_actions_7
)brace
suffix:semicolon
multiline_comment|/* state LLC_SAP_STATE_ACTIVE transition for LLC_SAP_EV_RX_TEST_R event */
DECL|variable|llc_sap_active_state_actions_8
r_static
id|llc_sap_action_t
id|llc_sap_active_state_actions_8
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_sap_action_test_ind
comma
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_sap_active_state_trans_8
r_static
r_struct
id|llc_sap_state_trans
id|llc_sap_active_state_trans_8
op_assign
(brace
dot
id|ev
op_assign
id|llc_sap_ev_rx_test_r
comma
dot
id|next_state
op_assign
id|LLC_SAP_STATE_ACTIVE
comma
dot
id|ev_actions
op_assign
id|llc_sap_active_state_actions_8
comma
)brace
suffix:semicolon
multiline_comment|/* state LLC_SAP_STATE_ACTIVE transition for&n; * LLC_SAP_EV_DEACTIVATION_REQ event&n; */
DECL|variable|llc_sap_active_state_actions_9
r_static
id|llc_sap_action_t
id|llc_sap_active_state_actions_9
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|llc_sap_action_report_status
comma
(braket
l_int|1
)braket
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|llc_sap_active_state_trans_9
r_static
r_struct
id|llc_sap_state_trans
id|llc_sap_active_state_trans_9
op_assign
(brace
dot
id|ev
op_assign
id|llc_sap_ev_deactivation_req
comma
dot
id|next_state
op_assign
id|LLC_SAP_STATE_INACTIVE
comma
dot
id|ev_actions
op_assign
id|llc_sap_active_state_actions_9
)brace
suffix:semicolon
multiline_comment|/* array of pointers; one to each transition */
DECL|variable|llc_sap_active_state_transitions
r_static
r_struct
id|llc_sap_state_trans
op_star
id|llc_sap_active_state_transitions
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
op_amp
id|llc_sap_active_state_trans_2
comma
(braket
l_int|1
)braket
op_assign
op_amp
id|llc_sap_active_state_trans_1
comma
(braket
l_int|2
)braket
op_assign
op_amp
id|llc_sap_active_state_trans_3
comma
(braket
l_int|3
)braket
op_assign
op_amp
id|llc_sap_active_state_trans_4
comma
(braket
l_int|4
)braket
op_assign
op_amp
id|llc_sap_active_state_trans_5
comma
(braket
l_int|5
)braket
op_assign
op_amp
id|llc_sap_active_state_trans_6
comma
(braket
l_int|6
)braket
op_assign
op_amp
id|llc_sap_active_state_trans_7
comma
(braket
l_int|7
)braket
op_assign
op_amp
id|llc_sap_active_state_trans_8
comma
(braket
l_int|8
)braket
op_assign
op_amp
id|llc_sap_active_state_trans_9
comma
(braket
l_int|9
)braket
op_assign
op_amp
id|llc_sap_state_trans_end
comma
)brace
suffix:semicolon
multiline_comment|/* SAP state transition table */
DECL|variable|llc_sap_state_table
r_struct
id|llc_sap_state
id|llc_sap_state_table
(braket
id|LLC_NR_SAP_STATES
)braket
op_assign
(brace
(braket
id|LLC_SAP_STATE_INACTIVE
op_minus
l_int|1
)braket
op_assign
(brace
dot
id|curr_state
op_assign
id|LLC_SAP_STATE_INACTIVE
comma
dot
id|transitions
op_assign
id|llc_sap_inactive_state_transitions
comma
)brace
comma
(braket
id|LLC_SAP_STATE_ACTIVE
op_minus
l_int|1
)braket
op_assign
(brace
dot
id|curr_state
op_assign
id|LLC_SAP_STATE_ACTIVE
comma
dot
id|transitions
op_assign
id|llc_sap_active_state_transitions
comma
)brace
comma
)brace
suffix:semicolon
eof
