multiline_comment|/*&n; *  linux/include/linux/sunrpc/clnt_xprt.h&n; *&n; *  Declarations for the RPC transport interface.&n; *&n; *  Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef _LINUX_SUNRPC_XPRT_H
DECL|macro|_LINUX_SUNRPC_XPRT_H
mdefine_line|#define _LINUX_SUNRPC_XPRT_H
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/sunrpc/sched.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
multiline_comment|/*&n; * The transport code maintains an estimate on the maximum number of out-&n; * standing RPC requests, using a smoothed version of the congestion&n; * avoidance implemented in 44BSD. This is basically the Van Jacobson&n; * congestion algorithm: If a retransmit occurs, the congestion window is&n; * halved; otherwise, it is incremented by 1/cwnd when&n; *&n; *&t;-&t;a reply is received and&n; *&t;-&t;a full number of requests are outstanding and&n; *&t;-&t;the congestion window hasn&squot;t been updated recently.&n; *&n; * Upper procedures may check whether a request would block waiting for&n; * a free RPC slot by using the RPC_CONGESTED() macro.&n; */
r_extern
r_int
r_int
id|xprt_udp_slot_table_entries
suffix:semicolon
r_extern
r_int
r_int
id|xprt_tcp_slot_table_entries
suffix:semicolon
DECL|macro|RPC_MIN_SLOT_TABLE
mdefine_line|#define RPC_MIN_SLOT_TABLE&t;(2U)
DECL|macro|RPC_DEF_SLOT_TABLE
mdefine_line|#define RPC_DEF_SLOT_TABLE&t;(16U)
DECL|macro|RPC_MAX_SLOT_TABLE
mdefine_line|#define RPC_MAX_SLOT_TABLE&t;(128U)
DECL|macro|RPC_CWNDSHIFT
mdefine_line|#define RPC_CWNDSHIFT&t;&t;(8U)
DECL|macro|RPC_CWNDSCALE
mdefine_line|#define RPC_CWNDSCALE&t;&t;(1U &lt;&lt; RPC_CWNDSHIFT)
DECL|macro|RPC_INITCWND
mdefine_line|#define RPC_INITCWND&t;&t;RPC_CWNDSCALE
DECL|macro|RPC_MAXCWND
mdefine_line|#define RPC_MAXCWND(xprt)&t;((xprt)-&gt;max_reqs &lt;&lt; RPC_CWNDSHIFT)
DECL|macro|RPCXPRT_CONGESTED
mdefine_line|#define RPCXPRT_CONGESTED(xprt) ((xprt)-&gt;cong &gt;= (xprt)-&gt;cwnd)
multiline_comment|/* Default timeout values */
DECL|macro|RPC_MAX_UDP_TIMEOUT
mdefine_line|#define RPC_MAX_UDP_TIMEOUT&t;(60*HZ)
DECL|macro|RPC_MAX_TCP_TIMEOUT
mdefine_line|#define RPC_MAX_TCP_TIMEOUT&t;(600*HZ)
multiline_comment|/*&n; * Wait duration for an RPC TCP connection to be established.  Solaris&n; * NFS over TCP uses 60 seconds, for example, which is in line with how&n; * long a server takes to reboot.&n; */
DECL|macro|RPC_CONNECT_TIMEOUT
mdefine_line|#define RPC_CONNECT_TIMEOUT&t;(60*HZ)
multiline_comment|/*&n; * Delay an arbitrary number of seconds before attempting to reconnect&n; * after an error.&n; */
DECL|macro|RPC_REESTABLISH_TIMEOUT
mdefine_line|#define RPC_REESTABLISH_TIMEOUT&t;(15*HZ)
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
DECL|member|to_initval
r_int
r_int
id|to_initval
comma
multiline_comment|/* initial timeout */
DECL|member|to_maxval
id|to_maxval
comma
multiline_comment|/* max timeout */
DECL|member|to_increment
id|to_increment
suffix:semicolon
multiline_comment|/* if !exponential */
DECL|member|to_retries
r_int
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
DECL|member|rq_snd_buf
r_struct
id|xdr_buf
id|rq_snd_buf
suffix:semicolon
multiline_comment|/* send buffer */
DECL|member|rq_rcv_buf
r_struct
id|xdr_buf
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
DECL|member|rq_cong
r_int
id|rq_cong
suffix:semicolon
multiline_comment|/* has incremented xprt-&gt;cong */
DECL|member|rq_received
r_int
id|rq_received
suffix:semicolon
multiline_comment|/* receive completed */
DECL|member|rq_seqno
id|u32
id|rq_seqno
suffix:semicolon
multiline_comment|/* gss seq no. used on req. */
DECL|member|rq_list
r_struct
id|list_head
id|rq_list
suffix:semicolon
DECL|member|rq_private_buf
r_struct
id|xdr_buf
id|rq_private_buf
suffix:semicolon
multiline_comment|/* The receive buffer&n;&t;&t;&t;&t;&t;&t;&t; * used in the softirq.&n;&t;&t;&t;&t;&t;&t;&t; */
DECL|member|rq_majortimeo
r_int
r_int
id|rq_majortimeo
suffix:semicolon
multiline_comment|/* major timeout alarm */
DECL|member|rq_timeout
r_int
r_int
id|rq_timeout
suffix:semicolon
multiline_comment|/* Current timeout value */
DECL|member|rq_retries
r_int
r_int
id|rq_retries
suffix:semicolon
multiline_comment|/* # of retries */
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
DECL|member|rq_xtime
r_int
r_int
id|rq_xtime
suffix:semicolon
multiline_comment|/* when transmitted */
DECL|member|rq_ntrans
r_int
id|rq_ntrans
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|rq_svec
mdefine_line|#define rq_svec&t;&t;&t;rq_snd_buf.head
DECL|macro|rq_slen
mdefine_line|#define rq_slen&t;&t;&t;rq_snd_buf.len
DECL|macro|XPRT_LAST_FRAG
mdefine_line|#define XPRT_LAST_FRAG&t;&t;(1 &lt;&lt; 0)
DECL|macro|XPRT_COPY_RECM
mdefine_line|#define XPRT_COPY_RECM&t;&t;(1 &lt;&lt; 1)
DECL|macro|XPRT_COPY_XID
mdefine_line|#define XPRT_COPY_XID&t;&t;(1 &lt;&lt; 2)
DECL|macro|XPRT_COPY_DATA
mdefine_line|#define XPRT_COPY_DATA&t;&t;(1 &lt;&lt; 3)
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
DECL|member|rcvsize
r_int
r_int
id|rcvsize
comma
multiline_comment|/* socket receive buffer size */
DECL|member|sndsize
id|sndsize
suffix:semicolon
multiline_comment|/* socket send buffer size */
DECL|member|sending
r_struct
id|rpc_wait_queue
id|sending
suffix:semicolon
multiline_comment|/* requests waiting to send */
DECL|member|resend
r_struct
id|rpc_wait_queue
id|resend
suffix:semicolon
multiline_comment|/* requests waiting to resend */
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
id|list_head
id|free
suffix:semicolon
multiline_comment|/* free slots */
DECL|member|slot
r_struct
id|rpc_rqst
op_star
id|slot
suffix:semicolon
multiline_comment|/* slot table storage */
DECL|member|max_reqs
r_int
r_int
id|max_reqs
suffix:semicolon
multiline_comment|/* total slots */
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
DECL|member|resvport
id|resvport
suffix:colon
l_int|1
comma
multiline_comment|/* use a reserved port */
DECL|member|stream
id|stream
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* TCP */
multiline_comment|/*&n;&t; * XID&n;&t; */
DECL|member|xid
id|__u32
id|xid
suffix:semicolon
multiline_comment|/* Next XID value to use */
multiline_comment|/*&n;&t; * State of TCP reply receive stuff&n;&t; */
DECL|member|tcp_recm
id|u32
id|tcp_recm
comma
multiline_comment|/* Fragment header */
DECL|member|tcp_xid
id|tcp_xid
comma
multiline_comment|/* Current XID */
DECL|member|tcp_reclen
id|tcp_reclen
comma
multiline_comment|/* fragment length */
DECL|member|tcp_offset
id|tcp_offset
suffix:semicolon
multiline_comment|/* fragment offset */
DECL|member|tcp_copied
r_int
r_int
id|tcp_copied
comma
multiline_comment|/* copied to request */
DECL|member|tcp_flags
id|tcp_flags
suffix:semicolon
multiline_comment|/*&n;&t; * Connection of sockets&n;&t; */
DECL|member|sock_connect
r_struct
id|work_struct
id|sock_connect
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
multiline_comment|/*&n;&t; * Disconnection of idle sockets&n;&t; */
DECL|member|task_cleanup
r_struct
id|work_struct
id|task_cleanup
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|last_used
r_int
r_int
id|last_used
suffix:semicolon
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
DECL|member|recv
r_struct
id|list_head
id|recv
suffix:semicolon
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
r_void
id|xprt_reserve
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_int
id|xprt_prepare_transmit
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
id|rpc_rqst
op_star
id|req
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
id|xprt_connect
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|xprt_sock_setbufsize
c_func
(paren
r_struct
id|rpc_xprt
op_star
)paren
suffix:semicolon
DECL|macro|XPRT_LOCKED
mdefine_line|#define XPRT_LOCKED&t;0
DECL|macro|XPRT_CONNECT
mdefine_line|#define XPRT_CONNECT&t;1
DECL|macro|XPRT_CONNECTING
mdefine_line|#define XPRT_CONNECTING&t;2
DECL|macro|xprt_connected
mdefine_line|#define xprt_connected(xp)&t;&t;(test_bit(XPRT_CONNECT, &amp;(xp)-&gt;sockstate))
DECL|macro|xprt_set_connected
mdefine_line|#define xprt_set_connected(xp)&t;&t;(set_bit(XPRT_CONNECT, &amp;(xp)-&gt;sockstate))
DECL|macro|xprt_test_and_set_connected
mdefine_line|#define xprt_test_and_set_connected(xp)&t;(test_and_set_bit(XPRT_CONNECT, &amp;(xp)-&gt;sockstate))
DECL|macro|xprt_test_and_clear_connected
mdefine_line|#define xprt_test_and_clear_connected(xp) &bslash;&n;&t;&t;&t;&t;&t;(test_and_clear_bit(XPRT_CONNECT, &amp;(xp)-&gt;sockstate))
DECL|macro|xprt_clear_connected
mdefine_line|#define xprt_clear_connected(xp)&t;(clear_bit(XPRT_CONNECT, &amp;(xp)-&gt;sockstate))
macro_line|#endif /* __KERNEL__*/
macro_line|#endif /* _LINUX_SUNRPC_XPRT_H */
eof
