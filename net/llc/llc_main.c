multiline_comment|/*&n; * llc_main.c - This module contains main functions to manage station, saps&n; * &t;and connections of the LLC.&n; *&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; * &t;&t; 2001-2003 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;net/llc.h&gt;
macro_line|#include &lt;net/llc_sap.h&gt;
macro_line|#include &lt;net/llc_conn.h&gt;
macro_line|#include &lt;net/llc_main.h&gt;
macro_line|#include &lt;net/llc_evnt.h&gt;
macro_line|#include &lt;net/llc_actn.h&gt;
macro_line|#include &lt;net/llc_stat.h&gt;
macro_line|#include &lt;net/llc_c_ac.h&gt;
macro_line|#include &lt;net/llc_s_ac.h&gt;
macro_line|#include &lt;net/llc_c_ev.h&gt;
macro_line|#include &lt;net/llc_c_st.h&gt;
macro_line|#include &lt;net/llc_s_ev.h&gt;
macro_line|#include &lt;net/llc_s_st.h&gt;
macro_line|#include &lt;net/llc_proc.h&gt;
multiline_comment|/* static function prototypes */
r_static
r_void
id|llc_station_service_events
c_func
(paren
r_struct
id|llc_station
op_star
id|station
)paren
suffix:semicolon
r_static
r_void
id|llc_station_free_ev
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
r_static
r_void
id|llc_station_send_pdus
c_func
(paren
r_struct
id|llc_station
op_star
id|station
)paren
suffix:semicolon
r_static
id|u16
id|llc_station_next_state
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
r_static
id|u16
id|llc_exec_station_trans_actions
c_func
(paren
r_struct
id|llc_station
op_star
id|station
comma
r_struct
id|llc_station_state_trans
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
id|llc_station_state_trans
op_star
id|llc_find_station_trans
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
DECL|variable|llc_main_station
r_struct
id|llc_station
id|llc_main_station
suffix:semicolon
multiline_comment|/* only one of its kind */
multiline_comment|/**&n; *&t;llc_sap_save - add sap to station list&n; *&t;@sap: Address of the sap&n; *&n; *&t;Adds a sap to the LLC&squot;s station sap list.&n; */
DECL|function|llc_sap_save
r_void
id|llc_sap_save
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|llc_main_station.sap_list.lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|sap-&gt;node
comma
op_amp
id|llc_main_station.sap_list.list
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|llc_main_station.sap_list.lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sap_find - searchs a SAP in station&n; *&t;@sap_value: sap to be found&n; *&n; *&t;Searchs for a sap in the sap list of the LLC&squot;s station upon the sap ID.&n; *&t;Returns the sap or %NULL if not found.&n; */
DECL|function|llc_sap_find
r_struct
id|llc_sap
op_star
id|llc_sap_find
c_func
(paren
id|u8
id|sap_value
)paren
(brace
r_struct
id|llc_sap
op_star
id|sap
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|llc_main_station.sap_list.lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|llc_main_station.sap_list.list
)paren
(brace
id|sap
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|llc_sap
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sap-&gt;laddr.lsap
op_eq
id|sap_value
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|entry
op_eq
op_amp
id|llc_main_station.sap_list.list
)paren
multiline_comment|/* not found */
id|sap
op_assign
l_int|NULL
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|llc_main_station.sap_list.lock
)paren
suffix:semicolon
r_return
id|sap
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_station_state_process: queue event and try to process queue.&n; *&t;@station: Address of the station&n; *&t;@skb: Address of the event&n; *&n; *&t;Queues an event (on the station event queue) for handling by the&n; *&t;station state machine and attempts to process any queued-up events.&n; */
DECL|function|llc_station_state_process
r_void
id|llc_station_state_process
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
(brace
id|spin_lock_bh
c_func
(paren
op_amp
id|station-&gt;ev_q.lock
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|station-&gt;ev_q.list
comma
id|skb
)paren
suffix:semicolon
id|llc_station_service_events
c_func
(paren
id|station
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|station-&gt;ev_q.lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_station_send_pdu - queues PDU to send&n; *&t;@station: Address of the station&n; *&t;@skb: Address of the PDU&n; *&n; *&t;Queues a PDU to send to the MAC layer.&n; */
DECL|function|llc_station_send_pdu
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
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|station-&gt;mac_pdu_q
comma
id|skb
)paren
suffix:semicolon
id|llc_station_send_pdus
c_func
(paren
id|station
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_station_send_pdus - tries to send queued PDUs&n; *&t;@station: Address of the station&n; *&n; *&t;Tries to send any PDUs queued in the station mac_pdu_q to the MAC&n; *&t;layer.&n; */
DECL|function|llc_station_send_pdus
r_static
r_void
id|llc_station_send_pdus
c_func
(paren
r_struct
id|llc_station
op_star
id|station
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|station-&gt;mac_pdu_q
)paren
)paren
op_ne
l_int|NULL
)paren
r_if
c_cond
(paren
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_station_free_ev - frees an event&n; *&t;@station: Address of the station&n; *&t;@skb: Address of the event&n; *&n; *&t;Frees an event.&n; */
DECL|function|llc_station_free_ev
r_static
r_void
id|llc_station_free_ev
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
(brace
r_struct
id|llc_station_state_ev
op_star
id|ev
op_assign
id|llc_station_ev
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ev-&gt;type
op_eq
id|LLC_STATION_EV_TYPE_PDU
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_station_service_events - service events in the queue&n; *&t;@station: Address of the station&n; *&n; *&t;Get an event from the station event queue (if any); attempt to service&n; *&t;the event; if event serviced, get the next event (if any) on the event&n; *&t;queue; if event not service, re-queue the event on the event queue and&n; *&t;attempt to service the next event; when serviced all events in queue,&n; *&t;finished; if don&squot;t transition to different state, just service all&n; *&t;events once; if transition to new state, service all events again.&n; *&t;Caller must hold station-&gt;ev_q.lock.&n; */
DECL|function|llc_station_service_events
r_static
r_void
id|llc_station_service_events
c_func
(paren
r_struct
id|llc_station
op_star
id|station
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|station-&gt;ev_q.list
)paren
)paren
op_ne
l_int|NULL
)paren
id|llc_station_next_state
c_func
(paren
id|station
comma
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_station_next_state - processes event and goes to the next state&n; *&t;@station: Address of the station&n; *&t;@skb: Address of the event&n; *&n; *&t;Processes an event, executes any transitions related to that event and&n; *&t;updates the state of the station.&n; */
DECL|function|llc_station_next_state
r_static
id|u16
id|llc_station_next_state
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
(brace
id|u16
id|rc
op_assign
l_int|1
suffix:semicolon
r_struct
id|llc_station_state_trans
op_star
id|trans
suffix:semicolon
r_if
c_cond
(paren
id|station-&gt;state
OG
id|LLC_NBR_STATION_STATES
)paren
r_goto
id|out
suffix:semicolon
id|trans
op_assign
id|llc_find_station_trans
c_func
(paren
id|station
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
multiline_comment|/* got the state to which we next transition; perform the&n;&t;&t; * actions associated with this transition before actually&n;&t;&t; * transitioning to the next state&n;&t;&t; */
id|rc
op_assign
id|llc_exec_station_trans_actions
c_func
(paren
id|station
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
multiline_comment|/* transition station to next state if all actions&n;&t;&t;&t; * execute successfully; done; wait for next event&n;&t;&t;&t; */
id|station-&gt;state
op_assign
id|trans-&gt;next_state
suffix:semicolon
)brace
r_else
multiline_comment|/* event not recognized in current state; re-queue it for&n;&t;&t; * processing again at a later time; return failure&n;&t;&t; */
id|rc
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|llc_station_free_ev
c_func
(paren
id|station
comma
id|skb
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_find_station_trans - finds transition for this event&n; *&t;@station: Address of the station&n; *&t;@skb: Address of the event&n; *&n; *&t;Search thru events of the current state of the station until list&n; *&t;exhausted or it&squot;s obvious that the event is not valid for the current&n; *&t;state. Returns the address of the transition if cound, %NULL otherwise.&n; */
r_static
r_struct
id|llc_station_state_trans
op_star
DECL|function|llc_find_station_trans
id|llc_find_station_trans
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
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_struct
id|llc_station_state_trans
op_star
id|rc
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|llc_station_state_trans
op_star
op_star
id|next_trans
suffix:semicolon
r_struct
id|llc_station_state
op_star
id|curr_state
op_assign
op_amp
id|llc_station_state_table
(braket
id|station-&gt;state
op_minus
l_int|1
)braket
suffix:semicolon
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
id|station
comma
id|skb
)paren
)paren
(brace
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
multiline_comment|/**&n; *&t;llc_exec_station_trans_actions - executes actions for transition&n; *&t;@station: Address of the station&n; *&t;@trans: Address of the transition&n; *&t;@skb: Address of the event that caused the transition&n; *&n; *&t;Executes actions of a transition of the station state machine. Returns&n; *&t;0 if all actions complete successfully, nonzero otherwise.&n; */
DECL|function|llc_exec_station_trans_actions
r_static
id|u16
id|llc_exec_station_trans_actions
c_func
(paren
r_struct
id|llc_station
op_star
id|station
comma
r_struct
id|llc_station_state_trans
op_star
id|trans
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|u16
id|rc
op_assign
l_int|0
suffix:semicolon
id|llc_station_action_t
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
id|station
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
multiline_comment|/*&n; *&t;llc_station_rcv - send received pdu to the station state machine&n; *&t;@skb: received frame.&n; *&n; *&t;Sends data unit to station state machine.&n; */
DECL|function|llc_station_rcv
r_static
r_void
id|llc_station_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|llc_station_state_ev
op_star
id|ev
op_assign
id|llc_station_ev
c_func
(paren
id|skb
)paren
suffix:semicolon
id|ev-&gt;type
op_assign
id|LLC_STATION_EV_TYPE_PDU
suffix:semicolon
id|ev-&gt;reason
op_assign
l_int|0
suffix:semicolon
id|llc_station_state_process
c_func
(paren
op_amp
id|llc_main_station
comma
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_alloc_frame - allocates sk_buff for frame&n; *&n; *&t;Allocates an sk_buff for frame and initializes sk_buff fields.&n; *&t;Returns allocated skb or %NULL when out of memory.&n; */
DECL|function|llc_alloc_frame
r_struct
id|sk_buff
op_star
id|llc_alloc_frame
c_func
(paren
r_void
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|alloc_skb
c_func
(paren
l_int|128
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|skb_reserve
c_func
(paren
id|skb
comma
l_int|50
)paren
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_802_2
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev_base-&gt;next
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;head
suffix:semicolon
)brace
r_return
id|skb
suffix:semicolon
)brace
DECL|variable|llc_packet_type
r_static
r_struct
id|packet_type
id|llc_packet_type
op_assign
(brace
dot
id|type
op_assign
id|__constant_htons
c_func
(paren
id|ETH_P_802_2
)paren
comma
dot
id|func
op_assign
id|llc_rcv
comma
dot
id|data
op_assign
(paren
r_void
op_star
)paren
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|llc_tr_packet_type
r_static
r_struct
id|packet_type
id|llc_tr_packet_type
op_assign
(brace
dot
id|type
op_assign
id|__constant_htons
c_func
(paren
id|ETH_P_TR_802_2
)paren
comma
dot
id|func
op_assign
id|llc_rcv
comma
dot
id|data
op_assign
(paren
r_void
op_star
)paren
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|llc_error_msg
(braket
)braket
id|__initdata
op_assign
id|KERN_ERR
l_string|&quot;LLC install NOT successful.&bslash;n&quot;
suffix:semicolon
DECL|function|llc_init
r_static
r_int
id|__init
id|llc_init
c_func
(paren
r_void
)paren
(brace
id|u16
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|llc_station_state_ev
op_star
id|ev
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|llc_main_station.sap_list.list
)paren
suffix:semicolon
id|rwlock_init
c_func
(paren
op_amp
id|llc_main_station.sap_list.lock
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|llc_main_station.mac_pdu_q
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|llc_main_station.ev_q.list
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|llc_main_station.ev_q.lock
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|llc_main_station.ack_timer
)paren
suffix:semicolon
id|llc_main_station.ack_timer.data
op_assign
(paren
r_int
r_int
)paren
op_amp
id|llc_main_station
suffix:semicolon
id|llc_main_station.ack_timer.function
op_assign
id|llc_station_ack_tmr_cb
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
l_int|0
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_goto
id|err
suffix:semicolon
id|llc_set_station_handler
c_func
(paren
id|llc_station_rcv
)paren
suffix:semicolon
id|ev
op_assign
id|llc_station_ev
c_func
(paren
id|skb
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ev
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_base-&gt;next
)paren
id|memcpy
c_func
(paren
id|llc_main_station.mac_sa
comma
id|dev_base-&gt;next-&gt;dev_addr
comma
id|ETH_ALEN
)paren
suffix:semicolon
r_else
id|memset
c_func
(paren
id|llc_main_station.mac_sa
comma
l_int|0
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|llc_main_station.ack_timer.expires
op_assign
id|jiffies
op_plus
l_int|3
op_star
id|HZ
suffix:semicolon
id|llc_main_station.maximum_retry
op_assign
l_int|1
suffix:semicolon
id|llc_main_station.state
op_assign
id|LLC_STATION_STATE_DOWN
suffix:semicolon
id|ev-&gt;type
op_assign
id|LLC_STATION_EV_TYPE_SIMPLE
suffix:semicolon
id|ev-&gt;prim_type
op_assign
id|LLC_STATION_EV_ENABLE_WITHOUT_DUP_ADDR_CHECK
suffix:semicolon
id|rc
op_assign
id|llc_station_next_state
c_func
(paren
op_amp
id|llc_main_station
comma
id|skb
)paren
suffix:semicolon
id|dev_add_pack
c_func
(paren
op_amp
id|llc_packet_type
)paren
suffix:semicolon
id|dev_add_pack
c_func
(paren
op_amp
id|llc_tr_packet_type
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
id|err
suffix:colon
id|printk
c_func
(paren
id|llc_error_msg
)paren
suffix:semicolon
id|rc
op_assign
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|llc_exit
r_static
r_void
id|__exit
id|llc_exit
c_func
(paren
r_void
)paren
(brace
id|dev_remove_pack
c_func
(paren
op_amp
id|llc_packet_type
)paren
suffix:semicolon
id|dev_remove_pack
c_func
(paren
op_amp
id|llc_tr_packet_type
)paren
suffix:semicolon
id|llc_set_station_handler
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|llc_init
id|module_init
c_func
(paren
id|llc_init
)paren
suffix:semicolon
DECL|variable|llc_exit
id|module_exit
c_func
(paren
id|llc_exit
)paren
suffix:semicolon
DECL|variable|llc_sap_find
id|EXPORT_SYMBOL
c_func
(paren
id|llc_sap_find
)paren
suffix:semicolon
DECL|variable|llc_alloc_frame
id|EXPORT_SYMBOL
c_func
(paren
id|llc_alloc_frame
)paren
suffix:semicolon
DECL|variable|llc_main_station
id|EXPORT_SYMBOL
c_func
(paren
id|llc_main_station
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Procom 1997, Jay Schullist 2001, Arnaldo C. Melo 2001-2003&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;LLC IEEE 802.2 extended support&quot;
)paren
suffix:semicolon
DECL|variable|PF_LLC
id|MODULE_ALIAS_NETPROTO
c_func
(paren
id|PF_LLC
)paren
suffix:semicolon
eof
