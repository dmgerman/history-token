multiline_comment|/*&n; * linux/net/sunrpc/pmap.c&n; *&n; * Portmapper client.&n; *&n; * FIXME: In a secure environment, we may want to use an authentication&n; * flavor other than AUTH_NULL.&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/xprt.h&gt;
macro_line|#include &lt;linux/sunrpc/sched.h&gt;
macro_line|#ifdef RPC_DEBUG
DECL|macro|RPCDBG_FACILITY
macro_line|# define RPCDBG_FACILITY&t;RPCDBG_PMAP
macro_line|#endif
DECL|macro|PMAP_SET
mdefine_line|#define PMAP_SET&t;&t;1
DECL|macro|PMAP_UNSET
mdefine_line|#define PMAP_UNSET&t;&t;2
DECL|macro|PMAP_GETPORT
mdefine_line|#define PMAP_GETPORT&t;&t;3
r_static
r_struct
id|rpc_clnt
op_star
id|pmap_create
c_func
(paren
r_char
op_star
comma
r_struct
id|sockaddr_in
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_void
id|pmap_getport_done
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|rpc_program
id|pmap_program
suffix:semicolon
DECL|variable|pmap_lock
r_static
id|spinlock_t
id|pmap_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * Obtain the port for a given RPC service on a given host. This one can&n; * be called for an ongoing RPC request.&n; */
r_void
DECL|function|rpc_getport
id|rpc_getport
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
comma
r_struct
id|rpc_clnt
op_star
id|clnt
)paren
(brace
r_struct
id|rpc_portmap
op_star
id|map
op_assign
op_amp
id|clnt-&gt;cl_pmap
suffix:semicolon
r_struct
id|sockaddr_in
op_star
id|sap
op_assign
op_amp
id|clnt-&gt;cl_xprt-&gt;addr
suffix:semicolon
r_struct
id|rpc_message
id|msg
op_assign
(brace
id|PMAP_GETPORT
comma
id|map
comma
op_amp
id|clnt-&gt;cl_port
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|pmap_clnt
suffix:semicolon
r_struct
id|rpc_task
op_star
id|child
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: %4d rpc_getport(%s, %d, %d, %d)&bslash;n&quot;
comma
id|task-&gt;tk_pid
comma
id|clnt-&gt;cl_server
comma
id|map-&gt;pm_prog
comma
id|map-&gt;pm_vers
comma
id|map-&gt;pm_prot
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pmap_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clnt-&gt;cl_binding
)paren
(brace
id|rpc_sleep_on
c_func
(paren
op_amp
id|clnt-&gt;cl_bindwait
comma
id|task
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pmap_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|clnt-&gt;cl_binding
op_assign
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pmap_lock
)paren
suffix:semicolon
id|task-&gt;tk_status
op_assign
op_minus
id|EACCES
suffix:semicolon
multiline_comment|/* why set this? returns -EIO below */
r_if
c_cond
(paren
op_logical_neg
(paren
id|pmap_clnt
op_assign
id|pmap_create
c_func
(paren
id|clnt-&gt;cl_server
comma
id|sap
comma
id|map-&gt;pm_prot
)paren
)paren
)paren
r_goto
id|bailout
suffix:semicolon
id|task-&gt;tk_status
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Note: rpc_new_child will release client after a failure.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|child
op_assign
id|rpc_new_child
c_func
(paren
id|pmap_clnt
comma
id|task
)paren
)paren
)paren
r_goto
id|bailout
suffix:semicolon
multiline_comment|/* Setup the call info struct */
id|rpc_call_setup
c_func
(paren
id|child
comma
op_amp
id|msg
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* ... and run the child task */
id|rpc_run_child
c_func
(paren
id|task
comma
id|child
comma
id|pmap_getport_done
)paren
suffix:semicolon
r_return
suffix:semicolon
id|bailout
suffix:colon
id|spin_lock
c_func
(paren
op_amp
id|pmap_lock
)paren
suffix:semicolon
id|clnt-&gt;cl_binding
op_assign
l_int|0
suffix:semicolon
id|rpc_wake_up
c_func
(paren
op_amp
id|clnt-&gt;cl_bindwait
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pmap_lock
)paren
suffix:semicolon
id|task-&gt;tk_status
op_assign
op_minus
id|EIO
suffix:semicolon
id|task-&gt;tk_action
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ROOT_NFS
r_int
DECL|function|rpc_getport_external
id|rpc_getport_external
c_func
(paren
r_struct
id|sockaddr_in
op_star
id|sin
comma
id|__u32
id|prog
comma
id|__u32
id|vers
comma
r_int
id|prot
)paren
(brace
r_struct
id|rpc_portmap
id|map
op_assign
(brace
id|prog
comma
id|vers
comma
id|prot
comma
l_int|0
)brace
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|pmap_clnt
suffix:semicolon
r_char
id|hostname
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      rpc_getport_external(%u.%u.%u.%u, %d, %d, %d)&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|sin-&gt;sin_addr.s_addr
)paren
comma
id|prog
comma
id|vers
comma
id|prot
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|hostname
comma
l_string|&quot;%u.%u.%u.%u&quot;
comma
id|NIPQUAD
c_func
(paren
id|sin-&gt;sin_addr.s_addr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pmap_clnt
op_assign
id|pmap_create
c_func
(paren
id|hostname
comma
id|sin
comma
id|prot
)paren
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
multiline_comment|/* Setup the call info struct */
id|status
op_assign
id|rpc_call
c_func
(paren
id|pmap_clnt
comma
id|PMAP_GETPORT
comma
op_amp
id|map
comma
op_amp
id|map.pm_port
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|map.pm_port
op_ne
l_int|0
)paren
r_return
id|map.pm_port
suffix:semicolon
id|status
op_assign
op_minus
id|EACCES
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
macro_line|#endif
r_static
r_void
DECL|function|pmap_getport_done
id|pmap_getport_done
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
r_struct
id|rpc_clnt
op_star
id|clnt
op_assign
id|task-&gt;tk_client
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: %4d pmap_getport_done(status %d, port %d)&bslash;n&quot;
comma
id|task-&gt;tk_pid
comma
id|task-&gt;tk_status
comma
id|clnt-&gt;cl_port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;tk_status
OL
l_int|0
)paren
(brace
multiline_comment|/* Make the calling task exit with an error */
id|task-&gt;tk_action
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|clnt-&gt;cl_port
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Program not registered */
id|task-&gt;tk_status
op_assign
op_minus
id|EACCES
suffix:semicolon
id|task-&gt;tk_action
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* byte-swap port number first */
id|clnt-&gt;cl_port
op_assign
id|htons
c_func
(paren
id|clnt-&gt;cl_port
)paren
suffix:semicolon
id|clnt-&gt;cl_xprt-&gt;addr.sin_port
op_assign
id|clnt-&gt;cl_port
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|pmap_lock
)paren
suffix:semicolon
id|clnt-&gt;cl_binding
op_assign
l_int|0
suffix:semicolon
id|rpc_wake_up
c_func
(paren
op_amp
id|clnt-&gt;cl_bindwait
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pmap_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set or unset a port registration with the local portmapper.&n; * port == 0 means unregister, port != 0 means register.&n; */
r_int
DECL|function|rpc_register
id|rpc_register
c_func
(paren
id|u32
id|prog
comma
id|u32
id|vers
comma
r_int
id|prot
comma
r_int
r_int
id|port
comma
r_int
op_star
id|okay
)paren
(brace
r_struct
id|sockaddr_in
id|sin
suffix:semicolon
r_struct
id|rpc_portmap
id|map
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|pmap_clnt
suffix:semicolon
r_int
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: registering (%d, %d, %d, %d) with portmapper.&bslash;n&quot;
comma
id|prog
comma
id|vers
comma
id|prot
comma
id|port
)paren
suffix:semicolon
id|sin.sin_family
op_assign
id|AF_INET
suffix:semicolon
id|sin.sin_addr.s_addr
op_assign
id|htonl
c_func
(paren
id|INADDR_LOOPBACK
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pmap_clnt
op_assign
id|pmap_create
c_func
(paren
l_string|&quot;localhost&quot;
comma
op_amp
id|sin
comma
id|IPPROTO_UDP
)paren
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: couldn&squot;t create pmap client&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
id|map.pm_prog
op_assign
id|prog
suffix:semicolon
id|map.pm_vers
op_assign
id|vers
suffix:semicolon
id|map.pm_prot
op_assign
id|prot
suffix:semicolon
id|map.pm_port
op_assign
id|port
suffix:semicolon
id|error
op_assign
id|rpc_call
c_func
(paren
id|pmap_clnt
comma
id|port
ques
c_cond
id|PMAP_SET
suffix:colon
id|PMAP_UNSET
comma
op_amp
id|map
comma
id|okay
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;RPC: failed to contact portmap (errno %d).&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: registration status %d/%d&bslash;n&quot;
comma
id|error
comma
op_star
id|okay
)paren
suffix:semicolon
multiline_comment|/* Client deleted automatically because cl_oneshot == 1 */
r_return
id|error
suffix:semicolon
)brace
r_static
r_struct
id|rpc_clnt
op_star
DECL|function|pmap_create
id|pmap_create
c_func
(paren
r_char
op_star
id|hostname
comma
r_struct
id|sockaddr_in
op_star
id|srvaddr
comma
r_int
id|proto
)paren
(brace
r_struct
id|rpc_xprt
op_star
id|xprt
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|clnt
suffix:semicolon
multiline_comment|/* printk(&quot;pmap: create xprt&bslash;n&quot;); */
r_if
c_cond
(paren
op_logical_neg
(paren
id|xprt
op_assign
id|xprt_create_proto
c_func
(paren
id|proto
comma
id|srvaddr
comma
l_int|NULL
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|xprt-&gt;addr.sin_port
op_assign
id|htons
c_func
(paren
id|RPC_PMAP_PORT
)paren
suffix:semicolon
multiline_comment|/* printk(&quot;pmap: create clnt&bslash;n&quot;); */
id|clnt
op_assign
id|rpc_create_client
c_func
(paren
id|xprt
comma
id|hostname
comma
op_amp
id|pmap_program
comma
id|RPC_PMAP_VERSION
comma
id|RPC_AUTH_NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clnt
)paren
(brace
id|xprt_destroy
c_func
(paren
id|xprt
)paren
suffix:semicolon
)brace
r_else
(brace
id|clnt-&gt;cl_softrtry
op_assign
l_int|1
suffix:semicolon
id|clnt-&gt;cl_chatty
op_assign
l_int|1
suffix:semicolon
id|clnt-&gt;cl_oneshot
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|clnt
suffix:semicolon
)brace
multiline_comment|/*&n; * XDR encode/decode functions for PMAP&n; */
r_static
r_int
DECL|function|xdr_error
id|xdr_error
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_void
op_star
id|dummy
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_static
r_int
DECL|function|xdr_encode_mapping
id|xdr_encode_mapping
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|rpc_portmap
op_star
id|map
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: xdr_encode_mapping(%d, %d, %d, %d)&bslash;n&quot;
comma
id|map-&gt;pm_prog
comma
id|map-&gt;pm_vers
comma
id|map-&gt;pm_prot
comma
id|map-&gt;pm_port
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|map-&gt;pm_prog
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|map-&gt;pm_vers
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|map-&gt;pm_prot
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|map-&gt;pm_port
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|xdr_decode_port
id|xdr_decode_port
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_int
r_int
op_star
id|portp
)paren
(brace
op_star
id|portp
op_assign
(paren
r_int
r_int
)paren
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|xdr_decode_bool
id|xdr_decode_bool
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_int
r_int
op_star
id|boolp
)paren
(brace
op_star
id|boolp
op_assign
(paren
r_int
r_int
)paren
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pmap_procedures
r_static
r_struct
id|rpc_procinfo
id|pmap_procedures
(braket
l_int|4
)braket
op_assign
(brace
(brace
dot
id|p_procname
op_assign
l_string|&quot;pmap_null&quot;
comma
dot
id|p_encode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_error
comma
dot
id|p_decode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_error
comma
dot
id|p_bufsiz
op_assign
l_int|0
comma
dot
id|p_count
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|p_procname
op_assign
l_string|&quot;pmap_set&quot;
comma
dot
id|p_encode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_encode_mapping
comma
dot
id|p_decode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_decode_bool
comma
dot
id|p_bufsiz
op_assign
l_int|4
comma
dot
id|p_count
op_assign
l_int|1
comma
)brace
comma
(brace
dot
id|p_procname
op_assign
l_string|&quot;pmap_unset&quot;
comma
dot
id|p_encode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_encode_mapping
comma
dot
id|p_decode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_decode_bool
comma
dot
id|p_bufsiz
op_assign
l_int|4
comma
dot
id|p_count
op_assign
l_int|1
comma
)brace
comma
(brace
dot
id|p_procname
op_assign
l_string|&quot;pmap_get&quot;
comma
dot
id|p_encode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_encode_mapping
comma
dot
id|p_decode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_decode_port
comma
dot
id|p_bufsiz
op_assign
l_int|4
comma
dot
id|p_count
op_assign
l_int|1
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|pmap_version2
r_static
r_struct
id|rpc_version
id|pmap_version2
op_assign
(brace
dot
id|number
op_assign
l_int|2
comma
dot
id|nrprocs
op_assign
l_int|4
comma
dot
id|procs
op_assign
id|pmap_procedures
)brace
suffix:semicolon
DECL|variable|pmap_version
r_static
r_struct
id|rpc_version
op_star
id|pmap_version
(braket
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|pmap_version2
)brace
suffix:semicolon
DECL|variable|pmap_stats
r_static
r_struct
id|rpc_stat
id|pmap_stats
suffix:semicolon
DECL|variable|pmap_program
r_struct
id|rpc_program
id|pmap_program
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;portmap&quot;
comma
dot
id|number
op_assign
id|RPC_PMAP_PROGRAM
comma
dot
id|nrvers
op_assign
r_sizeof
(paren
id|pmap_version
)paren
op_div
r_sizeof
(paren
id|pmap_version
(braket
l_int|0
)braket
)paren
comma
dot
id|version
op_assign
id|pmap_version
comma
dot
id|stats
op_assign
op_amp
id|pmap_stats
comma
)brace
suffix:semicolon
eof
