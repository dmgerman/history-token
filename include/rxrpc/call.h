multiline_comment|/* call.h: Rx call record&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_RXRPC_CALL_H
DECL|macro|_LINUX_RXRPC_CALL_H
mdefine_line|#define _LINUX_RXRPC_CALL_H
macro_line|#include &lt;rxrpc/types.h&gt;
macro_line|#include &lt;rxrpc/rxrpc.h&gt;
macro_line|#include &lt;rxrpc/packet.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
DECL|macro|RXRPC_CALL_ACK_WINDOW_SIZE
mdefine_line|#define RXRPC_CALL_ACK_WINDOW_SIZE&t;16
r_extern
r_int
id|rxrpc_call_rcv_timeout
suffix:semicolon
multiline_comment|/* receive activity timeout (secs) */
multiline_comment|/* application call state&n; * - only state 0 and ffff are reserved, the state is set to 1 after an opid is received&n; */
DECL|enum|rxrpc_app_cstate
r_enum
id|rxrpc_app_cstate
(brace
DECL|enumerator|RXRPC_CSTATE_COMPLETE
id|RXRPC_CSTATE_COMPLETE
op_assign
l_int|0
comma
multiline_comment|/* operation complete */
DECL|enumerator|RXRPC_CSTATE_ERROR
id|RXRPC_CSTATE_ERROR
comma
multiline_comment|/* operation ICMP error or aborted */
DECL|enumerator|RXRPC_CSTATE_SRVR_RCV_OPID
id|RXRPC_CSTATE_SRVR_RCV_OPID
comma
multiline_comment|/* [SERVER] receiving operation ID */
DECL|enumerator|RXRPC_CSTATE_SRVR_RCV_ARGS
id|RXRPC_CSTATE_SRVR_RCV_ARGS
comma
multiline_comment|/* [SERVER] receiving operation data */
DECL|enumerator|RXRPC_CSTATE_SRVR_GOT_ARGS
id|RXRPC_CSTATE_SRVR_GOT_ARGS
comma
multiline_comment|/* [SERVER] completely received operation data */
DECL|enumerator|RXRPC_CSTATE_SRVR_SND_REPLY
id|RXRPC_CSTATE_SRVR_SND_REPLY
comma
multiline_comment|/* [SERVER] sending operation reply */
DECL|enumerator|RXRPC_CSTATE_SRVR_RCV_FINAL_ACK
id|RXRPC_CSTATE_SRVR_RCV_FINAL_ACK
comma
multiline_comment|/* [SERVER] receiving final ACK */
DECL|enumerator|RXRPC_CSTATE_CLNT_SND_ARGS
id|RXRPC_CSTATE_CLNT_SND_ARGS
comma
multiline_comment|/* [CLIENT] sending operation args */
DECL|enumerator|RXRPC_CSTATE_CLNT_RCV_REPLY
id|RXRPC_CSTATE_CLNT_RCV_REPLY
comma
multiline_comment|/* [CLIENT] receiving operation reply */
DECL|enumerator|RXRPC_CSTATE_CLNT_GOT_REPLY
id|RXRPC_CSTATE_CLNT_GOT_REPLY
comma
multiline_comment|/* [CLIENT] completely received operation reply */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|rxrpc_call_states
(braket
)braket
suffix:semicolon
DECL|enum|rxrpc_app_estate
r_enum
id|rxrpc_app_estate
(brace
DECL|enumerator|RXRPC_ESTATE_NO_ERROR
id|RXRPC_ESTATE_NO_ERROR
op_assign
l_int|0
comma
multiline_comment|/* no error */
DECL|enumerator|RXRPC_ESTATE_LOCAL_ABORT
id|RXRPC_ESTATE_LOCAL_ABORT
comma
multiline_comment|/* aborted locally by application layer */
DECL|enumerator|RXRPC_ESTATE_PEER_ABORT
id|RXRPC_ESTATE_PEER_ABORT
comma
multiline_comment|/* aborted remotely by peer */
DECL|enumerator|RXRPC_ESTATE_LOCAL_ERROR
id|RXRPC_ESTATE_LOCAL_ERROR
comma
multiline_comment|/* local ICMP network error */
DECL|enumerator|RXRPC_ESTATE_REMOTE_ERROR
id|RXRPC_ESTATE_REMOTE_ERROR
comma
multiline_comment|/* remote ICMP network error */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|rxrpc_call_error_states
(braket
)braket
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Rx call record and application scratch buffer&n; * - the call record occupies the bottom of a complete page&n; * - the application scratch buffer occupies the rest&n; */
DECL|struct|rxrpc_call
r_struct
id|rxrpc_call
(brace
DECL|member|usage
id|atomic_t
id|usage
suffix:semicolon
DECL|member|conn
r_struct
id|rxrpc_connection
op_star
id|conn
suffix:semicolon
multiline_comment|/* connection upon which active */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* access lock */
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
multiline_comment|/* owner module */
DECL|member|waitq
id|wait_queue_head_t
id|waitq
suffix:semicolon
multiline_comment|/* wait queue for events to happen */
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
multiline_comment|/* general internal list link */
DECL|member|call_link
r_struct
id|list_head
id|call_link
suffix:semicolon
multiline_comment|/* master call list link */
DECL|member|chan_ix
id|__be32
id|chan_ix
suffix:semicolon
multiline_comment|/* connection channel index  */
DECL|member|call_id
id|__be32
id|call_id
suffix:semicolon
multiline_comment|/* call ID on connection  */
DECL|member|cjif
r_int
r_int
id|cjif
suffix:semicolon
multiline_comment|/* jiffies at call creation */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* control flags */
DECL|macro|RXRPC_CALL_ACKS_TIMO
mdefine_line|#define RXRPC_CALL_ACKS_TIMO&t;0x00000001&t;/* ACKS timeout reached */
DECL|macro|RXRPC_CALL_ACKR_TIMO
mdefine_line|#define RXRPC_CALL_ACKR_TIMO&t;0x00000002&t;/* ACKR timeout reached */
DECL|macro|RXRPC_CALL_RCV_TIMO
mdefine_line|#define RXRPC_CALL_RCV_TIMO&t;0x00000004&t;/* RCV timeout reached */
DECL|macro|RXRPC_CALL_RCV_PKT
mdefine_line|#define RXRPC_CALL_RCV_PKT&t;0x00000008&t;/* received packet */
multiline_comment|/* transmission */
DECL|member|snd_seq_count
id|rxrpc_seq_t
id|snd_seq_count
suffix:semicolon
multiline_comment|/* outgoing packet sequence number counter */
DECL|member|snd_nextmsg
r_struct
id|rxrpc_message
op_star
id|snd_nextmsg
suffix:semicolon
multiline_comment|/* next message being constructed for sending */
DECL|member|snd_ping
r_struct
id|rxrpc_message
op_star
id|snd_ping
suffix:semicolon
multiline_comment|/* last ping message sent */
DECL|member|snd_resend_cnt
r_int
r_int
id|snd_resend_cnt
suffix:semicolon
multiline_comment|/* count of resends since last ACK */
multiline_comment|/* transmission ACK tracking */
DECL|member|acks_pendq
r_struct
id|list_head
id|acks_pendq
suffix:semicolon
multiline_comment|/* messages pending ACK (ordered by seq) */
DECL|member|acks_pend_cnt
r_int
id|acks_pend_cnt
suffix:semicolon
multiline_comment|/* number of un-ACK&squot;d packets */
DECL|member|acks_dftv_seq
id|rxrpc_seq_t
id|acks_dftv_seq
suffix:semicolon
multiline_comment|/* highest definitively ACK&squot;d msg seq */
DECL|member|acks_timeout
r_struct
id|timer_list
id|acks_timeout
suffix:semicolon
multiline_comment|/* timeout on expected ACK */
multiline_comment|/* reception */
DECL|member|rcv_receiveq
r_struct
id|list_head
id|rcv_receiveq
suffix:semicolon
multiline_comment|/* messages pending reception (ordered by seq) */
DECL|member|rcv_krxiodq_lk
r_struct
id|list_head
id|rcv_krxiodq_lk
suffix:semicolon
multiline_comment|/* krxiod queue for new inbound packets */
DECL|member|rcv_timeout
r_struct
id|timer_list
id|rcv_timeout
suffix:semicolon
multiline_comment|/* call receive activity timeout */
multiline_comment|/* reception ACK&squot;ing */
DECL|member|ackr_win_bot
id|rxrpc_seq_t
id|ackr_win_bot
suffix:semicolon
multiline_comment|/* bottom of ACK window */
DECL|member|ackr_win_top
id|rxrpc_seq_t
id|ackr_win_top
suffix:semicolon
multiline_comment|/* top of ACK window */
DECL|member|ackr_high_seq
id|rxrpc_seq_t
id|ackr_high_seq
suffix:semicolon
multiline_comment|/* highest seqno yet received */
DECL|member|ackr_prev_seq
id|rxrpc_seq_net_t
id|ackr_prev_seq
suffix:semicolon
multiline_comment|/* previous seqno received */
DECL|member|ackr_pend_cnt
r_int
id|ackr_pend_cnt
suffix:semicolon
multiline_comment|/* number of pending ACKs */
DECL|member|ackr_dfr_timo
r_struct
id|timer_list
id|ackr_dfr_timo
suffix:semicolon
multiline_comment|/* timeout on deferred ACK */
DECL|member|ackr_dfr_perm
r_char
id|ackr_dfr_perm
suffix:semicolon
multiline_comment|/* request for deferred ACKs permitted */
DECL|member|ackr_dfr_seq
id|rxrpc_seq_t
id|ackr_dfr_seq
suffix:semicolon
multiline_comment|/* seqno for deferred ACK */
DECL|member|ackr
r_struct
id|rxrpc_ackpacket
id|ackr
suffix:semicolon
multiline_comment|/* pending normal ACK packet */
DECL|member|ackr_array
r_uint8
id|ackr_array
(braket
id|RXRPC_CALL_ACK_WINDOW_SIZE
)braket
suffix:semicolon
multiline_comment|/* ACK records */
multiline_comment|/* presentation layer */
DECL|member|app_last_rcv
r_char
id|app_last_rcv
suffix:semicolon
multiline_comment|/* T if received last packet from remote end */
DECL|member|app_call_state
r_enum
id|rxrpc_app_cstate
id|app_call_state
suffix:semicolon
multiline_comment|/* call state */
DECL|member|app_err_state
r_enum
id|rxrpc_app_estate
id|app_err_state
suffix:semicolon
multiline_comment|/* abort/error state */
DECL|member|app_readyq
r_struct
id|list_head
id|app_readyq
suffix:semicolon
multiline_comment|/* ordered ready received packet queue */
DECL|member|app_unreadyq
r_struct
id|list_head
id|app_unreadyq
suffix:semicolon
multiline_comment|/* ordered post-hole recv&squot;d packet queue */
DECL|member|app_ready_seq
id|rxrpc_seq_t
id|app_ready_seq
suffix:semicolon
multiline_comment|/* last seq number dropped into readyq */
DECL|member|app_ready_qty
r_int
id|app_ready_qty
suffix:semicolon
multiline_comment|/* amount of data ready in readyq */
DECL|member|app_opcode
r_int
id|app_opcode
suffix:semicolon
multiline_comment|/* operation ID */
DECL|member|app_abort_code
r_int
id|app_abort_code
suffix:semicolon
multiline_comment|/* abort code (when aborted) */
DECL|member|app_errno
r_int
id|app_errno
suffix:semicolon
multiline_comment|/* error number (when ICMP error received) */
multiline_comment|/* statisics */
DECL|member|pkt_rcv_count
r_int
id|pkt_rcv_count
suffix:semicolon
multiline_comment|/* count of received packets on this call */
DECL|member|pkt_snd_count
r_int
id|pkt_snd_count
suffix:semicolon
multiline_comment|/* count of sent packets on this call */
DECL|member|app_read_count
r_int
id|app_read_count
suffix:semicolon
multiline_comment|/* number of reads issued */
multiline_comment|/* bits for the application to use */
DECL|member|app_attn_func
id|rxrpc_call_attn_func_t
id|app_attn_func
suffix:semicolon
multiline_comment|/* callback when attention required */
DECL|member|app_error_func
id|rxrpc_call_error_func_t
id|app_error_func
suffix:semicolon
multiline_comment|/* callback when abort sent (cleanup and put) */
DECL|member|app_aemap_func
id|rxrpc_call_aemap_func_t
id|app_aemap_func
suffix:semicolon
multiline_comment|/* callback to map abort code to/from errno */
DECL|member|app_user
r_void
op_star
id|app_user
suffix:semicolon
multiline_comment|/* application data */
DECL|member|app_link
r_struct
id|list_head
id|app_link
suffix:semicolon
multiline_comment|/* application list linkage */
DECL|member|app_attn_link
r_struct
id|list_head
id|app_attn_link
suffix:semicolon
multiline_comment|/* application attention list linkage */
DECL|member|app_mark
r_int
id|app_mark
suffix:semicolon
multiline_comment|/* trigger callback when app_ready_qty&gt;=app_mark */
DECL|member|app_async_read
r_char
id|app_async_read
suffix:semicolon
multiline_comment|/* T if in async-read mode */
DECL|member|app_read_buf
r_uint8
op_star
id|app_read_buf
suffix:semicolon
multiline_comment|/* application async read buffer (app_mark size) */
DECL|member|app_scr_alloc
r_uint8
op_star
id|app_scr_alloc
suffix:semicolon
multiline_comment|/* application scratch allocation pointer */
DECL|member|app_scr_ptr
r_void
op_star
id|app_scr_ptr
suffix:semicolon
multiline_comment|/* application pointer into scratch buffer */
DECL|macro|RXRPC_APP_MARK_EOF
mdefine_line|#define RXRPC_APP_MARK_EOF 0xFFFFFFFFU&t;/* mark at end of input */
multiline_comment|/* application scratch buffer */
DECL|member|app_scratch
r_uint8
id|app_scratch
(braket
l_int|0
)braket
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
r_sizeof
(paren
r_int
)paren
)paren
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RXRPC_CALL_SCRATCH_SIZE
mdefine_line|#define RXRPC_CALL_SCRATCH_SIZE (PAGE_SIZE - sizeof(struct rxrpc_call))
DECL|macro|rxrpc_call_reset_scratch
mdefine_line|#define rxrpc_call_reset_scratch(CALL) &bslash;&n;do { (CALL)-&gt;app_scr_alloc = (CALL)-&gt;app_scratch; } while(0)
DECL|macro|rxrpc_call_alloc_scratch
mdefine_line|#define rxrpc_call_alloc_scratch(CALL,SIZE)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;void *ptr;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ptr = (CALL)-&gt;app_scr_alloc;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(CALL)-&gt;app_scr_alloc += (SIZE);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((SIZE)&gt;RXRPC_CALL_SCRATCH_SIZE ||&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    (size_t)((CALL)-&gt;app_scr_alloc - (u8*)(CALL)) &gt; RXRPC_CALL_SCRATCH_SIZE) {&t;&bslash;&n;&t;&t;printk(&quot;rxrpc_call_alloc_scratch(%p,%Zu)&bslash;n&quot;,(CALL),(size_t)(SIZE));&t;&bslash;&n;&t;&t;BUG();&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ptr;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|rxrpc_call_alloc_scratch_s
mdefine_line|#define rxrpc_call_alloc_scratch_s(CALL,TYPE)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;size_t size = sizeof(TYPE);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;TYPE *ptr;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ptr = (TYPE*)(CALL)-&gt;app_scr_alloc;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(CALL)-&gt;app_scr_alloc += size;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (size&gt;RXRPC_CALL_SCRATCH_SIZE ||&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    (size_t)((CALL)-&gt;app_scr_alloc - (u8*)(CALL)) &gt; RXRPC_CALL_SCRATCH_SIZE) {&t;&bslash;&n;&t;&t;printk(&quot;rxrpc_call_alloc_scratch(%p,%Zu)&bslash;n&quot;,(CALL),size);&t;&t;&bslash;&n;&t;&t;BUG();&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ptr;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|rxrpc_call_is_ack_pending
mdefine_line|#define rxrpc_call_is_ack_pending(CALL) ((CALL)-&gt;ackr.reason != 0)
r_extern
r_int
id|rxrpc_create_call
c_func
(paren
r_struct
id|rxrpc_connection
op_star
id|conn
comma
id|rxrpc_call_attn_func_t
id|attn
comma
id|rxrpc_call_error_func_t
id|error
comma
id|rxrpc_call_aemap_func_t
id|aemap
comma
r_struct
id|rxrpc_call
op_star
op_star
id|_call
)paren
suffix:semicolon
r_extern
r_int
id|rxrpc_incoming_call
c_func
(paren
r_struct
id|rxrpc_connection
op_star
id|conn
comma
r_struct
id|rxrpc_message
op_star
id|msg
comma
r_struct
id|rxrpc_call
op_star
op_star
id|_call
)paren
suffix:semicolon
DECL|function|rxrpc_get_call
r_static
r_inline
r_void
id|rxrpc_get_call
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
(brace
id|BUG_ON
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|call-&gt;usage
)paren
op_le
l_int|0
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|call-&gt;usage
)paren
suffix:semicolon
multiline_comment|/*printk(&quot;rxrpc_get_call(%p{u=%d})&bslash;n&quot;,(C),atomic_read(&amp;(C)-&gt;usage));*/
)brace
r_extern
r_void
id|rxrpc_put_call
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
r_extern
r_void
id|rxrpc_call_do_stuff
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
r_extern
r_int
id|rxrpc_call_abort
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
comma
r_int
id|error
)paren
suffix:semicolon
DECL|macro|RXRPC_CALL_READ_BLOCK
mdefine_line|#define RXRPC_CALL_READ_BLOCK&t;0x0001&t;/* block if not enough data and not yet EOF */
DECL|macro|RXRPC_CALL_READ_ALL
mdefine_line|#define RXRPC_CALL_READ_ALL&t;0x0002&t;/* error if insufficient data received */
r_extern
r_int
id|rxrpc_call_read_data
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
comma
r_void
op_star
id|buffer
comma
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_int
id|rxrpc_call_write_data
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
comma
r_int
id|sioc
comma
r_struct
id|kvec
op_star
id|siov
comma
r_uint8
id|rxhdr_flags
comma
r_int
id|alloc_flags
comma
r_int
id|dup_data
comma
r_int
op_star
id|size_sent
)paren
suffix:semicolon
r_extern
r_void
id|rxrpc_call_handle_error
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|conn
comma
r_int
id|local
comma
r_int
id|errno
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_RXRPC_CALL_H */
eof
