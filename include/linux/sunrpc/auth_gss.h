multiline_comment|/*&n; * linux/include/linux/auth_gss.h&n; *&n; * Declarations for RPCSEC_GSS&n; *&n; * Dug Song &lt;dugsong@monkey.org&gt;&n; * Andy Adamson &lt;andros@umich.edu&gt;&n; * Bruce Fields &lt;bfields@umich.edu&gt;&n; * Copyright (c) 2000 The Regents of the University of Michigan&n; *&n; * $Id$&n; */
macro_line|#ifndef _LINUX_SUNRPC_AUTH_GSS_H
DECL|macro|_LINUX_SUNRPC_AUTH_GSS_H
mdefine_line|#define _LINUX_SUNRPC_AUTH_GSS_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/sunrpc/auth.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/sunrpc/gss_api.h&gt;
DECL|macro|RPC_GSS_VERSION
mdefine_line|#define RPC_GSS_VERSION&t;&t;1
DECL|macro|MAXSEQ
mdefine_line|#define MAXSEQ 0x80000000 /* maximum legal sequence number, from rfc 2203 */
DECL|enum|rpc_gss_proc
r_enum
id|rpc_gss_proc
(brace
DECL|enumerator|RPC_GSS_PROC_DATA
id|RPC_GSS_PROC_DATA
op_assign
l_int|0
comma
DECL|enumerator|RPC_GSS_PROC_INIT
id|RPC_GSS_PROC_INIT
op_assign
l_int|1
comma
DECL|enumerator|RPC_GSS_PROC_CONTINUE_INIT
id|RPC_GSS_PROC_CONTINUE_INIT
op_assign
l_int|2
comma
DECL|enumerator|RPC_GSS_PROC_DESTROY
id|RPC_GSS_PROC_DESTROY
op_assign
l_int|3
)brace
suffix:semicolon
DECL|enum|rpc_gss_svc
r_enum
id|rpc_gss_svc
(brace
DECL|enumerator|RPC_GSS_SVC_NONE
id|RPC_GSS_SVC_NONE
op_assign
l_int|1
comma
DECL|enumerator|RPC_GSS_SVC_INTEGRITY
id|RPC_GSS_SVC_INTEGRITY
op_assign
l_int|2
comma
DECL|enumerator|RPC_GSS_SVC_PRIVACY
id|RPC_GSS_SVC_PRIVACY
op_assign
l_int|3
)brace
suffix:semicolon
multiline_comment|/* on-the-wire gss cred: */
DECL|struct|rpc_gss_wire_cred
r_struct
id|rpc_gss_wire_cred
(brace
DECL|member|gc_v
id|u32
id|gc_v
suffix:semicolon
multiline_comment|/* version */
DECL|member|gc_proc
id|u32
id|gc_proc
suffix:semicolon
multiline_comment|/* control procedure */
DECL|member|gc_seq
id|u32
id|gc_seq
suffix:semicolon
multiline_comment|/* sequence number */
DECL|member|gc_svc
id|u32
id|gc_svc
suffix:semicolon
multiline_comment|/* service */
DECL|member|gc_ctx
r_struct
id|xdr_netobj
id|gc_ctx
suffix:semicolon
multiline_comment|/* context handle */
)brace
suffix:semicolon
multiline_comment|/* on-the-wire gss verifier: */
DECL|struct|rpc_gss_wire_verf
r_struct
id|rpc_gss_wire_verf
(brace
DECL|member|gv_flavor
id|u32
id|gv_flavor
suffix:semicolon
DECL|member|gv_verf
r_struct
id|xdr_netobj
id|gv_verf
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* return from gss NULL PROC init sec context */
DECL|struct|rpc_gss_init_res
r_struct
id|rpc_gss_init_res
(brace
DECL|member|gr_ctx
r_struct
id|xdr_netobj
id|gr_ctx
suffix:semicolon
multiline_comment|/* context handle */
DECL|member|gr_major
id|u32
id|gr_major
suffix:semicolon
multiline_comment|/* major status */
DECL|member|gr_minor
id|u32
id|gr_minor
suffix:semicolon
multiline_comment|/* minor status */
DECL|member|gr_win
id|u32
id|gr_win
suffix:semicolon
multiline_comment|/* sequence window */
DECL|member|gr_token
r_struct
id|xdr_netobj
id|gr_token
suffix:semicolon
multiline_comment|/* token */
)brace
suffix:semicolon
multiline_comment|/* The gss_cl_ctx struct holds all the information the rpcsec_gss client&n; * code needs to know about a single security context.  In particular,&n; * gc_gss_ctx is the context handle that is used to do gss-api calls, while&n; * gc_wire_ctx is the context handle that is used to identify the context on&n; * the wire when communicating with a server. */
DECL|struct|gss_cl_ctx
r_struct
id|gss_cl_ctx
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|gc_proc
id|u32
id|gc_proc
suffix:semicolon
DECL|member|gc_seq
id|u32
id|gc_seq
suffix:semicolon
DECL|member|gc_seq_lock
id|spinlock_t
id|gc_seq_lock
suffix:semicolon
DECL|member|gc_gss_ctx
r_struct
id|gss_ctx
op_star
id|gc_gss_ctx
suffix:semicolon
DECL|member|gc_wire_ctx
r_struct
id|xdr_netobj
id|gc_wire_ctx
suffix:semicolon
DECL|member|gc_win
id|u32
id|gc_win
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|gss_cred
r_struct
id|gss_cred
(brace
DECL|member|gc_base
r_struct
id|rpc_cred
id|gc_base
suffix:semicolon
DECL|member|gc_flavor
id|u32
id|gc_flavor
suffix:semicolon
DECL|member|gc_ctx
r_struct
id|gss_cl_ctx
op_star
id|gc_ctx
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|gc_uid
mdefine_line|#define gc_uid&t;&t;&t;gc_base.cr_uid
DECL|macro|gc_count
mdefine_line|#define gc_count&t;&t;gc_base.cr_count
DECL|macro|gc_flags
mdefine_line|#define gc_flags&t;&t;gc_base.cr_flags
DECL|macro|gc_expire
mdefine_line|#define gc_expire&t;&t;gc_base.cr_expire
r_void
id|print_hexl
c_func
(paren
id|u32
op_star
id|p
comma
id|u_int
id|length
comma
id|u_int
id|offset
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SUNRPC_AUTH_GSS_H */
eof
