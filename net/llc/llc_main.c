multiline_comment|/*&n; * llc_main.c - This module contains main functions to manage station, saps&n; * &t;and connections of the LLC.&n; *&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; * &t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;net/llc_if.h&gt;
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
macro_line|#include &lt;net/llc_mac.h&gt;
macro_line|#include &lt;linux/llc.h&gt;
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
r_static
r_int
id|llc_rtn_all_conns
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
)paren
suffix:semicolon
DECL|variable|llc_main_station
r_static
r_struct
id|llc_station
id|llc_main_station
suffix:semicolon
multiline_comment|/* only one of its kind */
DECL|macro|LLC_REFCNT_DEBUG
macro_line|#undef LLC_REFCNT_DEBUG
macro_line|#ifdef LLC_REFCNT_DEBUG
DECL|variable|llc_sock_nr
r_static
id|atomic_t
id|llc_sock_nr
suffix:semicolon
macro_line|#endif
multiline_comment|/**&n; *&t;llc_sap_alloc - allocates and initializes sap.&n; *&n; *&t;Allocates and initializes sap.&n; */
DECL|function|llc_sap_alloc
r_struct
id|llc_sap
op_star
id|llc_sap_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|llc_sap
op_star
id|sap
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|sap
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sap
)paren
(brace
id|memset
c_func
(paren
id|sap
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sap
)paren
)paren
suffix:semicolon
id|sap-&gt;state
op_assign
id|LLC_SAP_STATE_ACTIVE
suffix:semicolon
id|memcpy
c_func
(paren
id|sap-&gt;laddr.mac
comma
id|llc_main_station.mac_sa
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|rwlock_init
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
)brace
r_return
id|sap
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_free_sap - frees a sap&n; *&t;@sap: Address of the sap&n; *&n; * &t;Frees all associated connections (if any), removes this sap from&n; * &t;the list of saps in te station and them frees the memory for this sap.&n; */
DECL|function|llc_free_sap
r_void
id|llc_free_sap
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
)paren
(brace
id|llc_rtn_all_conns
c_func
(paren
id|sap
)paren
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|sap-&gt;station-&gt;sap_list.lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|sap-&gt;node
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|sap-&gt;station-&gt;sap_list.lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sap
)paren
suffix:semicolon
)brace
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
multiline_comment|/**&n; *&t;llc_backlog_rcv - Processes rx frames and expired timers.&n; *&t;@sk: LLC sock (p8022 connection)&n; *&t;@skb: queued rx frame or event&n; *&n; *&t;This function processes frames that has received and timers that has&n; *&t;expired during sending an I pdu (refer to data_req_handler).  frames&n; *&t;queue by llc_rcv function (llc_mac.c) and timers queue by timer&n; *&t;callback functions(llc_c_ac.c).&n; */
DECL|function|llc_backlog_rcv
r_static
r_int
id|llc_backlog_rcv
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
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|llc_opt
op_star
id|llc
op_assign
id|llc_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|llc_backlog_type
c_func
(paren
id|skb
)paren
op_eq
id|LLC_PACKET
)paren
(brace
r_if
c_cond
(paren
id|llc-&gt;state
OG
l_int|1
)paren
multiline_comment|/* not closed */
id|rc
op_assign
id|llc_conn_rcv
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
r_else
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|llc_backlog_type
c_func
(paren
id|skb
)paren
op_eq
id|LLC_EVENT
)paren
(brace
multiline_comment|/* timer expiration event */
r_if
c_cond
(paren
id|llc-&gt;state
OG
l_int|1
)paren
multiline_comment|/* not closed */
id|rc
op_assign
id|llc_conn_state_process
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
r_else
id|llc_conn_free_ev
c_func
(paren
id|skb
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: invalid skb in backlog&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; *     llc_sk_init - Initializes a socket with default llc values.&n; *     @sk: socket to intiailize.&n; *&n; *     Initializes a socket with default llc values.&n; */
DECL|function|llc_sk_init
r_int
id|llc_sk_init
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|llc_opt
op_star
id|llc
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|llc
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|llc
)paren
r_goto
id|out
suffix:semicolon
id|memset
c_func
(paren
id|llc
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|llc
)paren
)paren
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
id|llc-&gt;sk
op_assign
id|sk
suffix:semicolon
id|llc-&gt;state
op_assign
id|LLC_CONN_STATE_ADM
suffix:semicolon
id|llc-&gt;inc_cntr
op_assign
id|llc-&gt;dec_cntr
op_assign
l_int|2
suffix:semicolon
id|llc-&gt;dec_step
op_assign
id|llc-&gt;connect_step
op_assign
l_int|1
suffix:semicolon
id|llc-&gt;ack_timer.expire
op_assign
id|LLC_ACK_TIME
suffix:semicolon
id|llc-&gt;ack_timer.timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|llc-&gt;ack_timer.timer.function
op_assign
id|llc_conn_ack_tmr_cb
suffix:semicolon
id|llc-&gt;pf_cycle_timer.expire
op_assign
id|LLC_P_TIME
suffix:semicolon
id|llc-&gt;pf_cycle_timer.timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|llc-&gt;pf_cycle_timer.timer.function
op_assign
id|llc_conn_pf_cycle_tmr_cb
suffix:semicolon
id|llc-&gt;rej_sent_timer.expire
op_assign
id|LLC_REJ_TIME
suffix:semicolon
id|llc-&gt;rej_sent_timer.timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|llc-&gt;rej_sent_timer.timer.function
op_assign
id|llc_conn_rej_tmr_cb
suffix:semicolon
id|llc-&gt;busy_state_timer.expire
op_assign
id|LLC_BUSY_TIME
suffix:semicolon
id|llc-&gt;busy_state_timer.timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|llc-&gt;busy_state_timer.timer.function
op_assign
id|llc_conn_busy_tmr_cb
suffix:semicolon
id|llc-&gt;n2
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* max retransmit */
id|llc-&gt;k
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* tx win size, will adjust dynam */
id|llc-&gt;rw
op_assign
l_int|128
suffix:semicolon
multiline_comment|/* rx win size (opt and equal to&n;&t;&t;        * tx_win of remote LLC) */
id|skb_queue_head_init
c_func
(paren
op_amp
id|llc-&gt;pdu_unack_q
)paren
suffix:semicolon
id|sk-&gt;backlog_rcv
op_assign
id|llc_backlog_rcv
suffix:semicolon
id|llc_sk
c_func
(paren
id|sk
)paren
op_assign
id|llc
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sk_alloc - Allocates LLC sock&n; *&t;@family: upper layer protocol family&n; *&t;@priority: for allocation (%GFP_KERNEL, %GFP_ATOMIC, etc)&n; *&n; *&t;Allocates a LLC sock and initializes it. Returns the new LLC sock&n; *&t;or %NULL if there&squot;s no memory available for one&n; */
DECL|function|llc_sk_alloc
r_struct
id|sock
op_star
id|llc_sk_alloc
c_func
(paren
r_int
id|family
comma
r_int
id|priority
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|sk_alloc
c_func
(paren
id|family
comma
id|priority
comma
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk
)paren
r_goto
id|decmod
suffix:semicolon
r_if
c_cond
(paren
id|llc_sk_init
c_func
(paren
id|sk
)paren
)paren
r_goto
id|outsk
suffix:semicolon
id|sock_init_data
c_func
(paren
l_int|NULL
comma
id|sk
)paren
suffix:semicolon
macro_line|#ifdef LLC_REFCNT_DEBUG
id|atomic_inc
c_func
(paren
op_amp
id|llc_sock_nr
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;LLC socket %p created in %s, now we have %d alive&bslash;n&quot;
comma
id|sk
comma
id|__FUNCTION__
comma
id|atomic_read
c_func
(paren
op_amp
id|llc_sock_nr
)paren
)paren
suffix:semicolon
macro_line|#endif
id|out
suffix:colon
r_return
id|sk
suffix:semicolon
id|outsk
suffix:colon
id|sk_free
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sk
op_assign
l_int|NULL
suffix:semicolon
id|decmod
suffix:colon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sk_free - Frees a LLC socket&n; *&t;@sk - socket to free&n; *&n; *&t;Frees a LLC socket&n; */
DECL|function|llc_sk_free
r_void
id|llc_sk_free
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|llc_opt
op_star
id|llc
op_assign
id|llc_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|llc-&gt;state
op_assign
id|LLC_CONN_OUT_OF_SVC
suffix:semicolon
multiline_comment|/* Stop all (possibly) running timers */
id|llc_conn_ac_stop_all_timers
c_func
(paren
id|sk
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_LLC_CONN_ALLOC
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: unackq=%d, txq=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|skb_queue_len
c_func
(paren
op_amp
id|llc-&gt;pdu_unack_q
)paren
comma
id|skb_queue_len
c_func
(paren
op_amp
id|sk-&gt;write_queue
)paren
)paren
suffix:semicolon
macro_line|#endif
id|skb_queue_purge
c_func
(paren
op_amp
id|sk-&gt;receive_queue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|sk-&gt;write_queue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|llc-&gt;pdu_unack_q
)paren
suffix:semicolon
macro_line|#ifdef LLC_REFCNT_DEBUG
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sk-&gt;refcnt
)paren
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Destruction of LLC sock %p delayed in %s, cnt=%d&bslash;n&quot;
comma
id|sk
comma
id|__FUNCTION__
comma
id|atomic_read
c_func
(paren
op_amp
id|sk-&gt;refcnt
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%d LLC sockets are still alive&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|llc_sock_nr
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|atomic_dec
c_func
(paren
op_amp
id|llc_sock_nr
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;LLC socket %p released in %s, %d are still alive&bslash;n&quot;
comma
id|sk
comma
id|__FUNCTION__
comma
id|atomic_read
c_func
(paren
op_amp
id|llc_sock_nr
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_sk_reset - resets a connection&n; *&t;@sk: LLC socket to reset&n; *&n; *&t;Resets a connection to the out of service state. Stops its timers&n; *&t;and frees any frames in the queues of the connection.&n; */
DECL|function|llc_sk_reset
r_void
id|llc_sk_reset
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|llc_opt
op_star
id|llc
op_assign
id|llc_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|llc_conn_ac_stop_all_timers
c_func
(paren
id|sk
comma
l_int|NULL
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|sk-&gt;write_queue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|llc-&gt;pdu_unack_q
)paren
suffix:semicolon
id|llc-&gt;remote_busy_flag
op_assign
l_int|0
suffix:semicolon
id|llc-&gt;cause_flag
op_assign
l_int|0
suffix:semicolon
id|llc-&gt;retry_count
op_assign
l_int|0
suffix:semicolon
id|llc_conn_set_p_flag
c_func
(paren
id|sk
comma
l_int|0
)paren
suffix:semicolon
id|llc-&gt;f_flag
op_assign
l_int|0
suffix:semicolon
id|llc-&gt;s_flag
op_assign
l_int|0
suffix:semicolon
id|llc-&gt;ack_pf
op_assign
l_int|0
suffix:semicolon
id|llc-&gt;first_pdu_Ns
op_assign
l_int|0
suffix:semicolon
id|llc-&gt;ack_must_be_send
op_assign
l_int|0
suffix:semicolon
id|llc-&gt;dec_step
op_assign
l_int|1
suffix:semicolon
id|llc-&gt;inc_cntr
op_assign
l_int|2
suffix:semicolon
id|llc-&gt;dec_cntr
op_assign
l_int|2
suffix:semicolon
id|llc-&gt;X
op_assign
l_int|0
suffix:semicolon
id|llc-&gt;failed_data_req
op_assign
l_int|0
suffix:semicolon
id|llc-&gt;last_nr
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_rtn_all_conns - Closes all connections of a sap&n; *&t;@sap: sap to close its connections&n; *&n; *&t;Closes all connections of a sap. Returns 0 if all actions complete&n; *&t;successfully, nonzero otherwise&n; */
DECL|function|llc_rtn_all_conns
r_static
r_int
id|llc_rtn_all_conns
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|sock
op_star
id|sk
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sk
op_assign
id|sap-&gt;sk_list.list
suffix:semicolon
id|sk
suffix:semicolon
id|sk
op_assign
id|sk-&gt;next
)paren
(brace
id|llc_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|state
op_assign
id|LLC_CONN_STATE_TEMP
suffix:semicolon
r_if
c_cond
(paren
id|llc_send_disc
c_func
(paren
id|sk
)paren
)paren
id|rc
op_assign
l_int|1
suffix:semicolon
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_station_get - get addr of global station.&n; *&n; *&t;Returns address of a place to copy the global station to it.&n; */
DECL|function|llc_station_get
r_struct
id|llc_station
op_star
id|llc_station_get
c_func
(paren
r_void
)paren
(brace
r_return
op_amp
id|llc_main_station
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
DECL|variable|llc_conn_state_names
r_static
r_char
op_star
id|llc_conn_state_names
(braket
)braket
op_assign
(brace
(braket
id|LLC_CONN_STATE_ADM
)braket
op_assign
l_string|&quot;adm&quot;
comma
(braket
id|LLC_CONN_STATE_SETUP
)braket
op_assign
l_string|&quot;setup&quot;
comma
(braket
id|LLC_CONN_STATE_NORMAL
)braket
op_assign
l_string|&quot;normal&quot;
comma
(braket
id|LLC_CONN_STATE_BUSY
)braket
op_assign
l_string|&quot;busy&quot;
comma
(braket
id|LLC_CONN_STATE_REJ
)braket
op_assign
l_string|&quot;rej&quot;
comma
(braket
id|LLC_CONN_STATE_AWAIT
)braket
op_assign
l_string|&quot;await&quot;
comma
(braket
id|LLC_CONN_STATE_AWAIT_BUSY
)braket
op_assign
l_string|&quot;await_busy&quot;
comma
(braket
id|LLC_CONN_STATE_AWAIT_REJ
)braket
op_assign
l_string|&quot;await_rej&quot;
comma
(braket
id|LLC_CONN_STATE_D_CONN
)braket
op_assign
l_string|&quot;d_conn&quot;
comma
(braket
id|LLC_CONN_STATE_RESET
)braket
op_assign
l_string|&quot;reset&quot;
comma
(braket
id|LLC_CONN_STATE_ERROR
)braket
op_assign
l_string|&quot;error&quot;
comma
(braket
id|LLC_CONN_STATE_TEMP
)braket
op_assign
l_string|&quot;temp&quot;
comma
)brace
suffix:semicolon
DECL|function|llc_proc_get_info
r_static
r_int
id|llc_proc_get_info
c_func
(paren
r_char
op_star
id|bf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
)paren
(brace
r_struct
id|list_head
op_star
id|sap_entry
suffix:semicolon
r_struct
id|sock
op_star
id|sk
suffix:semicolon
id|off_t
id|begin
op_assign
l_int|0
comma
id|pos
op_assign
l_int|0
suffix:semicolon
r_int
id|len
op_assign
l_int|0
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
id|sap_entry
comma
op_amp
id|llc_main_station.sap_list.list
)paren
(brace
r_struct
id|llc_sap
op_star
id|sap
op_assign
id|list_entry
c_func
(paren
id|sap_entry
comma
r_struct
id|llc_sap
comma
id|node
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|bf
op_plus
id|len
comma
l_string|&quot;lsap=%02X&bslash;n&quot;
comma
id|sap-&gt;laddr.lsap
)paren
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sap-&gt;sk_list.list
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|bf
op_plus
id|len
comma
l_string|&quot;no connections&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|unlock
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|bf
op_plus
id|len
comma
l_string|&quot;connection list:&bslash;n&quot;
l_string|&quot;dsap state      retr txw rxw &quot;
l_string|&quot;pf ff sf df rs cs &quot;
l_string|&quot;tack tpfc trs tbs blog busr&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sk
op_assign
id|sap-&gt;sk_list.list
suffix:semicolon
id|sk
suffix:semicolon
id|sk
op_assign
id|sk-&gt;next
)paren
(brace
r_struct
id|llc_opt
op_star
id|llc
op_assign
id|llc_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|bf
op_plus
id|len
comma
l_string|&quot; %02X  %-10s %3d  %3d %3d &quot;
l_string|&quot;%2d %2d %2d &quot;
l_string|&quot;%2d %2d %2d &quot;
l_string|&quot;%4d %4d %3d %3d %4d %4d&bslash;n&quot;
comma
id|llc-&gt;daddr.lsap
comma
id|llc_conn_state_names
(braket
id|llc-&gt;state
)braket
comma
id|llc-&gt;retry_count
comma
id|llc-&gt;k
comma
id|llc-&gt;rw
comma
id|llc-&gt;p_flag
comma
id|llc-&gt;f_flag
comma
id|llc-&gt;s_flag
comma
id|llc-&gt;data_flag
comma
id|llc-&gt;remote_busy_flag
comma
id|llc-&gt;cause_flag
comma
id|timer_pending
c_func
(paren
op_amp
id|llc-&gt;ack_timer.timer
)paren
comma
id|timer_pending
c_func
(paren
op_amp
id|llc-&gt;pf_cycle_timer.timer
)paren
comma
id|timer_pending
c_func
(paren
op_amp
id|llc-&gt;rej_sent_timer.timer
)paren
comma
id|timer_pending
c_func
(paren
op_amp
id|llc-&gt;busy_state_timer.timer
)paren
comma
op_logical_neg
op_logical_neg
id|sk-&gt;backlog.tail
comma
id|sk-&gt;lock.users
)paren
suffix:semicolon
)brace
id|unlock
suffix:colon
id|read_unlock_bh
c_func
(paren
op_amp
id|sap-&gt;sk_list.lock
)paren
suffix:semicolon
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Keep dumping into the buffer start */
id|begin
op_assign
id|pos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OG
id|offset
op_plus
id|length
)paren
multiline_comment|/* We have dumped enough */
r_break
suffix:semicolon
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|llc_main_station.sap_list.lock
)paren
suffix:semicolon
multiline_comment|/* The data in question runs from begin to begin + len */
op_star
id|start
op_assign
id|bf
op_plus
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
multiline_comment|/* Start of wanted data */
id|len
op_sub_assign
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
multiline_comment|/* Remove unwanted header data from length */
r_return
id|len
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
id|llc_banner
(braket
)braket
id|__initdata
op_assign
id|KERN_INFO
l_string|&quot;LLC 2.0 by Procom, 1997, Arnaldo C. Melo, 2001, 2002&bslash;n&quot;
id|KERN_INFO
l_string|&quot;NET 4.0 IEEE 802.2 extended support&bslash;n&quot;
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
id|printk
c_func
(paren
id|llc_banner
)paren
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
id|llc_build_offset_table
c_func
(paren
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
id|proc_net_create
c_func
(paren
l_string|&quot;802.2&quot;
comma
l_int|0
comma
id|llc_proc_get_info
)paren
suffix:semicolon
id|llc_ui_init
c_func
(paren
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
id|llc_ui_exit
c_func
(paren
)paren
suffix:semicolon
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
id|proc_net_remove
c_func
(paren
l_string|&quot;802.2&quot;
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Procom, 1997, Arnaldo C. Melo, Jay Schullist, 2001, 2002&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;LLC 2.0, NET4.0 IEEE 802.2 extended support&quot;
)paren
suffix:semicolon
eof
