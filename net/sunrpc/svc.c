multiline_comment|/*&n; * linux/net/sunrpc/svc.c&n; *&n; * High-level RPC service routines&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/sunrpc/types.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
macro_line|#include &lt;linux/sunrpc/stats.h&gt;
macro_line|#include &lt;linux/sunrpc/svcsock.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
DECL|macro|RPCDBG_FACILITY
mdefine_line|#define RPCDBG_FACILITY&t;RPCDBG_SVCDSP
DECL|macro|RPC_PARANOIA
mdefine_line|#define RPC_PARANOIA 1
multiline_comment|/*&n; * Create an RPC service&n; */
r_struct
id|svc_serv
op_star
DECL|function|svc_create
id|svc_create
c_func
(paren
r_struct
id|svc_program
op_star
id|prog
comma
r_int
r_int
id|bufsize
comma
r_int
r_int
id|xdrsize
)paren
(brace
r_struct
id|svc_serv
op_star
id|serv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|serv
op_assign
(paren
r_struct
id|svc_serv
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|serv
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|serv
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|serv
)paren
)paren
suffix:semicolon
id|serv-&gt;sv_program
op_assign
id|prog
suffix:semicolon
id|serv-&gt;sv_nrthreads
op_assign
l_int|1
suffix:semicolon
id|serv-&gt;sv_stats
op_assign
id|prog-&gt;pg_stats
suffix:semicolon
id|serv-&gt;sv_bufsz
op_assign
id|bufsize
ques
c_cond
id|bufsize
suffix:colon
l_int|4096
suffix:semicolon
id|serv-&gt;sv_xdrsize
op_assign
id|xdrsize
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|serv-&gt;sv_threads
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|serv-&gt;sv_sockets
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|serv-&gt;sv_tempsocks
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|serv-&gt;sv_permsocks
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|serv-&gt;sv_lock
)paren
suffix:semicolon
id|serv-&gt;sv_name
op_assign
id|prog-&gt;pg_name
suffix:semicolon
multiline_comment|/* Remove any stale portmap registrations */
id|svc_register
c_func
(paren
id|serv
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|serv
suffix:semicolon
)brace
multiline_comment|/*&n; * Destroy an RPC service&n; */
r_void
DECL|function|svc_destroy
id|svc_destroy
c_func
(paren
r_struct
id|svc_serv
op_star
id|serv
)paren
(brace
r_struct
id|svc_sock
op_star
id|svsk
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: svc_destroy(%s, %d)&bslash;n&quot;
comma
id|serv-&gt;sv_program-&gt;pg_name
comma
id|serv-&gt;sv_nrthreads
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serv-&gt;sv_nrthreads
)paren
(brace
r_if
c_cond
(paren
op_decrement
(paren
id|serv-&gt;sv_nrthreads
)paren
op_ne
l_int|0
)paren
(brace
id|svc_sock_update_bufs
c_func
(paren
id|serv
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;svc_destroy: no threads for serv=%p!&bslash;n&quot;
comma
id|serv
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|serv-&gt;sv_tempsocks
)paren
)paren
(brace
id|svsk
op_assign
id|list_entry
c_func
(paren
id|serv-&gt;sv_tempsocks.next
comma
r_struct
id|svc_sock
comma
id|sk_list
)paren
suffix:semicolon
id|svc_delete_socket
c_func
(paren
id|svsk
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|serv-&gt;sv_permsocks
)paren
)paren
(brace
id|svsk
op_assign
id|list_entry
c_func
(paren
id|serv-&gt;sv_permsocks.next
comma
r_struct
id|svc_sock
comma
id|sk_list
)paren
suffix:semicolon
id|svc_delete_socket
c_func
(paren
id|svsk
)paren
suffix:semicolon
)brace
multiline_comment|/* Unregister service with the portmapper */
id|svc_register
c_func
(paren
id|serv
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|serv
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate an RPC server buffer&n; * Later versions may do nifty things by allocating multiple pages&n; * of memory directly and putting them into the bufp-&gt;iov.&n; */
r_int
DECL|function|svc_init_buffer
id|svc_init_buffer
c_func
(paren
r_struct
id|svc_buf
op_star
id|bufp
comma
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bufp-&gt;area
op_assign
(paren
id|u32
op_star
)paren
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|bufp-&gt;base
op_assign
id|bufp-&gt;area
suffix:semicolon
id|bufp-&gt;buf
op_assign
id|bufp-&gt;area
suffix:semicolon
id|bufp-&gt;len
op_assign
l_int|0
suffix:semicolon
id|bufp-&gt;buflen
op_assign
id|size
op_rshift
l_int|2
suffix:semicolon
id|bufp-&gt;iov
(braket
l_int|0
)braket
dot
id|iov_base
op_assign
id|bufp-&gt;area
suffix:semicolon
id|bufp-&gt;iov
(braket
l_int|0
)braket
dot
id|iov_len
op_assign
id|size
suffix:semicolon
id|bufp-&gt;nriov
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Release an RPC server buffer&n; */
r_void
DECL|function|svc_release_buffer
id|svc_release_buffer
c_func
(paren
r_struct
id|svc_buf
op_star
id|bufp
)paren
(brace
id|kfree
c_func
(paren
id|bufp-&gt;area
)paren
suffix:semicolon
id|bufp-&gt;area
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Create a server thread&n; */
r_int
DECL|function|svc_create_thread
id|svc_create_thread
c_func
(paren
id|svc_thread_fn
id|func
comma
r_struct
id|svc_serv
op_star
id|serv
)paren
(brace
r_struct
id|svc_rqst
op_star
id|rqstp
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|rqstp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|rqstp
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rqstp
)paren
r_goto
id|out
suffix:semicolon
id|memset
c_func
(paren
id|rqstp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|rqstp
)paren
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|rqstp-&gt;rq_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rqstp-&gt;rq_argp
op_assign
(paren
id|u32
op_star
)paren
id|kmalloc
c_func
(paren
id|serv-&gt;sv_xdrsize
comma
id|GFP_KERNEL
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|rqstp-&gt;rq_resp
op_assign
(paren
id|u32
op_star
)paren
id|kmalloc
c_func
(paren
id|serv-&gt;sv_xdrsize
comma
id|GFP_KERNEL
)paren
)paren
op_logical_or
op_logical_neg
id|svc_init_buffer
c_func
(paren
op_amp
id|rqstp-&gt;rq_defbuf
comma
id|serv-&gt;sv_bufsz
)paren
)paren
r_goto
id|out_thread
suffix:semicolon
id|serv-&gt;sv_nrthreads
op_increment
suffix:semicolon
id|rqstp-&gt;rq_server
op_assign
id|serv
suffix:semicolon
id|error
op_assign
id|kernel_thread
c_func
(paren
(paren
r_int
(paren
op_star
)paren
(paren
r_void
op_star
)paren
)paren
id|func
comma
id|rqstp
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
r_goto
id|out_thread
suffix:semicolon
id|svc_sock_update_bufs
c_func
(paren
id|serv
)paren
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
id|out_thread
suffix:colon
id|svc_exit_thread
c_func
(paren
id|rqstp
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n; * Destroy an RPC server thread&n; */
r_void
DECL|function|svc_exit_thread
id|svc_exit_thread
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
)paren
(brace
r_struct
id|svc_serv
op_star
id|serv
op_assign
id|rqstp-&gt;rq_server
suffix:semicolon
id|svc_release_buffer
c_func
(paren
op_amp
id|rqstp-&gt;rq_defbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rqstp-&gt;rq_resp
)paren
id|kfree
c_func
(paren
id|rqstp-&gt;rq_resp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rqstp-&gt;rq_argp
)paren
id|kfree
c_func
(paren
id|rqstp-&gt;rq_argp
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|rqstp
)paren
suffix:semicolon
multiline_comment|/* Release the server */
r_if
c_cond
(paren
id|serv
)paren
id|svc_destroy
c_func
(paren
id|serv
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Register an RPC service with the local portmapper.&n; * To unregister a service, call this routine with &n; * proto and port == 0.&n; */
r_int
DECL|function|svc_register
id|svc_register
c_func
(paren
r_struct
id|svc_serv
op_star
id|serv
comma
r_int
id|proto
comma
r_int
r_int
id|port
)paren
(brace
r_struct
id|svc_program
op_star
id|progp
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
comma
id|error
op_assign
l_int|0
comma
id|dummy
suffix:semicolon
id|progp
op_assign
id|serv-&gt;sv_program
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: svc_register(%s, %s, %d)&bslash;n&quot;
comma
id|progp-&gt;pg_name
comma
id|proto
op_eq
id|IPPROTO_UDP
ques
c_cond
l_string|&quot;udp&quot;
suffix:colon
l_string|&quot;tcp&quot;
comma
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port
)paren
id|clear_thread_flag
c_func
(paren
id|TIF_SIGPENDING
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|progp-&gt;pg_nvers
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|progp-&gt;pg_vers
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|error
op_assign
id|rpc_register
c_func
(paren
id|progp-&gt;pg_prog
comma
id|i
comma
id|proto
comma
id|port
comma
op_amp
id|dummy
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|port
op_logical_and
op_logical_neg
id|dummy
)paren
(brace
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|port
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Process the RPC request.&n; */
r_int
DECL|function|svc_process
id|svc_process
c_func
(paren
r_struct
id|svc_serv
op_star
id|serv
comma
r_struct
id|svc_rqst
op_star
id|rqstp
)paren
(brace
r_struct
id|svc_program
op_star
id|progp
suffix:semicolon
r_struct
id|svc_version
op_star
id|versp
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* compiler food */
r_struct
id|svc_procedure
op_star
id|procp
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|svc_buf
op_star
id|argp
op_assign
op_amp
id|rqstp-&gt;rq_argbuf
suffix:semicolon
r_struct
id|svc_buf
op_star
id|resp
op_assign
op_amp
id|rqstp-&gt;rq_resbuf
suffix:semicolon
id|kxdrproc_t
id|xdr
suffix:semicolon
id|u32
op_star
id|bufp
comma
op_star
id|statp
suffix:semicolon
id|u32
id|dir
comma
id|prog
comma
id|vers
comma
id|proc
comma
id|auth_stat
comma
id|rpc_stat
suffix:semicolon
id|rpc_stat
op_assign
id|rpc_success
suffix:semicolon
id|bufp
op_assign
id|argp-&gt;buf
suffix:semicolon
r_if
c_cond
(paren
id|argp-&gt;len
OL
l_int|5
)paren
r_goto
id|err_short_len
suffix:semicolon
id|dir
op_assign
id|ntohl
c_func
(paren
op_star
id|bufp
op_increment
)paren
suffix:semicolon
id|vers
op_assign
id|ntohl
c_func
(paren
op_star
id|bufp
op_increment
)paren
suffix:semicolon
multiline_comment|/* First words of reply: */
id|svc_putlong
c_func
(paren
id|resp
comma
id|xdr_one
)paren
suffix:semicolon
multiline_comment|/* REPLY */
id|svc_putlong
c_func
(paren
id|resp
comma
id|xdr_zero
)paren
suffix:semicolon
multiline_comment|/* ACCEPT */
r_if
c_cond
(paren
id|dir
op_ne
l_int|0
)paren
multiline_comment|/* direction != CALL */
r_goto
id|err_bad_dir
suffix:semicolon
r_if
c_cond
(paren
id|vers
op_ne
l_int|2
)paren
multiline_comment|/* RPC version number */
r_goto
id|err_bad_rpc
suffix:semicolon
id|rqstp-&gt;rq_prog
op_assign
id|prog
op_assign
id|ntohl
c_func
(paren
op_star
id|bufp
op_increment
)paren
suffix:semicolon
multiline_comment|/* program number */
id|rqstp-&gt;rq_vers
op_assign
id|vers
op_assign
id|ntohl
c_func
(paren
op_star
id|bufp
op_increment
)paren
suffix:semicolon
multiline_comment|/* version number */
id|rqstp-&gt;rq_proc
op_assign
id|proc
op_assign
id|ntohl
c_func
(paren
op_star
id|bufp
op_increment
)paren
suffix:semicolon
multiline_comment|/* procedure number */
id|argp-&gt;buf
op_add_assign
l_int|5
suffix:semicolon
id|argp-&gt;len
op_sub_assign
l_int|5
suffix:semicolon
multiline_comment|/* Used by nfsd to only allow the NULL procedure for amd. */
r_if
c_cond
(paren
id|rqstp-&gt;rq_auth
op_logical_and
op_logical_neg
id|rqstp-&gt;rq_client
op_logical_and
id|proc
)paren
(brace
id|auth_stat
op_assign
id|rpc_autherr_badcred
suffix:semicolon
r_goto
id|err_bad_auth
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Decode auth data, and add verifier to reply buffer.&n;&t; * We do this before anything else in order to get a decent&n;&t; * auth verifier.&n;&t; */
id|svc_authenticate
c_func
(paren
id|rqstp
comma
op_amp
id|rpc_stat
comma
op_amp
id|auth_stat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rpc_stat
op_ne
id|rpc_success
)paren
r_goto
id|err_garbage
suffix:semicolon
r_if
c_cond
(paren
id|auth_stat
op_ne
id|rpc_auth_ok
)paren
r_goto
id|err_bad_auth
suffix:semicolon
id|progp
op_assign
id|serv-&gt;sv_program
suffix:semicolon
r_if
c_cond
(paren
id|prog
op_ne
id|progp-&gt;pg_prog
)paren
r_goto
id|err_bad_prog
suffix:semicolon
r_if
c_cond
(paren
id|vers
op_ge
id|progp-&gt;pg_nvers
op_logical_or
op_logical_neg
(paren
id|versp
op_assign
id|progp-&gt;pg_vers
(braket
id|vers
)braket
)paren
)paren
r_goto
id|err_bad_vers
suffix:semicolon
id|procp
op_assign
id|versp-&gt;vs_proc
op_plus
id|proc
suffix:semicolon
r_if
c_cond
(paren
id|proc
op_ge
id|versp-&gt;vs_nproc
op_logical_or
op_logical_neg
id|procp-&gt;pc_func
)paren
r_goto
id|err_bad_proc
suffix:semicolon
id|rqstp-&gt;rq_server
op_assign
id|serv
suffix:semicolon
id|rqstp-&gt;rq_procinfo
op_assign
id|procp
suffix:semicolon
multiline_comment|/* Syntactic check complete */
id|serv-&gt;sv_stats-&gt;rpccnt
op_increment
suffix:semicolon
multiline_comment|/* Build the reply header. */
id|statp
op_assign
id|resp-&gt;buf
suffix:semicolon
id|svc_putlong
c_func
(paren
id|resp
comma
id|rpc_success
)paren
suffix:semicolon
multiline_comment|/* RPC_SUCCESS */
multiline_comment|/* Bump per-procedure stats counter */
id|procp-&gt;pc_count
op_increment
suffix:semicolon
multiline_comment|/* Initialize storage for argp and resp */
id|memset
c_func
(paren
id|rqstp-&gt;rq_argp
comma
l_int|0
comma
id|procp-&gt;pc_argsize
)paren
suffix:semicolon
id|memset
c_func
(paren
id|rqstp-&gt;rq_resp
comma
l_int|0
comma
id|procp-&gt;pc_ressize
)paren
suffix:semicolon
multiline_comment|/* un-reserve some of the out-queue now that we have a &n;&t; * better idea of reply size&n;&t; */
r_if
c_cond
(paren
id|procp-&gt;pc_xdrressize
)paren
id|svc_reserve
c_func
(paren
id|rqstp
comma
id|procp-&gt;pc_xdrressize
op_lshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Call the function that processes the request. */
r_if
c_cond
(paren
op_logical_neg
id|versp-&gt;vs_dispatch
)paren
(brace
multiline_comment|/* Decode arguments */
id|xdr
op_assign
id|procp-&gt;pc_decode
suffix:semicolon
r_if
c_cond
(paren
id|xdr
op_logical_and
op_logical_neg
id|xdr
c_func
(paren
id|rqstp
comma
id|rqstp-&gt;rq_argbuf.buf
comma
id|rqstp-&gt;rq_argp
)paren
)paren
r_goto
id|err_garbage
suffix:semicolon
op_star
id|statp
op_assign
id|procp
op_member_access_from_pointer
id|pc_func
c_func
(paren
id|rqstp
comma
id|rqstp-&gt;rq_argp
comma
id|rqstp-&gt;rq_resp
)paren
suffix:semicolon
multiline_comment|/* Encode reply */
r_if
c_cond
(paren
op_star
id|statp
op_eq
id|rpc_success
op_logical_and
(paren
id|xdr
op_assign
id|procp-&gt;pc_encode
)paren
op_logical_and
op_logical_neg
id|xdr
c_func
(paren
id|rqstp
comma
id|rqstp-&gt;rq_resbuf.buf
comma
id|rqstp-&gt;rq_resp
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;svc: failed to encode reply&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* serv-&gt;sv_stats-&gt;rpcsystemerr++; */
op_star
id|statp
op_assign
id|rpc_system_err
suffix:semicolon
)brace
)brace
r_else
(brace
id|dprintk
c_func
(paren
l_string|&quot;svc: calling dispatcher&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|versp
op_member_access_from_pointer
id|vs_dispatch
c_func
(paren
id|rqstp
comma
id|statp
)paren
)paren
r_goto
id|dropit
suffix:semicolon
)brace
multiline_comment|/* Check RPC status result */
r_if
c_cond
(paren
op_star
id|statp
op_ne
id|rpc_success
)paren
id|resp-&gt;len
op_assign
id|statp
op_plus
l_int|1
op_minus
id|resp-&gt;base
suffix:semicolon
multiline_comment|/* Release reply info */
r_if
c_cond
(paren
id|procp-&gt;pc_release
)paren
id|procp
op_member_access_from_pointer
id|pc_release
c_func
(paren
id|rqstp
comma
l_int|NULL
comma
id|rqstp-&gt;rq_resp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|procp-&gt;pc_encode
op_eq
l_int|NULL
)paren
r_goto
id|dropit
suffix:semicolon
id|sendit
suffix:colon
r_return
id|svc_send
c_func
(paren
id|rqstp
)paren
suffix:semicolon
id|dropit
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;svc: svc_process dropit&bslash;n&quot;
)paren
suffix:semicolon
id|svc_drop
c_func
(paren
id|rqstp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_short_len
suffix:colon
macro_line|#ifdef RPC_PARANOIA
id|printk
c_func
(paren
l_string|&quot;svc: short len %d, dropping request&bslash;n&quot;
comma
id|argp-&gt;len
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|dropit
suffix:semicolon
multiline_comment|/* drop request */
id|err_bad_dir
suffix:colon
macro_line|#ifdef RPC_PARANOIA
id|printk
c_func
(paren
l_string|&quot;svc: bad direction %d, dropping request&bslash;n&quot;
comma
id|dir
)paren
suffix:semicolon
macro_line|#endif
id|serv-&gt;sv_stats-&gt;rpcbadfmt
op_increment
suffix:semicolon
r_goto
id|dropit
suffix:semicolon
multiline_comment|/* drop request */
id|err_bad_rpc
suffix:colon
id|serv-&gt;sv_stats-&gt;rpcbadfmt
op_increment
suffix:semicolon
id|resp-&gt;buf
(braket
op_minus
l_int|1
)braket
op_assign
id|xdr_one
suffix:semicolon
multiline_comment|/* REJECT */
id|svc_putlong
c_func
(paren
id|resp
comma
id|xdr_zero
)paren
suffix:semicolon
multiline_comment|/* RPC_MISMATCH */
id|svc_putlong
c_func
(paren
id|resp
comma
id|xdr_two
)paren
suffix:semicolon
multiline_comment|/* Only RPCv2 supported */
id|svc_putlong
c_func
(paren
id|resp
comma
id|xdr_two
)paren
suffix:semicolon
r_goto
id|sendit
suffix:semicolon
id|err_bad_auth
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;svc: authentication failed (%d)&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|auth_stat
)paren
)paren
suffix:semicolon
id|serv-&gt;sv_stats-&gt;rpcbadauth
op_increment
suffix:semicolon
id|resp-&gt;buf
(braket
op_minus
l_int|1
)braket
op_assign
id|xdr_one
suffix:semicolon
multiline_comment|/* REJECT */
id|svc_putlong
c_func
(paren
id|resp
comma
id|xdr_one
)paren
suffix:semicolon
multiline_comment|/* AUTH_ERROR */
id|svc_putlong
c_func
(paren
id|resp
comma
id|auth_stat
)paren
suffix:semicolon
multiline_comment|/* status */
r_goto
id|sendit
suffix:semicolon
id|err_bad_prog
suffix:colon
macro_line|#ifdef RPC_PARANOIA
r_if
c_cond
(paren
id|prog
op_ne
l_int|100227
op_logical_or
id|progp-&gt;pg_prog
op_ne
l_int|100003
)paren
id|printk
c_func
(paren
l_string|&quot;svc: unknown program %d (me %d)&bslash;n&quot;
comma
id|prog
comma
id|progp-&gt;pg_prog
)paren
suffix:semicolon
multiline_comment|/* else it is just a Solaris client seeing if ACLs are supported */
macro_line|#endif
id|serv-&gt;sv_stats-&gt;rpcbadfmt
op_increment
suffix:semicolon
id|svc_putlong
c_func
(paren
id|resp
comma
id|rpc_prog_unavail
)paren
suffix:semicolon
r_goto
id|sendit
suffix:semicolon
id|err_bad_vers
suffix:colon
macro_line|#ifdef RPC_PARANOIA
id|printk
c_func
(paren
l_string|&quot;svc: unknown version (%d)&bslash;n&quot;
comma
id|vers
)paren
suffix:semicolon
macro_line|#endif
id|serv-&gt;sv_stats-&gt;rpcbadfmt
op_increment
suffix:semicolon
id|svc_putlong
c_func
(paren
id|resp
comma
id|rpc_prog_mismatch
)paren
suffix:semicolon
id|svc_putlong
c_func
(paren
id|resp
comma
id|htonl
c_func
(paren
id|progp-&gt;pg_lovers
)paren
)paren
suffix:semicolon
id|svc_putlong
c_func
(paren
id|resp
comma
id|htonl
c_func
(paren
id|progp-&gt;pg_hivers
)paren
)paren
suffix:semicolon
r_goto
id|sendit
suffix:semicolon
id|err_bad_proc
suffix:colon
macro_line|#ifdef RPC_PARANOIA
id|printk
c_func
(paren
l_string|&quot;svc: unknown procedure (%d)&bslash;n&quot;
comma
id|proc
)paren
suffix:semicolon
macro_line|#endif
id|serv-&gt;sv_stats-&gt;rpcbadfmt
op_increment
suffix:semicolon
id|svc_putlong
c_func
(paren
id|resp
comma
id|rpc_proc_unavail
)paren
suffix:semicolon
r_goto
id|sendit
suffix:semicolon
id|err_garbage
suffix:colon
macro_line|#ifdef RPC_PARANOIA
id|printk
c_func
(paren
l_string|&quot;svc: failed to decode args&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|serv-&gt;sv_stats-&gt;rpcbadfmt
op_increment
suffix:semicolon
id|svc_putlong
c_func
(paren
id|resp
comma
id|rpc_garbage_args
)paren
suffix:semicolon
r_goto
id|sendit
suffix:semicolon
)brace
eof
