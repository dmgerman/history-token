multiline_comment|/*&n; * linux/include/linux/sunrpc/svc.h&n; *&n; * RPC server declarations.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef SUNRPC_SVC_H
DECL|macro|SUNRPC_SVC_H
mdefine_line|#define SUNRPC_SVC_H
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/sunrpc/types.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
macro_line|#include &lt;linux/sunrpc/svcauth.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
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
DECL|member|sv_allsocks
r_struct
id|list_head
id|sv_allsocks
suffix:semicolon
multiline_comment|/* all sockets */
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
mdefine_line|#define RPCSVC_MAXPAYLOAD&t;16384u
multiline_comment|/*&n; * Buffer to store RPC requests or replies in.&n; * Each server thread has one of these beasts.&n; *&n; * Area points to the allocated memory chunk currently owned by the&n; * buffer. Base points to the buffer containing the request, which is&n; * different from area when directly reading from an sk_buff. buf is&n; * the current read/write position while processing an RPC request.&n; *&n; * The array of iovecs can hold additional data that the server process&n; * may not want to copy into the RPC reply buffer, but pass to the &n; * network sendmsg routines directly. The prime candidate for this&n; * will of course be NFS READ operations, but one might also want to&n; * do something about READLINK and READDIR. It might be worthwhile&n; * to implement some generic readdir cache in the VFS layer...&n; *&n; * On the receiving end of the RPC server, the iovec may be used to hold&n; * the list of IP fragments once we get to process fragmented UDP&n; * datagrams directly.&n; */
DECL|macro|RPCSVC_MAXIOV
mdefine_line|#define RPCSVC_MAXIOV&t;&t;((RPCSVC_MAXPAYLOAD+PAGE_SIZE-1)/PAGE_SIZE + 1)
DECL|struct|svc_buf
r_struct
id|svc_buf
(brace
DECL|member|area
id|u32
op_star
id|area
suffix:semicolon
multiline_comment|/* allocated memory */
DECL|member|base
id|u32
op_star
id|base
suffix:semicolon
multiline_comment|/* base of RPC datagram */
DECL|member|buflen
r_int
id|buflen
suffix:semicolon
multiline_comment|/* total length of buffer */
DECL|member|buf
id|u32
op_star
id|buf
suffix:semicolon
multiline_comment|/* read/write pointer */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* current end of buffer */
multiline_comment|/* iovec for zero-copy NFS READs */
DECL|member|iov
r_struct
id|iovec
id|iov
(braket
id|RPCSVC_MAXIOV
)braket
suffix:semicolon
DECL|member|nriov
r_int
id|nriov
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|svc_getlong
mdefine_line|#define svc_getlong(argp, val)&t;{ (val) = *(argp)-&gt;buf++; (argp)-&gt;len--; }
DECL|macro|svc_putlong
mdefine_line|#define svc_putlong(resp, val)&t;{ *(resp)-&gt;buf++ = (val); (resp)-&gt;len++; }
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
DECL|member|rq_defbuf
r_struct
id|svc_buf
id|rq_defbuf
suffix:semicolon
multiline_comment|/* default buffer */
DECL|member|rq_argbuf
r_struct
id|svc_buf
id|rq_argbuf
suffix:semicolon
multiline_comment|/* argument buffer */
DECL|member|rq_resbuf
r_struct
id|svc_buf
id|rq_resbuf
suffix:semicolon
multiline_comment|/* result buffer */
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
DECL|member|rq_verfed
r_int
r_int
id|rq_verfed
suffix:colon
l_int|1
comma
multiline_comment|/* reply has verifier */
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
comma
multiline_comment|/* secure port */
DECL|member|rq_auth
id|rq_auth
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* check client */
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
multiline_comment|/* Catering to nfsd */
DECL|member|rq_client
r_struct
id|svc_client
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
DECL|member|rq_wait
id|wait_queue_head_t
id|rq_wait
suffix:semicolon
multiline_comment|/* synchronozation */
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
macro_line|#endif /* SUNRPC_SVC_H */
eof
