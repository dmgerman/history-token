multiline_comment|/*&n; * linux/fs/nfs/callback.c&n; *&n; * Copyright (C) 2004 Trond Myklebust&n; *&n; * NFSv4 callback handling&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/sunrpc/svcsock.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &quot;callback.h&quot;
DECL|macro|NFSDBG_FACILITY
mdefine_line|#define NFSDBG_FACILITY NFSDBG_CALLBACK
DECL|struct|nfs_callback_data
r_struct
id|nfs_callback_data
(brace
DECL|member|users
r_int
r_int
id|users
suffix:semicolon
DECL|member|serv
r_struct
id|svc_serv
op_star
id|serv
suffix:semicolon
DECL|member|pid
id|pid_t
id|pid
suffix:semicolon
DECL|member|started
r_struct
id|completion
id|started
suffix:semicolon
DECL|member|stopped
r_struct
id|completion
id|stopped
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|nfs_callback_info
r_static
r_struct
id|nfs_callback_data
id|nfs_callback_info
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|nfs_callback_sema
)paren
suffix:semicolon
DECL|variable|nfs4_callback_program
r_static
r_struct
id|svc_program
id|nfs4_callback_program
suffix:semicolon
DECL|variable|nfs_callback_tcpport
r_int
r_int
id|nfs_callback_tcpport
suffix:semicolon
multiline_comment|/*&n; * This is the callback kernel thread.&n; */
DECL|function|nfs_callback_svc
r_static
r_void
id|nfs_callback_svc
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
r_int
id|err
suffix:semicolon
id|__module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|nfs_callback_info.pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;nfsv4-svc&quot;
)paren
suffix:semicolon
multiline_comment|/* Process request with signals blocked, but allow SIGKILL.  */
id|allow_signal
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
id|complete
c_func
(paren
op_amp
id|nfs_callback_info.started
)paren
suffix:semicolon
r_while
c_loop
(paren
id|nfs_callback_info.users
op_ne
l_int|0
op_logical_or
op_logical_neg
id|signalled
c_func
(paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Listen for a request on the socket&n;&t;&t; */
id|err
op_assign
id|svc_recv
c_func
(paren
id|serv
comma
id|rqstp
comma
id|MAX_SCHEDULE_TIMEOUT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|EAGAIN
op_logical_or
id|err
op_eq
op_minus
id|EINTR
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: terminating on error %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
op_minus
id|err
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;%s: request from %u.%u.%u.%u&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|NIPQUAD
c_func
(paren
id|rqstp-&gt;rq_addr.sin_addr.s_addr
)paren
)paren
suffix:semicolon
id|svc_process
c_func
(paren
id|serv
comma
id|rqstp
)paren
suffix:semicolon
)brace
id|nfs_callback_info.pid
op_assign
l_int|0
suffix:semicolon
id|complete
c_func
(paren
op_amp
id|nfs_callback_info.stopped
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|module_put_and_exit
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Bring up the server process if it is not already up.&n; */
DECL|function|nfs_callback_up
r_int
id|nfs_callback_up
c_func
(paren
r_void
)paren
(brace
r_struct
id|svc_serv
op_star
id|serv
suffix:semicolon
r_struct
id|svc_sock
op_star
id|svsk
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|nfs_callback_sema
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfs_callback_info.users
op_increment
op_logical_or
id|nfs_callback_info.pid
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|init_completion
c_func
(paren
op_amp
id|nfs_callback_info.started
)paren
suffix:semicolon
id|init_completion
c_func
(paren
op_amp
id|nfs_callback_info.stopped
)paren
suffix:semicolon
id|serv
op_assign
id|svc_create
c_func
(paren
op_amp
id|nfs4_callback_program
comma
id|NFS4_CALLBACK_BUFSIZE
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serv
)paren
r_goto
id|out_err
suffix:semicolon
multiline_comment|/* FIXME: We don&squot;t want to register this socket with the portmapper */
id|ret
op_assign
id|svc_makesock
c_func
(paren
id|serv
comma
id|IPPROTO_TCP
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|out_destroy
suffix:semicolon
r_if
c_cond
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
id|nfs_callback_tcpport
op_assign
id|ntohs
c_func
(paren
id|inet_sk
c_func
(paren
id|svsk-&gt;sk_sk
)paren
op_member_access_from_pointer
id|sport
)paren
suffix:semicolon
id|dprintk
(paren
l_string|&quot;Callback port = 0x%x&bslash;n&quot;
comma
id|nfs_callback_tcpport
)paren
suffix:semicolon
)brace
r_else
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|svc_create_thread
c_func
(paren
id|nfs_callback_svc
comma
id|serv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|out_destroy
suffix:semicolon
id|nfs_callback_info.serv
op_assign
id|serv
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|nfs_callback_info.started
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|nfs_callback_sema
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|out_destroy
suffix:colon
id|svc_destroy
c_func
(paren
id|serv
)paren
suffix:semicolon
id|out_err
suffix:colon
id|nfs_callback_info.users
op_decrement
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n; * Kill the server process if it is not already up.&n; */
DECL|function|nfs_callback_down
r_int
id|nfs_callback_down
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|nfs_callback_sema
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|nfs_callback_info.users
op_logical_or
id|nfs_callback_info.pid
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|kill_proc
c_func
(paren
id|nfs_callback_info.pid
comma
id|SIGKILL
comma
l_int|1
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|nfs_callback_info.stopped
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|nfs_callback_sema
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * AUTH_NULL authentication&n; */
DECL|function|nfs_callback_null_accept
r_static
r_int
id|nfs_callback_null_accept
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|authp
)paren
(brace
r_struct
id|kvec
op_star
id|argv
op_assign
op_amp
id|rqstp-&gt;rq_arg.head
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|kvec
op_star
id|resv
op_assign
op_amp
id|rqstp-&gt;rq_res.head
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|argv-&gt;iov_len
OL
l_int|3
op_star
l_int|4
)paren
r_return
id|SVC_GARBAGE
suffix:semicolon
r_if
c_cond
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
op_ne
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;svc: bad null cred&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|authp
op_assign
id|rpc_autherr_badcred
suffix:semicolon
r_return
id|SVC_DENIED
suffix:semicolon
)brace
r_if
c_cond
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
op_ne
id|RPC_AUTH_NULL
op_logical_or
id|svc_getu32
c_func
(paren
id|argv
)paren
op_ne
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;svc: bad null verf&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|authp
op_assign
id|rpc_autherr_badverf
suffix:semicolon
r_return
id|SVC_DENIED
suffix:semicolon
)brace
multiline_comment|/* Signal that mapping to nobody uid/gid is required */
id|rqstp-&gt;rq_cred.cr_uid
op_assign
(paren
id|uid_t
)paren
op_minus
l_int|1
suffix:semicolon
id|rqstp-&gt;rq_cred.cr_gid
op_assign
(paren
id|gid_t
)paren
op_minus
l_int|1
suffix:semicolon
id|rqstp-&gt;rq_cred.cr_group_info
op_assign
id|groups_alloc
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rqstp-&gt;rq_cred.cr_group_info
op_eq
l_int|NULL
)paren
r_return
id|SVC_DROP
suffix:semicolon
multiline_comment|/* kmalloc failure - client must retry */
multiline_comment|/* Put NULL verifier */
id|svc_putu32
c_func
(paren
id|resv
comma
id|RPC_AUTH_NULL
)paren
suffix:semicolon
id|svc_putu32
c_func
(paren
id|resv
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;%s: success, returning %d!&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|SVC_OK
)paren
suffix:semicolon
r_return
id|SVC_OK
suffix:semicolon
)brace
DECL|function|nfs_callback_null_release
r_static
r_int
id|nfs_callback_null_release
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
id|rqstp-&gt;rq_cred.cr_group_info
)paren
id|put_group_info
c_func
(paren
id|rqstp-&gt;rq_cred.cr_group_info
)paren
suffix:semicolon
id|rqstp-&gt;rq_cred.cr_group_info
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* don&squot;t drop */
)brace
DECL|variable|nfs_callback_auth_null
r_static
r_struct
id|auth_ops
id|nfs_callback_auth_null
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;null&quot;
comma
dot
id|flavour
op_assign
id|RPC_AUTH_NULL
comma
dot
id|accept
op_assign
id|nfs_callback_null_accept
comma
dot
id|release
op_assign
id|nfs_callback_null_release
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * AUTH_SYS authentication&n; */
DECL|function|nfs_callback_unix_accept
r_static
r_int
id|nfs_callback_unix_accept
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|authp
)paren
(brace
r_struct
id|kvec
op_star
id|argv
op_assign
op_amp
id|rqstp-&gt;rq_arg.head
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|kvec
op_star
id|resv
op_assign
op_amp
id|rqstp-&gt;rq_res.head
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|svc_cred
op_star
id|cred
op_assign
op_amp
id|rqstp-&gt;rq_cred
suffix:semicolon
id|u32
id|slen
comma
id|i
suffix:semicolon
r_int
id|len
op_assign
id|argv-&gt;iov_len
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;%s: start&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|cred-&gt;cr_group_info
op_assign
l_int|NULL
suffix:semicolon
id|rqstp-&gt;rq_client
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
l_int|3
op_star
l_int|4
)paren
OL
l_int|0
)paren
r_return
id|SVC_GARBAGE
suffix:semicolon
multiline_comment|/* Get length, time stamp and machine name */
id|svc_getu32
c_func
(paren
id|argv
)paren
suffix:semicolon
id|svc_getu32
c_func
(paren
id|argv
)paren
suffix:semicolon
id|slen
op_assign
id|XDR_QUADLEN
c_func
(paren
id|ntohl
c_func
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slen
OG
l_int|64
op_logical_or
(paren
id|len
op_sub_assign
(paren
id|slen
op_plus
l_int|3
)paren
op_star
l_int|4
)paren
OL
l_int|0
)paren
r_goto
id|badcred
suffix:semicolon
id|argv-&gt;iov_base
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
id|u32
op_star
)paren
id|argv-&gt;iov_base
op_plus
id|slen
)paren
suffix:semicolon
id|argv-&gt;iov_len
op_sub_assign
id|slen
op_star
l_int|4
suffix:semicolon
id|cred-&gt;cr_uid
op_assign
id|ntohl
c_func
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
)paren
suffix:semicolon
id|cred-&gt;cr_gid
op_assign
id|ntohl
c_func
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
)paren
suffix:semicolon
id|slen
op_assign
id|ntohl
c_func
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slen
OG
l_int|16
op_logical_or
(paren
id|len
op_sub_assign
(paren
id|slen
op_plus
l_int|2
)paren
op_star
l_int|4
)paren
OL
l_int|0
)paren
r_goto
id|badcred
suffix:semicolon
id|cred-&gt;cr_group_info
op_assign
id|groups_alloc
c_func
(paren
id|slen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cred-&gt;cr_group_info
op_eq
l_int|NULL
)paren
r_return
id|SVC_DROP
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
id|slen
suffix:semicolon
id|i
op_increment
)paren
id|GROUP_AT
c_func
(paren
id|cred-&gt;cr_group_info
comma
id|i
)paren
op_assign
id|ntohl
c_func
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
op_ne
id|RPC_AUTH_NULL
op_logical_or
id|svc_getu32
c_func
(paren
id|argv
)paren
op_ne
l_int|0
)paren
(brace
op_star
id|authp
op_assign
id|rpc_autherr_badverf
suffix:semicolon
r_return
id|SVC_DENIED
suffix:semicolon
)brace
multiline_comment|/* Put NULL verifier */
id|svc_putu32
c_func
(paren
id|resv
comma
id|RPC_AUTH_NULL
)paren
suffix:semicolon
id|svc_putu32
c_func
(paren
id|resv
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;%s: success, returning %d!&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|SVC_OK
)paren
suffix:semicolon
r_return
id|SVC_OK
suffix:semicolon
id|badcred
suffix:colon
op_star
id|authp
op_assign
id|rpc_autherr_badcred
suffix:semicolon
r_return
id|SVC_DENIED
suffix:semicolon
)brace
DECL|function|nfs_callback_unix_release
r_static
r_int
id|nfs_callback_unix_release
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
id|rqstp-&gt;rq_cred.cr_group_info
)paren
id|put_group_info
c_func
(paren
id|rqstp-&gt;rq_cred.cr_group_info
)paren
suffix:semicolon
id|rqstp-&gt;rq_cred.cr_group_info
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|nfs_callback_auth_unix
r_static
r_struct
id|auth_ops
id|nfs_callback_auth_unix
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;unix&quot;
comma
dot
id|flavour
op_assign
id|RPC_AUTH_UNIX
comma
dot
id|accept
op_assign
id|nfs_callback_unix_accept
comma
dot
id|release
op_assign
id|nfs_callback_unix_release
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Hook the authentication protocol&n; */
DECL|function|nfs_callback_auth
r_static
r_int
id|nfs_callback_auth
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|authp
)paren
(brace
r_struct
id|in_addr
op_star
id|addr
op_assign
op_amp
id|rqstp-&gt;rq_addr.sin_addr
suffix:semicolon
r_struct
id|nfs4_client
op_star
id|clp
suffix:semicolon
r_struct
id|kvec
op_star
id|argv
op_assign
op_amp
id|rqstp-&gt;rq_arg.head
(braket
l_int|0
)braket
suffix:semicolon
r_int
id|flavour
suffix:semicolon
r_int
id|retval
suffix:semicolon
multiline_comment|/* Don&squot;t talk to strangers */
id|clp
op_assign
id|nfs4_find_client
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clp
op_eq
l_int|NULL
)paren
r_return
id|SVC_DROP
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;%s: %u.%u.%u.%u NFSv4 callback!&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|NIPQUAD
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
id|nfs4_put_client
c_func
(paren
id|clp
)paren
suffix:semicolon
id|flavour
op_assign
id|ntohl
c_func
(paren
id|svc_getu32
c_func
(paren
id|argv
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|flavour
)paren
(brace
r_case
id|RPC_AUTH_NULL
suffix:colon
r_if
c_cond
(paren
id|rqstp-&gt;rq_proc
op_ne
id|CB_NULL
)paren
(brace
op_star
id|authp
op_assign
id|rpc_autherr_tooweak
suffix:semicolon
id|retval
op_assign
id|SVC_DENIED
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rqstp-&gt;rq_authop
op_assign
op_amp
id|nfs_callback_auth_null
suffix:semicolon
id|retval
op_assign
id|nfs_callback_null_accept
c_func
(paren
id|rqstp
comma
id|authp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RPC_AUTH_UNIX
suffix:colon
multiline_comment|/* Eat the authentication flavour */
id|rqstp-&gt;rq_authop
op_assign
op_amp
id|nfs_callback_auth_unix
suffix:semicolon
id|retval
op_assign
id|nfs_callback_unix_accept
c_func
(paren
id|rqstp
comma
id|authp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* FIXME: need to add RPCSEC_GSS upcalls */
macro_line|#if 0
id|svc_ungetu32
c_func
(paren
id|argv
)paren
suffix:semicolon
id|retval
op_assign
id|svc_authenticate
c_func
(paren
id|rqstp
comma
id|authp
)paren
suffix:semicolon
macro_line|#else
op_star
id|authp
op_assign
id|rpc_autherr_rejectedcred
suffix:semicolon
id|retval
op_assign
id|SVC_DENIED
suffix:semicolon
macro_line|#endif
)brace
id|dprintk
c_func
(paren
l_string|&quot;%s: flavour %d returning error %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|flavour
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * Define NFS4 callback program&n; */
r_extern
r_struct
id|svc_version
id|nfs4_callback_version1
suffix:semicolon
DECL|variable|nfs4_callback_version
r_static
r_struct
id|svc_version
op_star
id|nfs4_callback_version
(braket
)braket
op_assign
(brace
(braket
l_int|1
)braket
op_assign
op_amp
id|nfs4_callback_version1
comma
)brace
suffix:semicolon
DECL|variable|nfs4_callback_stats
r_static
r_struct
id|svc_stat
id|nfs4_callback_stats
suffix:semicolon
DECL|variable|nfs4_callback_program
r_static
r_struct
id|svc_program
id|nfs4_callback_program
op_assign
(brace
dot
id|pg_prog
op_assign
id|NFS4_CALLBACK
comma
multiline_comment|/* RPC service number */
dot
id|pg_nvers
op_assign
id|ARRAY_SIZE
c_func
(paren
id|nfs4_callback_version
)paren
comma
multiline_comment|/* Number of entries */
dot
id|pg_vers
op_assign
id|nfs4_callback_version
comma
multiline_comment|/* version table */
dot
id|pg_name
op_assign
l_string|&quot;NFSv4 callback&quot;
comma
multiline_comment|/* service name */
dot
id|pg_class
op_assign
l_string|&quot;nfs&quot;
comma
multiline_comment|/* authentication class */
dot
id|pg_stats
op_assign
op_amp
id|nfs4_callback_stats
comma
dot
id|pg_authenticate_obsolete
op_assign
id|nfs_callback_auth
comma
)brace
suffix:semicolon
eof
