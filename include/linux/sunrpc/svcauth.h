multiline_comment|/*&n; * linux/include/linux/sunrpc/svcauth.h&n; *&n; * RPC server-side authentication stuff.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef _LINUX_SUNRPC_SVCAUTH_H_
DECL|macro|_LINUX_SUNRPC_SVCAUTH_H_
mdefine_line|#define _LINUX_SUNRPC_SVCAUTH_H_
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sunrpc/msg_prot.h&gt;
macro_line|#include &lt;linux/sunrpc/cache.h&gt;
macro_line|#include &lt;linux/hash.h&gt;
DECL|struct|svc_cred
r_struct
id|svc_cred
(brace
DECL|member|cr_uid
id|uid_t
id|cr_uid
suffix:semicolon
DECL|member|cr_gid
id|gid_t
id|cr_gid
suffix:semicolon
DECL|member|cr_groups
id|gid_t
id|cr_groups
(braket
id|NGROUPS
)braket
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|svc_rqst
suffix:semicolon
multiline_comment|/* forward decl */
multiline_comment|/* Authentication is done in the context of a domain.&n; * For a server, a domain represents a group of clients using&n; * a common mechanism for authentication and having a common mapping&n; * between local identity (uid) and network identity.  All clients&n; * in a domain have similar general access rights.  Each domain can&n; * contain multiple principals which will have different specific right&n; * based on normal Discretionary Access Control.&n; *&n; * For a client, a domain represents a number of servers which all&n; * use a common authentication mechanism and network identity name space.&n; *&n; * A domain is created by an authentication flavour module based on name&n; * only.  Userspace then fills in detail on demand.&n; *&n; * The creation of a domain typically implies creation of one or&n; * more caches for storing domain specific information.&n; */
DECL|struct|auth_domain
r_struct
id|auth_domain
(brace
DECL|member|h
r_struct
id|cache_head
id|h
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|flavour
r_int
id|flavour
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Each authentication flavour registers an auth_ops&n; * structure.&n; * name is simply the name.&n; * flavour gives the auth flavour. It determines where the flavour is registered&n; * accept() is given a request and should verify it.&n; *   It should inspect the authenticator and verifier, and possibly the data.&n; *    If there is a problem with the authentication *authp should be set.&n; *    The return value of accept() can indicate:&n; *      OK - authorised. client and credential are set in rqstp.&n; *           reqbuf points to arguments&n; *           resbuf points to good place for results.  verfier&n; *             is (probably) already in place.  Certainly space is&n; *&t;       reserved for it.&n; *      DROP - simply drop the request. It may have been deferred&n; *      GARBAGE - rpc garbage_args error&n; *      SYSERR - rpc system_err error&n; *      DENIED - authp holds reason for denial.&n; *&n; *   accept is passed the proc number so that it can accept NULL rpc requests&n; *   even if it cannot authenticate the client (as is sometimes appropriate).&n; *&n; * release() is given a request after the procedure has been run.&n; *  It should sign/encrypt the results if needed&n; * It should return:&n; *    OK - the resbuf is ready to be sent&n; *    DROP - the reply should be quitely dropped&n; *    DENIED - authp holds a reason for MSG_DENIED&n; *    SYSERR - rpc system_err&n; *&n; * domain_release()&n; *   This call releases a domain.&n; */
DECL|struct|auth_ops
r_struct
id|auth_ops
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|flavour
r_int
id|flavour
suffix:semicolon
DECL|member|accept
r_int
(paren
op_star
id|accept
)paren
(paren
r_struct
id|svc_rqst
op_star
id|rq
comma
id|u32
op_star
id|authp
)paren
suffix:semicolon
DECL|member|release
r_int
(paren
op_star
id|release
)paren
(paren
r_struct
id|svc_rqst
op_star
id|rq
)paren
suffix:semicolon
DECL|member|domain_release
r_void
(paren
op_star
id|domain_release
)paren
(paren
r_struct
id|auth_domain
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|auth_ops
op_star
id|authtab
(braket
id|RPC_AUTH_MAXFLAVOR
)braket
suffix:semicolon
DECL|macro|SVC_GARBAGE
mdefine_line|#define&t;SVC_GARBAGE&t;1
DECL|macro|SVC_SYSERR
mdefine_line|#define&t;SVC_SYSERR&t;2
DECL|macro|SVC_VALID
mdefine_line|#define&t;SVC_VALID&t;3
DECL|macro|SVC_NEGATIVE
mdefine_line|#define&t;SVC_NEGATIVE&t;4
DECL|macro|SVC_OK
mdefine_line|#define&t;SVC_OK&t;&t;5
DECL|macro|SVC_DROP
mdefine_line|#define&t;SVC_DROP&t;6
DECL|macro|SVC_DENIED
mdefine_line|#define&t;SVC_DENIED&t;7
DECL|macro|SVC_PENDING
mdefine_line|#define&t;SVC_PENDING&t;8
r_extern
r_int
id|svc_authenticate
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
suffix:semicolon
r_extern
r_int
id|svc_authorise
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
)paren
suffix:semicolon
r_extern
r_int
id|svc_auth_register
c_func
(paren
id|rpc_authflavor_t
id|flavor
comma
r_struct
id|auth_ops
op_star
id|aops
)paren
suffix:semicolon
r_extern
r_void
id|svc_auth_unregister
c_func
(paren
id|rpc_authflavor_t
id|flavor
)paren
suffix:semicolon
r_extern
r_struct
id|auth_domain
op_star
id|unix_domain_find
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|auth_domain_put
c_func
(paren
r_struct
id|auth_domain
op_star
id|item
)paren
suffix:semicolon
r_extern
r_int
id|auth_unix_add_addr
c_func
(paren
r_struct
id|in_addr
id|addr
comma
r_struct
id|auth_domain
op_star
id|dom
)paren
suffix:semicolon
r_extern
r_struct
id|auth_domain
op_star
id|auth_domain_lookup
c_func
(paren
r_struct
id|auth_domain
op_star
id|item
comma
r_int
id|set
)paren
suffix:semicolon
r_extern
r_struct
id|auth_domain
op_star
id|auth_domain_find
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_struct
id|auth_domain
op_star
id|auth_unix_lookup
c_func
(paren
r_struct
id|in_addr
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|auth_unix_forget_old
c_func
(paren
r_struct
id|auth_domain
op_star
id|dom
)paren
suffix:semicolon
r_extern
r_void
id|svcauth_unix_purge
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|hash_str
r_static
r_inline
r_int
r_int
id|hash_str
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|bits
)paren
(brace
r_int
r_int
id|hash
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|l
op_assign
l_int|0
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
(paren
id|c
op_assign
op_star
id|name
op_increment
)paren
)paren
)paren
(brace
id|c
op_assign
(paren
r_char
)paren
id|len
suffix:semicolon
id|len
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|l
op_assign
(paren
id|l
op_lshift
l_int|8
)paren
op_or
id|c
suffix:semicolon
id|len
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_amp
(paren
id|BITS_PER_LONG
op_div
l_int|8
op_minus
l_int|1
)paren
)paren
op_eq
l_int|0
)paren
id|hash
op_assign
id|hash_long
c_func
(paren
id|hash
op_xor
id|l
comma
id|BITS_PER_LONG
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
)paren
suffix:semicolon
r_return
id|hash
op_rshift
(paren
id|BITS_PER_LONG
op_minus
id|bits
)paren
suffix:semicolon
)brace
DECL|function|hash_mem
r_static
r_inline
r_int
r_int
id|hash_mem
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|length
comma
r_int
id|bits
)paren
(brace
r_int
r_int
id|hash
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|l
op_assign
l_int|0
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|len
op_eq
id|length
)paren
(brace
id|c
op_assign
(paren
r_char
)paren
id|len
suffix:semicolon
id|len
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
id|c
op_assign
op_star
id|buf
op_increment
suffix:semicolon
id|l
op_assign
(paren
id|l
op_lshift
l_int|8
)paren
op_or
id|c
suffix:semicolon
id|len
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_amp
(paren
id|BITS_PER_LONG
op_div
l_int|8
op_minus
l_int|1
)paren
)paren
op_eq
l_int|0
)paren
id|hash
op_assign
id|hash_long
c_func
(paren
id|hash
op_xor
id|l
comma
id|BITS_PER_LONG
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
)paren
suffix:semicolon
r_return
id|hash
op_rshift
(paren
id|BITS_PER_LONG
op_minus
id|bits
)paren
suffix:semicolon
)brace
r_extern
r_struct
id|cache_detail
id|auth_domain_cache
comma
id|ip_map_cache
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SUNRPC_SVCAUTH_H_ */
eof
