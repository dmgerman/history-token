multiline_comment|/*&n; * linux/include/linux/sunrpc/svc.h&n; *&n; * RPC server declarations.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef SUNRPC_SVC_H
DECL|macro|SUNRPC_SVC_H
mdefine_line|#define SUNRPC_SVC_H
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/sunrpc/types.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
macro_line|#include &lt;linux/sunrpc/svcauth.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/*&n; * RPC service.&n; *&n; * An RPC service is a ``daemon,&squot;&squot; possibly multithreaded, which&n; * receives and processes incoming RPC messages.&n; * It has one or more transport sockets associated with it, and maintains&n; * a list of idle threads waiting for input.&n; *&n; * We currently do not support more than one RPC program per daemon.&n; */
DECL|struct|svc_serv
r_struct
id|svc_serv
(brace
DECL|member|sv_threads
r_struct
id|list_head
id|sv_threads
suffix:semicolon
multiline_comment|/* idle server threads */
DECL|member|sv_sockets
r_struct
id|list_head
id|sv_sockets
suffix:semicolon
multiline_comment|/* pending sockets */
DECL|member|sv_program
r_struct
id|svc_program
op_star
id|sv_program
suffix:semicolon
multiline_comment|/* RPC program */
DECL|member|sv_stats
r_struct
id|svc_stat
op_star
id|sv_stats
suffix:semicolon
multiline_comment|/* RPC statistics */
DECL|member|sv_lock
id|spinlock_t
id|sv_lock
suffix:semicolon
DECL|member|sv_nrthreads
r_int
r_int
id|sv_nrthreads
suffix:semicolon
multiline_comment|/* # of server threads */
DECL|member|sv_bufsz
r_int
r_int
id|sv_bufsz
suffix:semicolon
multiline_comment|/* datagram buffer size */
DECL|member|sv_xdrsize
r_int
r_int
id|sv_xdrsize
suffix:semicolon
multiline_comment|/* XDR buffer size */
DECL|member|sv_permsocks
r_struct
id|list_head
id|sv_permsocks
suffix:semicolon
multiline_comment|/* all permanent sockets */
DECL|member|sv_tempsocks
r_struct
id|list_head
id|sv_tempsocks
suffix:semicolon
multiline_comment|/* all temporary sockets */
DECL|member|sv_tmpcnt
r_int
id|sv_tmpcnt
suffix:semicolon
multiline_comment|/* count of temporary sockets */
DECL|member|sv_name
r_char
op_star
id|sv_name
suffix:semicolon
multiline_comment|/* service name */
)brace
suffix:semicolon
multiline_comment|/*&n; * Maximum payload size supported by a kernel RPC server.&n; * This is use to determine the max number of pages nfsd is&n; * willing to return in a single READ operation.&n; */
DECL|macro|RPCSVC_MAXPAYLOAD
mdefine_line|#define RPCSVC_MAXPAYLOAD&t;(64*1024u)
multiline_comment|/*&n; * RPC Requsts and replies are stored in one or more pages.&n; * We maintain an array of pages for each server thread.&n; * Requests are copied into these pages as they arrive.  Remaining&n; * pages are available to write the reply into.&n; *&n; * Currently pages are all re-used by the same server.  Later we &n; * will use -&gt;sendpage to transmit pages with reduced copying.  In&n; * that case we will need to give away the page and allocate new ones.&n; * In preparation for this, we explicitly move pages off the recv&n; * list onto the transmit list, and back.&n; *&n; * We use xdr_buf for holding responses as it fits well with NFS&n; * read responses (that have a header, and some data pages, and possibly&n; * a tail) and means we can share some client side routines.&n; *&n; * The xdr_buf.head iovec always points to the first page in the rq_*pages&n; * list.  The xdr_buf.pages pointer points to the second page on that&n; * list.  xdr_buf.tail points to the end of the first page.&n; * This assumes that the non-page part of an rpc reply will fit&n; * in a page - NFSd ensures this.  lockd also has no trouble.&n; */
DECL|macro|RPCSVC_MAXPAGES
mdefine_line|#define RPCSVC_MAXPAGES&t;&t;((RPCSVC_MAXPAYLOAD+PAGE_SIZE-1)/PAGE_SIZE + 1)
DECL|function|svc_getu32
r_static
r_inline
id|u32
id|svc_getu32
c_func
(paren
r_struct
id|iovec
op_star
id|iov
)paren
(brace
id|u32
id|val
comma
op_star
id|vp
suffix:semicolon
id|vp
op_assign
id|iov-&gt;iov_base
suffix:semicolon
id|val
op_assign
op_star
id|vp
op_increment
suffix:semicolon
id|iov-&gt;iov_base
op_assign
(paren
r_void
op_star
)paren
id|vp
suffix:semicolon
id|iov-&gt;iov_len
op_sub_assign
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|svc_putu32
r_static
r_inline
r_void
id|svc_putu32
c_func
(paren
r_struct
id|iovec
op_star
id|iov
comma
id|u32
id|val
)paren
(brace
id|u32
op_star
id|vp
op_assign
id|iov-&gt;iov_base
op_plus
id|iov-&gt;iov_len
suffix:semicolon
op_star
id|vp
op_assign
id|val
suffix:semicolon
id|iov-&gt;iov_len
op_add_assign
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The context of a single thread, including the request currently being&n; * processed.&n; * NOTE: First two items must be prev/next.&n; */
DECL|struct|svc_rqst
r_struct
id|svc_rqst
(brace
DECL|member|rq_list
r_struct
id|list_head
id|rq_list
suffix:semicolon
multiline_comment|/* idle list */
DECL|member|rq_sock
r_struct
id|svc_sock
op_star
id|rq_sock
suffix:semicolon
multiline_comment|/* socket */
DECL|member|rq_addr
r_struct
id|sockaddr_in
id|rq_addr
suffix:semicolon
multiline_comment|/* peer address */
DECL|member|rq_addrlen
r_int
id|rq_addrlen
suffix:semicolon
DECL|member|rq_server
r_struct
id|svc_serv
op_star
id|rq_server
suffix:semicolon
multiline_comment|/* RPC service definition */
DECL|member|rq_procinfo
r_struct
id|svc_procedure
op_star
id|rq_procinfo
suffix:semicolon
multiline_comment|/* procedure info */
DECL|member|rq_authop
r_struct
id|auth_ops
op_star
id|rq_authop
suffix:semicolon
multiline_comment|/* authentication flavour */
DECL|member|rq_cred
r_struct
id|svc_cred
id|rq_cred
suffix:semicolon
multiline_comment|/* auth info */
DECL|member|rq_skbuff
r_struct
id|sk_buff
op_star
id|rq_skbuff
suffix:semicolon
multiline_comment|/* fast recv inet buffer */
DECL|member|rq_deferred
r_struct
id|svc_deferred_req
op_star
id|rq_deferred
suffix:semicolon
multiline_comment|/* deferred request we are replaying */
DECL|member|rq_arg
r_struct
id|xdr_buf
id|rq_arg
suffix:semicolon
DECL|member|rq_res
r_struct
id|xdr_buf
id|rq_res
suffix:semicolon
DECL|member|rq_argpages
r_struct
id|page
op_star
id|rq_argpages
(braket
id|RPCSVC_MAXPAGES
)braket
suffix:semicolon
DECL|member|rq_respages
r_struct
id|page
op_star
id|rq_respages
(braket
id|RPCSVC_MAXPAGES
)braket
suffix:semicolon
DECL|member|rq_restailpage
r_int
id|rq_restailpage
suffix:semicolon
DECL|member|rq_argused
r_int
id|rq_argused
suffix:semicolon
multiline_comment|/* pages used for argument */
DECL|member|rq_arghi
r_int
id|rq_arghi
suffix:semicolon
multiline_comment|/* pages available in argument page list */
DECL|member|rq_resused
r_int
id|rq_resused
suffix:semicolon
multiline_comment|/* pages used for result */
DECL|member|rq_xid
id|u32
id|rq_xid
suffix:semicolon
multiline_comment|/* transmission id */
DECL|member|rq_prog
id|u32
id|rq_prog
suffix:semicolon
multiline_comment|/* program number */
DECL|member|rq_vers
id|u32
id|rq_vers
suffix:semicolon
multiline_comment|/* program version */
DECL|member|rq_proc
id|u32
id|rq_proc
suffix:semicolon
multiline_comment|/* procedure number */
DECL|member|rq_prot
id|u32
id|rq_prot
suffix:semicolon
multiline_comment|/* IP protocol */
r_int
r_int
DECL|member|rq_userset
id|rq_userset
suffix:colon
l_int|1
comma
multiline_comment|/* auth-&gt;setuser OK */
DECL|member|rq_secure
id|rq_secure
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* secure port */
DECL|member|rq_argp
r_void
op_star
id|rq_argp
suffix:semicolon
multiline_comment|/* decoded arguments */
DECL|member|rq_resp
r_void
op_star
id|rq_resp
suffix:semicolon
multiline_comment|/* xdr&squot;d results */
DECL|member|rq_reserved
r_int
id|rq_reserved
suffix:semicolon
multiline_comment|/* space on socket outq&n;&t;&t;&t;&t;&t;&t; * reserved for this request&n;&t;&t;&t;&t;&t;&t; */
DECL|member|rq_chandle
r_struct
id|cache_req
id|rq_chandle
suffix:semicolon
multiline_comment|/* handle passed to caches for &n;&t;&t;&t;&t;&t;&t; * request delaying &n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* Catering to nfsd */
DECL|member|rq_client
r_struct
id|auth_domain
op_star
id|rq_client
suffix:semicolon
multiline_comment|/* RPC peer info */
DECL|member|rq_cacherep
r_struct
id|svc_cacherep
op_star
id|rq_cacherep
suffix:semicolon
multiline_comment|/* cache info */
DECL|member|rq_reffh
r_struct
id|knfsd_fh
op_star
id|rq_reffh
suffix:semicolon
multiline_comment|/* Referrence filehandle, used to&n;&t;&t;&t;&t;&t;&t; * determine what device number&n;&t;&t;&t;&t;&t;&t; * to report (real or virtual)&n;&t;&t;&t;&t;&t;&t; */
DECL|member|rq_wait
id|wait_queue_head_t
id|rq_wait
suffix:semicolon
multiline_comment|/* synchronization */
)brace
suffix:semicolon
multiline_comment|/*&n; * Check buffer bounds after decoding arguments&n; */
r_static
r_inline
r_int
DECL|function|xdr_argsize_check
id|xdr_argsize_check
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
)paren
(brace
r_char
op_star
id|cp
op_assign
(paren
r_char
op_star
)paren
id|p
suffix:semicolon
r_struct
id|iovec
op_star
id|vec
op_assign
op_amp
id|rqstp-&gt;rq_arg.head
(braket
l_int|0
)braket
suffix:semicolon
r_return
id|cp
op_minus
(paren
r_char
op_star
)paren
id|vec-&gt;iov_base
op_le
id|vec-&gt;iov_len
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|xdr_ressize_check
id|xdr_ressize_check
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
)paren
(brace
r_struct
id|iovec
op_star
id|vec
op_assign
op_amp
id|rqstp-&gt;rq_res.head
(braket
l_int|0
)braket
suffix:semicolon
r_char
op_star
id|cp
op_assign
(paren
r_char
op_star
)paren
id|p
suffix:semicolon
id|vec-&gt;iov_len
op_assign
id|cp
op_minus
(paren
r_char
op_star
)paren
id|vec-&gt;iov_base
suffix:semicolon
r_return
id|vec-&gt;iov_len
op_le
id|PAGE_SIZE
suffix:semicolon
)brace
DECL|function|svc_take_page
r_static
r_inline
r_int
id|svc_take_page
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
)paren
(brace
r_if
c_cond
(paren
id|rqstp-&gt;rq_arghi
op_le
id|rqstp-&gt;rq_argused
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|rqstp-&gt;rq_arghi
op_decrement
suffix:semicolon
id|rqstp-&gt;rq_respages
(braket
id|rqstp-&gt;rq_resused
)braket
op_assign
id|rqstp-&gt;rq_argpages
(braket
id|rqstp-&gt;rq_arghi
)braket
suffix:semicolon
id|rqstp-&gt;rq_resused
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|svc_pushback_allpages
r_static
r_inline
r_void
id|svc_pushback_allpages
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
)paren
(brace
r_while
c_loop
(paren
id|rqstp-&gt;rq_resused
)paren
(brace
r_if
c_cond
(paren
id|rqstp-&gt;rq_respages
(braket
op_decrement
id|rqstp-&gt;rq_resused
)braket
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|rqstp-&gt;rq_argpages
(braket
id|rqstp-&gt;rq_arghi
op_increment
)braket
op_assign
id|rqstp-&gt;rq_respages
(braket
id|rqstp-&gt;rq_resused
)braket
suffix:semicolon
id|rqstp-&gt;rq_respages
(braket
id|rqstp-&gt;rq_resused
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|svc_pushback_unused_pages
r_static
r_inline
r_void
id|svc_pushback_unused_pages
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
)paren
(brace
r_while
c_loop
(paren
id|rqstp-&gt;rq_resused
op_logical_and
id|rqstp-&gt;rq_res.pages
op_ne
op_amp
id|rqstp-&gt;rq_respages
(braket
id|rqstp-&gt;rq_resused
)braket
)paren
(brace
r_if
c_cond
(paren
id|rqstp-&gt;rq_respages
(braket
op_decrement
id|rqstp-&gt;rq_resused
)braket
op_ne
l_int|NULL
)paren
(brace
id|rqstp-&gt;rq_argpages
(braket
id|rqstp-&gt;rq_arghi
op_increment
)braket
op_assign
id|rqstp-&gt;rq_respages
(braket
id|rqstp-&gt;rq_resused
)braket
suffix:semicolon
id|rqstp-&gt;rq_respages
(braket
id|rqstp-&gt;rq_resused
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
DECL|function|svc_free_allpages
r_static
r_inline
r_void
id|svc_free_allpages
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
)paren
(brace
r_while
c_loop
(paren
id|rqstp-&gt;rq_resused
)paren
(brace
r_if
c_cond
(paren
id|rqstp-&gt;rq_respages
(braket
op_decrement
id|rqstp-&gt;rq_resused
)braket
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|put_page
c_func
(paren
id|rqstp-&gt;rq_respages
(braket
id|rqstp-&gt;rq_resused
)braket
)paren
suffix:semicolon
id|rqstp-&gt;rq_respages
(braket
id|rqstp-&gt;rq_resused
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|struct|svc_deferred_req
r_struct
id|svc_deferred_req
(brace
DECL|member|serv
r_struct
id|svc_serv
op_star
id|serv
suffix:semicolon
DECL|member|prot
id|u32
id|prot
suffix:semicolon
multiline_comment|/* protocol (UDP or TCP) */
DECL|member|addr
r_struct
id|sockaddr_in
id|addr
suffix:semicolon
DECL|member|svsk
r_struct
id|svc_sock
op_star
id|svsk
suffix:semicolon
multiline_comment|/* where reply must go */
DECL|member|handle
r_struct
id|cache_deferred_req
id|handle
suffix:semicolon
DECL|member|argslen
r_int
id|argslen
suffix:semicolon
DECL|member|args
id|u32
id|args
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * RPC program&n; */
DECL|struct|svc_program
r_struct
id|svc_program
(brace
DECL|member|pg_prog
id|u32
id|pg_prog
suffix:semicolon
multiline_comment|/* program number */
DECL|member|pg_lovers
r_int
r_int
id|pg_lovers
suffix:semicolon
multiline_comment|/* lowest version */
DECL|member|pg_hivers
r_int
r_int
id|pg_hivers
suffix:semicolon
multiline_comment|/* lowest version */
DECL|member|pg_nvers
r_int
r_int
id|pg_nvers
suffix:semicolon
multiline_comment|/* number of versions */
DECL|member|pg_vers
r_struct
id|svc_version
op_star
op_star
id|pg_vers
suffix:semicolon
multiline_comment|/* version array */
DECL|member|pg_name
r_char
op_star
id|pg_name
suffix:semicolon
multiline_comment|/* service name */
DECL|member|pg_class
r_char
op_star
id|pg_class
suffix:semicolon
multiline_comment|/* class name: services sharing authentication */
DECL|member|pg_stats
r_struct
id|svc_stat
op_star
id|pg_stats
suffix:semicolon
multiline_comment|/* rpc statistics */
)brace
suffix:semicolon
multiline_comment|/*&n; * RPC program version&n; */
DECL|struct|svc_version
r_struct
id|svc_version
(brace
DECL|member|vs_vers
id|u32
id|vs_vers
suffix:semicolon
multiline_comment|/* version number */
DECL|member|vs_nproc
id|u32
id|vs_nproc
suffix:semicolon
multiline_comment|/* number of procedures */
DECL|member|vs_proc
r_struct
id|svc_procedure
op_star
id|vs_proc
suffix:semicolon
multiline_comment|/* per-procedure info */
DECL|member|vs_xdrsize
id|u32
id|vs_xdrsize
suffix:semicolon
multiline_comment|/* xdrsize needed for this version */
multiline_comment|/* Override dispatch function (e.g. when caching replies).&n;&t; * A return value of 0 means drop the request. &n;&t; * vs_dispatch == NULL means use default dispatcher.&n;&t; */
DECL|member|vs_dispatch
r_int
(paren
op_star
id|vs_dispatch
)paren
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * RPC procedure info&n; */
DECL|typedef|svc_procfunc
r_typedef
r_int
(paren
op_star
id|svc_procfunc
)paren
(paren
r_struct
id|svc_rqst
op_star
comma
r_void
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
suffix:semicolon
DECL|struct|svc_procedure
r_struct
id|svc_procedure
(brace
DECL|member|pc_func
id|svc_procfunc
id|pc_func
suffix:semicolon
multiline_comment|/* process the request */
DECL|member|pc_decode
id|kxdrproc_t
id|pc_decode
suffix:semicolon
multiline_comment|/* XDR decode args */
DECL|member|pc_encode
id|kxdrproc_t
id|pc_encode
suffix:semicolon
multiline_comment|/* XDR encode result */
DECL|member|pc_release
id|kxdrproc_t
id|pc_release
suffix:semicolon
multiline_comment|/* XDR free result */
DECL|member|pc_argsize
r_int
r_int
id|pc_argsize
suffix:semicolon
multiline_comment|/* argument struct size */
DECL|member|pc_ressize
r_int
r_int
id|pc_ressize
suffix:semicolon
multiline_comment|/* result struct size */
DECL|member|pc_count
r_int
r_int
id|pc_count
suffix:semicolon
multiline_comment|/* call count */
DECL|member|pc_cachetype
r_int
r_int
id|pc_cachetype
suffix:semicolon
multiline_comment|/* cache info (NFS) */
DECL|member|pc_xdrressize
r_int
r_int
id|pc_xdrressize
suffix:semicolon
multiline_comment|/* maximum size of XDR reply */
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the RPC server thread function prototype&n; */
DECL|typedef|svc_thread_fn
r_typedef
r_void
(paren
op_star
id|svc_thread_fn
)paren
(paren
r_struct
id|svc_rqst
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Function prototypes.&n; */
r_struct
id|svc_serv
op_star
id|svc_create
c_func
(paren
r_struct
id|svc_program
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|svc_create_thread
c_func
(paren
id|svc_thread_fn
comma
r_struct
id|svc_serv
op_star
)paren
suffix:semicolon
r_void
id|svc_exit_thread
c_func
(paren
r_struct
id|svc_rqst
op_star
)paren
suffix:semicolon
r_void
id|svc_destroy
c_func
(paren
r_struct
id|svc_serv
op_star
)paren
suffix:semicolon
r_int
id|svc_process
c_func
(paren
r_struct
id|svc_serv
op_star
comma
r_struct
id|svc_rqst
op_star
)paren
suffix:semicolon
r_int
id|svc_register
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
id|svc_wake_up
c_func
(paren
r_struct
id|svc_serv
op_star
)paren
suffix:semicolon
r_void
id|svc_reserve
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_int
id|space
)paren
suffix:semicolon
macro_line|#endif /* SUNRPC_SVC_H */
eof
