multiline_comment|/*&n; * linux/fs/lockd/svc4proc.c&n; *&n; * Lockd server procedures. We don&squot;t implement the NLM_*_RES &n; * procedures because we don&squot;t use the async procedures.&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
macro_line|#include &lt;linux/lockd/lockd.h&gt;
macro_line|#include &lt;linux/lockd/share.h&gt;
macro_line|#include &lt;linux/lockd/sm_inter.h&gt;
DECL|macro|NLMDBG_FACILITY
mdefine_line|#define NLMDBG_FACILITY&t;&t;NLMDBG_CLIENT
r_static
id|u32
id|nlm4svc_callback
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
comma
r_struct
id|nlm_res
op_star
)paren
suffix:semicolon
r_static
r_void
id|nlm4svc_callback_exit
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Obtain client and file from arguments&n; */
r_static
id|u32
DECL|function|nlm4svc_retrieve_args
id|nlm4svc_retrieve_args
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_args
op_star
id|argp
comma
r_struct
id|nlm_host
op_star
op_star
id|hostp
comma
r_struct
id|nlm_file
op_star
op_star
id|filp
)paren
(brace
r_struct
id|nlm_host
op_star
id|host
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|nlm_file
op_star
id|file
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|nlm_lock
op_star
id|lock
op_assign
op_amp
id|argp-&gt;lock
suffix:semicolon
id|u32
id|error
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* nfsd callbacks must have been installed for this procedure */
r_if
c_cond
(paren
op_logical_neg
id|nlmsvc_ops
)paren
r_return
id|nlm_lck_denied_nolocks
suffix:semicolon
multiline_comment|/* Obtain handle for client host */
r_if
c_cond
(paren
id|rqstp-&gt;rq_client
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;lockd: unauthenticated request from (%08x:%d)&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|rqstp-&gt;rq_addr.sin_addr.s_addr
)paren
comma
id|ntohs
c_func
(paren
id|rqstp-&gt;rq_addr.sin_port
)paren
)paren
suffix:semicolon
r_return
id|nlm_lck_denied_nolocks
suffix:semicolon
)brace
multiline_comment|/* Obtain host handle */
r_if
c_cond
(paren
op_logical_neg
(paren
id|host
op_assign
id|nlmsvc_lookup_host
c_func
(paren
id|rqstp
)paren
)paren
op_logical_or
(paren
id|argp-&gt;monitor
op_logical_and
op_logical_neg
id|host-&gt;h_monitored
op_logical_and
id|nsm_monitor
c_func
(paren
id|host
)paren
OL
l_int|0
)paren
)paren
r_goto
id|no_locks
suffix:semicolon
op_star
id|hostp
op_assign
id|host
suffix:semicolon
multiline_comment|/* Obtain file pointer. Not used by FREE_ALL call. */
r_if
c_cond
(paren
id|filp
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|nlm_lookup_file
c_func
(paren
id|rqstp
comma
op_amp
id|file
comma
op_amp
id|lock-&gt;fh
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|no_locks
suffix:semicolon
op_star
id|filp
op_assign
id|file
suffix:semicolon
multiline_comment|/* Set up the missing parts of the file_lock structure */
id|lock-&gt;fl.fl_file
op_assign
op_amp
id|file-&gt;f_file
suffix:semicolon
id|lock-&gt;fl.fl_owner
op_assign
(paren
id|fl_owner_t
)paren
id|host
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|no_locks
suffix:colon
r_if
c_cond
(paren
id|host
)paren
id|nlm_release_host
c_func
(paren
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_return
id|nlm_lck_denied_nolocks
suffix:semicolon
)brace
multiline_comment|/*&n; * NULL: Test for presence of service&n; */
r_static
r_int
DECL|function|nlm4svc_proc_null
id|nlm4svc_proc_null
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_void
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: NULL          called&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
)brace
multiline_comment|/*&n; * TEST: Check for conflicting lock&n; */
r_static
r_int
DECL|function|nlm4svc_proc_test
id|nlm4svc_proc_test
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_args
op_star
id|argp
comma
r_struct
id|nlm_res
op_star
id|resp
)paren
(brace
r_struct
id|nlm_host
op_star
id|host
suffix:semicolon
r_struct
id|nlm_file
op_star
id|file
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: TEST4        called&bslash;n&quot;
)paren
suffix:semicolon
id|resp-&gt;cookie
op_assign
id|argp-&gt;cookie
suffix:semicolon
multiline_comment|/* Don&squot;t accept test requests during grace period */
r_if
c_cond
(paren
id|nlmsvc_grace_period
)paren
(brace
id|resp-&gt;status
op_assign
id|nlm_lck_denied_grace_period
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
)brace
multiline_comment|/* Obtain client and file */
r_if
c_cond
(paren
(paren
id|resp-&gt;status
op_assign
id|nlm4svc_retrieve_args
c_func
(paren
id|rqstp
comma
id|argp
comma
op_amp
id|host
comma
op_amp
id|file
)paren
)paren
)paren
r_return
id|rpc_success
suffix:semicolon
multiline_comment|/* Now check for conflicting locks */
id|resp-&gt;status
op_assign
id|nlmsvc_testlock
c_func
(paren
id|file
comma
op_amp
id|argp-&gt;lock
comma
op_amp
id|resp-&gt;lock
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: TEST4          status %d&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|resp-&gt;status
)paren
)paren
suffix:semicolon
id|nlm_release_host
c_func
(paren
id|host
)paren
suffix:semicolon
id|nlm_release_file
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
)brace
r_static
r_int
DECL|function|nlm4svc_proc_lock
id|nlm4svc_proc_lock
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_args
op_star
id|argp
comma
r_struct
id|nlm_res
op_star
id|resp
)paren
(brace
r_struct
id|nlm_host
op_star
id|host
suffix:semicolon
r_struct
id|nlm_file
op_star
id|file
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: LOCK          called&bslash;n&quot;
)paren
suffix:semicolon
id|resp-&gt;cookie
op_assign
id|argp-&gt;cookie
suffix:semicolon
multiline_comment|/* Don&squot;t accept new lock requests during grace period */
r_if
c_cond
(paren
id|nlmsvc_grace_period
op_logical_and
op_logical_neg
id|argp-&gt;reclaim
)paren
(brace
id|resp-&gt;status
op_assign
id|nlm_lck_denied_grace_period
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
)brace
multiline_comment|/* Obtain client and file */
r_if
c_cond
(paren
(paren
id|resp-&gt;status
op_assign
id|nlm4svc_retrieve_args
c_func
(paren
id|rqstp
comma
id|argp
comma
op_amp
id|host
comma
op_amp
id|file
)paren
)paren
)paren
r_return
id|rpc_success
suffix:semicolon
macro_line|#if 0
multiline_comment|/* If supplied state doesn&squot;t match current state, we assume it&squot;s&n;&t; * an old request that time-warped somehow. Any error return would&n;&t; * do in this case because it&squot;s irrelevant anyway.&n;&t; *&n;&t; * NB: We don&squot;t retrieve the remote host&squot;s state yet.&n;&t; */
r_if
c_cond
(paren
id|host-&gt;h_nsmstate
op_logical_and
id|host-&gt;h_nsmstate
op_ne
id|argp-&gt;state
)paren
(brace
id|resp-&gt;status
op_assign
id|nlm_lck_denied_nolocks
suffix:semicolon
)brace
r_else
macro_line|#endif
multiline_comment|/* Now try to lock the file */
id|resp-&gt;status
op_assign
id|nlmsvc_lock
c_func
(paren
id|rqstp
comma
id|file
comma
op_amp
id|argp-&gt;lock
comma
id|argp-&gt;block
comma
op_amp
id|argp-&gt;cookie
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: LOCK          status %d&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|resp-&gt;status
)paren
)paren
suffix:semicolon
id|nlm_release_host
c_func
(paren
id|host
)paren
suffix:semicolon
id|nlm_release_file
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
)brace
r_static
r_int
DECL|function|nlm4svc_proc_cancel
id|nlm4svc_proc_cancel
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_args
op_star
id|argp
comma
r_struct
id|nlm_res
op_star
id|resp
)paren
(brace
r_struct
id|nlm_host
op_star
id|host
suffix:semicolon
r_struct
id|nlm_file
op_star
id|file
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: CANCEL        called&bslash;n&quot;
)paren
suffix:semicolon
id|resp-&gt;cookie
op_assign
id|argp-&gt;cookie
suffix:semicolon
multiline_comment|/* Don&squot;t accept requests during grace period */
r_if
c_cond
(paren
id|nlmsvc_grace_period
)paren
(brace
id|resp-&gt;status
op_assign
id|nlm_lck_denied_grace_period
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
)brace
multiline_comment|/* Obtain client and file */
r_if
c_cond
(paren
(paren
id|resp-&gt;status
op_assign
id|nlm4svc_retrieve_args
c_func
(paren
id|rqstp
comma
id|argp
comma
op_amp
id|host
comma
op_amp
id|file
)paren
)paren
)paren
r_return
id|rpc_success
suffix:semicolon
multiline_comment|/* Try to cancel request. */
id|resp-&gt;status
op_assign
id|nlmsvc_cancel_blocked
c_func
(paren
id|file
comma
op_amp
id|argp-&gt;lock
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: CANCEL        status %d&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|resp-&gt;status
)paren
)paren
suffix:semicolon
id|nlm_release_host
c_func
(paren
id|host
)paren
suffix:semicolon
id|nlm_release_file
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
)brace
multiline_comment|/*&n; * UNLOCK: release a lock&n; */
r_static
r_int
DECL|function|nlm4svc_proc_unlock
id|nlm4svc_proc_unlock
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_args
op_star
id|argp
comma
r_struct
id|nlm_res
op_star
id|resp
)paren
(brace
r_struct
id|nlm_host
op_star
id|host
suffix:semicolon
r_struct
id|nlm_file
op_star
id|file
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: UNLOCK        called&bslash;n&quot;
)paren
suffix:semicolon
id|resp-&gt;cookie
op_assign
id|argp-&gt;cookie
suffix:semicolon
multiline_comment|/* Don&squot;t accept new lock requests during grace period */
r_if
c_cond
(paren
id|nlmsvc_grace_period
)paren
(brace
id|resp-&gt;status
op_assign
id|nlm_lck_denied_grace_period
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
)brace
multiline_comment|/* Obtain client and file */
r_if
c_cond
(paren
(paren
id|resp-&gt;status
op_assign
id|nlm4svc_retrieve_args
c_func
(paren
id|rqstp
comma
id|argp
comma
op_amp
id|host
comma
op_amp
id|file
)paren
)paren
)paren
r_return
id|rpc_success
suffix:semicolon
multiline_comment|/* Now try to remove the lock */
id|resp-&gt;status
op_assign
id|nlmsvc_unlock
c_func
(paren
id|file
comma
op_amp
id|argp-&gt;lock
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: UNLOCK        status %d&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|resp-&gt;status
)paren
)paren
suffix:semicolon
id|nlm_release_host
c_func
(paren
id|host
)paren
suffix:semicolon
id|nlm_release_file
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
)brace
multiline_comment|/*&n; * GRANTED: A server calls us to tell that a process&squot; lock request&n; * was granted&n; */
r_static
r_int
DECL|function|nlm4svc_proc_granted
id|nlm4svc_proc_granted
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_args
op_star
id|argp
comma
r_struct
id|nlm_res
op_star
id|resp
)paren
(brace
id|resp-&gt;cookie
op_assign
id|argp-&gt;cookie
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: GRANTED       called&bslash;n&quot;
)paren
suffix:semicolon
id|resp-&gt;status
op_assign
id|nlmclnt_grant
c_func
(paren
op_amp
id|argp-&gt;lock
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: GRANTED       status %d&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|resp-&gt;status
)paren
)paren
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
)brace
multiline_comment|/*&n; * `Async&squot; versions of the above service routines. They aren&squot;t really,&n; * because we send the callback before the reply proper. I hope this&n; * doesn&squot;t break any clients.&n; */
r_static
r_int
DECL|function|nlm4svc_proc_test_msg
id|nlm4svc_proc_test_msg
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_args
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_struct
id|nlm_res
id|res
suffix:semicolon
id|u32
id|stat
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: TEST_MSG      called&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|stat
op_assign
id|nlm4svc_proc_test
c_func
(paren
id|rqstp
comma
id|argp
comma
op_amp
id|res
)paren
)paren
op_eq
l_int|0
)paren
id|stat
op_assign
id|nlm4svc_callback
c_func
(paren
id|rqstp
comma
id|NLMPROC_TEST_RES
comma
op_amp
id|res
)paren
suffix:semicolon
r_return
id|stat
suffix:semicolon
)brace
r_static
r_int
DECL|function|nlm4svc_proc_lock_msg
id|nlm4svc_proc_lock_msg
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_args
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_struct
id|nlm_res
id|res
suffix:semicolon
id|u32
id|stat
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: LOCK_MSG      called&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|stat
op_assign
id|nlm4svc_proc_lock
c_func
(paren
id|rqstp
comma
id|argp
comma
op_amp
id|res
)paren
)paren
op_eq
l_int|0
)paren
id|stat
op_assign
id|nlm4svc_callback
c_func
(paren
id|rqstp
comma
id|NLMPROC_LOCK_RES
comma
op_amp
id|res
)paren
suffix:semicolon
r_return
id|stat
suffix:semicolon
)brace
r_static
r_int
DECL|function|nlm4svc_proc_cancel_msg
id|nlm4svc_proc_cancel_msg
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_args
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_struct
id|nlm_res
id|res
suffix:semicolon
id|u32
id|stat
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: CANCEL_MSG    called&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|stat
op_assign
id|nlm4svc_proc_cancel
c_func
(paren
id|rqstp
comma
id|argp
comma
op_amp
id|res
)paren
)paren
op_eq
l_int|0
)paren
id|stat
op_assign
id|nlm4svc_callback
c_func
(paren
id|rqstp
comma
id|NLMPROC_CANCEL_RES
comma
op_amp
id|res
)paren
suffix:semicolon
r_return
id|stat
suffix:semicolon
)brace
r_static
r_int
DECL|function|nlm4svc_proc_unlock_msg
id|nlm4svc_proc_unlock_msg
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_args
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_struct
id|nlm_res
id|res
suffix:semicolon
id|u32
id|stat
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: UNLOCK_MSG    called&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|stat
op_assign
id|nlm4svc_proc_unlock
c_func
(paren
id|rqstp
comma
id|argp
comma
op_amp
id|res
)paren
)paren
op_eq
l_int|0
)paren
id|stat
op_assign
id|nlm4svc_callback
c_func
(paren
id|rqstp
comma
id|NLMPROC_UNLOCK_RES
comma
op_amp
id|res
)paren
suffix:semicolon
r_return
id|stat
suffix:semicolon
)brace
r_static
r_int
DECL|function|nlm4svc_proc_granted_msg
id|nlm4svc_proc_granted_msg
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_args
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_struct
id|nlm_res
id|res
suffix:semicolon
id|u32
id|stat
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: GRANTED_MSG   called&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|stat
op_assign
id|nlm4svc_proc_granted
c_func
(paren
id|rqstp
comma
id|argp
comma
op_amp
id|res
)paren
)paren
op_eq
l_int|0
)paren
id|stat
op_assign
id|nlm4svc_callback
c_func
(paren
id|rqstp
comma
id|NLMPROC_GRANTED_RES
comma
op_amp
id|res
)paren
suffix:semicolon
r_return
id|stat
suffix:semicolon
)brace
multiline_comment|/*&n; * SHARE: create a DOS share or alter existing share.&n; */
r_static
r_int
DECL|function|nlm4svc_proc_share
id|nlm4svc_proc_share
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_args
op_star
id|argp
comma
r_struct
id|nlm_res
op_star
id|resp
)paren
(brace
r_struct
id|nlm_host
op_star
id|host
suffix:semicolon
r_struct
id|nlm_file
op_star
id|file
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: SHARE         called&bslash;n&quot;
)paren
suffix:semicolon
id|resp-&gt;cookie
op_assign
id|argp-&gt;cookie
suffix:semicolon
multiline_comment|/* Don&squot;t accept new lock requests during grace period */
r_if
c_cond
(paren
id|nlmsvc_grace_period
op_logical_and
op_logical_neg
id|argp-&gt;reclaim
)paren
(brace
id|resp-&gt;status
op_assign
id|nlm_lck_denied_grace_period
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
)brace
multiline_comment|/* Obtain client and file */
r_if
c_cond
(paren
(paren
id|resp-&gt;status
op_assign
id|nlm4svc_retrieve_args
c_func
(paren
id|rqstp
comma
id|argp
comma
op_amp
id|host
comma
op_amp
id|file
)paren
)paren
)paren
r_return
id|rpc_success
suffix:semicolon
multiline_comment|/* Now try to create the share */
id|resp-&gt;status
op_assign
id|nlmsvc_share_file
c_func
(paren
id|host
comma
id|file
comma
id|argp
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: SHARE         status %d&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|resp-&gt;status
)paren
)paren
suffix:semicolon
id|nlm_release_host
c_func
(paren
id|host
)paren
suffix:semicolon
id|nlm_release_file
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
)brace
multiline_comment|/*&n; * UNSHARE: Release a DOS share.&n; */
r_static
r_int
DECL|function|nlm4svc_proc_unshare
id|nlm4svc_proc_unshare
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_args
op_star
id|argp
comma
r_struct
id|nlm_res
op_star
id|resp
)paren
(brace
r_struct
id|nlm_host
op_star
id|host
suffix:semicolon
r_struct
id|nlm_file
op_star
id|file
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: UNSHARE       called&bslash;n&quot;
)paren
suffix:semicolon
id|resp-&gt;cookie
op_assign
id|argp-&gt;cookie
suffix:semicolon
multiline_comment|/* Don&squot;t accept requests during grace period */
r_if
c_cond
(paren
id|nlmsvc_grace_period
)paren
(brace
id|resp-&gt;status
op_assign
id|nlm_lck_denied_grace_period
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
)brace
multiline_comment|/* Obtain client and file */
r_if
c_cond
(paren
(paren
id|resp-&gt;status
op_assign
id|nlm4svc_retrieve_args
c_func
(paren
id|rqstp
comma
id|argp
comma
op_amp
id|host
comma
op_amp
id|file
)paren
)paren
)paren
r_return
id|rpc_success
suffix:semicolon
multiline_comment|/* Now try to lock the file */
id|resp-&gt;status
op_assign
id|nlmsvc_unshare_file
c_func
(paren
id|host
comma
id|file
comma
id|argp
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: UNSHARE       status %d&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|resp-&gt;status
)paren
)paren
suffix:semicolon
id|nlm_release_host
c_func
(paren
id|host
)paren
suffix:semicolon
id|nlm_release_file
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
)brace
multiline_comment|/*&n; * NM_LOCK: Create an unmonitored lock&n; */
r_static
r_int
DECL|function|nlm4svc_proc_nm_lock
id|nlm4svc_proc_nm_lock
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_args
op_star
id|argp
comma
r_struct
id|nlm_res
op_star
id|resp
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: NM_LOCK       called&bslash;n&quot;
)paren
suffix:semicolon
id|argp-&gt;monitor
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* just clean the monitor flag */
r_return
id|nlm4svc_proc_lock
c_func
(paren
id|rqstp
comma
id|argp
comma
id|resp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * FREE_ALL: Release all locks and shares held by client&n; */
r_static
r_int
DECL|function|nlm4svc_proc_free_all
id|nlm4svc_proc_free_all
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_args
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_struct
id|nlm_host
op_star
id|host
suffix:semicolon
multiline_comment|/* Obtain client */
r_if
c_cond
(paren
id|nlm4svc_retrieve_args
c_func
(paren
id|rqstp
comma
id|argp
comma
op_amp
id|host
comma
l_int|NULL
)paren
)paren
r_return
id|rpc_success
suffix:semicolon
id|nlmsvc_free_host_resources
c_func
(paren
id|host
)paren
suffix:semicolon
id|nlm_release_host
c_func
(paren
id|host
)paren
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
)brace
multiline_comment|/*&n; * SM_NOTIFY: private callback from statd (not part of official NLM proto)&n; */
r_static
r_int
DECL|function|nlm4svc_proc_sm_notify
id|nlm4svc_proc_sm_notify
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_reboot
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_struct
id|sockaddr_in
id|saddr
op_assign
id|rqstp-&gt;rq_addr
suffix:semicolon
r_int
id|vers
op_assign
id|rqstp-&gt;rq_vers
suffix:semicolon
r_int
id|prot
op_assign
id|rqstp-&gt;rq_prot
suffix:semicolon
r_struct
id|nlm_host
op_star
id|host
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: SM_NOTIFY     called&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saddr.sin_addr.s_addr
op_ne
id|htonl
c_func
(paren
id|INADDR_LOOPBACK
)paren
op_logical_or
id|ntohs
c_func
(paren
id|saddr.sin_port
)paren
op_ge
l_int|1024
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lockd: rejected NSM callback from %08x:%d&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|rqstp-&gt;rq_addr.sin_addr.s_addr
)paren
comma
id|ntohs
c_func
(paren
id|rqstp-&gt;rq_addr.sin_port
)paren
)paren
suffix:semicolon
r_return
id|rpc_system_err
suffix:semicolon
)brace
multiline_comment|/* Obtain the host pointer for this NFS server and try to&n;&t; * reclaim all locks we hold on this server.&n;&t; */
id|saddr.sin_addr.s_addr
op_assign
id|argp-&gt;addr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|host
op_assign
id|nlmclnt_lookup_host
c_func
(paren
op_amp
id|saddr
comma
id|prot
comma
id|vers
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|nlmclnt_recovery
c_func
(paren
id|host
comma
id|argp-&gt;state
)paren
suffix:semicolon
id|nlm_release_host
c_func
(paren
id|host
)paren
suffix:semicolon
)brace
multiline_comment|/* If we run on an NFS server, delete all locks held by the client */
r_if
c_cond
(paren
id|nlmsvc_ops
op_ne
l_int|NULL
)paren
(brace
r_struct
id|svc_client
op_star
id|clnt
suffix:semicolon
id|saddr.sin_addr.s_addr
op_assign
id|argp-&gt;addr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|clnt
op_assign
id|nlmsvc_ops
op_member_access_from_pointer
id|exp_getclient
c_func
(paren
op_amp
id|saddr
)paren
)paren
op_ne
l_int|NULL
op_logical_and
(paren
id|host
op_assign
id|nlm_lookup_host
c_func
(paren
id|clnt
comma
op_amp
id|saddr
comma
l_int|0
comma
l_int|0
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|nlmsvc_free_host_resources
c_func
(paren
id|host
)paren
suffix:semicolon
)brace
id|nlm_release_host
c_func
(paren
id|host
)paren
suffix:semicolon
)brace
r_return
id|rpc_success
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the generic lockd callback for async RPC calls&n; */
r_static
id|u32
DECL|function|nlm4svc_callback
id|nlm4svc_callback
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
id|proc
comma
r_struct
id|nlm_res
op_star
id|resp
)paren
(brace
r_struct
id|nlm_host
op_star
id|host
suffix:semicolon
r_struct
id|nlm_rqst
op_star
id|call
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|call
op_assign
id|nlmclnt_alloc_call
c_func
(paren
)paren
)paren
)paren
r_return
id|rpc_system_err
suffix:semicolon
id|host
op_assign
id|nlmclnt_lookup_host
c_func
(paren
op_amp
id|rqstp-&gt;rq_addr
comma
id|rqstp-&gt;rq_prot
comma
id|rqstp-&gt;rq_vers
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host
)paren
(brace
id|kfree
c_func
(paren
id|call
)paren
suffix:semicolon
r_return
id|rpc_system_err
suffix:semicolon
)brace
id|call-&gt;a_flags
op_assign
id|RPC_TASK_ASYNC
suffix:semicolon
id|call-&gt;a_host
op_assign
id|host
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|call-&gt;a_args
comma
id|resp
comma
r_sizeof
(paren
op_star
id|resp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nlmsvc_async_call
c_func
(paren
id|call
comma
id|proc
comma
id|nlm4svc_callback_exit
)paren
OL
l_int|0
)paren
r_goto
id|error
suffix:semicolon
r_return
id|rpc_success
suffix:semicolon
id|error
suffix:colon
id|kfree
c_func
(paren
id|call
)paren
suffix:semicolon
id|nlm_release_host
c_func
(paren
id|host
)paren
suffix:semicolon
r_return
id|rpc_system_err
suffix:semicolon
)brace
r_static
r_void
DECL|function|nlm4svc_callback_exit
id|nlm4svc_callback_exit
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
r_struct
id|nlm_rqst
op_star
id|call
op_assign
(paren
r_struct
id|nlm_rqst
op_star
)paren
id|task-&gt;tk_calldata
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;tk_status
OL
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: %4d callback failed (errno = %d)&bslash;n&quot;
comma
id|task-&gt;tk_pid
comma
op_minus
id|task-&gt;tk_status
)paren
suffix:semicolon
)brace
id|nlm_release_host
c_func
(paren
id|call-&gt;a_host
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|call
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * NLM Server procedures.&n; */
DECL|macro|nlm4svc_encode_norep
mdefine_line|#define nlm4svc_encode_norep&t;nlm4svc_encode_void
DECL|macro|nlm4svc_decode_norep
mdefine_line|#define nlm4svc_decode_norep&t;nlm4svc_decode_void
DECL|macro|nlm4svc_decode_testres
mdefine_line|#define nlm4svc_decode_testres&t;nlm4svc_decode_void
DECL|macro|nlm4svc_decode_lockres
mdefine_line|#define nlm4svc_decode_lockres&t;nlm4svc_decode_void
DECL|macro|nlm4svc_decode_unlockres
mdefine_line|#define nlm4svc_decode_unlockres&t;nlm4svc_decode_void
DECL|macro|nlm4svc_decode_cancelres
mdefine_line|#define nlm4svc_decode_cancelres&t;nlm4svc_decode_void
DECL|macro|nlm4svc_decode_grantedres
mdefine_line|#define nlm4svc_decode_grantedres&t;nlm4svc_decode_void
DECL|macro|nlm4svc_proc_none
mdefine_line|#define nlm4svc_proc_none&t;nlm4svc_proc_null
DECL|macro|nlm4svc_proc_test_res
mdefine_line|#define nlm4svc_proc_test_res&t;nlm4svc_proc_null
DECL|macro|nlm4svc_proc_lock_res
mdefine_line|#define nlm4svc_proc_lock_res&t;nlm4svc_proc_null
DECL|macro|nlm4svc_proc_cancel_res
mdefine_line|#define nlm4svc_proc_cancel_res&t;nlm4svc_proc_null
DECL|macro|nlm4svc_proc_unlock_res
mdefine_line|#define nlm4svc_proc_unlock_res&t;nlm4svc_proc_null
DECL|macro|nlm4svc_proc_granted_res
mdefine_line|#define nlm4svc_proc_granted_res&t;nlm4svc_proc_null
DECL|struct|nlm_void
DECL|member|dummy
r_struct
id|nlm_void
(brace
r_int
id|dummy
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PROC
mdefine_line|#define PROC(name, xargt, xrest, argt, rest)&t;&bslash;&n; { (svc_procfunc) nlm4svc_proc_##name,&t;&bslash;&n;   (kxdrproc_t) nlm4svc_decode_##xargt,&t;&bslash;&n;   (kxdrproc_t) nlm4svc_encode_##xrest,&t;&bslash;&n;   NULL,&t;&t;&t;&t;&bslash;&n;   sizeof(struct nlm_##argt),&t;&t;&bslash;&n;   sizeof(struct nlm_##rest),&t;&t;&bslash;&n;   0,&t;&t;&t;&t;&t;&bslash;&n;   0&t;&t;&t;&t;&t;&bslash;&n; }
DECL|variable|nlmsvc_procedures4
r_struct
id|svc_procedure
id|nlmsvc_procedures4
(braket
)braket
op_assign
(brace
id|PROC
c_func
(paren
id|null
comma
r_void
comma
r_void
comma
r_void
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|test
comma
id|testargs
comma
id|testres
comma
id|args
comma
id|res
)paren
comma
id|PROC
c_func
(paren
id|lock
comma
id|lockargs
comma
id|res
comma
id|args
comma
id|res
)paren
comma
id|PROC
c_func
(paren
id|cancel
comma
id|cancargs
comma
id|res
comma
id|args
comma
id|res
)paren
comma
id|PROC
c_func
(paren
id|unlock
comma
id|unlockargs
comma
id|res
comma
id|args
comma
id|res
)paren
comma
id|PROC
c_func
(paren
id|granted
comma
id|testargs
comma
id|res
comma
id|args
comma
id|res
)paren
comma
id|PROC
c_func
(paren
id|test_msg
comma
id|testargs
comma
id|norep
comma
id|args
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|lock_msg
comma
id|lockargs
comma
id|norep
comma
id|args
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|cancel_msg
comma
id|cancargs
comma
id|norep
comma
id|args
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|unlock_msg
comma
id|unlockargs
comma
id|norep
comma
id|args
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|granted_msg
comma
id|testargs
comma
id|norep
comma
id|args
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|test_res
comma
id|testres
comma
id|norep
comma
id|res
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|lock_res
comma
id|lockres
comma
id|norep
comma
id|res
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|cancel_res
comma
id|cancelres
comma
id|norep
comma
id|res
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|unlock_res
comma
id|unlockres
comma
id|norep
comma
id|res
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|granted_res
comma
id|grantedres
comma
id|norep
comma
id|res
comma
r_void
)paren
comma
multiline_comment|/* statd callback */
id|PROC
c_func
(paren
id|sm_notify
comma
id|reboot
comma
r_void
comma
id|reboot
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|none
comma
r_void
comma
r_void
comma
r_void
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|none
comma
r_void
comma
r_void
comma
r_void
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|none
comma
r_void
comma
r_void
comma
r_void
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|share
comma
id|shareargs
comma
id|shareres
comma
id|args
comma
id|res
)paren
comma
id|PROC
c_func
(paren
id|unshare
comma
id|shareargs
comma
id|shareres
comma
id|args
comma
id|res
)paren
comma
id|PROC
c_func
(paren
id|nm_lock
comma
id|lockargs
comma
id|res
comma
id|args
comma
id|res
)paren
comma
id|PROC
c_func
(paren
id|free_all
comma
id|notify
comma
r_void
comma
id|args
comma
r_void
)paren
comma
)brace
suffix:semicolon
eof
