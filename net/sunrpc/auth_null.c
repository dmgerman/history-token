multiline_comment|/*&n; * linux/net/sunrpc/auth_null.c&n; *&n; * AUTH_NULL authentication. Really :-)&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#ifdef RPC_DEBUG
DECL|macro|RPCDBG_FACILITY
macro_line|# define RPCDBG_FACILITY&t;RPCDBG_AUTH
macro_line|#endif
DECL|variable|null_credops
r_static
r_struct
id|rpc_credops
id|null_credops
suffix:semicolon
r_static
r_struct
id|rpc_auth
op_star
DECL|function|nul_create
id|nul_create
c_func
(paren
r_struct
id|rpc_clnt
op_star
id|clnt
)paren
(brace
r_struct
id|rpc_auth
op_star
id|auth
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: creating NULL authenticator for client %p&bslash;n&quot;
comma
id|clnt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|auth
op_assign
(paren
r_struct
id|rpc_auth
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|auth
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|auth-&gt;au_cslack
op_assign
l_int|4
suffix:semicolon
id|auth-&gt;au_rslack
op_assign
l_int|2
suffix:semicolon
id|auth-&gt;au_ops
op_assign
op_amp
id|authnull_ops
suffix:semicolon
id|auth-&gt;au_expire
op_assign
l_int|1800
op_star
id|HZ
suffix:semicolon
id|rpcauth_init_credcache
c_func
(paren
id|auth
)paren
suffix:semicolon
r_return
(paren
r_struct
id|rpc_auth
op_star
)paren
id|auth
suffix:semicolon
)brace
r_static
r_void
DECL|function|nul_destroy
id|nul_destroy
c_func
(paren
r_struct
id|rpc_auth
op_star
id|auth
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: destroying NULL authenticator %p&bslash;n&quot;
comma
id|auth
)paren
suffix:semicolon
id|rpcauth_free_credcache
c_func
(paren
id|auth
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|auth
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create NULL creds for current process&n; */
r_static
r_struct
id|rpc_cred
op_star
DECL|function|nul_create_cred
id|nul_create_cred
c_func
(paren
r_int
id|flags
)paren
(brace
r_struct
id|rpc_cred
op_star
id|cred
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cred
op_assign
(paren
r_struct
id|rpc_cred
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|cred
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|cred-&gt;cr_count
comma
l_int|0
)paren
suffix:semicolon
id|cred-&gt;cr_flags
op_assign
id|RPCAUTH_CRED_UPTODATE
suffix:semicolon
id|cred-&gt;cr_uid
op_assign
id|current-&gt;uid
suffix:semicolon
id|cred-&gt;cr_ops
op_assign
op_amp
id|null_credops
suffix:semicolon
r_return
id|cred
suffix:semicolon
)brace
multiline_comment|/*&n; * Destroy cred handle.&n; */
r_static
r_void
DECL|function|nul_destroy_cred
id|nul_destroy_cred
c_func
(paren
r_struct
id|rpc_cred
op_star
id|cred
)paren
(brace
id|kfree
c_func
(paren
id|cred
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Match cred handle against current process&n; */
r_static
r_int
DECL|function|nul_match
id|nul_match
c_func
(paren
r_struct
id|rpc_cred
op_star
id|cred
comma
r_int
id|taskflags
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Marshal credential.&n; */
r_static
id|u32
op_star
DECL|function|nul_marshal
id|nul_marshal
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
comma
id|u32
op_star
id|p
comma
r_int
id|ruid
)paren
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|RPC_AUTH_NULL
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|RPC_AUTH_NULL
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * Refresh credential. This is a no-op for AUTH_NULL&n; */
r_static
r_int
DECL|function|nul_refresh
id|nul_refresh
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
r_return
id|task-&gt;tk_status
op_assign
op_minus
id|EACCES
suffix:semicolon
)brace
r_static
id|u32
op_star
DECL|function|nul_validate
id|nul_validate
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
comma
id|u32
op_star
id|p
)paren
(brace
id|rpc_authflavor_t
id|flavor
suffix:semicolon
id|u32
id|size
suffix:semicolon
id|flavor
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
id|flavor
op_ne
id|RPC_AUTH_NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RPC: bad verf flavor: %u&bslash;n&quot;
comma
id|flavor
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|size
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
id|size
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RPC: bad verf size: %u&bslash;n&quot;
comma
id|size
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
DECL|variable|authnull_ops
r_struct
id|rpc_authops
id|authnull_ops
op_assign
(brace
dot
id|au_flavor
op_assign
id|RPC_AUTH_NULL
comma
macro_line|#ifdef RPC_DEBUG
dot
id|au_name
op_assign
l_string|&quot;NULL&quot;
comma
macro_line|#endif
dot
id|create
op_assign
id|nul_create
comma
dot
id|destroy
op_assign
id|nul_destroy
comma
dot
id|crcreate
op_assign
id|nul_create_cred
comma
)brace
suffix:semicolon
r_static
DECL|variable|null_credops
r_struct
id|rpc_credops
id|null_credops
op_assign
(brace
dot
id|crdestroy
op_assign
id|nul_destroy_cred
comma
dot
id|crmatch
op_assign
id|nul_match
comma
dot
id|crmarshal
op_assign
id|nul_marshal
comma
dot
id|crrefresh
op_assign
id|nul_refresh
comma
dot
id|crvalidate
op_assign
id|nul_validate
comma
)brace
suffix:semicolon
eof
