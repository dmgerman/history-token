multiline_comment|/*&n; * linux/include/linux/sunrpc/svcsock.h&n; *&n; * RPC server socket I/O.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef SUNRPC_SVCSOCK_H
DECL|macro|SUNRPC_SVCSOCK_H
mdefine_line|#define SUNRPC_SVCSOCK_H
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
multiline_comment|/*&n; * RPC server socket.&n; * NOTE: First two items must be prev/next.&n; */
DECL|struct|svc_sock
r_struct
id|svc_sock
(brace
DECL|member|sk_prev
r_struct
id|svc_sock
op_star
id|sk_prev
suffix:semicolon
multiline_comment|/* list of ready sockets */
DECL|member|sk_next
r_struct
id|svc_sock
op_star
id|sk_next
suffix:semicolon
DECL|member|sk_list
r_struct
id|svc_sock
op_star
id|sk_list
suffix:semicolon
multiline_comment|/* list of all sockets */
DECL|member|sk_sock
r_struct
id|socket
op_star
id|sk_sock
suffix:semicolon
multiline_comment|/* berkeley socket layer */
DECL|member|sk_sk
r_struct
id|sock
op_star
id|sk_sk
suffix:semicolon
multiline_comment|/* INET layer */
DECL|member|sk_lock
id|spinlock_t
id|sk_lock
suffix:semicolon
DECL|member|sk_server
r_struct
id|svc_serv
op_star
id|sk_server
suffix:semicolon
multiline_comment|/* service for this socket */
DECL|member|sk_inuse
r_int
r_char
id|sk_inuse
suffix:semicolon
multiline_comment|/* use count */
DECL|member|sk_busy
r_int
r_char
id|sk_busy
suffix:semicolon
multiline_comment|/* enqueued/receiving */
DECL|member|sk_conn
r_int
r_char
id|sk_conn
suffix:semicolon
multiline_comment|/* conn pending */
DECL|member|sk_close
r_int
r_char
id|sk_close
suffix:semicolon
multiline_comment|/* dead or dying */
DECL|member|sk_data
r_int
id|sk_data
suffix:semicolon
multiline_comment|/* data pending */
DECL|member|sk_temp
r_int
r_int
id|sk_temp
suffix:colon
l_int|1
comma
multiline_comment|/* temp socket */
DECL|member|sk_qued
id|sk_qued
suffix:colon
l_int|1
comma
multiline_comment|/* on serv-&gt;sk_sockets */
DECL|member|sk_dead
id|sk_dead
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* socket closed */
DECL|member|sk_recvfrom
r_int
(paren
op_star
id|sk_recvfrom
)paren
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
)paren
suffix:semicolon
DECL|member|sk_sendto
r_int
(paren
op_star
id|sk_sendto
)paren
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
)paren
suffix:semicolon
multiline_comment|/* We keep the old state_change and data_ready CB&squot;s here */
DECL|member|sk_ostate
r_void
(paren
op_star
id|sk_ostate
)paren
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
DECL|member|sk_odata
r_void
(paren
op_star
id|sk_odata
)paren
(paren
r_struct
id|sock
op_star
comma
r_int
id|bytes
)paren
suffix:semicolon
multiline_comment|/* private TCP part */
DECL|member|sk_reclen
r_int
id|sk_reclen
suffix:semicolon
multiline_comment|/* length of record */
DECL|member|sk_tcplen
r_int
id|sk_tcplen
suffix:semicolon
multiline_comment|/* current read length */
multiline_comment|/* Debugging */
DECL|member|sk_rqstp
r_struct
id|svc_rqst
op_star
id|sk_rqstp
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Function prototypes.&n; */
r_int
id|svc_makesock
c_func
(paren
r_struct
id|svc_serv
op_star
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|svc_delete_socket
c_func
(paren
r_struct
id|svc_sock
op_star
)paren
suffix:semicolon
r_int
id|svc_recv
c_func
(paren
r_struct
id|svc_serv
op_star
comma
r_struct
id|svc_rqst
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|svc_send
c_func
(paren
r_struct
id|svc_rqst
op_star
)paren
suffix:semicolon
r_void
id|svc_drop
c_func
(paren
r_struct
id|svc_rqst
op_star
)paren
suffix:semicolon
macro_line|#endif /* SUNRPC_SVCSOCK_H */
eof
