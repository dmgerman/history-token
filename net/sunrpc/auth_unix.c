multiline_comment|/*&n; * linux/net/sunrpc/auth_unix.c&n; *&n; * UNIX-style authentication; no AUTH_SHORT support&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/auth.h&gt;
DECL|macro|NFS_NGROUPS
mdefine_line|#define NFS_NGROUPS&t;16
DECL|struct|unx_cred
r_struct
id|unx_cred
(brace
DECL|member|uc_base
r_struct
id|rpc_cred
id|uc_base
suffix:semicolon
DECL|member|uc_gid
id|gid_t
id|uc_gid
suffix:semicolon
DECL|member|uc_puid
id|uid_t
id|uc_puid
suffix:semicolon
multiline_comment|/* process uid */
DECL|member|uc_pgid
id|gid_t
id|uc_pgid
suffix:semicolon
multiline_comment|/* process gid */
DECL|member|uc_gids
id|gid_t
id|uc_gids
(braket
id|NFS_NGROUPS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|uc_uid
mdefine_line|#define uc_uid&t;&t;&t;uc_base.cr_uid
DECL|macro|uc_count
mdefine_line|#define uc_count&t;&t;uc_base.cr_count
DECL|macro|uc_flags
mdefine_line|#define uc_flags&t;&t;uc_base.cr_flags
DECL|macro|uc_expire
mdefine_line|#define uc_expire&t;&t;uc_base.cr_expire
DECL|macro|UNX_CRED_EXPIRE
mdefine_line|#define UNX_CRED_EXPIRE&t;&t;(60 * HZ)
DECL|macro|UNX_WRITESLACK
mdefine_line|#define UNX_WRITESLACK&t;&t;(21 + (UNX_MAXNODENAME &gt;&gt; 2))
macro_line|#ifdef RPC_DEBUG
DECL|macro|RPCDBG_FACILITY
macro_line|# define RPCDBG_FACILITY&t;RPCDBG_AUTH
macro_line|#endif
DECL|variable|unix_auth
r_static
r_struct
id|rpc_auth
id|unix_auth
suffix:semicolon
DECL|variable|unix_cred_cache
r_static
r_struct
id|rpc_cred_cache
id|unix_cred_cache
suffix:semicolon
DECL|variable|unix_credops
r_static
r_struct
id|rpc_credops
id|unix_credops
suffix:semicolon
r_static
r_struct
id|rpc_auth
op_star
DECL|function|unx_create
id|unx_create
c_func
(paren
r_struct
id|rpc_clnt
op_star
id|clnt
comma
id|rpc_authflavor_t
id|flavor
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: creating UNIX authenticator for client %p&bslash;n&quot;
comma
id|clnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_inc_return
c_func
(paren
op_amp
id|unix_auth.au_count
)paren
op_eq
l_int|0
)paren
id|unix_cred_cache.nextgc
op_assign
id|jiffies
op_plus
(paren
id|unix_cred_cache.expire
op_rshift
l_int|1
)paren
suffix:semicolon
r_return
op_amp
id|unix_auth
suffix:semicolon
)brace
r_static
r_void
DECL|function|unx_destroy
id|unx_destroy
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
l_string|&quot;RPC: destroying UNIX authenticator %p&bslash;n&quot;
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
)brace
multiline_comment|/*&n; * Lookup AUTH_UNIX creds for current process&n; */
r_static
r_struct
id|rpc_cred
op_star
DECL|function|unx_lookup_cred
id|unx_lookup_cred
c_func
(paren
r_struct
id|rpc_auth
op_star
id|auth
comma
r_struct
id|auth_cred
op_star
id|acred
comma
r_int
id|flags
)paren
(brace
r_return
id|rpcauth_lookup_credcache
c_func
(paren
id|auth
comma
id|acred
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_struct
id|rpc_cred
op_star
DECL|function|unx_create_cred
id|unx_create_cred
c_func
(paren
r_struct
id|rpc_auth
op_star
id|auth
comma
r_struct
id|auth_cred
op_star
id|acred
comma
r_int
id|flags
)paren
(brace
r_struct
id|unx_cred
op_star
id|cred
suffix:semicolon
r_int
id|i
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      allocating UNIX cred for uid %d gid %d&bslash;n&quot;
comma
id|acred-&gt;uid
comma
id|acred-&gt;gid
)paren
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
id|unx_cred
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
id|cred-&gt;uc_count
comma
l_int|1
)paren
suffix:semicolon
id|cred-&gt;uc_flags
op_assign
id|RPCAUTH_CRED_UPTODATE
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|RPC_TASK_ROOTCREDS
)paren
(brace
id|cred-&gt;uc_uid
op_assign
id|cred-&gt;uc_puid
op_assign
l_int|0
suffix:semicolon
id|cred-&gt;uc_gid
op_assign
id|cred-&gt;uc_pgid
op_assign
l_int|0
suffix:semicolon
id|cred-&gt;uc_gids
(braket
l_int|0
)braket
op_assign
id|NOGROUP
suffix:semicolon
)brace
r_else
(brace
r_int
id|groups
op_assign
id|acred-&gt;group_info-&gt;ngroups
suffix:semicolon
r_if
c_cond
(paren
id|groups
OG
id|NFS_NGROUPS
)paren
id|groups
op_assign
id|NFS_NGROUPS
suffix:semicolon
id|cred-&gt;uc_uid
op_assign
id|acred-&gt;uid
suffix:semicolon
id|cred-&gt;uc_gid
op_assign
id|acred-&gt;gid
suffix:semicolon
id|cred-&gt;uc_puid
op_assign
id|current-&gt;uid
suffix:semicolon
id|cred-&gt;uc_pgid
op_assign
id|current-&gt;gid
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
id|groups
suffix:semicolon
id|i
op_increment
)paren
id|cred-&gt;uc_gids
(braket
id|i
)braket
op_assign
id|GROUP_AT
c_func
(paren
id|acred-&gt;group_info
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|NFS_NGROUPS
)paren
id|cred-&gt;uc_gids
(braket
id|i
)braket
op_assign
id|NOGROUP
suffix:semicolon
)brace
id|cred-&gt;uc_base.cr_ops
op_assign
op_amp
id|unix_credops
suffix:semicolon
r_return
(paren
r_struct
id|rpc_cred
op_star
)paren
id|cred
suffix:semicolon
)brace
r_static
r_void
DECL|function|unx_destroy_cred
id|unx_destroy_cred
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
multiline_comment|/*&n; * Match credentials against current process creds.&n; * The root_override argument takes care of cases where the caller may&n; * request root creds (e.g. for NFS swapping).&n; */
r_static
r_int
DECL|function|unx_match
id|unx_match
c_func
(paren
r_struct
id|auth_cred
op_star
id|acred
comma
r_struct
id|rpc_cred
op_star
id|rcred
comma
r_int
id|taskflags
)paren
(brace
r_struct
id|unx_cred
op_star
id|cred
op_assign
(paren
r_struct
id|unx_cred
op_star
)paren
id|rcred
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|taskflags
op_amp
id|RPC_TASK_ROOTCREDS
)paren
)paren
(brace
r_int
id|groups
suffix:semicolon
r_if
c_cond
(paren
id|cred-&gt;uc_uid
op_ne
id|acred-&gt;uid
op_logical_or
id|cred-&gt;uc_gid
op_ne
id|acred-&gt;gid
op_logical_or
id|cred-&gt;uc_puid
op_ne
id|current-&gt;uid
op_logical_or
id|cred-&gt;uc_pgid
op_ne
id|current-&gt;gid
)paren
r_return
l_int|0
suffix:semicolon
id|groups
op_assign
id|acred-&gt;group_info-&gt;ngroups
suffix:semicolon
r_if
c_cond
(paren
id|groups
OG
id|NFS_NGROUPS
)paren
id|groups
op_assign
id|NFS_NGROUPS
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
id|groups
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|cred-&gt;uc_gids
(braket
id|i
)braket
op_ne
id|GROUP_AT
c_func
(paren
id|acred-&gt;group_info
comma
id|i
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
(paren
id|cred-&gt;uc_uid
op_eq
l_int|0
op_logical_and
id|cred-&gt;uc_puid
op_eq
l_int|0
op_logical_and
id|cred-&gt;uc_gid
op_eq
l_int|0
op_logical_and
id|cred-&gt;uc_pgid
op_eq
l_int|0
op_logical_and
id|cred-&gt;uc_gids
(braket
l_int|0
)braket
op_eq
(paren
id|gid_t
)paren
id|NOGROUP
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Marshal credentials.&n; * Maybe we should keep a cached credential for performance reasons.&n; */
r_static
id|u32
op_star
DECL|function|unx_marshal
id|unx_marshal
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
r_struct
id|rpc_clnt
op_star
id|clnt
op_assign
id|task-&gt;tk_client
suffix:semicolon
r_struct
id|unx_cred
op_star
id|cred
op_assign
(paren
r_struct
id|unx_cred
op_star
)paren
id|task-&gt;tk_msg.rpc_cred
suffix:semicolon
id|u32
op_star
id|base
comma
op_star
id|hold
suffix:semicolon
r_int
id|i
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|RPC_AUTH_UNIX
)paren
suffix:semicolon
id|base
op_assign
id|p
op_increment
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|jiffies
op_div
id|HZ
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Copy the UTS nodename captured when the client was created.&n;&t; */
id|p
op_assign
id|xdr_encode_array
c_func
(paren
id|p
comma
id|clnt-&gt;cl_nodename
comma
id|clnt-&gt;cl_nodelen
)paren
suffix:semicolon
multiline_comment|/* Note: we don&squot;t use real uid if it involves raising privilege */
r_if
c_cond
(paren
id|ruid
op_logical_and
id|cred-&gt;uc_puid
op_ne
l_int|0
op_logical_and
id|cred-&gt;uc_pgid
op_ne
l_int|0
)paren
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|cred-&gt;uc_puid
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|cred-&gt;uc_pgid
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|cred-&gt;uc_uid
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|cred-&gt;uc_gid
)paren
suffix:semicolon
)brace
id|hold
op_assign
id|p
op_increment
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
l_int|16
op_logical_and
id|cred-&gt;uc_gids
(braket
id|i
)braket
op_ne
(paren
id|gid_t
)paren
id|NOGROUP
suffix:semicolon
id|i
op_increment
)paren
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|cred-&gt;uc_gids
(braket
id|i
)braket
)paren
suffix:semicolon
op_star
id|hold
op_assign
id|htonl
c_func
(paren
id|p
op_minus
id|hold
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* gid array length */
op_star
id|base
op_assign
id|htonl
c_func
(paren
(paren
id|p
op_minus
id|base
op_minus
l_int|1
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/* cred length */
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
id|htonl
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * Refresh credentials. This is a no-op for AUTH_UNIX&n; */
r_static
r_int
DECL|function|unx_refresh
id|unx_refresh
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
id|task-&gt;tk_msg.rpc_cred-&gt;cr_flags
op_or_assign
id|RPCAUTH_CRED_UPTODATE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|u32
op_star
DECL|function|unx_validate
id|unx_validate
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
op_logical_and
id|flavor
op_ne
id|RPC_AUTH_UNIX
op_logical_and
id|flavor
op_ne
id|RPC_AUTH_SHORT
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
OG
id|RPC_MAX_AUTH_SIZE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RPC: giant verf size: %u&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|task-&gt;tk_auth-&gt;au_rslack
op_assign
(paren
id|size
op_rshift
l_int|2
)paren
op_plus
l_int|2
suffix:semicolon
id|p
op_add_assign
(paren
id|size
op_rshift
l_int|2
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|variable|authunix_ops
r_struct
id|rpc_authops
id|authunix_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|au_flavor
op_assign
id|RPC_AUTH_UNIX
comma
macro_line|#ifdef RPC_DEBUG
dot
id|au_name
op_assign
l_string|&quot;UNIX&quot;
comma
macro_line|#endif
dot
id|create
op_assign
id|unx_create
comma
dot
id|destroy
op_assign
id|unx_destroy
comma
dot
id|lookup_cred
op_assign
id|unx_lookup_cred
comma
dot
id|crcreate
op_assign
id|unx_create_cred
comma
)brace
suffix:semicolon
r_static
DECL|variable|unix_cred_cache
r_struct
id|rpc_cred_cache
id|unix_cred_cache
op_assign
(brace
dot
id|expire
op_assign
id|UNX_CRED_EXPIRE
comma
)brace
suffix:semicolon
r_static
DECL|variable|unix_auth
r_struct
id|rpc_auth
id|unix_auth
op_assign
(brace
dot
id|au_cslack
op_assign
id|UNX_WRITESLACK
comma
dot
id|au_rslack
op_assign
l_int|2
comma
multiline_comment|/* assume AUTH_NULL verf */
dot
id|au_ops
op_assign
op_amp
id|authunix_ops
comma
dot
id|au_count
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
comma
dot
id|au_credcache
op_assign
op_amp
id|unix_cred_cache
comma
)brace
suffix:semicolon
r_static
DECL|variable|unix_credops
r_struct
id|rpc_credops
id|unix_credops
op_assign
(brace
dot
id|cr_name
op_assign
l_string|&quot;AUTH_UNIX&quot;
comma
dot
id|crdestroy
op_assign
id|unx_destroy_cred
comma
dot
id|crmatch
op_assign
id|unx_match
comma
dot
id|crmarshal
op_assign
id|unx_marshal
comma
dot
id|crrefresh
op_assign
id|unx_refresh
comma
dot
id|crvalidate
op_assign
id|unx_validate
comma
)brace
suffix:semicolon
eof
