multiline_comment|/*&n; *  linux/include/linux/sunrpc/clnt.h&n; *&n; *  Declarations for the high-level RPC client interface&n; *&n; *  Copyright (C) 1995, 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef _LINUX_SUNRPC_CLNT_H
DECL|macro|_LINUX_SUNRPC_CLNT_H
mdefine_line|#define _LINUX_SUNRPC_CLNT_H
macro_line|#include &lt;linux/sunrpc/msg_prot.h&gt;
macro_line|#include &lt;linux/sunrpc/sched.h&gt;
macro_line|#include &lt;linux/sunrpc/xprt.h&gt;
macro_line|#include &lt;linux/sunrpc/auth.h&gt;
macro_line|#include &lt;linux/sunrpc/stats.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
multiline_comment|/*&n; * This defines an RPC port mapping&n; */
DECL|struct|rpc_portmap
r_struct
id|rpc_portmap
(brace
DECL|member|pm_prog
id|__u32
id|pm_prog
suffix:semicolon
DECL|member|pm_vers
id|__u32
id|pm_vers
suffix:semicolon
DECL|member|pm_prot
id|__u32
id|pm_prot
suffix:semicolon
DECL|member|pm_port
id|__u16
id|pm_port
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The high-level client handle&n; */
DECL|struct|rpc_clnt
r_struct
id|rpc_clnt
(brace
DECL|member|cl_users
id|atomic_t
id|cl_users
suffix:semicolon
multiline_comment|/* number of references */
DECL|member|cl_xprt
r_struct
id|rpc_xprt
op_star
id|cl_xprt
suffix:semicolon
multiline_comment|/* transport */
DECL|member|cl_procinfo
r_struct
id|rpc_procinfo
op_star
id|cl_procinfo
suffix:semicolon
multiline_comment|/* procedure info */
DECL|member|cl_maxproc
id|u32
id|cl_maxproc
suffix:semicolon
multiline_comment|/* max procedure number */
DECL|member|cl_server
r_char
op_star
id|cl_server
suffix:semicolon
multiline_comment|/* server machine name */
DECL|member|cl_protname
r_char
op_star
id|cl_protname
suffix:semicolon
multiline_comment|/* protocol name */
DECL|member|cl_auth
r_struct
id|rpc_auth
op_star
id|cl_auth
suffix:semicolon
multiline_comment|/* authenticator */
DECL|member|cl_stats
r_struct
id|rpc_stat
op_star
id|cl_stats
suffix:semicolon
multiline_comment|/* statistics */
DECL|member|cl_softrtry
r_int
r_int
id|cl_softrtry
suffix:colon
l_int|1
comma
multiline_comment|/* soft timeouts */
DECL|member|cl_intr
id|cl_intr
suffix:colon
l_int|1
comma
multiline_comment|/* interruptible */
DECL|member|cl_chatty
id|cl_chatty
suffix:colon
l_int|1
comma
multiline_comment|/* be verbose */
DECL|member|cl_autobind
id|cl_autobind
suffix:colon
l_int|1
comma
multiline_comment|/* use getport() */
DECL|member|cl_binding
id|cl_binding
suffix:colon
l_int|1
comma
multiline_comment|/* doing a getport() */
DECL|member|cl_droppriv
id|cl_droppriv
suffix:colon
l_int|1
comma
multiline_comment|/* enable NFS suid hack */
DECL|member|cl_oneshot
id|cl_oneshot
suffix:colon
l_int|1
comma
multiline_comment|/* dispose after use */
DECL|member|cl_dead
id|cl_dead
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* abandoned */
DECL|member|cl_flags
r_int
r_int
id|cl_flags
suffix:semicolon
multiline_comment|/* misc client flags */
DECL|member|cl_hardmax
r_int
r_int
id|cl_hardmax
suffix:semicolon
multiline_comment|/* max hard timeout */
DECL|member|cl_pmap
r_struct
id|rpc_portmap
id|cl_pmap
suffix:semicolon
multiline_comment|/* port mapping */
DECL|member|cl_bindwait
r_struct
id|rpc_wait_queue
id|cl_bindwait
suffix:semicolon
multiline_comment|/* waiting on getport() */
DECL|member|cl_nodelen
r_int
id|cl_nodelen
suffix:semicolon
multiline_comment|/* nodename length */
DECL|member|cl_nodename
r_char
id|cl_nodename
(braket
id|UNX_MAXNODENAME
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|cl_timeout
mdefine_line|#define cl_timeout&t;&t;cl_xprt-&gt;timeout
DECL|macro|cl_prog
mdefine_line|#define cl_prog&t;&t;&t;cl_pmap.pm_prog
DECL|macro|cl_vers
mdefine_line|#define cl_vers&t;&t;&t;cl_pmap.pm_vers
DECL|macro|cl_port
mdefine_line|#define cl_port&t;&t;&t;cl_pmap.pm_port
DECL|macro|cl_prot
mdefine_line|#define cl_prot&t;&t;&t;cl_pmap.pm_prot
multiline_comment|/*&n; * General RPC program info&n; */
DECL|macro|RPC_MAXVERSION
mdefine_line|#define RPC_MAXVERSION&t;&t;4
DECL|struct|rpc_program
r_struct
id|rpc_program
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* protocol name */
DECL|member|number
id|u32
id|number
suffix:semicolon
multiline_comment|/* program number */
DECL|member|nrvers
r_int
r_int
id|nrvers
suffix:semicolon
multiline_comment|/* number of versions */
DECL|member|version
r_struct
id|rpc_version
op_star
op_star
id|version
suffix:semicolon
multiline_comment|/* version array */
DECL|member|stats
r_struct
id|rpc_stat
op_star
id|stats
suffix:semicolon
multiline_comment|/* statistics */
)brace
suffix:semicolon
DECL|struct|rpc_version
r_struct
id|rpc_version
(brace
DECL|member|number
id|u32
id|number
suffix:semicolon
multiline_comment|/* version number */
DECL|member|nrprocs
r_int
r_int
id|nrprocs
suffix:semicolon
multiline_comment|/* number of procs */
DECL|member|procs
r_struct
id|rpc_procinfo
op_star
id|procs
suffix:semicolon
multiline_comment|/* procedure array */
)brace
suffix:semicolon
multiline_comment|/*&n; * Procedure information&n; */
DECL|struct|rpc_procinfo
r_struct
id|rpc_procinfo
(brace
DECL|member|p_procname
r_char
op_star
id|p_procname
suffix:semicolon
multiline_comment|/* procedure name */
DECL|member|p_encode
id|kxdrproc_t
id|p_encode
suffix:semicolon
multiline_comment|/* XDR encode function */
DECL|member|p_decode
id|kxdrproc_t
id|p_decode
suffix:semicolon
multiline_comment|/* XDR decode function */
DECL|member|p_bufsiz
r_int
r_int
id|p_bufsiz
suffix:semicolon
multiline_comment|/* req. buffer size */
DECL|member|p_count
r_int
r_int
id|p_count
suffix:semicolon
multiline_comment|/* call count */
)brace
suffix:semicolon
DECL|macro|rpcproc_bufsiz
mdefine_line|#define rpcproc_bufsiz(clnt, proc)&t;((clnt)-&gt;cl_procinfo[proc].p_bufsiz)
DECL|macro|rpcproc_encode
mdefine_line|#define rpcproc_encode(clnt, proc)&t;((clnt)-&gt;cl_procinfo[proc].p_encode)
DECL|macro|rpcproc_decode
mdefine_line|#define rpcproc_decode(clnt, proc)&t;((clnt)-&gt;cl_procinfo[proc].p_decode)
DECL|macro|rpcproc_name
mdefine_line|#define rpcproc_name(clnt, proc)&t;((clnt)-&gt;cl_procinfo[proc].p_procname)
DECL|macro|rpcproc_count
mdefine_line|#define rpcproc_count(clnt, proc)&t;((clnt)-&gt;cl_procinfo[proc].p_count)
DECL|macro|RPC_CONGESTED
mdefine_line|#define RPC_CONGESTED(clnt)&t;(RPCXPRT_CONGESTED((clnt)-&gt;cl_xprt))
DECL|macro|RPC_PEERADDR
mdefine_line|#define RPC_PEERADDR(clnt)&t;(&amp;(clnt)-&gt;cl_xprt-&gt;addr)
macro_line|#ifdef __KERNEL__
r_struct
id|rpc_clnt
op_star
id|rpc_create_client
c_func
(paren
r_struct
id|rpc_xprt
op_star
id|xprt
comma
r_char
op_star
id|servname
comma
r_struct
id|rpc_program
op_star
id|info
comma
id|u32
id|version
comma
r_int
id|authflavor
)paren
suffix:semicolon
r_int
id|rpc_shutdown_client
c_func
(paren
r_struct
id|rpc_clnt
op_star
)paren
suffix:semicolon
r_int
id|rpc_destroy_client
c_func
(paren
r_struct
id|rpc_clnt
op_star
)paren
suffix:semicolon
r_void
id|rpc_release_client
c_func
(paren
r_struct
id|rpc_clnt
op_star
)paren
suffix:semicolon
r_void
id|rpc_getport
c_func
(paren
r_struct
id|rpc_task
op_star
comma
r_struct
id|rpc_clnt
op_star
)paren
suffix:semicolon
r_int
id|rpc_register
c_func
(paren
id|u32
comma
id|u32
comma
r_int
comma
r_int
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_void
id|rpc_call_setup
c_func
(paren
r_struct
id|rpc_task
op_star
comma
r_struct
id|rpc_message
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|rpc_call_async
c_func
(paren
r_struct
id|rpc_clnt
op_star
id|clnt
comma
r_struct
id|rpc_message
op_star
id|msg
comma
r_int
id|flags
comma
id|rpc_action
id|callback
comma
r_void
op_star
id|clntdata
)paren
suffix:semicolon
r_int
id|rpc_call_sync
c_func
(paren
r_struct
id|rpc_clnt
op_star
id|clnt
comma
r_struct
id|rpc_message
op_star
id|msg
comma
r_int
id|flags
)paren
suffix:semicolon
r_void
id|rpc_restart_call
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|rpc_clnt_sigmask
c_func
(paren
r_struct
id|rpc_clnt
op_star
id|clnt
comma
id|sigset_t
op_star
id|oldset
)paren
suffix:semicolon
r_void
id|rpc_clnt_sigunmask
c_func
(paren
r_struct
id|rpc_clnt
op_star
id|clnt
comma
id|sigset_t
op_star
id|oldset
)paren
suffix:semicolon
r_static
id|__inline__
DECL|function|rpc_call
r_int
id|rpc_call
c_func
(paren
r_struct
id|rpc_clnt
op_star
id|clnt
comma
id|u32
id|proc
comma
r_void
op_star
id|argp
comma
r_void
op_star
id|resp
comma
r_int
id|flags
)paren
(brace
r_struct
id|rpc_message
id|msg
op_assign
(brace
id|proc
comma
id|argp
comma
id|resp
comma
l_int|NULL
)brace
suffix:semicolon
r_return
id|rpc_call_sync
c_func
(paren
id|clnt
comma
op_amp
id|msg
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|rpc_set_timeout
id|rpc_set_timeout
c_func
(paren
r_struct
id|rpc_clnt
op_star
id|clnt
comma
r_int
r_int
id|retr
comma
r_int
r_int
id|incr
)paren
(brace
id|xprt_set_timeout
c_func
(paren
op_amp
id|clnt-&gt;cl_timeout
comma
id|retr
comma
id|incr
)paren
suffix:semicolon
)brace
r_extern
r_void
id|rpciod_tcp_dispatcher
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rpciod_wake_up
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Helper function for NFSroot support&n; */
r_int
id|rpc_getport_external
c_func
(paren
r_struct
id|sockaddr_in
op_star
comma
id|__u32
comma
id|__u32
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SUNRPC_CLNT_H */
eof
