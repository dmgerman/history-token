multiline_comment|/*&n; * linux/include/linux/lockd/xdr.h&n; *&n; * XDR types for the NLM protocol&n; *&n; * Copyright (C) 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef LOCKD_XDR_H
DECL|macro|LOCKD_XDR_H
mdefine_line|#define LOCKD_XDR_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
DECL|macro|NLM_MAXSTRLEN
mdefine_line|#define NLM_MAXSTRLEN&t;&t;1024
DECL|macro|QUADLEN
mdefine_line|#define QUADLEN(len)&t;&t;(((len) + 3) &gt;&gt; 2)
DECL|macro|nlm_granted
mdefine_line|#define&t;nlm_granted&t;&t;__constant_htonl(NLM_LCK_GRANTED)
DECL|macro|nlm_lck_denied
mdefine_line|#define&t;nlm_lck_denied&t;&t;__constant_htonl(NLM_LCK_DENIED)
DECL|macro|nlm_lck_denied_nolocks
mdefine_line|#define&t;nlm_lck_denied_nolocks&t;__constant_htonl(NLM_LCK_DENIED_NOLOCKS)
DECL|macro|nlm_lck_blocked
mdefine_line|#define&t;nlm_lck_blocked&t;&t;__constant_htonl(NLM_LCK_BLOCKED)
DECL|macro|nlm_lck_denied_grace_period
mdefine_line|#define&t;nlm_lck_denied_grace_period&t;__constant_htonl(NLM_LCK_DENIED_GRACE_PERIOD)
multiline_comment|/* Lock info passed via NLM */
DECL|struct|nlm_lock
r_struct
id|nlm_lock
(brace
DECL|member|caller
r_char
op_star
id|caller
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* length of &quot;caller&quot; */
DECL|member|fh
r_struct
id|nfs_fh
id|fh
suffix:semicolon
DECL|member|oh
r_struct
id|xdr_netobj
id|oh
suffix:semicolon
DECL|member|fl
r_struct
id|file_lock
id|fl
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;NLM cookies. Technically they can be 1K, Nobody uses over 8 bytes&n; *&t;however.&n; */
DECL|struct|nlm_cookie
r_struct
id|nlm_cookie
(brace
DECL|member|data
r_int
r_char
id|data
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Generic lockd arguments for all but sm_notify&n; */
DECL|struct|nlm_args
r_struct
id|nlm_args
(brace
DECL|member|cookie
r_struct
id|nlm_cookie
id|cookie
suffix:semicolon
DECL|member|lock
r_struct
id|nlm_lock
id|lock
suffix:semicolon
DECL|member|block
id|u32
id|block
suffix:semicolon
DECL|member|reclaim
id|u32
id|reclaim
suffix:semicolon
DECL|member|state
id|u32
id|state
suffix:semicolon
DECL|member|monitor
id|u32
id|monitor
suffix:semicolon
DECL|member|fsm_access
id|u32
id|fsm_access
suffix:semicolon
DECL|member|fsm_mode
id|u32
id|fsm_mode
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|nlm_args
r_typedef
r_struct
id|nlm_args
id|nlm_args
suffix:semicolon
multiline_comment|/*&n; * Generic lockd result&n; */
DECL|struct|nlm_res
r_struct
id|nlm_res
(brace
DECL|member|cookie
r_struct
id|nlm_cookie
id|cookie
suffix:semicolon
DECL|member|status
id|u32
id|status
suffix:semicolon
DECL|member|lock
r_struct
id|nlm_lock
id|lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * statd callback when client has rebooted&n; */
DECL|struct|nlm_reboot
r_struct
id|nlm_reboot
(brace
DECL|member|mon
r_char
op_star
id|mon
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|state
id|u32
id|state
suffix:semicolon
DECL|member|addr
id|u32
id|addr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Contents of statd callback when monitored host rebooted&n; */
DECL|macro|NLMSVC_XDRSIZE
mdefine_line|#define NLMSVC_XDRSIZE&t;&t;sizeof(struct nlm_args)
r_int
id|nlmsvc_decode_testargs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nlm_args
op_star
)paren
suffix:semicolon
r_int
id|nlmsvc_encode_testres
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nlm_res
op_star
)paren
suffix:semicolon
r_int
id|nlmsvc_decode_lockargs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nlm_args
op_star
)paren
suffix:semicolon
r_int
id|nlmsvc_decode_cancargs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nlm_args
op_star
)paren
suffix:semicolon
r_int
id|nlmsvc_decode_unlockargs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nlm_args
op_star
)paren
suffix:semicolon
r_int
id|nlmsvc_encode_res
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nlm_res
op_star
)paren
suffix:semicolon
r_int
id|nlmsvc_decode_res
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nlm_res
op_star
)paren
suffix:semicolon
r_int
id|nlmsvc_encode_void
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_int
id|nlmsvc_decode_void
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_int
id|nlmsvc_decode_shareargs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nlm_args
op_star
)paren
suffix:semicolon
r_int
id|nlmsvc_encode_shareres
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nlm_res
op_star
)paren
suffix:semicolon
r_int
id|nlmsvc_decode_notify
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nlm_args
op_star
)paren
suffix:semicolon
r_int
id|nlmsvc_decode_reboot
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nlm_reboot
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;int&t;nlmclt_encode_testargs(struct rpc_rqst *, u32 *, struct nlm_args *);&n;int&t;nlmclt_encode_lockargs(struct rpc_rqst *, u32 *, struct nlm_args *);&n;int&t;nlmclt_encode_cancargs(struct rpc_rqst *, u32 *, struct nlm_args *);&n;int&t;nlmclt_encode_unlockargs(struct rpc_rqst *, u32 *, struct nlm_args *);&n; */
macro_line|#endif /* LOCKD_XDR_H */
eof
