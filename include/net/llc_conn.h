macro_line|#ifndef LLC_CONN_H
DECL|macro|LLC_CONN_H
mdefine_line|#define LLC_CONN_H
multiline_comment|/*&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; * &t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;net/llc_if.h&gt;
DECL|macro|DEBUG_LLC_CONN_ALLOC
macro_line|#undef DEBUG_LLC_CONN_ALLOC
DECL|struct|llc_timer
r_struct
id|llc_timer
(brace
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|running
id|u8
id|running
suffix:semicolon
multiline_comment|/* timer is running or no */
DECL|member|expire
id|u16
id|expire
suffix:semicolon
multiline_comment|/* timer expire time */
)brace
suffix:semicolon
DECL|struct|llc_opt
r_struct
id|llc_opt
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
multiline_comment|/* entry in sap-&gt;sk_list.list */
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
multiline_comment|/* sock that has this llc_opt */
DECL|member|handler
r_void
op_star
id|handler
suffix:semicolon
multiline_comment|/* for upper layers usage */
DECL|member|state
id|u8
id|state
suffix:semicolon
multiline_comment|/* state of connection */
DECL|member|sap
r_struct
id|llc_sap
op_star
id|sap
suffix:semicolon
multiline_comment|/* pointer to parent SAP */
DECL|member|laddr
r_struct
id|llc_addr
id|laddr
suffix:semicolon
multiline_comment|/* lsap/mac pair */
DECL|member|daddr
r_struct
id|llc_addr
id|daddr
suffix:semicolon
multiline_comment|/* dsap/mac pair */
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* device to send to remote */
DECL|member|retry_count
id|u8
id|retry_count
suffix:semicolon
multiline_comment|/* number of retries */
DECL|member|ack_must_be_send
id|u8
id|ack_must_be_send
suffix:semicolon
DECL|member|first_pdu_Ns
id|u8
id|first_pdu_Ns
suffix:semicolon
DECL|member|npta
id|u8
id|npta
suffix:semicolon
DECL|member|ack_timer
r_struct
id|llc_timer
id|ack_timer
suffix:semicolon
DECL|member|pf_cycle_timer
r_struct
id|llc_timer
id|pf_cycle_timer
suffix:semicolon
DECL|member|rej_sent_timer
r_struct
id|llc_timer
id|rej_sent_timer
suffix:semicolon
DECL|member|busy_state_timer
r_struct
id|llc_timer
id|busy_state_timer
suffix:semicolon
multiline_comment|/* ind busy clr at remote LLC */
DECL|member|vS
id|u8
id|vS
suffix:semicolon
multiline_comment|/* seq# next in-seq I-PDU tx&squot;d*/
DECL|member|vR
id|u8
id|vR
suffix:semicolon
multiline_comment|/* seq# next in-seq I-PDU rx&squot;d*/
DECL|member|n2
id|u32
id|n2
suffix:semicolon
multiline_comment|/* max nbr re-tx&squot;s for timeout*/
DECL|member|n1
id|u32
id|n1
suffix:semicolon
multiline_comment|/* max nbr octets in I PDU */
DECL|member|k
id|u8
id|k
suffix:semicolon
multiline_comment|/* tx window size; max = 127 */
DECL|member|rw
id|u8
id|rw
suffix:semicolon
multiline_comment|/* rx window size; max = 127 */
DECL|member|p_flag
id|u8
id|p_flag
suffix:semicolon
multiline_comment|/* state flags */
DECL|member|f_flag
id|u8
id|f_flag
suffix:semicolon
DECL|member|s_flag
id|u8
id|s_flag
suffix:semicolon
DECL|member|data_flag
id|u8
id|data_flag
suffix:semicolon
DECL|member|remote_busy_flag
id|u8
id|remote_busy_flag
suffix:semicolon
DECL|member|cause_flag
id|u8
id|cause_flag
suffix:semicolon
DECL|member|pdu_unack_q
r_struct
id|sk_buff_head
id|pdu_unack_q
suffix:semicolon
multiline_comment|/* PUDs sent/waiting ack */
DECL|member|link
id|u16
id|link
suffix:semicolon
multiline_comment|/* network layer link number */
DECL|member|X
id|u8
id|X
suffix:semicolon
multiline_comment|/* a temporary variable */
DECL|member|ack_pf
id|u8
id|ack_pf
suffix:semicolon
multiline_comment|/* this flag indicates what is&n;&t;&t;&t;&t;&t;&t;   the P-bit of acknowledge */
DECL|member|failed_data_req
id|u8
id|failed_data_req
suffix:semicolon
multiline_comment|/* recognize that already exist a&n;&t;&t;&t;&t;&t;&t;failed llc_data_req_handler&n;&t;&t;&t;&t;&t;&t;(tx_buffer_full or unacceptable&n;&t;&t;&t;&t;&t;&t;state */
DECL|member|dec_step
id|u8
id|dec_step
suffix:semicolon
DECL|member|inc_cntr
id|u8
id|inc_cntr
suffix:semicolon
DECL|member|dec_cntr
id|u8
id|dec_cntr
suffix:semicolon
DECL|member|connect_step
id|u8
id|connect_step
suffix:semicolon
DECL|member|last_nr
id|u8
id|last_nr
suffix:semicolon
multiline_comment|/* NR of last pdu recieved */
DECL|member|rx_pdu_hdr
id|u32
id|rx_pdu_hdr
suffix:semicolon
multiline_comment|/* used for saving header of last pdu&n;&t;&t;&t;&t;&t;      received and caused sending FRMR.&n;&t;&t;&t;&t;&t;      Used for resending FRMR */
macro_line|#ifdef DEBUG_LLC_CONN_ALLOC
DECL|member|f_alloc
r_char
op_star
id|f_alloc
comma
multiline_comment|/* function that allocated this connection */
DECL|member|f_free
op_star
id|f_free
suffix:semicolon
multiline_comment|/* function that freed this connection */
DECL|member|l_alloc
r_int
id|l_alloc
comma
multiline_comment|/* line that allocated this connection */
DECL|member|l_free
id|l_free
suffix:semicolon
multiline_comment|/* line that freed this connection */
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|llc_sk
mdefine_line|#define llc_sk(__sk) ((struct llc_opt *)(__sk)-&gt;protinfo)
r_struct
id|llc_conn_state_ev
suffix:semicolon
r_extern
r_struct
id|sock
op_star
id|__llc_sock_alloc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__llc_sock_free
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
id|u8
id|free
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_LLC_CONN_ALLOC
DECL|macro|dump_stack
mdefine_line|#define dump_stack() printk(KERN_INFO &quot;call trace: %p, %p, %p&bslash;n&quot;,&t;&bslash;&n;&t;&t;&t;&t;__builtin_return_address(0),&t;&t;&bslash;&n;&t;&t;&t;&t;__builtin_return_address(1),&t;&t;&bslash;&n;&t;&t;&t;&t;__builtin_return_address(2));
DECL|macro|llc_sock_alloc
mdefine_line|#define llc_sock_alloc()&t;({&t;&t;&t;&t;&t;&bslash;&n;&t;struct sock *__sk = __llc_sock_alloc();&t;&t;&t;&t;&bslash;&n;&t;if (__sk) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;llc_sk(__sk)-&gt;f_alloc = __FUNCTION__;&t;&t;&t;&bslash;&n;&t;&t;llc_sk(__sk)-&gt;l_alloc = __LINE__;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__sk;})
DECL|macro|__llc_sock_assert
mdefine_line|#define __llc_sock_assert(__sk)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (llc_sk(__sk)-&gt;f_free) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;printk(KERN_ERR&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;%p conn (alloc&squot;d @ %s(%d)) &quot;&t;&t;&t;&bslash;&n;&t;&t;       &quot;already freed @ %s(%d) &quot;&t;&t;&t;&bslash;&n;&t;&t;       &quot;being used again @ %s(%d)&bslash;n&quot;,&t;&t;&t;&bslash;&n;&t;&t;       llc_sk(__sk),&t;&t;&t;&t;&t;&bslash;&n;&t;&t;       llc_sk(__sk)-&gt;f_alloc, llc_sk(__sk)-&gt;l_alloc,&t;&bslash;&n;&t;&t;       llc_sk(__sk)-&gt;f_free, llc_sk(__sk)-&gt;l_free,&t;&bslash;&n;&t;&t;       __FUNCTION__, __LINE__);&t;&t;&t;&t;&bslash;&n;&t;&t;dump_stack();
DECL|macro|llc_sock_free
mdefine_line|#define llc_sock_free(__sk)&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__llc_sock_assert(__sk)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__llc_sock_free(__sk, 0);&t;&t;&t;&t;&bslash;&n;&t;&t;llc_sk(__sk)-&gt;f_free = __FUNCTION__;&t;&t;&t;&bslash;&n;&t;&t;llc_sk(__sk)-&gt;l_free = __LINE__;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|llc_sock_assert
mdefine_line|#define llc_sock_assert(__sk)&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__llc_sock_assert(__sk);&t;&t;&t;&t;&t;&bslash;&n;&t;return; }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|llc_sock_assert_ret
mdefine_line|#define llc_sock_assert_ret(__sk, __ret)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__llc_sock_assert(__sk);&t;&t;&t;&t;&t;&bslash;&n;&t;return __ret; }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#else /* DEBUG_LLC_CONN_ALLOC */
DECL|macro|llc_sock_alloc
mdefine_line|#define llc_sock_alloc() __llc_sock_alloc()
DECL|macro|llc_sock_free
mdefine_line|#define llc_sock_free(__sk) __llc_sock_free(__sk, 1)
DECL|macro|llc_sock_assert
mdefine_line|#define llc_sock_assert(__sk)
DECL|macro|llc_sock_assert_ret
mdefine_line|#define llc_sock_assert_ret(__sk)
macro_line|#endif /* DEBUG_LLC_CONN_ALLOC */
r_extern
r_void
id|llc_sock_reset
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_int
id|llc_sock_init
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
multiline_comment|/* Access to a connection */
r_extern
r_struct
id|llc_conn_state_ev
op_star
id|llc_conn_alloc_ev
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_int
id|llc_conn_send_ev
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|llc_conn_state_ev
op_star
id|ev
)paren
suffix:semicolon
r_extern
r_void
id|llc_conn_send_pdu
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
r_void
id|llc_conn_rtn_pdu
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
comma
r_struct
id|llc_conn_state_ev
op_star
id|ev
)paren
suffix:semicolon
r_extern
r_void
id|llc_conn_free_ev
c_func
(paren
r_struct
id|llc_conn_state_ev
op_star
id|ev
)paren
suffix:semicolon
r_extern
r_void
id|llc_conn_resend_i_pdu_as_cmd
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
id|u8
id|nr
comma
id|u8
id|first_p_bit
)paren
suffix:semicolon
r_extern
r_void
id|llc_conn_resend_i_pdu_as_rsp
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
id|u8
id|nr
comma
id|u8
id|first_f_bit
)paren
suffix:semicolon
r_extern
r_int
id|llc_conn_remove_acked_pdus
c_func
(paren
r_struct
id|sock
op_star
id|conn
comma
id|u8
id|nr
comma
id|u16
op_star
id|how_many_unacked
)paren
suffix:semicolon
r_extern
r_struct
id|sock
op_star
id|llc_find_sock
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|llc_addr
op_star
id|daddr
comma
r_struct
id|llc_addr
op_star
id|laddr
)paren
suffix:semicolon
r_extern
id|u8
id|llc_data_accept_state
c_func
(paren
id|u8
id|state
)paren
suffix:semicolon
r_extern
r_void
id|llc_build_offset_table
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* LLC_CONN_H */
eof
