multiline_comment|/*&n; * linux/fs/lockd/xdr4.c&n; *&n; * XDR support for lockd and the lock client.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; * Copyright (C) 1999, Trond Myklebust &lt;trond.myklebust@fys.uio.no&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/sunrpc/stats.h&gt;
macro_line|#include &lt;linux/lockd/lockd.h&gt;
macro_line|#include &lt;linux/lockd/sm_inter.h&gt;
DECL|macro|NLMDBG_FACILITY
mdefine_line|#define NLMDBG_FACILITY&t;&t;NLMDBG_XDR
r_static
r_inline
id|loff_t
DECL|function|s64_to_loff_t
id|s64_to_loff_t
c_func
(paren
id|__s64
id|offset
)paren
(brace
r_return
(paren
id|loff_t
)paren
id|offset
suffix:semicolon
)brace
r_static
r_inline
id|s64
DECL|function|loff_t_to_s64
id|loff_t_to_s64
c_func
(paren
id|loff_t
id|offset
)paren
(brace
id|s64
id|res
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
id|NLM4_OFFSET_MAX
)paren
id|res
op_assign
id|NLM4_OFFSET_MAX
suffix:semicolon
r_else
r_if
c_cond
(paren
id|offset
OL
op_minus
id|NLM4_OFFSET_MAX
)paren
id|res
op_assign
op_minus
id|NLM4_OFFSET_MAX
suffix:semicolon
r_else
id|res
op_assign
id|offset
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * XDR functions for basic NLM types&n; */
r_static
id|u32
op_star
DECL|function|nlm4_decode_cookie
id|nlm4_decode_cookie
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|nlm_cookie
op_star
id|c
)paren
(brace
r_int
r_int
id|len
suffix:semicolon
id|len
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
(brace
id|c-&gt;len
op_assign
l_int|4
suffix:semicolon
id|memset
c_func
(paren
id|c-&gt;data
comma
l_int|0
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* hockeypux brain damage */
)brace
r_else
r_if
c_cond
(paren
id|len
op_le
l_int|8
)paren
(brace
id|c-&gt;len
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|c-&gt;data
comma
id|p
comma
id|len
)paren
suffix:semicolon
id|p
op_add_assign
(paren
id|len
op_plus
l_int|3
)paren
op_rshift
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;lockd: bad cookie size %d (only cookies under 8 bytes are supported.)&bslash;n&quot;
comma
id|len
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
r_static
id|u32
op_star
DECL|function|nlm4_encode_cookie
id|nlm4_encode_cookie
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|nlm_cookie
op_star
id|c
)paren
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|c-&gt;len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
id|c-&gt;data
comma
id|c-&gt;len
)paren
suffix:semicolon
id|p
op_add_assign
(paren
id|c-&gt;len
op_plus
l_int|3
)paren
op_rshift
l_int|2
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
r_static
id|u32
op_star
DECL|function|nlm4_decode_fh
id|nlm4_decode_fh
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|nfs_fh
op_star
id|f
)paren
(brace
id|memset
c_func
(paren
id|f-&gt;data
comma
l_int|0
comma
r_sizeof
(paren
id|f-&gt;data
)paren
)paren
suffix:semicolon
id|f-&gt;size
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;size
OG
id|NFS_MAXFHSIZE
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;lockd: bad fhandle size %d (should be &lt;=%d)&bslash;n&quot;
comma
id|f-&gt;size
comma
id|NFS_MAXFHSIZE
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|f-&gt;data
comma
id|p
comma
id|f-&gt;size
)paren
suffix:semicolon
r_return
id|p
op_plus
id|XDR_QUADLEN
c_func
(paren
id|f-&gt;size
)paren
suffix:semicolon
)brace
r_static
id|u32
op_star
DECL|function|nlm4_encode_fh
id|nlm4_encode_fh
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|nfs_fh
op_star
id|f
)paren
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|f-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;size
)paren
id|p
(braket
id|XDR_QUADLEN
c_func
(paren
id|f-&gt;size
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* don&squot;t leak anything */
id|memcpy
c_func
(paren
id|p
comma
id|f-&gt;data
comma
id|f-&gt;size
)paren
suffix:semicolon
r_return
id|p
op_plus
id|XDR_QUADLEN
c_func
(paren
id|f-&gt;size
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode and decode owner handle&n; */
r_static
id|u32
op_star
DECL|function|nlm4_decode_oh
id|nlm4_decode_oh
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|xdr_netobj
op_star
id|oh
)paren
(brace
r_return
id|xdr_decode_netobj
c_func
(paren
id|p
comma
id|oh
)paren
suffix:semicolon
)brace
r_static
id|u32
op_star
DECL|function|nlm4_encode_oh
id|nlm4_encode_oh
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|xdr_netobj
op_star
id|oh
)paren
(brace
r_return
id|xdr_encode_netobj
c_func
(paren
id|p
comma
id|oh
)paren
suffix:semicolon
)brace
r_static
id|u32
op_star
DECL|function|nlm4_decode_lock
id|nlm4_decode_lock
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|nlm_lock
op_star
id|lock
)paren
(brace
r_struct
id|file_lock
op_star
id|fl
op_assign
op_amp
id|lock-&gt;fl
suffix:semicolon
id|__s64
id|len
comma
id|start
comma
id|end
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|xdr_decode_string_inplace
c_func
(paren
id|p
comma
op_amp
id|lock-&gt;caller
comma
op_amp
id|lock-&gt;len
comma
id|NLM_MAXSTRLEN
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_fh
c_func
(paren
id|p
comma
op_amp
id|lock-&gt;fh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_oh
c_func
(paren
id|p
comma
op_amp
id|lock-&gt;oh
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|locks_init_lock
c_func
(paren
id|fl
)paren
suffix:semicolon
id|fl-&gt;fl_owner
op_assign
id|current-&gt;files
suffix:semicolon
id|fl-&gt;fl_pid
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fl-&gt;fl_flags
op_assign
id|FL_POSIX
suffix:semicolon
id|fl-&gt;fl_type
op_assign
id|F_RDLCK
suffix:semicolon
multiline_comment|/* as good as anything else */
id|p
op_assign
id|xdr_decode_hyper
c_func
(paren
id|p
comma
op_amp
id|start
)paren
suffix:semicolon
id|p
op_assign
id|xdr_decode_hyper
c_func
(paren
id|p
comma
op_amp
id|len
)paren
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|len
op_minus
l_int|1
suffix:semicolon
id|fl-&gt;fl_start
op_assign
id|s64_to_loff_t
c_func
(paren
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
op_logical_or
id|end
OL
l_int|0
)paren
id|fl-&gt;fl_end
op_assign
id|OFFSET_MAX
suffix:semicolon
r_else
id|fl-&gt;fl_end
op_assign
id|s64_to_loff_t
c_func
(paren
id|end
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode a lock as part of an NLM call&n; */
r_static
id|u32
op_star
DECL|function|nlm4_encode_lock
id|nlm4_encode_lock
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|nlm_lock
op_star
id|lock
)paren
(brace
r_struct
id|file_lock
op_star
id|fl
op_assign
op_amp
id|lock-&gt;fl
suffix:semicolon
id|__s64
id|start
comma
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|xdr_encode_string
c_func
(paren
id|p
comma
id|lock-&gt;caller
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_fh
c_func
(paren
id|p
comma
op_amp
id|lock-&gt;fh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_oh
c_func
(paren
id|p
comma
op_amp
id|lock-&gt;oh
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;fl_start
OG
id|NLM4_OFFSET_MAX
op_logical_or
(paren
id|fl-&gt;fl_end
OG
id|NLM4_OFFSET_MAX
op_logical_and
id|fl-&gt;fl_end
op_ne
id|OFFSET_MAX
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|fl-&gt;fl_pid
)paren
suffix:semicolon
id|start
op_assign
id|loff_t_to_s64
c_func
(paren
id|fl-&gt;fl_start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;fl_end
op_eq
id|OFFSET_MAX
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_else
id|len
op_assign
id|loff_t_to_s64
c_func
(paren
id|fl-&gt;fl_end
op_minus
id|fl-&gt;fl_start
op_plus
l_int|1
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_hyper
c_func
(paren
id|p
comma
id|start
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_hyper
c_func
(paren
id|p
comma
id|len
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode result of a TEST/TEST_MSG call&n; */
r_static
id|u32
op_star
DECL|function|nlm4_encode_testres
id|nlm4_encode_testres
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|nlm_res
op_star
id|resp
)paren
(brace
id|s64
id|start
comma
id|len
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;xdr: before encode_testres (p %p resp %p)&bslash;n&quot;
comma
id|p
comma
id|resp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_cookie
c_func
(paren
id|p
comma
op_amp
id|resp-&gt;cookie
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|resp-&gt;status
suffix:semicolon
r_if
c_cond
(paren
id|resp-&gt;status
op_eq
id|nlm_lck_denied
)paren
(brace
r_struct
id|file_lock
op_star
id|fl
op_assign
op_amp
id|resp-&gt;lock.fl
suffix:semicolon
op_star
id|p
op_increment
op_assign
(paren
id|fl-&gt;fl_type
op_eq
id|F_RDLCK
)paren
ques
c_cond
id|xdr_zero
suffix:colon
id|xdr_one
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|fl-&gt;fl_pid
)paren
suffix:semicolon
multiline_comment|/* Encode owner handle. */
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|xdr_encode_netobj
c_func
(paren
id|p
comma
op_amp
id|resp-&gt;lock.oh
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|start
op_assign
id|loff_t_to_s64
c_func
(paren
id|fl-&gt;fl_start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;fl_end
op_eq
id|OFFSET_MAX
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_else
id|len
op_assign
id|loff_t_to_s64
c_func
(paren
id|fl-&gt;fl_end
op_minus
id|fl-&gt;fl_start
op_plus
l_int|1
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_hyper
c_func
(paren
id|p
comma
id|start
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_hyper
c_func
(paren
id|p
comma
id|len
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;xdr: encode_testres (status %d pid %d type %d start %Ld end %Ld)&bslash;n&quot;
comma
id|resp-&gt;status
comma
id|fl-&gt;fl_pid
comma
id|fl-&gt;fl_type
comma
(paren
r_int
r_int
)paren
id|fl-&gt;fl_start
comma
(paren
r_int
r_int
)paren
id|fl-&gt;fl_end
)paren
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;xdr: after encode_testres (p %p resp %p)&bslash;n&quot;
comma
id|p
comma
id|resp
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * Check buffer bounds after decoding arguments&n; */
r_static
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
r_struct
id|svc_buf
op_star
id|buf
op_assign
op_amp
id|rqstp-&gt;rq_argbuf
suffix:semicolon
r_return
id|p
op_minus
id|buf-&gt;base
op_le
id|buf-&gt;buflen
suffix:semicolon
)brace
r_static
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
id|svc_buf
op_star
id|buf
op_assign
op_amp
id|rqstp-&gt;rq_resbuf
suffix:semicolon
id|buf-&gt;len
op_assign
id|p
op_minus
id|buf-&gt;base
suffix:semicolon
r_return
(paren
id|buf-&gt;len
op_le
id|buf-&gt;buflen
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * First, the server side XDR functions&n; */
r_int
DECL|function|nlm4svc_decode_testargs
id|nlm4svc_decode_testargs
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
comma
id|nlm_args
op_star
id|argp
)paren
(brace
id|u32
id|exclusive
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_cookie
c_func
(paren
id|p
comma
op_amp
id|argp-&gt;cookie
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|exclusive
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_lock
c_func
(paren
id|p
comma
op_amp
id|argp-&gt;lock
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|exclusive
)paren
id|argp-&gt;lock.fl.fl_type
op_assign
id|F_WRLCK
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nlm4svc_encode_testres
id|nlm4svc_encode_testres
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
comma
r_struct
id|nlm_res
op_star
id|resp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_testres
c_func
(paren
id|p
comma
id|resp
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nlm4svc_decode_lockargs
id|nlm4svc_decode_lockargs
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
comma
id|nlm_args
op_star
id|argp
)paren
(brace
id|u32
id|exclusive
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_cookie
c_func
(paren
id|p
comma
op_amp
id|argp-&gt;cookie
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|argp-&gt;block
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|exclusive
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_lock
c_func
(paren
id|p
comma
op_amp
id|argp-&gt;lock
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|exclusive
)paren
id|argp-&gt;lock.fl.fl_type
op_assign
id|F_WRLCK
suffix:semicolon
id|argp-&gt;reclaim
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|argp-&gt;state
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|argp-&gt;monitor
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* monitor client by default */
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nlm4svc_decode_cancargs
id|nlm4svc_decode_cancargs
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
comma
id|nlm_args
op_star
id|argp
)paren
(brace
id|u32
id|exclusive
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_cookie
c_func
(paren
id|p
comma
op_amp
id|argp-&gt;cookie
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|argp-&gt;block
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|exclusive
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_lock
c_func
(paren
id|p
comma
op_amp
id|argp-&gt;lock
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|exclusive
)paren
id|argp-&gt;lock.fl.fl_type
op_assign
id|F_WRLCK
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nlm4svc_decode_unlockargs
id|nlm4svc_decode_unlockargs
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
comma
id|nlm_args
op_star
id|argp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_cookie
c_func
(paren
id|p
comma
op_amp
id|argp-&gt;cookie
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_lock
c_func
(paren
id|p
comma
op_amp
id|argp-&gt;lock
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|argp-&gt;lock.fl.fl_type
op_assign
id|F_UNLCK
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nlm4svc_decode_shareargs
id|nlm4svc_decode_shareargs
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
comma
id|nlm_args
op_star
id|argp
)paren
(brace
r_struct
id|nlm_lock
op_star
id|lock
op_assign
op_amp
id|argp-&gt;lock
suffix:semicolon
id|memset
c_func
(paren
id|lock
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|lock
)paren
)paren
suffix:semicolon
id|locks_init_lock
c_func
(paren
op_amp
id|lock-&gt;fl
)paren
suffix:semicolon
id|lock-&gt;fl.fl_pid
op_assign
op_complement
(paren
id|u32
)paren
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_cookie
c_func
(paren
id|p
comma
op_amp
id|argp-&gt;cookie
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|xdr_decode_string_inplace
c_func
(paren
id|p
comma
op_amp
id|lock-&gt;caller
comma
op_amp
id|lock-&gt;len
comma
id|NLM_MAXSTRLEN
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_fh
c_func
(paren
id|p
comma
op_amp
id|lock-&gt;fh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_oh
c_func
(paren
id|p
comma
op_amp
id|lock-&gt;oh
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|argp-&gt;fsm_mode
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|argp-&gt;fsm_access
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nlm4svc_encode_shareres
id|nlm4svc_encode_shareres
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
comma
r_struct
id|nlm_res
op_star
id|resp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_cookie
c_func
(paren
id|p
comma
op_amp
id|resp-&gt;cookie
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|resp-&gt;status
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|xdr_zero
suffix:semicolon
multiline_comment|/* sequence argument */
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nlm4svc_encode_res
id|nlm4svc_encode_res
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
comma
r_struct
id|nlm_res
op_star
id|resp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_cookie
c_func
(paren
id|p
comma
op_amp
id|resp-&gt;cookie
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|resp-&gt;status
suffix:semicolon
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nlm4svc_decode_notify
id|nlm4svc_decode_notify
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
comma
r_struct
id|nlm_args
op_star
id|argp
)paren
(brace
r_struct
id|nlm_lock
op_star
id|lock
op_assign
op_amp
id|argp-&gt;lock
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|xdr_decode_string_inplace
c_func
(paren
id|p
comma
op_amp
id|lock-&gt;caller
comma
op_amp
id|lock-&gt;len
comma
id|NLM_MAXSTRLEN
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|argp-&gt;state
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nlm4svc_decode_reboot
id|nlm4svc_decode_reboot
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
comma
r_struct
id|nlm_reboot
op_star
id|argp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|xdr_decode_string_inplace
c_func
(paren
id|p
comma
op_amp
id|argp-&gt;mon
comma
op_amp
id|argp-&gt;len
comma
id|SM_MAXSTRLEN
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|argp-&gt;state
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
multiline_comment|/* Preserve the address in network byte order */
id|argp-&gt;addr
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nlm4svc_decode_res
id|nlm4svc_decode_res
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
comma
r_struct
id|nlm_res
op_star
id|resp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_cookie
c_func
(paren
id|p
comma
op_amp
id|resp-&gt;cookie
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|resp-&gt;status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nlm4svc_decode_void
id|nlm4svc_decode_void
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
comma
r_void
op_star
id|dummy
)paren
(brace
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nlm4svc_encode_void
id|nlm4svc_encode_void
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
comma
r_void
op_star
id|dummy
)paren
(brace
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Now, the client side XDR functions&n; */
r_static
r_int
DECL|function|nlm4clt_encode_void
id|nlm4clt_encode_void
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
id|ptr
)paren
(brace
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
DECL|function|nlm4clt_decode_void
id|nlm4clt_decode_void
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
id|ptr
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|nlm4clt_encode_testargs
id|nlm4clt_encode_testargs
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
id|nlm_args
op_star
id|argp
)paren
(brace
r_struct
id|nlm_lock
op_star
id|lock
op_assign
op_amp
id|argp-&gt;lock
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_cookie
c_func
(paren
id|p
comma
op_amp
id|argp-&gt;cookie
)paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
op_star
id|p
op_increment
op_assign
(paren
id|lock-&gt;fl.fl_type
op_eq
id|F_WRLCK
)paren
ques
c_cond
id|xdr_one
suffix:colon
id|xdr_zero
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_lock
c_func
(paren
id|p
comma
id|lock
)paren
)paren
)paren
r_return
op_minus
id|EIO
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
DECL|function|nlm4clt_decode_testres
id|nlm4clt_decode_testres
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
id|nlm_res
op_star
id|resp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_cookie
c_func
(paren
id|p
comma
op_amp
id|resp-&gt;cookie
)paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|resp-&gt;status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resp-&gt;status
op_eq
id|NLM_LCK_DENIED
)paren
(brace
r_struct
id|file_lock
op_star
id|fl
op_assign
op_amp
id|resp-&gt;lock.fl
suffix:semicolon
id|u32
id|excl
suffix:semicolon
id|s64
id|start
comma
id|end
comma
id|len
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|resp-&gt;lock
comma
l_int|0
comma
r_sizeof
(paren
id|resp-&gt;lock
)paren
)paren
suffix:semicolon
id|locks_init_lock
c_func
(paren
id|fl
)paren
suffix:semicolon
id|excl
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fl-&gt;fl_pid
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_oh
c_func
(paren
id|p
comma
op_amp
id|resp-&gt;lock.oh
)paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|fl-&gt;fl_flags
op_assign
id|FL_POSIX
suffix:semicolon
id|fl-&gt;fl_type
op_assign
id|excl
ques
c_cond
id|F_WRLCK
suffix:colon
id|F_RDLCK
suffix:semicolon
id|p
op_assign
id|xdr_decode_hyper
c_func
(paren
id|p
comma
op_amp
id|start
)paren
suffix:semicolon
id|p
op_assign
id|xdr_decode_hyper
c_func
(paren
id|p
comma
op_amp
id|len
)paren
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|len
op_minus
l_int|1
suffix:semicolon
id|fl-&gt;fl_start
op_assign
id|s64_to_loff_t
c_func
(paren
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
op_logical_or
id|end
OL
l_int|0
)paren
id|fl-&gt;fl_end
op_assign
id|OFFSET_MAX
suffix:semicolon
r_else
id|fl-&gt;fl_end
op_assign
id|s64_to_loff_t
c_func
(paren
id|end
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|nlm4clt_encode_lockargs
id|nlm4clt_encode_lockargs
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
id|nlm_args
op_star
id|argp
)paren
(brace
r_struct
id|nlm_lock
op_star
id|lock
op_assign
op_amp
id|argp-&gt;lock
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_cookie
c_func
(paren
id|p
comma
op_amp
id|argp-&gt;cookie
)paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|argp-&gt;block
ques
c_cond
id|xdr_one
suffix:colon
id|xdr_zero
suffix:semicolon
op_star
id|p
op_increment
op_assign
(paren
id|lock-&gt;fl.fl_type
op_eq
id|F_WRLCK
)paren
ques
c_cond
id|xdr_one
suffix:colon
id|xdr_zero
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_lock
c_func
(paren
id|p
comma
id|lock
)paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|argp-&gt;reclaim
ques
c_cond
id|xdr_one
suffix:colon
id|xdr_zero
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|argp-&gt;state
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
DECL|function|nlm4clt_encode_cancargs
id|nlm4clt_encode_cancargs
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
id|nlm_args
op_star
id|argp
)paren
(brace
r_struct
id|nlm_lock
op_star
id|lock
op_assign
op_amp
id|argp-&gt;lock
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_cookie
c_func
(paren
id|p
comma
op_amp
id|argp-&gt;cookie
)paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|argp-&gt;block
ques
c_cond
id|xdr_one
suffix:colon
id|xdr_zero
suffix:semicolon
op_star
id|p
op_increment
op_assign
(paren
id|lock-&gt;fl.fl_type
op_eq
id|F_WRLCK
)paren
ques
c_cond
id|xdr_one
suffix:colon
id|xdr_zero
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_lock
c_func
(paren
id|p
comma
id|lock
)paren
)paren
)paren
r_return
op_minus
id|EIO
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
DECL|function|nlm4clt_encode_unlockargs
id|nlm4clt_encode_unlockargs
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
id|nlm_args
op_star
id|argp
)paren
(brace
r_struct
id|nlm_lock
op_star
id|lock
op_assign
op_amp
id|argp-&gt;lock
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_cookie
c_func
(paren
id|p
comma
op_amp
id|argp-&gt;cookie
)paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_lock
c_func
(paren
id|p
comma
id|lock
)paren
)paren
)paren
r_return
op_minus
id|EIO
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
DECL|function|nlm4clt_encode_res
id|nlm4clt_encode_res
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
id|nlm_res
op_star
id|resp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_cookie
c_func
(paren
id|p
comma
op_amp
id|resp-&gt;cookie
)paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|resp-&gt;status
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
DECL|function|nlm4clt_encode_testres
id|nlm4clt_encode_testres
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
id|nlm_res
op_star
id|resp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_encode_testres
c_func
(paren
id|p
comma
id|resp
)paren
)paren
)paren
r_return
op_minus
id|EIO
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
DECL|function|nlm4clt_decode_res
id|nlm4clt_decode_res
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
id|nlm_res
op_star
id|resp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|nlm4_decode_cookie
c_func
(paren
id|p
comma
op_amp
id|resp-&gt;cookie
)paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|resp-&gt;status
op_assign
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
multiline_comment|/*&n; * Buffer requirements for NLM&n; */
DECL|macro|NLM4_void_sz
mdefine_line|#define NLM4_void_sz&t;&t;0
DECL|macro|NLM4_cookie_sz
mdefine_line|#define NLM4_cookie_sz&t;&t;3&t;/* 1 len , 2 data */
DECL|macro|NLM4_caller_sz
mdefine_line|#define NLM4_caller_sz&t;&t;1+XDR_QUADLEN(NLM_MAXSTRLEN)
DECL|macro|NLM4_netobj_sz
mdefine_line|#define NLM4_netobj_sz&t;&t;1+XDR_QUADLEN(XDR_MAX_NETOBJ)
multiline_comment|/* #define NLM4_owner_sz&t;&t;1+XDR_QUADLEN(NLM4_MAXOWNER) */
DECL|macro|NLM4_fhandle_sz
mdefine_line|#define NLM4_fhandle_sz&t;&t;1+XDR_QUADLEN(NFS3_FHSIZE)
DECL|macro|NLM4_lock_sz
mdefine_line|#define NLM4_lock_sz&t;&t;5+NLM4_caller_sz+NLM4_netobj_sz+NLM4_fhandle_sz
DECL|macro|NLM4_holder_sz
mdefine_line|#define NLM4_holder_sz&t;&t;6+NLM4_netobj_sz
DECL|macro|NLM4_testargs_sz
mdefine_line|#define NLM4_testargs_sz&t;NLM4_cookie_sz+1+NLM4_lock_sz
DECL|macro|NLM4_lockargs_sz
mdefine_line|#define NLM4_lockargs_sz&t;NLM4_cookie_sz+4+NLM4_lock_sz
DECL|macro|NLM4_cancargs_sz
mdefine_line|#define NLM4_cancargs_sz&t;NLM4_cookie_sz+2+NLM4_lock_sz
DECL|macro|NLM4_unlockargs_sz
mdefine_line|#define NLM4_unlockargs_sz&t;NLM4_cookie_sz+NLM4_lock_sz
DECL|macro|NLM4_testres_sz
mdefine_line|#define NLM4_testres_sz&t;&t;NLM4_cookie_sz+1+NLM4_holder_sz
DECL|macro|NLM4_res_sz
mdefine_line|#define NLM4_res_sz&t;&t;NLM4_cookie_sz+1
DECL|macro|NLM4_norep_sz
mdefine_line|#define NLM4_norep_sz&t;&t;0
macro_line|#ifndef MAX
DECL|macro|MAX
macro_line|# define MAX(a,b)&t;&t;(((a) &gt; (b))? (a) : (b))
macro_line|#endif
multiline_comment|/*&n; * For NLM, a void procedure really returns nothing&n; */
DECL|macro|nlm4clt_decode_norep
mdefine_line|#define nlm4clt_decode_norep&t;NULL
DECL|macro|PROC
mdefine_line|#define PROC(proc, argtype, restype)&t;&t;&t;&t;&bslash;&n;    { &quot;nlm4_&quot; #proc,&t;&t;&t;&t;&t;&t;&bslash;&n;      (kxdrproc_t) nlm4clt_encode_##argtype,&t;&t;&t;&bslash;&n;      (kxdrproc_t) nlm4clt_decode_##restype,&t;&t;&t;&bslash;&n;      MAX(NLM4_##argtype##_sz, NLM4_##restype##_sz) &lt;&lt; 2,&t;&bslash;&n;      0&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    }
DECL|variable|nlm4_procedures
r_static
r_struct
id|rpc_procinfo
id|nlm4_procedures
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
)paren
comma
id|PROC
c_func
(paren
id|canc
comma
id|cancargs
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
)paren
comma
id|PROC
c_func
(paren
id|canc_msg
comma
id|cancargs
comma
id|norep
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
)paren
comma
id|PROC
c_func
(paren
id|lock_res
comma
id|res
comma
id|norep
)paren
comma
id|PROC
c_func
(paren
id|canc_res
comma
id|res
comma
id|norep
)paren
comma
id|PROC
c_func
(paren
id|unlock_res
comma
id|res
comma
id|norep
)paren
comma
id|PROC
c_func
(paren
id|granted_res
comma
id|res
comma
id|norep
)paren
comma
id|PROC
c_func
(paren
id|undef
comma
r_void
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|undef
comma
r_void
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|undef
comma
r_void
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|undef
comma
r_void
comma
r_void
)paren
comma
macro_line|#ifdef NLMCLNT_SUPPORT_SHARES
id|PROC
c_func
(paren
id|share
comma
id|shareargs
comma
id|shareres
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
)paren
comma
macro_line|#else
id|PROC
c_func
(paren
id|undef
comma
r_void
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|undef
comma
r_void
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|undef
comma
r_void
comma
r_void
)paren
comma
id|PROC
c_func
(paren
id|undef
comma
r_void
comma
r_void
)paren
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|variable|nlm_version4
r_struct
id|rpc_version
id|nlm_version4
op_assign
(brace
l_int|4
comma
l_int|24
comma
id|nlm4_procedures
comma
)brace
suffix:semicolon
eof
