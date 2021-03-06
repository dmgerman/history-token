multiline_comment|/*&n; * linux/include/linux/sunrpc/auth.h&n; *&n; * Declarations for the RPC client authentication machinery.&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef _LINUX_SUNRPC_AUTH_H
DECL|macro|_LINUX_SUNRPC_AUTH_H
mdefine_line|#define _LINUX_SUNRPC_AUTH_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sunrpc/sched.h&gt;
macro_line|#include &lt;linux/sunrpc/msg_prot.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/* size of the nodename buffer */
DECL|macro|UNX_MAXNODENAME
mdefine_line|#define UNX_MAXNODENAME&t;32
multiline_comment|/* Maximum size (in bytes) of an rpc credential or verifier */
DECL|macro|RPC_MAX_AUTH_SIZE
mdefine_line|#define RPC_MAX_AUTH_SIZE (400)
multiline_comment|/* Work around the lack of a VFS credential */
DECL|struct|auth_cred
r_struct
id|auth_cred
(brace
DECL|member|uid
id|uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|gid_t
id|gid
suffix:semicolon
DECL|member|group_info
r_struct
id|group_info
op_star
id|group_info
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Client user credentials&n; */
DECL|struct|rpc_cred
r_struct
id|rpc_cred
(brace
DECL|member|cr_hash
r_struct
id|hlist_node
id|cr_hash
suffix:semicolon
multiline_comment|/* hash chain */
DECL|member|cr_ops
r_struct
id|rpc_credops
op_star
id|cr_ops
suffix:semicolon
DECL|member|cr_expire
r_int
r_int
id|cr_expire
suffix:semicolon
multiline_comment|/* when to gc */
DECL|member|cr_count
id|atomic_t
id|cr_count
suffix:semicolon
multiline_comment|/* ref count */
DECL|member|cr_flags
r_int
r_int
id|cr_flags
suffix:semicolon
multiline_comment|/* various flags */
macro_line|#ifdef RPC_DEBUG
DECL|member|cr_magic
r_int
r_int
id|cr_magic
suffix:semicolon
multiline_comment|/* 0x0f4aa4f0 */
macro_line|#endif
DECL|member|cr_uid
id|uid_t
id|cr_uid
suffix:semicolon
multiline_comment|/* per-flavor data */
)brace
suffix:semicolon
DECL|macro|RPCAUTH_CRED_LOCKED
mdefine_line|#define RPCAUTH_CRED_LOCKED&t;0x0001
DECL|macro|RPCAUTH_CRED_UPTODATE
mdefine_line|#define RPCAUTH_CRED_UPTODATE&t;0x0002
DECL|macro|RPCAUTH_CRED_MAGIC
mdefine_line|#define RPCAUTH_CRED_MAGIC&t;0x0f4aa4f0
multiline_comment|/*&n; * Client authentication handle&n; */
DECL|macro|RPC_CREDCACHE_NR
mdefine_line|#define RPC_CREDCACHE_NR&t;8
DECL|macro|RPC_CREDCACHE_MASK
mdefine_line|#define RPC_CREDCACHE_MASK&t;(RPC_CREDCACHE_NR - 1)
DECL|struct|rpc_cred_cache
r_struct
id|rpc_cred_cache
(brace
DECL|member|hashtable
r_struct
id|hlist_head
id|hashtable
(braket
id|RPC_CREDCACHE_NR
)braket
suffix:semicolon
DECL|member|nextgc
r_int
r_int
id|nextgc
suffix:semicolon
multiline_comment|/* next garbage collection */
DECL|member|expire
r_int
r_int
id|expire
suffix:semicolon
multiline_comment|/* cache expiry interval */
)brace
suffix:semicolon
DECL|struct|rpc_auth
r_struct
id|rpc_auth
(brace
DECL|member|au_cslack
r_int
r_int
id|au_cslack
suffix:semicolon
multiline_comment|/* call cred size estimate */
DECL|member|au_rslack
r_int
r_int
id|au_rslack
suffix:semicolon
multiline_comment|/* reply verf size guess */
DECL|member|au_flags
r_int
r_int
id|au_flags
suffix:semicolon
multiline_comment|/* various flags */
DECL|member|au_ops
r_struct
id|rpc_authops
op_star
id|au_ops
suffix:semicolon
multiline_comment|/* operations */
DECL|member|au_flavor
id|rpc_authflavor_t
id|au_flavor
suffix:semicolon
multiline_comment|/* pseudoflavor (note may&n;&t;&t;&t;&t;&t;&t; * differ from the flavor in&n;&t;&t;&t;&t;&t;&t; * au_ops-&gt;au_flavor in gss&n;&t;&t;&t;&t;&t;&t; * case) */
DECL|member|au_count
id|atomic_t
id|au_count
suffix:semicolon
multiline_comment|/* Reference counter */
DECL|member|au_credcache
r_struct
id|rpc_cred_cache
op_star
id|au_credcache
suffix:semicolon
multiline_comment|/* per-flavor data */
)brace
suffix:semicolon
DECL|macro|RPC_AUTH_PROC_CREDS
mdefine_line|#define RPC_AUTH_PROC_CREDS&t;0x0010&t;&t;/* process creds (including&n;&t;&t;&t;&t;&t;&t; * uid/gid, fs[ug]id, gids)&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * Client authentication ops&n; */
DECL|struct|rpc_authops
r_struct
id|rpc_authops
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|au_flavor
id|rpc_authflavor_t
id|au_flavor
suffix:semicolon
multiline_comment|/* flavor (RPC_AUTH_*) */
macro_line|#ifdef RPC_DEBUG
DECL|member|au_name
r_char
op_star
id|au_name
suffix:semicolon
macro_line|#endif
DECL|member|create
r_struct
id|rpc_auth
op_star
(paren
op_star
id|create
)paren
(paren
r_struct
id|rpc_clnt
op_star
comma
id|rpc_authflavor_t
)paren
suffix:semicolon
DECL|member|destroy
r_void
(paren
op_star
id|destroy
)paren
(paren
r_struct
id|rpc_auth
op_star
)paren
suffix:semicolon
DECL|member|lookup_cred
r_struct
id|rpc_cred
op_star
(paren
op_star
id|lookup_cred
)paren
(paren
r_struct
id|rpc_auth
op_star
comma
r_struct
id|auth_cred
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|crcreate
r_struct
id|rpc_cred
op_star
(paren
op_star
id|crcreate
)paren
(paren
r_struct
id|rpc_auth
op_star
comma
r_struct
id|auth_cred
op_star
comma
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rpc_credops
r_struct
id|rpc_credops
(brace
DECL|member|cr_name
r_const
r_char
op_star
id|cr_name
suffix:semicolon
multiline_comment|/* Name of the auth flavour */
DECL|member|crdestroy
r_void
(paren
op_star
id|crdestroy
)paren
(paren
r_struct
id|rpc_cred
op_star
)paren
suffix:semicolon
DECL|member|crmatch
r_int
(paren
op_star
id|crmatch
)paren
(paren
r_struct
id|auth_cred
op_star
comma
r_struct
id|rpc_cred
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|crmarshal
id|u32
op_star
(paren
op_star
id|crmarshal
)paren
(paren
r_struct
id|rpc_task
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
DECL|member|crrefresh
r_int
(paren
op_star
id|crrefresh
)paren
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
DECL|member|crvalidate
id|u32
op_star
(paren
op_star
id|crvalidate
)paren
(paren
r_struct
id|rpc_task
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
DECL|member|crwrap_req
r_int
(paren
op_star
id|crwrap_req
)paren
(paren
r_struct
id|rpc_task
op_star
comma
id|kxdrproc_t
comma
r_void
op_star
comma
id|u32
op_star
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|crunwrap_resp
r_int
(paren
op_star
id|crunwrap_resp
)paren
(paren
r_struct
id|rpc_task
op_star
comma
id|kxdrproc_t
comma
r_void
op_star
comma
id|u32
op_star
comma
r_void
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|rpc_authops
id|authunix_ops
suffix:semicolon
r_extern
r_struct
id|rpc_authops
id|authnull_ops
suffix:semicolon
macro_line|#ifdef CONFIG_SUNRPC_SECURE
r_extern
r_struct
id|rpc_authops
id|authdes_ops
suffix:semicolon
macro_line|#endif
r_int
id|rpcauth_register
c_func
(paren
r_struct
id|rpc_authops
op_star
)paren
suffix:semicolon
r_int
id|rpcauth_unregister
c_func
(paren
r_struct
id|rpc_authops
op_star
)paren
suffix:semicolon
r_struct
id|rpc_auth
op_star
id|rpcauth_create
c_func
(paren
id|rpc_authflavor_t
comma
r_struct
id|rpc_clnt
op_star
)paren
suffix:semicolon
r_void
id|rpcauth_destroy
c_func
(paren
r_struct
id|rpc_auth
op_star
)paren
suffix:semicolon
r_struct
id|rpc_cred
op_star
id|rpcauth_lookup_credcache
c_func
(paren
r_struct
id|rpc_auth
op_star
comma
r_struct
id|auth_cred
op_star
comma
r_int
)paren
suffix:semicolon
r_struct
id|rpc_cred
op_star
id|rpcauth_lookupcred
c_func
(paren
r_struct
id|rpc_auth
op_star
comma
r_int
)paren
suffix:semicolon
r_struct
id|rpc_cred
op_star
id|rpcauth_bindcred
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|rpcauth_holdcred
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|put_rpccred
c_func
(paren
r_struct
id|rpc_cred
op_star
)paren
suffix:semicolon
r_void
id|rpcauth_unbindcred
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
id|u32
op_star
id|rpcauth_marshcred
c_func
(paren
r_struct
id|rpc_task
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
id|u32
op_star
id|rpcauth_checkverf
c_func
(paren
r_struct
id|rpc_task
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
r_int
id|rpcauth_wrap_req
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
comma
id|kxdrproc_t
id|encode
comma
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
r_int
id|rpcauth_unwrap_resp
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
comma
id|kxdrproc_t
id|decode
comma
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
r_int
id|rpcauth_refreshcred
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|rpcauth_invalcred
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_int
id|rpcauth_uptodatecred
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_int
id|rpcauth_init_credcache
c_func
(paren
r_struct
id|rpc_auth
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|rpcauth_free_credcache
c_func
(paren
r_struct
id|rpc_auth
op_star
)paren
suffix:semicolon
r_static
r_inline
DECL|function|get_rpccred
r_struct
id|rpc_cred
op_star
id|get_rpccred
c_func
(paren
r_struct
id|rpc_cred
op_star
id|cred
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|cred-&gt;cr_count
)paren
suffix:semicolon
r_return
id|cred
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SUNRPC_AUTH_H */
eof
