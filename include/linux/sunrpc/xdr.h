multiline_comment|/*&n; * include/linux/sunrpc/xdr.h&n; *&n; * Copyright (C) 1995-1997 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef _SUNRPC_XDR_H_
DECL|macro|_SUNRPC_XDR_H_
mdefine_line|#define _SUNRPC_XDR_H_
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/uio.h&gt;
multiline_comment|/*&n; * Buffer adjustment&n; */
DECL|macro|XDR_QUADLEN
mdefine_line|#define XDR_QUADLEN(l)&t;&t;(((l) + 3) &gt;&gt; 2)
multiline_comment|/*&n; * Generic opaque `network object.&squot; At the kernel level, this type&n; * is used only by lockd.&n; */
DECL|macro|XDR_MAX_NETOBJ
mdefine_line|#define XDR_MAX_NETOBJ&t;&t;1024
DECL|struct|xdr_netobj
r_struct
id|xdr_netobj
(brace
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|data
id|u8
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the generic XDR function. rqstp is either a rpc_rqst (client&n; * side) or svc_rqst pointer (server side).&n; * Encode functions always assume there&squot;s enough room in the buffer.&n; */
DECL|typedef|kxdrproc_t
r_typedef
r_int
(paren
op_star
id|kxdrproc_t
)paren
(paren
r_void
op_star
id|rqstp
comma
id|u32
op_star
id|data
comma
r_void
op_star
id|obj
)paren
suffix:semicolon
multiline_comment|/*&n; * pre-xdr&squot;ed macros.&n; */
DECL|macro|xdr_zero
mdefine_line|#define&t;xdr_zero&t;__constant_htonl(0)
DECL|macro|xdr_one
mdefine_line|#define&t;xdr_one&t;&t;__constant_htonl(1)
DECL|macro|xdr_two
mdefine_line|#define&t;xdr_two&t;&t;__constant_htonl(2)
DECL|macro|rpc_success
mdefine_line|#define&t;rpc_success&t;&t;__constant_htonl(RPC_SUCCESS)
DECL|macro|rpc_prog_unavail
mdefine_line|#define&t;rpc_prog_unavail&t;__constant_htonl(RPC_PROG_UNAVAIL)
DECL|macro|rpc_prog_mismatch
mdefine_line|#define&t;rpc_prog_mismatch&t;__constant_htonl(RPC_PROG_MISMATCH)
DECL|macro|rpc_proc_unavail
mdefine_line|#define&t;rpc_proc_unavail&t;__constant_htonl(RPC_PROC_UNAVAIL)
DECL|macro|rpc_garbage_args
mdefine_line|#define&t;rpc_garbage_args&t;__constant_htonl(RPC_GARBAGE_ARGS)
DECL|macro|rpc_system_err
mdefine_line|#define&t;rpc_system_err&t;&t;__constant_htonl(RPC_SYSTEM_ERR)
DECL|macro|rpc_auth_ok
mdefine_line|#define&t;rpc_auth_ok&t;&t;__constant_htonl(RPC_AUTH_OK)
DECL|macro|rpc_autherr_badcred
mdefine_line|#define&t;rpc_autherr_badcred&t;__constant_htonl(RPC_AUTH_BADCRED)
DECL|macro|rpc_autherr_rejectedcred
mdefine_line|#define&t;rpc_autherr_rejectedcred __constant_htonl(RPC_AUTH_REJECTEDCRED)
DECL|macro|rpc_autherr_badverf
mdefine_line|#define&t;rpc_autherr_badverf&t;__constant_htonl(RPC_AUTH_BADVERF)
DECL|macro|rpc_autherr_rejectedverf
mdefine_line|#define&t;rpc_autherr_rejectedverf __constant_htonl(RPC_AUTH_REJECTEDVERF)
DECL|macro|rpc_autherr_tooweak
mdefine_line|#define&t;rpc_autherr_tooweak&t;__constant_htonl(RPC_AUTH_TOOWEAK)
multiline_comment|/*&n; * Miscellaneous XDR helper functions&n; */
id|u32
op_star
id|xdr_encode_array
c_func
(paren
id|u32
op_star
id|p
comma
r_const
r_char
op_star
id|s
comma
r_int
r_int
id|len
)paren
suffix:semicolon
id|u32
op_star
id|xdr_encode_string
c_func
(paren
id|u32
op_star
id|p
comma
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
id|u32
op_star
id|xdr_decode_string
c_func
(paren
id|u32
op_star
id|p
comma
r_char
op_star
op_star
id|sp
comma
r_int
op_star
id|lenp
comma
r_int
id|maxlen
)paren
suffix:semicolon
id|u32
op_star
id|xdr_decode_string_inplace
c_func
(paren
id|u32
op_star
id|p
comma
r_char
op_star
op_star
id|sp
comma
r_int
op_star
id|lenp
comma
r_int
id|maxlen
)paren
suffix:semicolon
id|u32
op_star
id|xdr_encode_netobj
c_func
(paren
id|u32
op_star
id|p
comma
r_const
r_struct
id|xdr_netobj
op_star
)paren
suffix:semicolon
id|u32
op_star
id|xdr_decode_netobj
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|xdr_netobj
op_star
)paren
suffix:semicolon
id|u32
op_star
id|xdr_decode_netobj_fixed
c_func
(paren
id|u32
op_star
id|p
comma
r_void
op_star
id|obj
comma
r_int
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/*&n; * Decode 64bit quantities (NFSv3 support)&n; */
r_static
r_inline
id|u32
op_star
DECL|function|xdr_encode_hyper
id|xdr_encode_hyper
c_func
(paren
id|u32
op_star
id|p
comma
id|__u64
id|val
)paren
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|val
op_rshift
l_int|32
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|val
op_amp
l_int|0xFFFFFFFF
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|xdr_decode_hyper
id|xdr_decode_hyper
c_func
(paren
id|u32
op_star
id|p
comma
id|__u64
op_star
id|valp
)paren
(brace
op_star
id|valp
op_assign
(paren
(paren
id|__u64
)paren
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
op_lshift
l_int|32
suffix:semicolon
op_star
id|valp
op_or_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * Adjust iovec to reflect end of xdr&squot;ed data (RPC client XDR)&n; */
r_static
r_inline
r_int
DECL|function|xdr_adjust_iovec
id|xdr_adjust_iovec
c_func
(paren
r_struct
id|iovec
op_star
id|iov
comma
id|u32
op_star
id|p
)paren
(brace
r_return
id|iov-&gt;iov_len
op_assign
(paren
(paren
id|u8
op_star
)paren
id|p
op_minus
(paren
id|u8
op_star
)paren
id|iov-&gt;iov_base
)paren
suffix:semicolon
)brace
r_void
id|xdr_shift_iovec
c_func
(paren
r_struct
id|iovec
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|xdr_zero_iovec
c_func
(paren
r_struct
id|iovec
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _SUNRPC_XDR_H_ */
eof
