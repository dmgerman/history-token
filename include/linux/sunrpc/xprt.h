multiline_comment|/*&n; *  linux/include/linux/sunrpc/clnt_xprt.h&n; *&n; *  Declarations for the RPC transport interface.&n; *&n; *  Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef _LINUX_SUNRPC_XPRT_H
DECL|macro|_LINUX_SUNRPC_XPRT_H
mdefine_line|#define _LINUX_SUNRPC_XPRT_H
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/sunrpc/sched.h&gt;
multiline_comment|/*&n; * Maximum number of iov&squot;s we use.&n; */
DECL|macro|MAX_IOVEC
mdefine_line|#define MAX_IOVEC&t;10
multiline_comment|/*&n; * The transport code maintains an estimate on the maximum number of out-&n; * standing RPC requests, using a smoothed version of the congestion&n; * avoidance implemented in 44BSD. This is basically the Van Jacobson&n; * slow start algorithm: If a retransmit occurs, the congestion window is&n; * halved; otherwise, it is incremented by 1/cwnd when&n; *&n; *&t;-&t;a reply is received and&n; *&t;-&t;a full number of requests are outstanding and&n; *&t;-&t;the congestion window hasn&squot;t been updated recently.&n; *&n; * Upper procedures may check whether a request would block waiting for&n; * a free RPC slot by using the RPC_CONGESTED() macro.&n; *&n; * Note: on machines with low memory we should probably use a smaller&n; * MAXREQS value: At 32 outstanding reqs with 8 megs of RAM, fragment&n; * reassembly will frequently run out of memory.&n; * Come Linux 2.3, we&squot;ll handle fragments directly.&n; */
DECL|macro|RPC_MAXCONG
mdefine_line|#define RPC_MAXCONG&t;&t;16
DECL|macro|RPC_MAXREQS
mdefine_line|#define RPC_MAXREQS&t;&t;(RPC_MAXCONG + 1)
DECL|macro|RPC_CWNDSCALE
mdefine_line|#define RPC_CWNDSCALE&t;&t;256
DECL|macro|RPC_MAXCWND
mdefine_line|#define RPC_MAXCWND&t;&t;(RPC_MAXCONG * RPC_CWNDSCALE)
DECL|macro|RPC_INITCWND
mdefine_line|#define RPC_INITCWND&t;&t;RPC_CWNDSCALE
DECL|macro|RPCXPRT_CONGESTED
mdefine_line|#define RPCXPRT_CONGESTED(xprt) &bslash;&n;&t;((xprt)-&gt;cong &gt;= (xprt)-&gt;cwnd)
multiline_comment|/* Default timeout values */
DECL|macro|RPC_MAX_UDP_TIMEOUT
mdefine_line|#define RPC_MAX_UDP_TIMEOUT&t;(60*HZ)
DECL|macro|RPC_MAX_TCP_TIMEOUT
mdefine_line|#define RPC_MAX_TCP_TIMEOUT&t;(600*HZ)
multiline_comment|/* RPC call and reply header size as number of 32bit words (verifier&n; * size computed separately)&n; */
DECL|macro|RPC_CALLHDRSIZE
mdefine_line|#define RPC_CALLHDRSIZE&t;&t;6
DECL|macro|RPC_REPHDRSIZE
mdefine_line|#define RPC_REPHDRSIZE&t;&t;4
multiline_comment|/*&n; * This describes a timeout strategy&n; */
DECL|struct|rpc_timeout
r_struct
id|rpc_timeout
(brace
DECL|member|to_current
r_int
r_int
id|to_current
comma
multiline_comment|/* current timeout */
DECL|member|to_initval
id|to_initval
comma
multiline_comment|/* initial timeout */
DECL|member|to_maxval
id|to_maxval
comma
multiline_comment|/* max timeout */
DECL|member|to_increment
id|to_increment
comma
multiline_comment|/* if !exponential */
DECL|member|to_resrvval
id|to_resrvval
suffix:semicolon
multiline_comment|/* reserve timeout */
DECL|member|to_retries
r_int
id|to_retries
suffix:semicolon
multiline_comment|/* max # of retries */
DECL|member|to_exponential
r_int
r_char
id|to_exponential
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the RPC buffer&n; */
DECL|struct|rpc_iov
r_struct
id|rpc_iov
(brace
DECL|member|io_vec
r_struct
id|iovec
id|io_vec
(braket
id|MAX_IOVEC
)braket
suffix:semicolon
DECL|member|io_nr
r_int
r_int
id|io_nr
suffix:semicolon
DECL|member|io_len
r_int
r_int
id|io_len
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This describes a complete RPC request&n; */
DECL|struct|rpc_rqst
r_struct
id|rpc_rqst
(brace
multiline_comment|/*&n;&t; * This is the user-visible part&n;&t; */
DECL|member|rq_xprt
r_struct
id|rpc_xprt
op_star
id|rq_xprt
suffix:semicolon
multiline_comment|/* RPC client */
DECL|member|rq_timeout
r_struct
id|rpc_timeout
id|rq_timeout
suffix:semicolon
multiline_comment|/* timeout parms */
DECL|member|rq_snd_buf
r_struct
id|rpc_iov
id|rq_snd_buf
suffix:semicolon
multiline_comment|/* send buffer */
DECL|member|rq_rcv_buf
r_struct
id|rpc_iov
id|rq_rcv_buf
suffix:semicolon
multiline_comment|/* recv buffer */
multiline_comment|/*&n;&t; * This is the private part&n;&t; */
DECL|member|rq_task
r_struct
id|rpc_task
op_star
id|rq_task
suffix:semicolon
multiline_comment|/* RPC task data */
DECL|member|rq_xid
id|__u32
id|rq_xid
suffix:semicolon
multiline_comment|/* request XID */
DECL|member|rq_next
r_struct
id|rpc_rqst
op_star
id|rq_next
suffix:semicolon
multiline_comment|/* free list */
DECL|member|rq_received
r_volatile
r_int
r_char
id|rq_received
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* receive completed */
multiline_comment|/*&n;&t; * For authentication (e.g. auth_des)&n;&t; */
DECL|member|rq_creddata
id|u32
id|rq_creddata
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Partial send handling&n;&t; */
DECL|member|rq_bytes_sent
id|u32
id|rq_bytes_sent
suffix:semicolon
multiline_comment|/* Bytes we have sent */
macro_line|#ifdef RPC_PROFILE
DECL|member|rq_xtime
r_int
r_int
id|rq_xtime
suffix:semicolon
multiline_comment|/* when transmitted */
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|rq_svec
mdefine_line|#define rq_svec&t;&t;&t;rq_snd_buf.io_vec
DECL|macro|rq_snr
mdefine_line|#define rq_snr&t;&t;&t;rq_snd_buf.io_nr
DECL|macro|rq_slen
mdefine_line|#define rq_slen&t;&t;&t;rq_snd_buf.io_len
DECL|macro|rq_rvec
mdefine_line|#define rq_rvec&t;&t;&t;rq_rcv_buf.io_vec
DECL|macro|rq_rnr
mdefine_line|#define rq_rnr&t;&t;&t;rq_rcv_buf.io_nr
DECL|macro|rq_rlen
mdefine_line|#define rq_rlen&t;&t;&t;rq_rcv_buf.io_len
DECL|struct|rpc_xprt
r_struct
id|rpc_xprt
(brace
DECL|member|sock
r_struct
id|socket
op_star
id|sock
suffix:semicolon
multiline_comment|/* BSD socket layer */
DECL|member|inet
r_struct
id|sock
op_star
id|inet
suffix:semicolon
multiline_comment|/* INET layer */
DECL|member|timeout
r_struct
id|rpc_timeout
id|timeout
suffix:semicolon
multiline_comment|/* timeout parms */
DECL|member|addr
r_struct
id|sockaddr_in
id|addr
suffix:semicolon
multiline_comment|/* server address */
DECL|member|prot
r_int
id|prot
suffix:semicolon
multiline_comment|/* IP protocol */
DECL|member|cong
r_int
r_int
id|cong
suffix:semicolon
multiline_comment|/* current congestion */
DECL|member|cwnd
r_int
r_int
id|cwnd
suffix:semicolon
multiline_comment|/* congestion window */
DECL|member|congtime
r_int
r_int
id|congtime
suffix:semicolon
multiline_comment|/* hold cwnd until then */
DECL|member|sending
r_struct
id|rpc_wait_queue
id|sending
suffix:semicolon
multiline_comment|/* requests waiting to send */
DECL|member|pending
r_struct
id|rpc_wait_queue
id|pending
suffix:semicolon
multiline_comment|/* requests in flight */
DECL|member|backlog
r_struct
id|rpc_wait_queue
id|backlog
suffix:semicolon
multiline_comment|/* waiting for slot */
DECL|member|free
r_struct
id|rpc_rqst
op_star
id|free
suffix:semicolon
multiline_comment|/* free slots */
DECL|member|slot
r_struct
id|rpc_rqst
id|slot
(braket
id|RPC_MAXREQS
)braket
suffix:semicolon
DECL|member|sockstate
r_int
r_int
id|sockstate
suffix:semicolon
multiline_comment|/* Socket state */
DECL|member|shutdown
r_int
r_char
id|shutdown
suffix:colon
l_int|1
comma
multiline_comment|/* being shut down */
DECL|member|nocong
id|nocong
suffix:colon
l_int|1
comma
multiline_comment|/* no congestion control */
DECL|member|stream
id|stream
suffix:colon
l_int|1
comma
multiline_comment|/* TCP */
DECL|member|tcp_more
id|tcp_more
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* more record fragments */
multiline_comment|/*&n;&t; * State of TCP reply receive stuff&n;&t; */
DECL|member|tcp_recm
id|u32
id|tcp_recm
suffix:semicolon
multiline_comment|/* Fragment header */
DECL|member|tcp_xid
id|u32
id|tcp_xid
suffix:semicolon
multiline_comment|/* Current XID */
DECL|member|tcp_reclen
r_int
r_int
id|tcp_reclen
comma
multiline_comment|/* fragment length */
DECL|member|tcp_offset
id|tcp_offset
comma
multiline_comment|/* fragment offset */
DECL|member|tcp_copied
id|tcp_copied
suffix:semicolon
multiline_comment|/* copied to request */
DECL|member|rx_pending
r_struct
id|list_head
id|rx_pending
suffix:semicolon
multiline_comment|/* receive pending list */
multiline_comment|/*&n;&t; * Send stuff&n;&t; */
DECL|member|sock_lock
id|spinlock_t
id|sock_lock
suffix:semicolon
multiline_comment|/* lock socket info */
DECL|member|xprt_lock
id|spinlock_t
id|xprt_lock
suffix:semicolon
multiline_comment|/* lock xprt info */
DECL|member|snd_task
r_struct
id|rpc_task
op_star
id|snd_task
suffix:semicolon
multiline_comment|/* Task blocked in send */
DECL|member|old_data_ready
r_void
(paren
op_star
id|old_data_ready
)paren
(paren
r_struct
id|sock
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|old_state_change
r_void
(paren
op_star
id|old_state_change
)paren
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
DECL|member|old_write_space
r_void
(paren
op_star
id|old_write_space
)paren
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
DECL|member|cong_wait
id|wait_queue_head_t
id|cong_wait
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_struct
id|rpc_xprt
op_star
id|xprt_create_proto
c_func
(paren
r_int
id|proto
comma
r_struct
id|sockaddr_in
op_star
id|addr
comma
r_struct
id|rpc_timeout
op_star
id|toparms
)paren
suffix:semicolon
r_int
id|xprt_destroy
c_func
(paren
r_struct
id|rpc_xprt
op_star
)paren
suffix:semicolon
r_void
id|xprt_shutdown
c_func
(paren
r_struct
id|rpc_xprt
op_star
)paren
suffix:semicolon
r_void
id|xprt_default_timeout
c_func
(paren
r_struct
id|rpc_timeout
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|xprt_set_timeout
c_func
(paren
r_struct
id|rpc_timeout
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|xprt_reserve
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|xprt_transmit
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|xprt_receive
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_int
id|xprt_adjust_timeout
c_func
(paren
r_struct
id|rpc_timeout
op_star
)paren
suffix:semicolon
r_void
id|xprt_release
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|xprt_reconnect
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_int
id|xprt_clear_backlog
c_func
(paren
r_struct
id|rpc_xprt
op_star
)paren
suffix:semicolon
r_int
id|xprt_tcp_pending
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|__rpciod_tcp_dispatcher
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|XPRT_WSPACE
mdefine_line|#define XPRT_WSPACE&t;0
DECL|macro|XPRT_CONNECT
mdefine_line|#define XPRT_CONNECT&t;1
DECL|macro|xprt_wspace
mdefine_line|#define xprt_wspace(xp)&t;&t;&t;(test_bit(XPRT_WSPACE, &amp;(xp)-&gt;sockstate))
DECL|macro|xprt_test_and_set_wspace
mdefine_line|#define xprt_test_and_set_wspace(xp)&t;(test_and_set_bit(XPRT_WSPACE, &amp;(xp)-&gt;sockstate))
DECL|macro|xprt_clear_wspace
mdefine_line|#define xprt_clear_wspace(xp)&t;&t;(clear_bit(XPRT_WSPACE, &amp;(xp)-&gt;sockstate))
DECL|macro|xprt_connected
mdefine_line|#define xprt_connected(xp)&t;&t;(!(xp)-&gt;stream || test_bit(XPRT_CONNECT, &amp;(xp)-&gt;sockstate))
DECL|macro|xprt_set_connected
mdefine_line|#define xprt_set_connected(xp)&t;&t;(set_bit(XPRT_CONNECT, &amp;(xp)-&gt;sockstate))
DECL|macro|xprt_test_and_set_connected
mdefine_line|#define xprt_test_and_set_connected(xp)&t;(test_and_set_bit(XPRT_CONNECT, &amp;(xp)-&gt;sockstate))
DECL|macro|xprt_clear_connected
mdefine_line|#define xprt_clear_connected(xp)&t;(clear_bit(XPRT_CONNECT, &amp;(xp)-&gt;sockstate))
r_static
r_inline
DECL|function|rpciod_tcp_dispatcher
r_void
id|rpciod_tcp_dispatcher
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|xprt_tcp_pending
c_func
(paren
)paren
)paren
id|__rpciod_tcp_dispatcher
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__*/
macro_line|#endif /* _LINUX_SUNRPC_XPRT_H */
eof
